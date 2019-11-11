#ifndef ARCA_H
#define ARCA_H

#include "grid.h"

class Arca : public Graph_lib::Ellipse
{
  public:
    Arca(Graph_lib::Point p, double w, double h, double alpha1, double alpha2)
        : Ellipse(p, w, h), a1(alpha1), a2(alpha2)
    {
    }

    void set_alpha1(double alpha1) { a1 = alpha1; }

    void set_alpha2(double alpha2) { a2 = alpha2; }

    double alpha1() const { return a1; }

    double alpha2() const { return a2; }

  protected:
    void draw_lines() const override;

  private:
    double a1;
    double a2;
};

#endif // ARCA_H
