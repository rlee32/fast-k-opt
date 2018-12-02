#pragma once

// This represents a TSPLIB-formatted Euclidean TSP instance.

#include <distance_functions.h>

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
    int count() const { return m_x.size(); }
    const std::vector<double>& x() const { return m_x; }
    const std::vector<double>& y() const { return m_y; }

    // Only computes Euclidean distances.
    distance_functions::distance_t cycle_length(const std::vector<uint32_t>& path) const;

private:
    std::vector<double> m_x;
    std::vector<double> m_y;
};

} // namespace fileio
