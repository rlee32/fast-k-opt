#pragma once

// This represents a specific TSP solution.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Tour
{
public:
    Tour() = default;
    Tour(const char* file_path);
    int count() const { return m_point_ids.size(); }

private:
    std::vector<size_t> m_point_ids;
};
