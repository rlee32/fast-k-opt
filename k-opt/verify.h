#pragma once

#include "DistanceTable.h"
#include "Segment.h"
#include "primitives.h"
#include "quadtree/QuadtreeNode.h"

#include <algorithm> // fill
#include <iostream>

namespace verify {

inline void fill_next(const quadtree::QuadtreeNode* node, std::vector<primitives::point_id_t>& next)
{
    for (const auto& s : node->segments())
    {
        next[s.a] = s.b;
    }
    for (const auto& unique_ptr : node->children())
    {
        if (unique_ptr)
        {
            fill_next(unique_ptr.get(), next);
        }
    }
}

inline bool valid_cycle(const quadtree::QuadtreeNode* root)
{
    // fill next table.
    std::vector<primitives::point_id_t> next;
    next.resize(root->total_segment_count());
    std::fill(next.begin(), next.end(), primitives::InvalidPoint);
    fill_next(root, next);
    // check visited points.
    std::vector<int> visited;
    visited.resize(root->total_segment_count());
    std::fill(visited.begin(), visited.end(), 0);
    constexpr primitives::point_id_t start_point{0};
    primitives::point_id_t current{start_point};
    do
    {
        if (visited[current] > 0)
        {
            std::cout << __func__ << ": ERROR: city revisited." << std::endl;
            return false;
        }
        visited[current] += 1;
        current = next[current];
    } while (current != start_point);
    for (primitives::point_id_t i{0}; i < visited.size(); ++i)
    {
        if (visited[i] < 1)
        {
            std::cout << __func__ << ": ERROR: city " << i << " not visited." << std::endl;
            return false;
        }
    }
    return true;
}


inline primitives::length_t tour_length(const quadtree::QuadtreeNode* node)
{
    primitives::length_t length{0};
    for (const auto& s : node->segments())
    {
        length += s.length;
    }
    for (const auto& unique_ptr : node->children())
    {
        if (unique_ptr)
        {
            length += tour_length(unique_ptr.get());
        }
    }
    return length;
}

} // namespace verify
