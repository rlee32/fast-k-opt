#pragma once

#include "primitives.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class DistanceTable
{
public:
    DistanceTable(const std::vector<primitives::space_t>& x, const std::vector<primitives::space_t>& y)
        : m_x(x), m_y(y) {}

    primitives::length_t lookup_length(primitives::point_id_t a, primitives::point_id_t b) const
    {
        return m_table[std::min(a, b)][std::max(a, b) - std::min(a, b) - 1]; // defunct until logarithmic table is implemented.
    }
    primitives::length_t compute_length(primitives::point_id_t a, primitives::point_id_t b) const
    {
        return compute_euc2d(a, b);
    }

    const primitives::space_t& x(primitives::point_id_t i) const { return m_x[i]; }
    const primitives::space_t& y(primitives::point_id_t i) const { return m_y[i]; }

private:
    const std::vector<primitives::space_t>& m_x;
    const std::vector<primitives::space_t>& m_y;
    std::vector<std::vector<primitives::length_t>> m_table; // TODO: implement logarithmic table.

    primitives::length_t compute_euc2d(primitives::point_id_t a, primitives::point_id_t b) const
    {
        auto dx = m_x[a] - m_x[b];
        auto dy = m_y[a] - m_y[b];
        auto exact = std::sqrt(dx * dx + dy * dy);
        return exact + 0.5; // return type cast.
    }
};
