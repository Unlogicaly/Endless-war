#include <cstdio>
#include <iterator>
#include <windows.h>
#include "map.h"
#include "sstream"
#include "node.h"

using Graph_lib::Image;
using Graph_lib::Point;
using std::string;
using std::vector;
using std::string;
using std::pair;

const string source = "D:\\Endless_war\\source";

double heuristic(Field *f1, Field *f2)
{
    return 2 * sqrt(pow(f1->get_name()[0] - f2->get_name()[0], 2) +
                pow(f1->get_name()[1] - f2->get_name()[1], 2));
}

#define d double

d dist(d x1, d y1, d x2, d y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

#define point pair<int, int>
#define feature pair<double, double>
#define matr vector<vector<feature>>

template<typename T>
T &at(vector<vector<T>> &src, const point &sub) {
    return src[sub.first][sub.second];
}

template<typename T>
void del(vector<T> &src, T &sub) {
    for (auto i = 0; i < src.size(); ++i)
        if (src[i] == sub) {
            src.erase(src.begin() + i, src.begin() + i + 1);
            return;
        }
}

string pton(point p) {
    return string(1, char(p.first + 'a')) + Func::str(p.second + 1);
}

point ntop(string name) {
    return {name[0] - 'a', name[1] - '1'};
}

void re_add(matr &matrix, vector<point> &av_nodes, point cur, int h_m, int w_m) {
    int n = cur.first, m = cur.second;
    if (n and !Func::in(av_nodes, {n - 1, m}) and !at(matrix, {n - 1, m}).first) av_nodes.push_back({n - 1, m});
    if (m and !Func::in(av_nodes, {n, m - 1}) and !at(matrix, {n, m - 1}).first) av_nodes.push_back({n, m - 1});
    if (h_m - n - 1 and !Func::in(av_nodes, {n + 1, m}) and !at(matrix, {n + 1, m}).first) av_nodes.push_back({n + 1, m});
    if (w_m - m - 1 and !Func::in(av_nodes, {n, m + 1}) and !at(matrix, {n, m + 1}).first) av_nodes.push_back({n, m + 1});
}

void re_weight(feature &c, const feature &p, double w) {
    if (c.first)
        c.first = std::min(p.first + w + c.second,
                     c.first);
    else
        c.first = p.first + w + c.second;

}

vector<string> A_star(const Map &m, const Field &start, const Field &end)
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

    bool ended{false};

    vector<point> av_nodes;

    point prev = {s_h, s_w};

    re_add(matrix, av_nodes, prev, h_m, w_m);

    for (auto &t: av_nodes)
        re_weight(at(matrix, t), prev, m.get_field(pton(t))->get_weight());

    while(!ended) {
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

        std::cout << "current: " << cur << "\n";
        Func::print(av_nodes, " ", "\n\n");
        Func::print(matrix, " ", "\n", "\n\n");

        prev = cur;
//        Func::print(av_nodes);
    }
    std::cout << "\n\n";
    Func::print(matrix);

    return {};
}

int main()
{

    auto win = create_window("m");

    int size = 128;

    Map m{size, source + "\\landscape.txt", source + "\\terrain.txt", source + "\\units.txt"};

//    m.get_field("b2")->print_land();
//    m.get_field("b2")->print_ter();
//    m.get_field("b2")->print_unit();

//    std::cout << m.get_field("b2")->get_weight();

    win->attach(m);


//    vector<vector<pair<int, int>>> matrix;
//    for (auto i = 0; i < m.get_h(); ++i) {
//        matrix.emplace_back();
//        for (auto j = 0; j < m.get_w(); ++j) {
//            matrix[i].push_back({0, 0});
//        }
//    }

    A_star(m, *m.get_field("a1"), *m.get_field("b3"));

    win->wait_for_button();

//    clear(*win);

    return 0;
}
