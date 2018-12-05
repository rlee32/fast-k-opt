#include "PointSet.h"

namespace fileio {

PointSet::PointSet(const char* file_path)
{
    std::cout << "\nReading point set file: " << file_path << std::endl;
    std::ifstream file_stream(file_path);
    if (not file_stream.is_open())
    {
        std::cout << "ERROR: could not open file: " << file_path << std::endl;
        return;
    }
    size_t point_count{0};
    // header.
    std::string line;
    while (not file_stream.eof())
    {
        std::getline(file_stream, line);
        if (line.find("NODE_COORD_SECTION") != std::string::npos) // header end.
        {
            break;
        }
        if (line.find("DIMENSION") != std::string::npos) // point count.
        {
            std::string point_count_string = line.substr(line.find(':') + 1);
            point_count = std::stoi(point_count_string);
            std::cout << "Number of points according to header: " << point_count << std::endl;
        }
    }
    if (point_count == 0)
    {
        std::cout << "ERROR: could not read any points from the point set file." << std::endl;
        return;
    }
    // coordinates.
    while (not file_stream.eof())
    {
        if (m_x.size() >= point_count)
        {
            break;
        }
        std::getline(file_stream, line);
        std::stringstream line_stream(line);
        primitives::point_id_t point_id{0};
        line_stream >> point_id;
        if (point_id == m_x.size() + 1)
        {
            primitives::space_t value{0};
            line_stream >> value;
            m_x.push_back(value);
            line_stream >> value;
            m_y.push_back(value);
        }
        else
        {
            std::cout << "ERROR: point id ("
                << point_id
                << ")does not match number of currently read points ("
                << m_x.size()
                << ")." << std::endl;
        }
    }
    std::cout << "Finished reading point set file.\n" << std::endl;
}

} // namespace fileio

