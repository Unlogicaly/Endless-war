#ifndef FIELD_H
#define FIELD_H

#include "node.h"
#include "editting_files.h"
#include <iostream>

class Landscape : public Graph_lib::Image
{
  private:
    std::string type;
    std::string sub_type;
    std::string path;
    Graph_lib::Point p;

    int number{1};
    int size;

  public:
    virtual void draw_lines() const override { Graph_lib::Image::draw_lines(); }
    Landscape(Graph_lib::Point p, const std::string &sub_type, int size = 128);
    Graph_lib::Point Point() { return p; }
    std::string get_type() {return type;}
    std::string get_sub_type() {return sub_type;}
};


class Terrain : public Graph_lib::Image
{
  private:
    std::string team = "none";
    std::string type;
    std::string sub_type;
    std::string path;
    Graph_lib::Point p;

    int number{1};
    int size;

  public:
    virtual void draw_lines() const override { Image::draw_lines(); }
    Terrain(Graph_lib::Point p, const std::string &sub_type, int size = 128, const std::string &team = "none");
    Graph_lib::Point Point() { return p; }
    std::string get_type() {return type;}
    std::string get_sub_type() {return sub_type;}
};

class Unit : public Graph_lib::Image
{
private:
    std::string team;
    std::string type;
    std::string sub_type;
    std::string path;
    Graph_lib::Point p;

    int size;

public:
    virtual void draw_lines() const override { Image::draw_lines(); }
    Unit(Graph_lib::Point p, const std::string &sub_type, int size = 128, const std::string &team = "red");
    Graph_lib::Point Point() { return p; }
    std::string get_type() { return type; }
    std::string get_sub_type() { return sub_type; }
};

class Field : public Graph_lib::Shape, public Node
{
  private:
    Landscape *landscape;
    Terrain *terrain;

    bool full{false};
    Unit *unit;

    Graph_lib::Point p;

    int size;

  public:
    Field(Graph_lib::Point p, const std::string &land_sub_type, const std::string &ter_sub_type, const std::string &name, int size);
    Field(Landscape *land, Terrain *ter, bool full, Unit *unit, const std::string& name, int size);

    void print_land();
    void print_ter();
    void print_unit();

//    std::string get_name() const override;

    void draw_lines() const override;
};

#endif // FIELD_H
