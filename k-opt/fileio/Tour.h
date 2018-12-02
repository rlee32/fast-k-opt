#pragma once

// This represents a specific TSP solution.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fileio {

class Tour
{
public:
    Tour() = default;
    Tour(const char* file_path);
    int count() const { return m_point_ids.size(); }
    const std::vector<int>& point_ids() const { return m_point_ids; }

private:
    std::vector<int> m_point_ids;
};

} // namespace fileio
