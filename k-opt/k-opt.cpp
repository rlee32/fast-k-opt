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
    Tour initial_tour;
    if (argc > 2)
    {
        initial_tour = Tour(argv[2]);
    }
    return 0;
}
