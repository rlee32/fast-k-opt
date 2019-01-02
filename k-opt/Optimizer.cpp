#include "Optimizer.h"

int searches{0}; // TODO: remove

void Optimizer::print_radii_comparison(aliases::RadiusMap& lengths) const // TODO: remove
{
    for (primitives::depth_t depth{0}; depth < primitives::DepthEnd; ++depth)
    {
        std::cout << "default radius:\t" << m_radius[depth] << "\n";
        const auto& map = m_depth_map.get_nodes(depth);
        if (map.size() == 0)
        {
            break;
        }
        for (const auto& hash_node_pair : map)
        {
            const auto node = hash_node_pair.second;
            for (const auto& current_segment : node->segments())
            {
                std::cout << "\t" << lengths[current_segment] << "\n";
            }
        }
    }
}

/*
   OMP SAMPLE

void TreeOpt::FindBestSwap()
{
  ResetSwapCandidate();
  #ifdef _OPENMP
    // Parallel version
    int CHUNKS = 2*omp_get_num_procs();
    // cout << "omp_get_num_procs: " << omp_get_num_procs() << endl;
    // cout << "omp_get_max_threads: " << omp_get_max_threads() << endl;
    int elements_per_chunk = ( tour_->cities() + CHUNKS - 1 ) / CHUNKS;
    SwapCandidate* candidates = new SwapCandidate[CHUNKS]();
    #pragma omp parallel for
    for(int c = 0; c < CHUNKS; ++c)
    {
      int start = c*elements_per_chunk;
      int end = (c+1)*elements_per_chunk;
      end = (end < tour_->cities()) ? end : tour_->cities();
      for(int i = start; i < end; ++i)
      {
        EvaluateNode(quadtree_->root(),*(tour_->segment(i)),
          candidates[c]);
      }
    }
    int best_index = 0;
    cost_t best_cost = 0;
    for(int c = 0; c < CHUNKS; ++c)
    {
      if(candidates[c].swap_cost < best_cost)
      {
        best_index = c;
        best_cost = candidates[c].swap_cost;
      }
    }
    swap_candidate_.swap_cost = candidates[best_index].swap_cost;
    swap_candidate_.segment1 = candidates[best_index].segment1;
    swap_candidate_.segment2 = candidates[best_index].segment2;
    delete[] candidates;
  #else
    //Serial version
    for(int i = 0; i < tour_->cities(); ++i)
    {
      EvaluateNode(quadtree_->root(),*(tour_->segment(i)), swap_candidate_);
    }
  #endif
}

*/

void Optimizer::find_best()
{
    m_calls = 0;
    m_best = SearchState();
    update_grid_radii();

    const auto segments = segments_in_traversal_order();
    auto max_old_lengths = compute_max_old_lengths(segments);
    auto max_length_vectors = compute_max_length_vectors(segments);

    for (primitives::depth_t depth{0}; depth < primitives::DepthEnd; ++depth)
    {
        const auto& map = m_depth_map.get_nodes(depth);
        if (map.size() == 0)
        {
            break;
        }
        #pragma omp parallel for reduction(max: m_best.improvement)
        for (const auto& hash_node_pair : map)
        {
            const auto hash = hash_node_pair.first;
            const auto node = hash_node_pair.second;
            replace_segments(depth, hash, node, max_old_lengths, max_length_vectors);
        }
    }
    std::cout << m_k << "-opt checks: " << m_calls << std::endl;
}

void Optimizer::replace_segments(primitives::depth_t d
    , quadtree::depth_map::transform::hash_t node_hash
    , const quadtree::QuadtreeNode* node
    , const aliases::RadiusMap& max_old_lengths
    , const aliases::LengthsMap& max_length_vectors)
{
    auto sit = optimizer::SegmentIterator(node);
    // loop over each segment in this node to be the first in a candidate segment set.
    for (const auto& current_segment : node->segments())
    {
        // start candidate set with first segment.
        m_current = SearchState(current_segment);
        // space between the current / first segment and the bounding box in which it resides.
        // slightly reduces the search radius.
        const auto segment_margin = compute_segment_margin(d, current_segment);
        const auto max_radius = max_old_lengths.find(current_segment)->second;
        const auto max_radius_fp = static_cast<primitives::space_t>(max_radius);
        const auto sr = compute_search_range(d, node_hash, segment_margin, max_radius_fp);
        auto xradius = std::ceil(max_radius_fp / m_domain.xdim(d));
        auto yradius = std::ceil(max_radius_fp / m_domain.ydim(d));
        const auto sb = optimizer::SearchBox<>(sr.cx, sr.cy, xradius, yradius);
        const auto psn = partial_search_nodes(sr);
        const auto fsn = full_search_nodes(sr);
        const auto nit = optimizer::NodeIterator(psn, fsn, sb);
        searches = 0;
        m_filter_stack.emplace(current_segment
            , max_radius_fp
            , max_length_vectors.find(current_segment)->second);
        add_candidate_segment(nit, sit, false);
        // std::cout << "\t" << searches << std::endl;
        m_filter_stack.pop();
        ++sit;
    }
}

void Optimizer::add_candidate_segment(optimizer::NodeIterator nit, optimizer::SegmentIterator sit, bool increment_first)
{
    check_segments(nit, sit, increment_first);
    if (increment_first)
    {
        ++nit;
    }
    while (not nit.done())
    {
        sit = optimizer::SegmentIterator(nit);
        check_segments(nit, sit);
        ++nit;
    }
}

void Optimizer::check_segments(optimizer::NodeIterator& nit, optimizer::SegmentIterator& sit, bool increment_first)
{
    while (not sit.done())
    {
        if (not m_current.valid(*sit))
        {
            ++sit;
            continue;
        }
        auto new_top = m_filter_stack.top();
        if (not new_top.insert(*sit))
        {
            ++sit;
            continue;
        }
        m_filter_stack.push(new_top);
        m_current.push_back(*sit);
        if (m_current.size() == m_k)
        {
            ++searches; // TODO: remove
            check_best();
            ++sit;
        }
        else
        {
            const auto old_sb = nit.sb();
            nit.restrict_search();
            add_candidate_segment(nit, ++sit, increment_first);
            nit.sb(old_sb);
        }
        m_current.pop_back();
        m_filter_stack.pop();
    }
}

Optimizer::SegmentMargin Optimizer::compute_segment_margin(primitives::depth_t d, const Segment& s) const
{
    SegmentMargin segment_margin;
    auto ax = m_dt.x(s.a);
    auto bx = m_dt.x(s.b);
    auto xmin = std::min(ax, bx);
    auto node_xdim = m_domain.xdim(d);
    segment_margin.xleft = std::fmod(xmin, node_xdim);
    auto xmax = std::max(ax, bx);
    segment_margin.xright = node_xdim - std::fmod(xmax, node_xdim);
    auto ay = m_dt.y(s.a);
    auto by = m_dt.y(s.b);
    auto ymin = std::min(ay, by);
    auto node_ydim = m_domain.ydim(d);
    segment_margin.ybottom = std::fmod(ymin, node_ydim);
    auto ymax = std::max(ay, by);
    segment_margin.ytop = node_ydim - std::fmod(ymax, node_ydim);
    return segment_margin;
}

Optimizer::SearchRange Optimizer::compute_search_range(primitives::depth_t d
    , quadtree::depth_map::transform::hash_t center_node_hash
    , const SegmentMargin& sm
    , primitives::space_t max_radius) const
{
    // Searchable nodes meet the following criteria:
    //  1. Same depth.
    //  2. For fully searched nodes, higher node hash value.
    //  3. For partially searched nodes (only children), lower node hash values.
    //  4. Within a certain distance.
    // Assumes higher x-coordinate always gives higher node hash.
    SearchRange sr;
    sr.depth = d;
    sr.center_node_hash = center_node_hash;
    sr.cx = quadtree::depth_map::transform::unhash_x(center_node_hash);
    sr.cy = quadtree::depth_map::transform::unhash_y(center_node_hash);
    primitives::grid_t grid_dim = 1 << d;
    if (constants::naive_mode)
    {
        sr.xmin = 0;
        sr.ymin = 0;
        sr.xend = grid_dim;
        sr.yend = grid_dim;
    }
    else
    {
        primitives::grid_t r = std::ceil((max_radius - sm.xleft) / m_domain.xdim(d));
        r = std::max(0, r);
        sr.xmin = std::max(0, sr.cx - r);
        r = std::ceil((max_radius - sm.ybottom) / m_domain.ydim(d));
        r = std::max(0, r);
        sr.ymin = std::max(0, sr.cy - r);
        r = std::ceil((max_radius - sm.xright) / m_domain.xdim(d));
        r = std::max(0, r);
        sr.xend = std::min(grid_dim, sr.cx + r + 1);
        r = std::ceil((max_radius - sm.ytop) / m_domain.ydim(d));
        r = std::max(0, r);
        sr.yend = std::min(grid_dim, sr.cy + r + 1);
    }
    return sr;
}

std::vector<const quadtree::QuadtreeNode*> Optimizer::partial_search_nodes(const SearchRange& sr) const
{
    std::vector<const quadtree::QuadtreeNode*> nodes;
    for (int x{sr.xmin}; x < sr.cx; ++x)
    {
        for (int y{sr.ymin}; y < sr.yend; ++y)
        {
            find_and_add_node(sr.depth, x, y, nodes);
        }
    }
    for (int y{sr.ymin}; y < sr.cy; ++y)
    {
        find_and_add_node(sr.depth, sr.cx, y, nodes);
    }
    return nodes;
}

std::vector<const quadtree::QuadtreeNode*> Optimizer::full_search_nodes(const SearchRange& sr) const
{
    std::vector<const quadtree::QuadtreeNode*> nodes;
    for (int y{sr.cy + 1}; y < sr.yend; ++y)
    {
        find_and_add_node(sr.depth, sr.cx, y, nodes);
    }
    for (int x{sr.cx + 1}; x < sr.xend; ++x)
    {
        for (int y{sr.ymin}; y < sr.yend; ++y)
        {
            find_and_add_node(sr.depth, x, y, nodes);
        }
    }
    return nodes;
}

void Optimizer::find_and_add_node(primitives::depth_t depth
    , primitives::grid_t grid_x, primitives::grid_t grid_y
    , std::vector<const quadtree::QuadtreeNode*>& nodes) const
{
    auto hash = quadtree::depth_map::transform::hash_grid_coord(grid_x, grid_y);
    const auto it = m_depth_map.get_nodes(depth).find(hash);
    if (it != m_depth_map.get_nodes(depth).end())
    {
        nodes.push_back(it->second);
    }
}

void Optimizer::check_best()
{
    ++m_calls;
    std::vector<Segment> ordered_segments = m_current.segments;
    std::sort(std::begin(ordered_segments)
        , std::end(ordered_segments)
        , [&m_sequence_ids = m_sequence_ids](const Segment& a, const Segment& b) { return m_sequence_ids[a.a] < m_sequence_ids[b.a]; });
    auto& new_segments = m_current.new_segments;
    if (new_segments.size() != m_k)
    {
        new_segments.resize(m_k);
    }
    switch (m_k)
    {
        case 2:
        {
            opt::two(ordered_segments, m_current, m_best, m_dt);
        } break;
        case 3:
        {
            opt::three(ordered_segments, m_current, m_best, m_dt);
        } break;
        case 4:
        {
            opt::four(ordered_segments, m_current, m_best, m_dt);
        } break;
        case 5:
        {
            opt::five(ordered_segments, m_current, m_best, m_dt);
        } break;
        case 6:
        {
            // opt::six(ordered_segments, m_current, m_best, m_dt);
        } break;
        default:
        {
        } break;
    }
}

void Optimizer::traverse_tree()
{
    int segments{0};
    uint64_t length{0};
    for (int i{0}; i < primitives::MaxTreeDepth; ++i)
    {
        const auto& map = m_depth_map.get_nodes(i);
        std::cout << "depth " << i << " nodes: " << map.size() << std::endl;
        for (const auto& pair : map)
        {
            const auto node = pair.second;
            segments += node->segments().size();
            for (const auto& s : node->segments())
            {
                length += s.length;
            }
        }
    }
    std::cout << "Total segments tallied by root node: " << m_depth_map.get_nodes(0).begin()->second->total_segment_count() << std::endl;
    std::cout << "Total segments recounted by traversing tree: " << segments << std::endl;
    std::cout << "Total tour length recalculated by traversing tree: " << length << std::endl;
}

void Optimizer::update_grid_radii()
{
    std::fill(m_radius.begin(), m_radius.end(), 0);
    KContainer<> kc(m_k);
    for (primitives::depth_t i{0}; i < primitives::DepthEnd; ++i)
    {
        auto depth = primitives::DepthEnd - 1 - i;
        insert_max_lengths(kc, depth);
        m_radius[depth] = kc.kopt_sum();
    }
}

void Optimizer::insert_max_lengths(KContainer<>& kc, primitives::depth_t depth) const
{
    if (m_length_table.lengths(depth).size() == 0)
    {
        return;
    }
    for (auto it = m_length_table.lengths(depth).crbegin(); it != m_length_table.lengths(depth).crend(); ++it)
    {
        if (not kc.insert(*it))
        {
            return;
        }
    }
}

std::vector<Segment> Optimizer::segments_in_traversal_order() const
{
    std::vector<Segment> segments;
    for (primitives::depth_t depth{0}; depth < primitives::DepthEnd; ++depth)
    {
        const auto& nodes = m_depth_map.get_nodes(depth);
        if (nodes.size() == 0)
        {
            break;
        }
        for (const auto& hash_node_pair : nodes)
        {
            const auto node = hash_node_pair.second;
            for (const auto& s : node->segments())
            {
                segments.push_back(s);
            }
        }
    }
    return segments;
}

aliases::RadiusMap Optimizer::compute_max_old_lengths(const std::vector<Segment>& segments) const
{
    aliases::RadiusMap lengths;
    KContainer<> kc(m_k);
    for (auto it = segments.rbegin(); it != segments.rend(); ++it)
    {
        lengths[*it] = kc.sum();
        kc.insert(it->length);
    }
    return lengths;
}

aliases::LengthsMap Optimizer::compute_max_length_vectors(const std::vector<Segment>& segments) const
{
    aliases::LengthsMap lengths;
    KContainer<> kc(m_k);
    for (auto it = segments.rbegin(); it != segments.rend(); ++it)
    {
        lengths[*it] = kc.vector();
        kc.insert(it->length);
    }
    return lengths;
}

aliases::RadiusMap Optimizer::compute_min_single_lengths(const std::vector<Segment>& segments) const
{
    aliases::RadiusMap min_lengths;
    KContainer<> kc(m_k);
    for (auto it = segments.rbegin(); it != segments.rend(); ++it)
    {
        min_lengths[*it] = kc.min();
        kc.insert(it->length);
    }
    return min_lengths;
}


