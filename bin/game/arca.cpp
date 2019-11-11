#include "arca.h"

void Arca::draw_lines() const
{
    auto w = major();
    auto h = minor();

    if (fill_color().visibility())
    { // fill
        fl_color(fill_color().as_int());
        fl_pie(point(0).x, point(0).y, w + w - 1, h + h - 1, a1, a2);
        fl_color(color().as_int()); // reset color
    }
    if (color().visibility())
        fl_arc(point(0).x, point(0).y, w + w, h + h, a1, a2);
}
