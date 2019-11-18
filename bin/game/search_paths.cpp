#include "search_paths.h"

using namespace std;

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
        win->attach(*new Graph_lib::Image{Graph_lib::Point(reverse(ntop(p)) * size), get_pic(source+"Pic\\step.gif", size)});
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

            auto [weight, path] = A_star(m, *m.get_field(start), *m.get_field(pton({i, j})));
            if (weight <= speed) {
                win->attach(*new Graph_lib::Image{Graph_lib::Point(size * j, size * i), get_pic(source + "Pic\\step.gif", size)});
            }
        }
    }
}
