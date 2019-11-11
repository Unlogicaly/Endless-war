#include "Field.h"
#include <iostream>

//using Graph_lib::Point;
using Graph_lib::Image;

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

//Field::Field(Graph_lib::Point p, const std::string &land_sub_type, const std::string &ter_sub_type, const std::string &name, int size)
//    : Node::Node{name, define_weight(land_sub_type, ter_sub_type)},
//      landscape{new Landscape{p, land_sub_type, size}},
//      terrain{new Terrain{p, ter_sub_type, size}},
//      p{p}
//{
//}

Field::Field(Landscape *land, Terrain *ter, bool full, Unit *unit, const std::string &name, int size) :
    Node::Node{name, define_weight(land->get_sub_type(), ter->get_sub_type())},
    landscape{land},
    terrain{ter},
    full{full},
    p{land->Point()},
    size{size}
{
    if (full) this->unit = unit;
}

void Field::print_land() {
    std::cout << "(" << landscape->Point().x << "; " << landscape->Point().y << ")" << std::endl;
    std::cout << landscape->get_type() << std::endl;
    std::cout << landscape->get_sub_type() << std::endl;
}

void Field::print_ter() {
    std::cout << "(" << terrain->Point().x << "; " << terrain->Point().y << ")" << std::endl;
    std::cout << terrain->get_type() << std::endl;
    std::cout << terrain->get_sub_type() << std::endl;
}

void Field::print_unit() {
    if (!full) return;
    std::cout << "(" << unit->Point().x << "; " << unit->Point().y << ")" << std::endl;
    std::cout << unit->get_type() << std::endl;
    std::cout << unit->get_sub_type() << std::endl;
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
