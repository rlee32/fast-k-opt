#pragma once

// This represents a specific TSP solution.

#include <cstdint>
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
    size_t count() const { return m_point_ids.size(); }
    const std::vector<uint32_t>& point_ids() const { return m_point_ids; }

private:
    std::vector<uint32_t> m_point_ids;
};

} // namespace fileio
