#pragma once

#include "primitives.h"
#include "Segment.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <vector>

class PointSequence
{
    using Adjacents = std::array<primitives::point_id_t, 2>;
public:
    PointSequence(const std::vector<primitives::point_id_t>& sequence);

    const std::vector<primitives::point_id_t>& next() { return m_next; }

    void reorder(const std::vector<Segment>& old_segments, const std::vector<Segment>& new_segments);
    void update_next();
    const std::vector<Adjacents>& adjacents() { return m_adjacents; }

private:
    static constexpr auto m_invalid_point = std::numeric_limits<primitives::point_id_t>::max();

    std::vector<Adjacents> m_adjacents;
    std::vector<primitives::point_id_t> m_next;

    primitives::point_id_t get_other(primitives::point_id_t point, primitives::point_id_t adjacent) const;
    void create_adjacency(primitives::point_id_t point1, primitives::point_id_t point2);
    void fill_adjacent(primitives::point_id_t point, primitives::point_id_t new_adjacent);
    void break_adjacency(primitives::point_id_t point1, primitives::point_id_t point2);
    void vacate_adjacent_slot(primitives::point_id_t point, primitives::point_id_t adjacent, int slot);
};
