#include "A_star.h"

using std::pair;
using std::string;
using std::vector;

#define d double
#define point std::pair<int, int>
#define feature std::pair<d, d>
#define matr std::vector<std::vector<feature>>

template<typename T>
T &at(std::vector<std::vector<T>> &src, const point &sub) {
    return src[sub.first][sub.second];
}

template<typename T>
void del(std::vector<T> &src, T &sub) {
    for (auto i = 0; i < src.size(); ++i)
        if (src[i] == sub) {
            src.erase(src.begin() + i, src.begin() + i + 1);
            return;
        }
}

double heuristic(Field *f1, Field *f2)
{
    return 2 * sqrt(pow(f1->get_name()[0] - f2->get_name()[0], 2) +
            pow(f1->get_name()[1] - f2->get_name()[1], 2));
}

d dist(d x1, d y1, d x2, d y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

std::string pton(std::pair<int, int> p) {
    return std::string(1, char(p.first + 'a')) + Func::str(p.second + 1);
}

pair<int, int> ntop(string name) {
    return {name[0] - 'a', name[1] - '1'};
}

void re_add(vector<vector<pair<d, d> > > &matrix, vector<pair<int, int> > &av_nodes, pair<int, int> cur, int h_m, int w_m) {
    int n = cur.first, m = cur.second;
    if (n and !Func::in(av_nodes, {n - 1, m}) and !at(matrix, {n - 1, m}).first) av_nodes.push_back({n - 1, m});
    if (m and !Func::in(av_nodes, {n, m - 1}) and !at(matrix, {n, m - 1}).first) av_nodes.push_back({n, m - 1});
    if (h_m - n - 1 and !Func::in(av_nodes, {n + 1, m}) and !at(matrix, {n + 1, m}).first) av_nodes.push_back({n + 1, m});
    if (w_m - m - 1 and !Func::in(av_nodes, {n, m + 1}) and !at(matrix, {n, m + 1}).first) av_nodes.push_back({n, m + 1});
}

void add_neighbours(vector<pair<int, int> > &av_nodes, pair<int, int> cur, int h_m, int w_m)
{
    av_nodes.clear();
    int n = cur.first, m = cur.second;
    if (n) av_nodes.push_back({n - 1, m});
    if (m) av_nodes.push_back({n, m - 1});
    if (h_m - n - 1) av_nodes.push_back({n + 1, m});
    if (w_m - m - 1) av_nodes.push_back({n, m + 1});
}

void re_weight(pair<d, d> &c, const pair<d, d> &p, d w) {
    if (c.first)
        c.first = std::min(p.first + w + c.second,
                           c.first);
    else
        c.first = p.first + w + c.second;

}

std::pair<int, vector<string> > A_star(const Map &m, const Field &start, const Field &end)
{
    auto h_m = m.get_h(), w_m = m.get_w();

    auto matrix = Func::matrix_2d(h_m, w_m, feature{0, 0});

    auto [s_h, s_w] = ntop(start.get_name());
            auto [e_h, e_w] = ntop(end.get_name());

            for (auto i = 0; i < h_m; ++i) {
        for (auto j = 0; j < w_m; ++j) {
            matrix[i][j].second = Func::round(dist(i, j, e_h, e_w), 2);
        }
    }

    matrix[s_h][s_w].first = matrix[s_h][s_w].second;

    vector<point> av_nodes;

    point prev = {s_h, s_w};

    re_add(matrix, av_nodes, prev, h_m, w_m);

    for (auto &t: av_nodes)
        re_weight(at(matrix, t), prev, m.get_field(pton(t))->get_weight());

    while(true) {
        point cur = av_nodes[0];
        for (auto &t: av_nodes)
            cur = std::min(cur, t, [&matrix](point p1, point p2) {
                    return at(matrix, p1).first < at(matrix, p2).first;
    });

        if (cur == ntop(end.get_name())) break;

        del(av_nodes, cur);

        re_add(matrix, av_nodes, cur, h_m, w_m);

        for (auto &t: av_nodes)
            re_weight(at(matrix, t), at(matrix, prev), m.get_field(pton(t))->get_weight());

        prev = cur;
    }

    vector<string> path{end.get_name()};
    av_nodes.clear();

    add_neighbours(av_nodes, ntop(path[0]), h_m, w_m);

    point cur;
    d weight = 0;

    while (true)
    {
        cur = av_nodes[0];
        for (auto &t: av_nodes)
            if (at(matrix, t).first)
                cur = std::min(cur, t, [&matrix](point p1, point p2) {
                        return at(matrix, p1).first < at(matrix, p2).first;
    });

        weight += m.get_field(pton(cur))->get_weight();
        path.insert(path.begin(), pton(cur));

        if (cur == point{s_h, s_w}) break;

        av_nodes.clear();

        add_neighbours(av_nodes, cur, h_m, w_m);
    }

    return {weight, path};
}
