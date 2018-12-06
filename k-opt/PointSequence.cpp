#include "PointSequence.h"

PointSequence::PointSequence(const std::vector<primitives::point_id_t>& sequence)
{
    m_adjacents.resize(sequence.size());
    m_sequence_ids.resize(sequence.size());
    for (auto& a : m_adjacents)
    {
        a = {primitives::InvalidPoint, primitives::InvalidPoint};
    }
    auto prev = sequence.back();
    for (auto p : sequence)
    {
        create_adjacency(p, prev);
        prev = p;
    }
    m_next.resize(sequence.size());
    update_next();
}


void PointSequence::new_tour(quadtree::Quadtree& qt
    , const std::vector<Segment>& old_segments
    , const std::vector<Segment>& new_segments)
{
    for (const auto& s : old_segments)
    {
        qt.erase(s);
    }
    for (const auto& s : new_segments)
    {
        qt.insert(s);
    }
    reorder(old_segments, new_segments);
    update_next();
    align(qt.root());
}

void PointSequence::align(quadtree::QuadtreeNode* node) const
{
    align(node->segments());
    for (auto& unique_ptr : node->children())
    {
        if (unique_ptr)
        {
            align(unique_ptr.get());
        }
    }
}

void PointSequence::align(Segment::Container& segments) const
{
    std::vector<Segment> reverse;
    for (auto& s : segments)
    {
        if (s.a == m_next[s.b])
        {
            reverse.push_back(s);
        }
    }
    for (const auto& s : reverse)
    {
        segments.erase(s);
    }
    for (auto& s : reverse)
    {
        //std::cout << "before realign: " << s << std::endl;
        std::swap(s.a, s.b);
        //std::cout << "after: " << s << std::endl;
        segments.insert(s);
    }
}

void PointSequence::update_next()
{
    primitives::point_id_t current{0};
    primitives::point_id_t sequence_id{0};
    m_sequence_ids[current] = sequence_id;
    m_next[current] = m_adjacents[current].front();
    do
    {
        auto prev = current;
        current = m_next[current];
        m_sequence_ids[current] = ++sequence_id;
        m_next[current] = get_other(current, prev);
        //std::cout << "next: " << current << " to " << m_next[current] << std::endl;
    } while (current != 0); // cycle condition.
}

void PointSequence::reorder(const std::vector<Segment>& old_segments, const std::vector<Segment>& new_segments)
{
    // break old segments.
    for (const auto& s : old_segments)
    {
        //std::cout << "Breaking segment: " << s << std::endl;
        break_adjacency(s.a, s.b);
    }
    // form new segments.
    for (const auto& s : new_segments)
    {
        //std::cout << "Creating segment: " << s << std::endl;
        create_adjacency(s.a, s.b);
    }
    for (size_t i{0}; i < m_adjacents.size(); ++i)
    {
        //std::cout << "new adjacency for " << i << ": " << m_adjacents[i][0] << ", " << m_adjacents[i][1] << std::endl;
    }
}

primitives::point_id_t PointSequence::get_other(primitives::point_id_t point, primitives::point_id_t adjacent) const
{
    const auto& a = m_adjacents[point];
    if (a.front() == adjacent)
    {
        return a.back();
    }
    else
    {
        return a.front();
    }
}
void PointSequence::create_adjacency(primitives::point_id_t point1, primitives::point_id_t point2)
{
    fill_adjacent(point1, point2);
    fill_adjacent(point2, point1);
}
void PointSequence::fill_adjacent(primitives::point_id_t point, primitives::point_id_t new_adjacent)
{
    if (m_adjacents[point].front() == primitives::InvalidPoint)
    {
        m_adjacents[point].front() = new_adjacent;
    }
    else if (m_adjacents[point].back() == primitives::InvalidPoint)
    {
        m_adjacents[point].back() = new_adjacent;
    }
}
void PointSequence::break_adjacency(primitives::point_id_t point1, primitives::point_id_t point2)
{
    vacate_adjacent_slot(point1, point2, 0);
    vacate_adjacent_slot(point1, point2, 1);
    vacate_adjacent_slot(point2, point1, 0);
    vacate_adjacent_slot(point2, point1, 1);
}
void PointSequence::vacate_adjacent_slot(primitives::point_id_t point, primitives::point_id_t adjacent, int slot)
{
    if (m_adjacents[point][slot] == adjacent)
    {
        m_adjacents[point][slot] = primitives::InvalidPoint;
    }
}

