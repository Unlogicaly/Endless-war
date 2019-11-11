#include "area_define_type.h"
#include <iostream>

std::string define_landscape_type(const std::string &s)
{
    for (auto type : areas::landscape)
    {
        for (auto &sub : type.second)
            if (sub.first == s)
                return type.first;
    }
    throw std::runtime_error("Wrong landscape name");
}

std::string define_terrain_type(const std::string &s)
{
    for (auto type : areas::terrain)
    {
        for (auto &sub : type.second)
            if (sub.first == s)
                return type.first;
    }
    throw std::runtime_error("Wrong terrain name");
}

std::string define_unit_type(const std::string &s)
{
    for (auto type : areas::unit)
    {
        for (auto &sub : type.second)
            if (sub.first == s)
                return type.first;
    }
    throw std::runtime_error("Wrong unit name");
}

std::string define_type(const std::string &s)
{
    try
    {
        define_landscape_type(s);
        return "landscape";
    }
    catch (...)
    {
    }

    try
    {
        define_terrain_type(s);
        return "terrain";
    }
    catch (...)
    {
    }

    try
    {
        define_unit_type(s);
        return "unit";
    }
    catch (...)
    {
    }

    throw std::runtime_error("Wrong name");
}

double define_weight(std::string l_sub_type, std::string t_sub_type)
{

    l_sub_type = separate(l_sub_type).first;

    t_sub_type = separate(t_sub_type).first;

    auto l_type = define_landscape_type(l_sub_type);
    auto t_type = define_terrain_type(t_sub_type);
    return areas::landscape.at(l_type).at(l_sub_type)[4] + areas::terrain.at(t_type).at(t_sub_type)[4];
}
