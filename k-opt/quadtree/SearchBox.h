#pragma once

#include <primitives.h>

#include <algorithm>

namespace quadtree {

struct SearchBox
{
    SearchBox(primitives::grid_t xc, primitives::grid_t yc, primitives::grid_t radius)
        : xmin(xc - radius), xmax(xc + radius)
        , ymin(yc - radius), ymax(yc + radius) {}
    void overlay(primitives::grid_t xc, primitives::grid_t yc, primitives::grid_t radius)
    {
        xmin = std::max(xmin, xc - radius);
        xmax = std::min(xmax, xc + radius);
        ymin = std::max(ymin, yc - radius);
        ymax = std::min(ymax, yc + radius);
    }
    bool contains(primitives::grid_t x, primitives::grid_t y) const
    {
        return x >= xmin and x <= xmax and y >= ymin and y <= ymax;
    }

    primitives::grid_t xmin{0};
    primitives::grid_t xmax{0};
    primitives::grid_t ymin{0};
    primitives::grid_t ymax{0};
};

} // namespace quadtree
