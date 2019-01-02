#pragma once

// Parallelization is easily achieved if each thread instantiates an Optimizer.

#include "DistanceTable.h"
#include "KContainer.h"
#include "SearchState.h"
#include "aliases.h"
#include "constants.h"
#include "opt/five.h"
#include "opt/four.h"
#include "opt/three.h"
#include "opt/two.h"
#include "optimizer/CliqueFilter.h"
#include "optimizer/NodeIterator.h"
#include "optimizer/SearchBox.h"
#include "optimizer/SegmentIterator.h"
#include "primitives.h"
#include "quadtree/Domain.h"
#include "quadtree/LengthTable.h"
#include "quadtree/QuadtreeNode.h"
#include "quadtree/depth_map/DepthMap.h"
#include "quadtree/depth_map/transform.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <ostream>
#include <set>
#include <stack>
#include <vector>

class Optimizer
{
    using NodeContainer = std::vector<const quadtree::QuadtreeNode*>;
    using node_iterator = NodeContainer::const_iterator;
    using segment_iterator = quadtree::QuadtreeNode::SegmentContainer::const_iterator;
public:
    Optimizer(const quadtree::depth_map::DepthMap& depth_map, const DistanceTable& dt
        , const quadtree::LengthTable& lt, const quadtree::Domain& domain
        , const std::vector<primitives::point_id_t>& sequence_ids)
        : m_depth_map(depth_map), m_dt(dt), m_length_table(lt), m_domain(domain), m_sequence_ids(sequence_ids) {}

    void find_best();
    const SearchState& best() const { return m_best; }
    void k(size_t k) { m_k = k; }

    // debug
    void print_radii_comparison(aliases::RadiusMap& max_old_lengths) const; // TODO: remove
    void traverse_tree();

private:
    const quadtree::depth_map::DepthMap& m_depth_map;
    const DistanceTable& m_dt;
    const quadtree::LengthTable& m_length_table;
    const quadtree::Domain& m_domain;
    const std::vector<primitives::point_id_t>& m_sequence_ids;
    std::array<primitives::space_t, primitives::DepthEnd> m_radius; // max grid boxes to search in any direction.

    size_t m_k{0}; // as in k-opt.
    std::stack<optimizer::CliqueFilter> m_filter_stack;

    SearchState m_best;
    SearchState m_current;
    size_t m_calls{0};

    void replace_segments(primitives::depth_t depth
        , quadtree::depth_map::transform::hash_t node_hash
        , const quadtree::QuadtreeNode* node
        , const aliases::RadiusMap& max_old_lengths
        , const aliases::LengthsMap& max_length_vectors);

    void check_best();

    void update_grid_radii();
    void insert_max_lengths(KContainer<>&, primitives::depth_t depth) const;

    struct SearchRange
    {
        primitives::depth_t depth{0};
        quadtree::depth_map::transform::hash_t center_node_hash{0};
        primitives::grid_t cx{0};
        primitives::grid_t cy{0};
        primitives::grid_t xmin{0};
        primitives::grid_t xend{0};
        primitives::grid_t ymin{0};
        primitives::grid_t yend{0};
    };
    std::vector<const quadtree::QuadtreeNode*> full_search_nodes(const SearchRange& sr) const;
    std::vector<const quadtree::QuadtreeNode*> partial_search_nodes(const SearchRange& sr) const;

    inline void find_and_add_node(primitives::depth_t depth
        , primitives::grid_t grid_x, primitives::grid_t grid_y
        , std::vector<const quadtree::QuadtreeNode*>& nodes) const;

    struct SegmentMargin // margin between segment bounding-box and grid node boundary.
    {
        primitives::length_t xleft{0};
        primitives::length_t xright{0};
        primitives::length_t ytop{0};
        primitives::length_t ybottom{0};
    };

    SegmentMargin compute_segment_margin(primitives::depth_t depth, const Segment& s) const;
    SearchRange compute_search_range(primitives::depth_t d
        , quadtree::depth_map::transform::hash_t center_node_hash
        , const SegmentMargin&
        , primitives::space_t max_radius) const;

    void add_candidate_segment(optimizer::NodeIterator nit, optimizer::SegmentIterator sit, bool increment_first = true);
    void check_segments(optimizer::NodeIterator& nit, optimizer::SegmentIterator& sit, bool increment_first = true);

    std::vector<Segment> segments_in_traversal_order() const;
    aliases::RadiusMap compute_max_old_lengths(const std::vector<Segment>&) const;
    aliases::RadiusMap compute_min_single_lengths(const std::vector<Segment>&) const;
    aliases::LengthsMap compute_max_length_vectors(const std::vector<Segment>&) const;
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

