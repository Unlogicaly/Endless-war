#include "box.h"

Box::Box(Graph_lib::Point p1, int ww, int hh, int rr) : Graph_lib::Rectangle(p1, ww, hh)
{
    if (rr < 0)
        throw std::runtime_error("...");
    if (rr == automat)
        r = std::min(ww, hh) * 0.1;
    else
        r = rr;
}

Box::Box(Graph_lib::Point p1, Graph_lib::Point p2, int rr) : Box(p1, p2.x - p1.x, p1.y - p2.y, rr) {}

void Box::draw_lines() const
{
    int x = point(0).x;
    int y = point(0).y;

    Graph_lib::Point c1(x + r + width(), y - r), c2(x - r + width(), y + height() - r),
        c3(x - r + width(), y + height() - r), c4(x + r, y + height() - r);

    if (fill_color().visible)
    {
        fl_color(fill_color().as_int());

        fl_rectf(x + r, y, width() - 2 * r, height());
        fl_rectf(x, y + r, r, width() - 2 * r);
        fl_rectf(x + width() - r, y + r, r, height() - 2 * r);

        fl_pie(c1.x, c1.y, 2 * r - 1, 2 * r - 1, 0, 90);
        fl_pie(c2.x, c2.y, 2 * r - 1, 2 * r - 1, 90, 180);
        fl_pie(c3.x, c3.y, 2 * r - 1, 2 * r - 1, 180, 270);
        fl_pie(c4.x, c4.y, 2 * r - 1, 2 * r - 1, 270, 360);

        fl_color(color().as_int());
    }

    if (color().visibility())
    {
        fl_line(x + r, y, x + width() - r, y);
        fl_line(x + width(), y + r, x + width(), y + height() - r);
        fl_line(x, y + height(), -r, y + r);
        fl_arc(c1.x, c1.y, 2 * r - 1, 2 * r - 1, 0, 90);
        fl_arc(c2.x, c2.y, 2 * r - 1, 2 * r - 1, 90, 180);
        fl_arc(c3.x, c3.y, 2 * r - 1, 2 * r - 1, 180, 270);
        fl_arc(c4.x, c4.y, 2 * r - 1, 2 * r - 1, 270, 360);
    }
}
