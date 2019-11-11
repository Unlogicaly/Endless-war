#ifndef AREA_BONUSES_H
#define AREA_BONUSES_H

#include "split.h"
#include <map>

// order: attack, defense, spell, spell defece, speed, heal
namespace areas{

const std::map<std::string, std::map<std::string, std::vector<double>>> landscape{
    {
        "earth", {
            {"snow", {-5, 5, 5, 5, 1.7, 0}},
            {"grass", {0, 0, 0, 0, 1.3, 0}}
        }
    },
    {   "road", {
            {"road", {5, -5, 5, 0, 1, 0}}
        }
    },
    {   "water", {
            {"sea", {-10, -5, 0, 5, 2.5, 0}},
            {"ice", {-5, -5, 5, -5, 1.5, 0}}
        }
    }
};

const std::map<std::string, std::map<std::string, std::vector<double>>> terrain {
    {
        "earth", {
            {"forest", {-5, 10, 0, 5, 0.8, 0}},
            {"mountain", {0, 15, 5, 10, 1.7, 0}},
            {"hills", {5, 5, 5, 10, 0.8, 0}},
            {"house", {5, 10, 0, 0, 0, 20}},
            {"castle", {10, 15, 5, 15, 0, 20}}
                 }
    },
    {   "water", {
            {"rocks", {5, 5, 5, 5, 0.5, 0}},
            {"shallow", {5, 0, 5, 0, -0.5, 0}}
              }
    },
    {   "none", {
            {"none", {0, 0, 0, 0, 0}}
             }
    }
};

//order: attack, defense, spell, spell defence, speed, heal, base_hp, range
const std::map<std::string, std::map<std::string, std::vector<double>>> unit {
    {
        "land", {
            {"soldier", {25, 10, 0, -5, 4, 0, 100, 1}},
            {"archer", {25, 5, 0, -5, 4, 0, 100, 3}},
            {"wizard", {0, 0, 40, 20, 4, 0, 100, 2}}
        }
    },
    {   "fly", {
            {"eagle", {35, 0, 0, 5, 0, 80, 1}}
        }
    },
    {   "water", {
            {"water element", {30, 5, 0, 5, 0, 100, 1}}
        }
    }
};

}


#endif // AREA_BONUSES_H
