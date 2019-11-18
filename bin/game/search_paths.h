#ifndef SEARCH_PATHS_H
#define SEARCH_PATHS_H

#include "A_star.h"

void step(Graph_lib::Window *win, const Map &m, const std::string &start, const std::string &end);

void av_fields(Graph_lib::Window *win, const Map &m, const std::string &start, int speed);

#endif // SEARCH_PATHS_H
