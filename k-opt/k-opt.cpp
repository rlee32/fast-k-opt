#include "fileio/PointSet.h"
#include "fileio/Tour.h"
#include "quadtree/Quadtree.h"
#include "quadtree/morton_keys.h"

#include <iostream>
#include <string>
#include <algorithm>


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: point_set_file_path optional_tour_file_path" << std::endl;
        return 0;
    }
    fileio::PointSet point_set(argv[1]);
    quadtree::Quadtree quadtree;
    const auto keys = quadtree::morton_keys::compute_point_morton_keys(point_set.x(), point_set.y());
    if (argc > 2)
    {
        fileio::Tour initial_tour(argv[2]);
        const auto length = point_set.cycle_length(initial_tour.point_ids());
        std::cout << "Initial tour length: " << length << std::endl;
        auto prev = initial_tour.point_ids().back();
        for (auto i : initial_tour.point_ids())
        {
            Segment s{std::min(prev, i)
                , std::max(prev, i)
                , distance_functions::euc2d(point_set.x(), point_set.y(), prev, i)};
            const auto insertion_path = quadtree::morton_keys::segment_insertion_path(keys[prev], keys[i]);
            quadtree.insert(s, insertion_path);
            prev = i;
        }
    }
    else
    {
        for (uint32_t i{0}; i < point_set.count(); ++i)
        {
            uint32_t next = (i + 1) % point_set.count();
            Segment s{std::min(next, i)
                , std::max(next, i)
                , distance_functions::euc2d(point_set.x(), point_set.y(), next, i)};
            const auto insertion_path = quadtree::morton_keys::segment_insertion_path(keys[next], keys[i]);
            quadtree.insert(s, insertion_path);
        }
    }
    return 0;
}
