#include "Field.h"
#include <iostream>

//using Graph_lib::Point;
using Graph_lib::Image;

constexpr int l_stats_num = 4;
constexpr int u_stats_num = 8;
constexpr int info_box_x = 1700;
constexpr int info_box_y = 0;
constexpr int lines_h = 30;
constexpr int lines_x = 1710;
constexpr int l_lines_y = 30;
constexpr int u_lines_y = l_lines_y + lines_h * (l_stats_num + 1);
constexpr int info_box_w = 220;
constexpr int info_box_h = u_lines_y + lines_h * u_stats_num;

Landscape::Landscape(Graph_lib::Point p, const std::string &sub_type, int size)
    : Image{p, get_pic(sub_type, size)},
    p{p},
    size{size}
{
    auto temp = separate(sub_type);
    path = get_pic(sub_type, size);
    this->sub_type = temp.first;
    this->number = temp.second;
    this->type = define_landscape_type(this->sub_type);
}

Terrain::Terrain(Graph_lib::Point p, const std::string &sub_type, int size, const std::string &team)
    : Image{p, get_pic(sub_type, size, team)},
    p{p},
    size{size}
{
    auto temp = separate(sub_type);
    path = get_pic(sub_type, size, team);
    this->sub_type = temp.first;
    this->number = temp.second;
    this->type = define_terrain_type(this->sub_type);
    if (team != "none" and temp.first != "house" and temp.first != "castle")
        throw std::runtime_error("Non building terrain can't belong to player");
    this->team = team;
}

Unit::Unit(Graph_lib::Point p, const std::string &sub_type, int size, const std::string &team) :
    Image::Image{p, get_pic(sub_type, size, team)},
    p{p},
    size{size}
{
    auto temp = separate(sub_type);
    path = get_pic(sub_type, size, team);
    this->sub_type = temp.first;
    this->type = define_unit_type(this->sub_type);
    this->team = team;
}


Field::Field(Landscape *land, Terrain *ter, bool full, Unit *unit, const std::string &name, int size, Graph_lib::Callback cb_info, Graph_lib::Window &win) :
    Node::Node{name, define_weight(land->get_sub_type(), ter->get_sub_type())},
    info(land->Point(), size, size, "", cb_info),
    landscape{land},
    terrain{ter},
    full{full},
    p{land->Point()},
    size{size},
    win{win}
{
    if (full) this->unit = unit;
}

std::vector<double> Field::get_unit_stats() const
{
    if (full)
        return areas::unit.at(unit->get_type()).at(unit->get_sub_type());
    else {

        return std::vector<double>(9, 0);
    }
}

//void Field::show_info(InfBox *inf) const {
//    inf->reload(this);
//}

std::vector<double> Field::get_land_stats() const
{
    return areas::landscape.at(landscape->get_type()).at(landscape->get_sub_type()) +
           areas::terrain.at(terrain->get_type()).at(terrain->get_sub_type());
}

//std::string Field::get_name() const
//{
//    return Node::get_name();
//}

void Field::draw_lines() const
{
    landscape->draw_lines();
    terrain->draw_lines();
    if (full) unit->draw_lines();
}


InfBox::InfBox() :
    cur_field{nullptr},
    background{new Graph_lib::Rectangle({info_box_x, info_box_y}, info_box_w, info_box_h)}
{
    background->set_fill_color(Graph_lib::Color::white);

    for (auto i = 0; i < l_stats_num; ++i) {
        land_stats.push_back(new Graph_lib::Text({lines_x, lines_h * i + l_lines_y}, ""));
        land_stats[i]->set_font(Graph_lib::Font::Font_type::courier);
        land_stats[i]->set_font_size(16);
    }

    for (auto i = 0; i < u_stats_num; ++i) {
        unit_stats.push_back(new Graph_lib::Text({lines_x, lines_h * i + u_lines_y}, ""));
        unit_stats[i]->set_font(Graph_lib::Font::Font_type::courier);
        unit_stats[i]->set_font_size(16);
    }
}

void InfBox::reload(Field *field) {
    cur_field = field;
    auto temp_land_stats = field->get_land_stats();
    auto temp_unit_stats = field->get_unit_stats();

    for (auto i = 0; i < l_stats_num; ++i)
        land_stats[i]->set_label(area_order[i] + ": " + Func::str(int(temp_land_stats[i])));

    for (auto i = 0; i < u_stats_num; ++i){
        unit_stats[i]->set_label(unit_order[i] + ": " + Func::str(int(temp_unit_stats[i])));
    }
    Fl::redraw();
}

void InfBox::draw_lines() const
{
    background->draw();
    for (auto &t: land_stats)
        t->draw();

    for (auto &t: unit_stats)
        t->draw();
}
