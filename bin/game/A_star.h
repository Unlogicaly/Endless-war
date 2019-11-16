#ifndef A_STAR_H
#define A_STAR_H

#include "map.h"

#define point std::pair<ull, ull>
#define feature std::pair<d, d>

inline std::string pton(point p) {
    return std::string(1, char(p.first + 'a')) + Func::str(p.second + 1);
}

inline point ntop(std::string name) {
    return {name[0] - 'a', name[1] - '1'};
}

std::pair<int, std::vector<std::string>> A_star(const Map &m, const Field &start, const Field &end);

#endif // A_STAR_H
