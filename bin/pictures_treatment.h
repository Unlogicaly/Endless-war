#ifndef PICTURES_TREATMENT_H
#define PICTURES_TREATMENT_H

#include "area_define_type.h"

const std::string game_path{"D:\\My"};

std::string get_pic(const std::string &_name, int size = 128, const std::string &team = "none");

int get_field_size(Simple_window &win);

#endif // PICTURES_TREATMENT_H
