#ifndef FIELD_H
#define FIELD_H

#include "node.h"
#include "editting_files.h"
#include <iostream>

class myWin;

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
    std::string get_path() {return path;}
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
    std::string get_path() {return path;}
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


    Unit *unit;

    Graph_lib::Point p;

    int size;

    Graph_lib::Window &win;

  public:
    bool full{false};

    Field(Landscape *land, Terrain *ter, bool full, Unit *unit, const std::string& name, int size, Graph_lib::Callback cb_info, Graph_lib::Window &win);

    Graph_lib::Button info;

//    void show_info(InfBox *inf) const;

    void attach(Graph_lib::Window &win) { info.attach(win); }

    std::vector<double> get_land_stats() const;
    std::vector<double> get_unit_stats() const;

    void draw_lines() const override;
};

struct InfBox : public Graph_lib::Shape
{
    Field *cur_field{nullptr};

    std::vector<Graph_lib::Text*> land_stats;
    std::vector<Graph_lib::Text*> unit_stats;

    Graph_lib::Rectangle *background{nullptr};

    InfBox();

    void reload(Field *field);

    void draw_lines() const override;
};


#endif // FIELD_H
