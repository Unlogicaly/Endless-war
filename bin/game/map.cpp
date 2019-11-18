#include "map.h"

using std::string;
using std::vector;

#define s_pair std::pair<string,string>

Field *Map::get_field(const string &name) const
{
    auto [h, w] = ntop(name);
    return m[h][w];
}

void Map::show_info(Graph_lib::Address pwin) {
    Fl_Widget &w = Graph_lib::reference_to<Fl_Widget>(pwin);
    auto f = this->get_field(pton({w.y() / 128, w.x() / 128}));

    inf->reload(f);

    Fl::redraw();
}

Map::Map(int size,
         const string &lands_src,
         const string &terrain_src,
         const string &units_src) : field_size{size}, Simple_window({0, 0}, 1920, 1080, ""), inf(new InfBox())
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
                name, size, cb_info, *this
            } );

            attach(m[i][j]->info);

            attach(*m[i][j]);
        }
    }

    inf->reload(m[0][0]);

    attach(*inf);
}
