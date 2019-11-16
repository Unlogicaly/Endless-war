#include <cstdio>
#include <iterator>
#include <windows.h>
#include "A_star.h"
#include "sstream"
#include "node.h"

using Graph_lib::Image;
using Graph_lib::Point;
using std::string;
using std::vector;
using std::string;
using std::pair;

constexpr int size = 128;

template<typename T>
point operator * (point a, T x) {
    return {a.first * x, a.second * x};
}

inline point reverse(point p) {
    return {p.second, p.first};
}

void step(Graph_lib::Window *win, const Map &m, const string &start, const string &end) {
    auto [weight, path] = A_star(m, *m.get_field(start), *m.get_field(end));

    for (auto &p: path) {
        win->attach(*new Image{Point(reverse(ntop(p)) * size), get_pic(source+"Pic\\step.gif", size)});
    }
}

void av_fields(Graph_lib::Window *win, const Map &m, const string &start, int speed) {
    auto [y_start, x_start] = ntop(start);
    auto y_max = m.get_h(), x_max = m.get_w();

    auto top = y_start < speed ? 0 : y_start - speed;
    auto bottom = y_max - y_start <= speed ? y_max : y_start + speed + 1;

    auto left= x_start < speed ? 0 : x_start - speed;
    auto right = x_max - x_start <= speed ? x_max : x_start + speed + 1;

    for (auto i = top; i < bottom; ++i) {
        for (auto j = left; j < right; ++j) {
            std::cerr << __LINE__ << "\t\t" << pton({i, j}) << std::endl ;
            auto [weight, path] = A_star(m, *m.get_field(start), *m.get_field(pton({i, j})));
            if (weight <= speed) {
                win->attach(*new Image{Point(size * j, size * i), get_pic(source + "Pic\\step.gif", size)});
            }
        }

    }
}

int main()
{
    auto win = create_window("m");

    Map m{size, source + "\\landscape.txt", source + "\\terrain.txt", source + "\\units.txt"};

    win->attach(m);

//    auto [weight, path] = A_star(m, *m.get_field("a1"), *m.get_field("e7"));

//    std::cout << weight << std::endl;
//    Func::print(path);

    step(win, m, "a1", "e7");

    win->wait_for_button();


//    clear(*win);

    return 0;
}
