#ifndef AREA_DEFINE_TYPE_H
#define AREA_DEFINE_TYPE_H

#include "area_bonuses.h"

std::string define_landscape_type(const std::string &s);

std::string define_terrain_type(const std::string &s);

std::string define_unit_type(const std::string &s);

std::string define_type(const std::string &s);

double define_weight(std::string l_sub_type, std::string t_sub_type);

#endif // AREA_DEFINE_TYPE_H
