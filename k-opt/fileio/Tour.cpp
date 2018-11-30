#include "Tour.h"

Tour::Tour(const char* file_path)
{
    std::cout << "\nReading tour file: " << file_path << std::endl;
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
        std::cout << "ERROR: could not read any points from the tour file." << std::endl;
        return;
    }
    // point ids.
    while (not file_stream.eof())
    {
        if (m_point_ids.size() >= point_count)
        {
            break;
        }
        std::getline(file_stream, line);
        size_t point_id = std::stoi(line);
        if (point_id == m_point_ids.size() + 1)
        {
            m_point_ids.push_back(point_id);
        }
        else
        {
            std::cout << "ERROR: point id ("
                << point_id
                << ")does not match number of currently read points ("
                << m_point_ids.size()
                << ")." << std::endl;
        }
    }
    std::cout << "Finished reading tour file.\n" << std::endl;
}
