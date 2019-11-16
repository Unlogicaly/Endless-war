#include <cstdio>
#include <iterator>
#include <windows.h>
#include "A_star.h"
#include "sstream"
#include "node.h"

using Graph_lib::Image;
using Graph_lib::Point;
using std::string;
using std::vector;
using std::string;
using std::pair;

int main()
{
    auto win = create_window("m");

    int size = 128;

    Map m{size, source + "\\landscape.txt", source + "\\terrain.txt", source + "\\units.txt"};

    win->attach(m);

    auto [weight, path] = A_star(m, *m.get_field("a1"), *m.get_field("b3"));

    std::cout << weight << std::endl;
    Func::print(path);

    win->wait_for_button();

//    clear(*win);

    return 0;
}
