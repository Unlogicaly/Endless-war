#include "pictures_treatment.h"
#include "editting_files.h"
//#include "split.h"
#include <fstream>
#include <iostream>

using std::string;

string get_pic(const string &_name, int size, const string &team)
{
    string name = (team == "none" or team == "" ? "" : team + "_") + split(_name, '\\').back();
    if (split(name, '.').size() == 1)
        name += ".gif";

    auto init_path = game_path + "\\Source\\Pic\\" + name;

    if (!check_file(init_path))
    {
        std::cerr << "can't open image '" << name << "'";
        exit(-1);
    }

    auto final_path = game_path + "\\Temp\\Pic\\" + name;

    if (!check_file(final_path))
    {
        auto input_file = game_path + "\\Temp\\im_create.in";
        std::ofstream os{input_file};
        os << init_path << std::endl << final_path << std::endl << std::to_string(size) << std::endl;
        std::system((game_path + "\\resize_image.py < " + input_file).c_str());
        del(input_file);
    }
    return final_path;
}

int get_field_size(Simple_window &win)
{
    return 128;
}
