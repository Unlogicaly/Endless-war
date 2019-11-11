#include "editting_files.h"
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
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

void print(vector<vector<string>> &vec)
{
    for (auto &t: vec)
    {
        for (auto &s: t){
            std::cout << s << "\t\t";
        }
        std::cout << std::endl;
    }
}

double heuristic(Field *f1, Field *f2)
{
    return sqrt(pow(f1->get_name()[0] - f2->get_name()[0], 2) +
                pow(f1->get_name()[1] - f2->get_name()[1], 2));
}

#define d double

d dist(d x1, d y1, d x2, d y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

#define point pair<int, int>
#define feuture pair<double, double>

template<typename T>
T &at(vector<vector<T>> &src, point &sub) {
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

//vector<string> A_star(const Map &m, const Field &start, const Field &end)
//{
//    auto matrix = Func::vector_2d(m.get_h(), m.get_w(), pair<double, double>{0, 0});

//    auto s_h = start.get_name()[0] - 'a', s_w = start.get_name()[1] - '1';

//    for (auto i = 0; i < matrix.size(); ++i) {
//        for (auto j = 0; j < matrix[0].size(); ++j) {
//            matrix[i][j].second = Func::round(dist(i, j, s_h, s_w), 2);
//        }
//    }

//    bool ended{false};

//    vector<point> av_nodes;
//    if (s_h != 0) av_nodes.push_back({s_h - 1, s_w});
//    if (s_w != 0) av_nodes.push_back({s_h, s_w - 1});
//    if (s_h != matrix.size() - 1) av_nodes.push_back({s_h + 1, s_w});
//    if (s_w != matrix[0].size() - 1) av_nodes.push_back({s_h, s_w + 1});
//    point prev =
//    while(!ended) {
//        point cur = av_nodes[0];
//        for (auto &t: av_nodes)
//            cur = std::min(at(matrix, cur), at(matrix, t), [](point p1, point p2) {
//                return p1.first + p1.second < p2.first + p2.second;
//            });
//        del(av_nodes, cur);
//        at(matrix, cur).first +=
//    }
//}

int main()
{

//    auto win = create_window("m");

    int size = 128;

    Map m{size, "D:\\My\\Source\\landscape.txt", "D:\\My\\Source\\terrain.txt", "D:\\My\\Source\\units.txt"};

//    m.get_field("b2")->print_land();
//    m.get_field("b2")->print_ter();
//    m.get_field("b2")->print_unit();

//    std::cout << m.get_field("b2")->get_weight();

//    win->attach(m);

//    win->wait_for_button();
//    vector<vector<pair<int, int>>> matrix;
//    for (auto i = 0; i < m.get_h(); ++i) {
//        matrix.emplace_back();
//        for (auto j = 0; j < m.get_w(); ++j) {
//            matrix[i].push_back({0, 0});
//        }
//    }
    A_star(m, *m.get_field("a1"), *m.get_field("b2"));

//    win->wait_for_button();

//    clear(*win);

    return 0;
}
