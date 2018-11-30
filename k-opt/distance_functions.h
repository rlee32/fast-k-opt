#pragma once

// euc2d stands for "Euclidean distance, 2D".

#include <cmath>
#include <vector>

namespace distance_functions {

using distance_t = uint64_t;

inline distance_t euc2d(double x1, double y1, double x2, double y2)
{
    double dx = x1 - x2;
    double dy = y1 - y2;
    double exact = std::sqrt(dx * dx + dy * dy);
    return exact + 0.5; // raturn type cast.
}
inline distance_t euc2d(const std::vector<double>& x
    , const std::vector<double>& y
    , int point1
    , int point2)
{
    double dx = x[point1] - x[point2];
    double dy = y[point1] - y[point2];
    double exact = std::sqrt(dx * dx + dy * dy);
    return exact + 0.5; // raturn type cast.
}

} // namespace distance_functions
