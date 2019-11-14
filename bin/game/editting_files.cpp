#include "editting_files.h"
#include <fstream>
#include <sstream>

using std::string;

const string source = "D:\\Endless_war\\source\\";

void del(const string &path)
{
    std::remove(path.c_str());
}

void read_directory(const std::string &name, std::vector<string> &v)
{
    string buffer = "list_dir_temp.out";
    string command = "dir /b " + name + " > " + buffer;
    std::ifstream is{buffer};
    system(command.c_str());

    string s;
    while (!is.eof())
    {
        getline(is, s);
        v.push_back(s);
    }

    del(buffer);
}

void clear(Simple_window &win)
{
    std::vector<std::string> files;
    read_directory(game_path + "\\Temp\\Pic", files);
    for (auto &file : files)
    {
        if (!file.empty())
            del(get_pic(file, get_field_size(win)));
    }
}

/**
 * @brief get_field_size: temporary function returns only one number - 128 (for 1920x1080 screens)
 * ToDo: make several functions, which will calculate appropriate field size and padding
 * @param win: current game window
 * @return size of one field (one of its dimensions)
 */
bool check_file(const std::string &path)
{
    std::ifstream is{path};
    return is.good();
}

void cl(std::vector<string> &src) {
    for (auto i = 0; i < src.size(); ++i)
        if (src[i].empty()) {
            src.erase(src.begin() + i, src.begin() + i + 1);
            --i;
        }
}

std::vector<std::vector<std::pair<std::string, std::string>>> get_states(const string &src)
{
    std::ifstream t_is{::source + "size.txt"};
    if (!t_is.good()) throw std::runtime_error("File '" + source + "size.txt' is damaged or doesn't exist");

    int n = 0, m = 0;

    t_is >> n >> m;

    t_is.close();

    auto res = Func::matrix_2d(n, m, std::pair<std::string, std::string>{"", ""});

    std::ifstream is{src};

    for (auto i = 0; i < n; ++i)
    {
        for (auto j = 0; j < m; ++j){
            string s; is >> s;
            auto temp = split(s, '_');
            res[i][j].first = temp[0] + temp.back();
            res[i][j].second = (temp.size() == 2 ? "none" : temp[1]);
        }
    }
    is.close();
    return res;
}
