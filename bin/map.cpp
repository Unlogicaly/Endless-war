#include "map.h"

using std::string;
using std::vector;

#define s_pair std::pair<string,string>

Field *Map::get_field(const string &name) const
{
    for (auto &t: m)
        for (auto field: t)
            if (field->get_name() == name) return field;
    throw std::runtime_error("Can't find field called '" + name + "'\n");
}

void Map::draw_lines() const
{
    for (auto i = 0; i < m.size(); ++i)
        for (auto j = 0; j < m[0].size(); ++j) m[i][j]->draw_lines();
}

Map::Map(int size, const string &lands_src,
         const string &terrain_src,
         const string &units_src) : field_size{size}
{
    auto lands = get_states(lands_src);
    auto ters = get_states(terrain_src);
    auto units = get_states(units_src);

    h = lands.size(); w = lands[0].size();

    if (h != ters.size() or h != units.size()) throw std::runtime_error("Maps' heights mismatch");
    if (w != ters[0].size() or w != units[0].size()) throw std::runtime_error("Maps' widths mismatch");

    for (auto i = 0; i < lands.size(); ++i)
    {
        m.emplace_back();
        for (auto j = 0; j < lands[0].size(); ++j) {
            const string name = string(1, 'a' + i) + std::to_string(j + 1);
            bool full = (units[i][j].first != "none1");
            m.back().push_back( new Field{
                new Landscape({j * 128, i * 128}, lands[i][j].first, size),
                new Terrain({j * 128, i * 128}, ters[i][j].first, size, ters[i][j].second),
                full,
                full ? new Unit({j * 128, i * 128}, units[i][j].first, size, units[i][j].second) : nullptr,
                name, size
            } );
        }
    }
}
