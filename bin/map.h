#ifndef MAP_H
#define MAP_H

#include "Field.h"

class Map : public Graph_lib::Shape
{
private:
    std::vector<std::vector<Field*>> m;
    int field_size;

    int h, w;
protected:
    void draw_lines() const override;

public:
    Map(int field_size, const std::string &lands_src,
        const std::string &terrain_src = "",
        const std::string &units_src = "");

    Field *get_field(const std::string &name) const;

    int get_h() const { return h; }
    int get_w() const { return w; }

    std::vector<Field*> operator[] (int i);
};

#endif // MAP_H
