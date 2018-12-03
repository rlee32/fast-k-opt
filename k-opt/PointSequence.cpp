#include "PointSequence.h"

PointSequence::PointSequence(const std::vector<primitives::point_id_t>& sequence)
{
    m_adjacents.resize(sequence.size());
    auto prev = sequence.back();
    for (auto p : sequence)
    {
        create_adjacency(p, prev);
        prev = p;
    }
    m_next.resize(sequence.size());
    update_next();
}

void PointSequence::update_next()
{
    primitives::point_id_t current{0};
    m_next[current] = m_adjacents[current].front();
    do
    {
        auto prev = current;
        current = m_next[current];
        m_next[current] = get_other(current, prev);
    } while (current != 0); // cycle condition.
}

void PointSequence::reorder(const std::vector<Segment>& old_segments, const std::vector<Segment>& new_segments)
{
    // break old segments.
    for (const auto& s : old_segments)
    {
        break_adjacency(s.a, s.b);
    }
    // form new segments.
    for (const auto& s : new_segments)
    {
        create_adjacency(s.a, s.b);
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
    if (m_adjacents[point].front() == m_invalid_point)
    {
        m_adjacents[point].front() = new_adjacent;
    }
    else if (m_adjacents[point].back() == m_invalid_point)
    {
        m_adjacents[point].back() = new_adjacent;
    }
}
void PointSequence::break_adjacency(primitives::point_id_t point1, primitives::point_id_t point2)
{
    vacate_adjacent_slot(point1, point2, 0);
    vacate_adjacent_slot(point1, point2, 0);
    vacate_adjacent_slot(point2, point1, 1);
    vacate_adjacent_slot(point2, point1, 1);
}
void PointSequence::vacate_adjacent_slot(primitives::point_id_t point, primitives::point_id_t adjacent, int slot)
{
    if (m_adjacents[point][slot] == adjacent)
    {
        m_adjacents[point][slot] = m_invalid_point;
    }
}

