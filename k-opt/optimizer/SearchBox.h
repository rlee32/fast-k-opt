#pragma once

// This applies to search ranges within the same quadtree depth.
// Therefore, xradius and yradius will be the same for all overlays.

#include <primitives.h>

#include <algorithm>

namespace optimizer {

template <typename CoordinateType = primitives::grid_t>
struct SearchBox
{
    SearchBox(CoordinateType xc
        , CoordinateType yc
        , CoordinateType xradius
        , CoordinateType yradius)
        : xmin(xc - xradius), xmax(xc + xradius)
        , ymin(yc - yradius), ymax(yc + yradius)
        , xradius(xradius), yradius(yradius) {}
    void overlay(CoordinateType xc, CoordinateType yc)
    {
        xmin = std::max(xmin, xc - xradius);
        xmax = std::min(xmax, xc + xradius);
        ymin = std::max(ymin, yc - yradius);
        ymax = std::min(ymax, yc + yradius);
    }
    bool contains(CoordinateType x, CoordinateType y) const
    {
        return x >= xmin and x <= xmax and y >= ymin and y <= ymax;
    }

    CoordinateType xmin{0};
    CoordinateType xmax{0};
    CoordinateType ymin{0};
    CoordinateType ymax{0};

    CoordinateType xradius{0};
    CoordinateType yradius{0};
};

} // namespace optimizer
