#include "A_star.h"

using std::pair;
using std::string;
using std::vector;

#define d double
#define matr std::vector<std::vector<feature>>

template<typename T>
void del(std::vector<T> &src, T &sub) {
    for (ull i = 0; i < src.size(); ++i)
        if (src[i] == sub) {
            src.erase(src.begin() + i, src.begin() + i + 1);
            return;
        }
}

inline double heuristic(Field *f1, Field *f2)
{
    return 2 * sqrt(pow(f1->get_name()[0] - f2->get_name()[0], 2) +
            pow(f1->get_name()[1] - f2->get_name()[1], 2));
}

inline d dist(d x1, d y1, d x2, d y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void re_add(vector<vector<pair<d, d> > > &matrix, vector<point > &av_nodes, const point &cur, ull h_m, ull w_m) {
    auto n = cur.first, m = cur.second;
    if (n and !Func::in(av_nodes, {n - 1, m}) and !bool(at(matrix, {n - 1, m}).first)) av_nodes.push_back({n - 1, m});
    if (m and !Func::in(av_nodes, {n, m - 1}) and !bool(at(matrix, {n, m - 1}).first)) av_nodes.push_back({n, m - 1});
    if (h_m - n - 1 and !Func::in(av_nodes, {n + 1, m}) and !bool(at(matrix, {n + 1, m}).first)) av_nodes.push_back({n + 1, m});
    if (w_m - m - 1 and !Func::in(av_nodes, {n, m + 1}) and !bool(at(matrix, {n, m + 1}).first)) av_nodes.push_back({n, m + 1});
}

void add_neighbours(vector<point> &av_nodes, const point &cur, ull h_m, ull w_m)
{
    av_nodes.clear();
    auto n = cur.first, m = cur.second;
    if (n) av_nodes.push_back({n - 1, m});
    if (m) av_nodes.push_back({n, m - 1});
    if (h_m - n - 1) av_nodes.push_back({n + 1, m});
    if (w_m - m - 1) av_nodes.push_back({n, m + 1});
}

void re_weight(feature &c, const feature &p, d w)
{
    if (!c.first)
        c.first = p.first + w + c.second;
}

void filling(const Map &m, vector<vector<feature>> &matrix, const point &start, const point &end, ull x_max, ull y_max)
{
    at(matrix, start).first = at(matrix, start).second;

    vector<point> av_nodes;

    point prev = start;

    re_add(matrix, av_nodes, prev, y_max, x_max);

    for (auto &t: av_nodes)
        re_weight(at(matrix, t), prev, m.get_field(pton(t))->get_weight());

    while(true) {
        point cur = av_nodes[0];
        for (auto &t: av_nodes)
            cur = std::min(cur, t, [&matrix](point p1, point p2) {
                return at(matrix, p1).first < at(matrix, p2).first;
            });

        if (cur == end) break;

        del(av_nodes, cur);

        re_add(matrix, av_nodes, cur, y_max, x_max);

        for (auto &t: av_nodes)
            re_weight(at(matrix, t), at(matrix, prev), m.get_field(pton(t))->get_weight());

        prev = cur;
    }
}

d back(const Map &m, vector<vector<feature>> &matrix, vector<string> &path, const point &start, const point &end, ull x_max, ull y_max) {

    path.push_back(pton(end));

    vector<point> av_nodes;

    add_neighbours(av_nodes, ntop(path[0]), y_max, x_max);

    point cur;
    d weight = 0;

    while (true)
    {
        cur = {-1, 0};
        for (auto &t: av_nodes)
            if (bool(at(matrix, t).first)){
                if (cur.first == -1) {
                    cur = t;
                    continue;
                }
                cur = std::min(cur, t, [&matrix](point p1, point p2) {
                    return at(matrix, p1).first < at(matrix, p2).first;
                });
            }


        weight += m.get_field(pton(cur))->get_weight();
        path.insert(path.begin(), pton(cur));

        if (cur == start) break;

        av_nodes.clear();

        add_neighbours(av_nodes, cur, y_max, x_max);
    }
    return weight;
}

std::pair<int, vector<string>> A_star(const Map &m, const Field &start, const Field &end)
{
    if (start.get_name() == end.get_name())
        return {0, {start.get_name()}};

    auto y_max = m.get_h(), x_max = m.get_w();

    auto [y_start, x_start] = ntop(start.get_name());
    auto [y_end, x_end] = ntop(end.get_name());

    auto matrix = Func::matrix_2d(y_max, x_max, feature{0, 0});

    for (ull i = 0; i < y_max; ++i) {
        for (ull j = 0; j < x_max; ++j) {
            matrix[i][j].second = Func::round(dist(i, j, y_end, x_end), 2);
        }
    }

    filling(m, matrix, {y_start, x_start}, {y_end, x_end}, x_max, y_max);

    Func::print(matrix, "\t");

    vector<string> path;

    auto weight = back(m, matrix, path, {y_start, x_start}, {y_end, x_end}, x_max, y_max);

    return {weight, path};
}
