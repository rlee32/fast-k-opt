#pragma once

// euc2d stands for "Euclidean distance, 2D".

#include <primitives.h>

#include <cmath>
#include <vector>

namespace distance_functions {

inline primitives::length_t euc2d(primitives::space_t x1, primitives::space_t y1, primitives::space_t x2, primitives::space_t y2)
{
    primitives::space_t dx = x1 - x2;
    primitives::space_t dy = y1 - y2;
    primitives::space_t exact = std::sqrt(dx * dx + dy * dy);
    return exact + 0.5; // raturn type cast.
}
inline primitives::length_t euc2d(const std::vector<primitives::space_t>& x
    , const std::vector<primitives::space_t>& y
    , primitives::point_id_t point1
    , primitives::point_id_t point2)
{
    primitives::space_t dx = x[point1] - x[point2];
    primitives::space_t dy = y[point1] - y[point2];
    primitives::space_t exact = std::sqrt(dx * dx + dy * dy);
    return exact + 0.5; // raturn type cast.
}

} // namespace distance_functions
