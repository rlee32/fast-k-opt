#pragma once

// This represents a TSPLIB-formatted Euclidean TSP instance.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class PointSet
{
public:
    PointSet(std::string file_path);
    int count() const { return m_x.size(); }
    const std::vector<double> x() const { return m_x; }
    const std::vector<double> y() const { return m_y; }

private:
    std::vector<double> m_x;
    std::vector<double> m_y;

    void read(std::string file_path);
    void read_coordinates(std::string file_path);
};
