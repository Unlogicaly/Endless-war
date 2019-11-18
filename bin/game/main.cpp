#include <cstdio>
#include <iterator>
#include <windows.h>
#include "A_star.h"
#include "sstream"
#include "node.h"

using Graph_lib::Address;
using Graph_lib::Image;
using Graph_lib::Point;
using std::string;
using std::vector;
using std::string;
using std::pair;

constexpr int size = 128;

int main()
{
    Map map{size, source + "landscape.txt", source + "terrain.txt", source + "units.txt"};

    auto [weight, path] = A_star(map, *map.get_field("c3"), *map.get_field("b5"));

    std::cout << weight << std::endl;
    Func::print(path);

//    clear(*win);

    return Graph_lib::gui_main();
}

