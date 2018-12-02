#pragma once

// This represents a TSPLIB-formatted Euclidean TSP instance.

#include <distance_functions.h>
#include <primitives.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace fileio {

class PointSet
{
public:
    PointSet(const char* file_path);
    size_t count() const { return m_x.size(); }
    const std::vector<primitives::space_t>& x() const { return m_x; }
    const std::vector<primitives::space_t>& y() const { return m_y; }

    // Only computes Euclidean distances.
    primitives::length_t cycle_length(const std::vector<primitives::point_id_t>& path) const;

private:
    std::vector<primitives::space_t> m_x;
    std::vector<primitives::space_t> m_y;
};

} // namespace fileio
