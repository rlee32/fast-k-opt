#include "Optimizer.h"
#include "PointSequence.h"
#include "fileio/PointSet.h"
#include "fileio/Tour.h"
#include "primitives.h"
#include "quadtree/Quadtree.h"
#include "quadtree/morton_keys.h"

#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: point_set_file_path optional_tour_file_path" << std::endl;
        return 0;
    }
    fileio::PointSet point_set(argv[1]);
    quadtree::depth_map::DepthMap depth_map;
    quadtree::Quadtree quadtree(depth_map);
    depth_map.add_root(quadtree.root());
    Optimizer optimizer(depth_map, point_set.x(), point_set.y());
    const auto keys = quadtree::morton_keys::compute_point_morton_keys(point_set.x(), point_set.y());
    // Initialize tour.
    std::vector<primitives::point_id_t> tour;
    if (argc > 2)
    {
        fileio::Tour initial_tour(argv[2]);
        tour = initial_tour.point_ids();
    }
    else
    {
        for (primitives::point_id_t i{0}; i < point_set.count(); ++i)
        {
            tour.push_back(i);
        }
    }
    const auto length = point_set.cycle_length(tour);
    std::cout << "Initial tour length: " << length << std::endl;
    // Initialize quadtree with segments.
    PointSequence point_sequence(tour);
    const auto& next = point_sequence.next();
    for (auto id : tour)
    {
        auto length = distance_functions::euc2d(point_set.x(), point_set.y(), id, next[id]);
        Segment s{id, next[id], length};
        quadtree.insert(s, keys);
    }
    optimizer.iterate();
    optimizer.find_best();
    std::cout << optimizer << std::endl;
    return 0;
}
