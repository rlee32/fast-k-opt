#include "LengthTable.h"

namespace quadtree {

void LengthTable::insert(depth_t depth, length_t length)
{
    m_lengths[depth].insert(length);
}

bool LengthTable::erase_one(depth_t depth, length_t length)
{
    const auto& first = m_lengths[depth].find(length);
    if (first == m_lengths[depth].end())
    {
        return false;
    }
    m_lengths[depth].erase(first);
    return true;
}

const LengthTable::LengthContainer& LengthTable::lengths(depth_t depth) const
{
    return m_lengths[depth];
}

} // namespace quadtree
