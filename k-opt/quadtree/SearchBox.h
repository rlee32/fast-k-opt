#pragma once

// This applies to search ranges within the same quadtree depth.
// Therefore, xradius and yradius will be the same for all overlays.

#include <primitives.h>

#include <algorithm>

namespace quadtree {

struct SearchBox
{
    SearchBox(primitives::grid_t xc, primitives::grid_t yc, primitives::grid_t xradius, primitives::grid_t yradius)
        : xmin(xc - xradius), xmax(xc + xradius)
        , ymin(yc - yradius), ymax(yc + yradius)
        , xradius(xradius), yradius(yradius) {}
    void overlay(primitives::grid_t xc, primitives::grid_t yc)
    {
        xmin = std::max(xmin, xc - xradius);
        xmax = std::min(xmax, xc + xradius);
        ymin = std::max(ymin, yc - yradius);
        ymax = std::min(ymax, yc + yradius);
    }
    bool contains(primitives::grid_t x, primitives::grid_t y) const
    {
        return x >= xmin and x <= xmax and y >= ymin and y <= ymax;
    }

    primitives::grid_t xmin{0};
    primitives::grid_t xmax{0};
    primitives::grid_t ymin{0};
    primitives::grid_t ymax{0};

    primitives::grid_t xradius{0};
    primitives::grid_t yradius{0};
};

} // namespace quadtree
