#ifndef A_STAR_H
#define A_STAR_H

#include "map.h"

std::pair<int, std::vector<std::string>> A_star(const Map &m, const Field &start, const Field &end);

#endif // A_STAR_H
