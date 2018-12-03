#pragma once

// This handles the generation and sorting of Morton keys, and quadtree construction.

#include "depth_map/transform.h"
#include "depth_map/DepthMap.h"
#include "QuadtreeNode.h"
#include "Segment.h"
#include "morton_keys.h"
#include <primitives.h>
#include <SearchState.h>

#include <algorithm>
#include <cstdint>
#include <set>
#include <vector>

namespace quadtree {

class Quadtree
{
public:
    Quadtree() { m_depth_map.add_node(0, 0, 0, &m_root); }
    QuadtreeNode& root() { return m_root; }
    void insert(Segment, const std::vector<primitives::morton_key_t>& keys);
    void erase(Segment, const std::vector<primitives::morton_key_t>& keys);

    bool optimal() const { return m_best.empty(); }
    void iterate();

private:
    QuadtreeNode m_root;
    std::multiset<primitives::length_t> m_segment_lengths;
    depth_map::DepthMap m_depth_map;

    size_t m_k{2}; // as in k-opt.
    SearchState m_best;
    SearchState m_current;

    std::vector<QuadtreeNode*> gather_searchable_nodes(int depth, depth_map::transform::hash_t center_node_hash) const;
    void compare_best();

    void find_best();
    void find_best(int depth, depth_map::transform::hash_t node_hash, const QuadtreeNode*);
    void find_best(const QuadtreeNode*);
    void find_best(const QuadtreeNode*, QuadtreeNode::SegmentContainer::const_iterator);
};

} // namespace quadtree
