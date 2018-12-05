#pragma once

// Parallelization is easily achieved if each thread instantiates an Optimizer.

#include "DistanceTable.h"
#include "KContainer.h"
#include "SearchState.h"
#include "primitives.h"
#include "quadtree/Domain.h"
#include "quadtree/LengthTable.h"
#include "quadtree/LengthTable.h"
#include "quadtree/QuadtreeNode.h"
#include "quadtree/depth_map/DepthMap.h"
#include "quadtree/depth_map/transform.h"

#include <array>
#include <algorithm>
#include <cmath>
#include <ostream>
#include <vector>
#include <set>

class Optimizer
{
public:
    Optimizer(const quadtree::depth_map::DepthMap& depth_map, const DistanceTable& dt
        , const quadtree::LengthTable& lt, const quadtree::Domain& domain)
        : m_depth_map(depth_map), m_dt(dt), m_length_table(lt), m_domain(domain) {}

    void find_best();
    void iterate();
    const SearchState& best() const { return m_best; }

private:
    const quadtree::depth_map::DepthMap& m_depth_map;
    const DistanceTable& m_dt;
    const quadtree::LengthTable& m_length_table;
    const quadtree::Domain& m_domain;
    std::array<primitives::depth_t, primitives::MaxTreeDepth> m_xradius; // max grid boxes to search in the x-direction.
    std::array<primitives::depth_t, primitives::MaxTreeDepth> m_yradius; // max grid boxes to search in the y-direction.

    size_t m_k{2}; // as in k-opt.
    SearchState m_best;
    SearchState m_current;

    void find_best(int depth, quadtree::depth_map::transform::hash_t node_hash, const quadtree::QuadtreeNode* node);
    void find_best(const quadtree::QuadtreeNode* node);
    void find_best(const quadtree::QuadtreeNode* node, quadtree::QuadtreeNode::SegmentContainer::const_iterator it);

    std::vector<quadtree::QuadtreeNode*> gather_searchable_nodes(int depth, quadtree::depth_map::transform::hash_t center_node_hash) const;
    void check_best();

    void update_grid_radii();
    void insert_max_lengths(KContainer&, const std::multiset<primitives::length_t>& lengths) const;
};

inline std::ostream& operator<<(std::ostream& out, const Optimizer& optimizer)
{
    if (optimizer.best().empty())
    {
        return out << "No improving swap found.";
    }
    out << "Best swap found:\n";
    out << "\tPoint ID of each segment:\n";
    for (const auto& s : optimizer.best().segments)
    {
        out << "\t" << s.a << "\t" << s.b << "\n";
    }
    out << "\tOld length: " << optimizer.best().length << "\n";
    return out << "\tImprovement: " << optimizer.best().improvement;
}

