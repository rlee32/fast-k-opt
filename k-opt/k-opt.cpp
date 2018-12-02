#include "fileio/PointSet.h"
#include "fileio/Tour.h"
#include "quadtree/Quadtree.h"
#include "quadtree/morton_keys.h"

#include <iostream>
#include <string>


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: point_set_file_path optional_tour_file_path" << std::endl;
        return 0;
    }
    fileio::PointSet point_set(argv[1]);
    fileio::Tour initial_tour;
    if (argc > 2)
    {
        initial_tour = fileio::Tour(argv[2]);
        const auto length = point_set.cycle_length(initial_tour.point_ids());
        std::cout << "Initial tour length: " << length << std::endl;
    }
    quadtree::Quadtree quadtree;
    const auto keys = quadtree::morton_keys::compute_point_morton_keys(point_set.x(), point_set.y());
    return 0;
}
