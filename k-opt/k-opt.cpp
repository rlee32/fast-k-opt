#include "Optimizer.h"
#include "PointSequence.h"
#include "fileio/PointSet.h"
#include "fileio/Tour.h"
#include "primitives.h"
#include "quadtree/Domain.h"
#include "quadtree/Quadtree.h"
#include "quadtree/morton_keys.h"
#include "verify.h"

#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    // Read input files.
    if (argc < 2)
    {
        std::cout << "Arguments: point_set_file_path optional_tour_file_path" << std::endl;
        return 0;
    }
    fileio::PointSet point_set(argv[1]);
    // Initial tour.
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
    // Initialize distance table.
    // TODO: implement logarithmic table; currently recomputes all distances.
    DistanceTable dt(point_set.x(), point_set.y());
    // Initialize quadtree.
    quadtree::depth_map::DepthMap depth_map;
    const quadtree::Domain domain(point_set.x(), point_set.y());
    const auto keys = quadtree::morton_keys::compute_point_morton_keys(point_set.x(), point_set.y(), domain);
    quadtree::Quadtree quadtree(depth_map, keys);
    depth_map.add_root(quadtree.root());
    // Initial segments.
    PointSequence point_sequence(tour);
    const auto& next = point_sequence.next();
    for (auto id : tour)
    {
        auto length = dt.compute_length(id, next[id]);
        Segment s{id, next[id], length};
        quadtree.insert(s);
    }
    // Hill-climbing loop.
    Optimizer optimizer(depth_map, dt, quadtree.length_table(), domain, point_sequence.sequence_ids());
    auto prev_length = verify::tour_length(quadtree.root());
    std::cout << "Initial tour length: " << prev_length << std::endl;
    int iteration{1};
    constexpr bool debug_mode{false};
    primitives::length_t improvement{1};
    do
    {
        optimizer.find_best();
        point_sequence.new_tour(quadtree, optimizer.best().segments, optimizer.best().new_segments);
        if (debug_mode)
        {
            std::cout << optimizer << std::endl;
            if (verify::valid_cycle(quadtree.root()))
            {
                std::cout << "Tour is still a valid cycle." << std::endl;
            }
            else
            {
                std::cout << "ERROR: tour has become invalid!" << std::endl;
                break;
            }
        }
        constexpr int print_period{1};
        if (iteration % print_period == 0)
        {
            auto current_length = verify::tour_length(quadtree.root());
            improvement = prev_length - current_length;
            std::cout << "Iteration " << iteration
                << " final tour length: " << current_length
                << " (improvement since last update: " << improvement << ")\n";
            prev_length = current_length;
        }
        ++iteration;
    } while (improvement > 0);
    if (improvement == 0)
    {
        std::cout << "Local optimum reached." << std::endl;
    }
    else
    {
        std::cout << "Hill-climbing optimization prematurely stopped." << std::endl;
    }
    if (debug_mode)
    {
        optimizer.traverse_tree();
    }
    return 0;
}
