#include "PointSet.h"

#include <iostream>
#include <string>


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: point_set_file_path optional_tour_file_path" << std::endl;
        return 0;
    }
    std::string point_set_file_path(argv[1]);
    PointSet point_set(point_set_file_path);
    return 0;
}
