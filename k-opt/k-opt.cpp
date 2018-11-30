#include "fileio/PointSet.h"
#include "fileio/Tour.h"

#include <iostream>
#include <string>


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: point_set_file_path optional_tour_file_path" << std::endl;
        return 0;
    }
    PointSet point_set(argv[1]);
    if (argc > 2)
    {
        Tour initial_tour(argv[2]);
        const auto length = point_set.cycle_length(initial_tour.point_ids());
        std::cout << "Initial tour length: " << length << std::endl;
    }
    return 0;
}
