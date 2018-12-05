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
        std::cout << "Arguments: point_set_file_path optional_tour_file_path" << std::endl;
        return 0;
    }
    fileio::PointSet point_set(argv[1]);
    quadtree::depth_map::DepthMap depth_map;
    const auto keys = quadtree::morton_keys::compute_point_morton_keys(point_set.x(), point_set.y());
    quadtree::Quadtree quadtree(depth_map, keys);
    depth_map.add_root(quadtree.root());
    DistanceTable dt(point_set.x(), point_set.y());
    Optimizer optimizer(depth_map, dt);
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
    // Initialize quadtree with segments.
    PointSequence point_sequence(tour);
    const auto& next = point_sequence.next();
    for (auto id : tour)
    {
        auto length = dt.compute_length(id, next[id]);
        Segment s{id, next[id], length};
        quadtree.insert(s);
    }
    optimizer.iterate();
    optimizer.find_best();
    std::cout << optimizer << std::endl;
    return 0;
}
