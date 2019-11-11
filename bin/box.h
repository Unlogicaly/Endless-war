#ifndef BOX_H
#define BOX_H

#include "arca.h"
#include <limits>

class Box : public Graph_lib::Rectangle
{
  public:
    Box(Graph_lib::Point p1, int ww, int hh, int rr = automat);
    Box(Graph_lib::Point p1, Graph_lib::Point p2, int rr = automat);

    int round() const { return r; }

  protected:
    void draw_lines() const;

  private:
    int r;
    enum
    {
        automat = std::numeric_limits<int>::max()
    };
};

#endif // BOX_H
