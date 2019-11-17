#ifndef MAP_H
#define MAP_H

#include "Field.h"

#define point std::pair<ull, ull>

template<typename T>
inline T &at(std::vector<std::vector<T>> &src, const point &sub) {
    return src[sub.first][sub.second];
}

inline point ntop(std::string name) {
    return {name[0] - 'a', name[1] - '1'};
}

inline std::string pton(point p) {
    return std::string(1, char(p.first + 'a')) + Func::str(p.second + 1);
}

class Map : public Simple_window
{
private:
    std::vector<std::vector<Field*>> m;
    int field_size;

    InfBox *inf;

    static void cb_info(Graph_lib::Address pwin, Graph_lib::Address pwid) {
        Graph_lib::reference_to<Map>(pwid).show_info(pwin);
    }



    ull h, w;

public:
    Map(int field_size,
        const std::string &lands_src,
        const std::string &terrain_src = "",
        const std::string &units_src = "");

    int get_field_size() { return field_size; }



    Field *get_field(const std::string &name) const;

    void show_info(Graph_lib::Address pwin);
    ull get_h() const { return h; }
    ull get_w() const { return w; }

    std::vector<Field*> operator[] (int i);
};

#endif // MAP_H
