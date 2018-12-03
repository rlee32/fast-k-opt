#include "Quadtree.h"

namespace quadtree {

void Quadtree::insert(Segment s, const std::vector<primitives::morton_key_t>& keys)
{
    const auto insertion_path = morton_keys::segment_insertion_path(keys[s.a], keys[s.b]);
    QuadtreeNode* segment_destination{&m_root};
    for (auto quadrant : insertion_path)
    {
        auto child = segment_destination->child(quadrant);
        if (not child)
        {
            segment_destination->create_child(quadrant);
            child = segment_destination->child(quadrant);
        }
        segment_destination = child;
    }
    segment_destination->insert(s);
    m_segment_lengths.insert(s.length);
}
void Quadtree::erase(Segment s, const std::vector<primitives::morton_key_t>& keys)
{
    auto insertion_path = morton_keys::segment_insertion_path(keys[s.a], keys[s.b]);
    QuadtreeNode* segment_destination{&m_root};
    QuadtreeNode* parent{nullptr};
    for (auto quadrant : insertion_path)
    {
        parent = segment_destination;
        segment_destination = segment_destination->child(quadrant);
    }
    auto remaining = segment_destination->erase(s);
    while (parent and remaining == 0)
    {
        parent->reset(insertion_path.back());
        insertion_path.pop_back();
        remaining = parent->total_segment_count();
        parent = parent->parent();
    }
    m_segment_lengths.erase(s.length);
}

std::vector<Segment> Quadtree::suboptimal_segments()
{
    std::vector<Segment> replaceable; // TODO: populate non-trivially.
    for (const auto& s : replaceable)
    {
        m_segment_lengths.erase(s.length);
    }
    return replaceable;
}

void Quadtree::iterate()
{
}

} // namespace quadtree
