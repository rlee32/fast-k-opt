#!/usr/bin/env python3

# Each point is represented by a 2-tuple: (edge_id, head)
# Cycle traversal goes from tail to head.
# So if head = True, it is the 2nd point to traverse in the edge.
# Alternative naming: a == (head == False), b == (head == True)
#  e.g., a to b, tail to head.

# Each edge is represented by a 4-tuple: (edge_id1, head1, edge_id2, head2)
# edge_id1 is less than edge_id2. If the same, then head1 is False.

# In the plot, green edges represent the rest of the tour that are not changing.
# black dotted edges represent the original edges, to be replaced by the solid black lines.

import itertools
import math
import sys
from matplotlib import pyplot as plt

if len(sys.argv) < 2:
    print("Usage: " + sys.argv[0] + " k")
    sys.exit()
k = int(sys.argv[1])

max_combos = math.factorial(k - 1) * 2 ** (k - 1)

points = []
for i in range(1, k + 1):
    points.append((i, False))
    points.append((i, True))

def make_edge(point1, point2):
    if point1 > point2:
        return point2 + point1
    return point1 + point2

original_edges = []
for i in range(k):
    a = 2 * i
    b = a + 1
    original_edges.append(make_edge(points[a], points[b]))

# these would cause disjoint cycles.
invalid_edges = []
for i in range(k):
    a = 2 * i + 1
    b = (a + 1) % (2 * k)
    invalid_edges.append(make_edge(points[a], points[b]))

def convert_to_fixed_edge(combo):
    # converts points to labels that would occur if adjacent fixed edges
    # were numbered the same as original (replaced) edges.
    converted = []
    for edge in combo:
        if edge[1]:
            new_p1 = (edge[0], False)
        else:
            new_p1 = ((edge[0] + len(combo) - 1) % len(combo), True)
        if edge[3]:
            new_p2 = (edge[2], False)
        else:
            new_p2 = ((edge[2] + len(combo) - 1) % len(combo), True)
        converted.append(new_p1 + new_p2)
    return converted
def has_cycle(combo):
    # combo has fixed-edge points.
    for k in range(2, len(combo)):
        for sub_combo in itertools.combinations(combo, k):
            involved = set()
            for x in sub_combo:
                involved.add(x[0])
                involved.add(x[2])
            if len(involved) < k:
                print("has_cycle: unexpected error; investigate.")
                sys.exit()
            if len(involved) == k:
                return True
    return False
def has_subk(combo):
    for k in range(2, len(combo)):
        for sub_combo in itertools.combinations(combo, k):
            involved = set()
            for x in sub_combo:
                involved.add(x[0])
                involved.add(x[2])
            if len(involved) < k:
                print("has_cycle: unexpected error; investigate.")
                sys.exit()
            if len(involved) == k:
                involved = list(involved)
                involved.sort()
                diffs = [involved[i + 1] - involved[i] for i in range(len(involved) - 1)]
                adjacent = all([x == 1 for x in diffs])
                if adjacent:
                    return True
    return False
edge_combinations = []
def make_edge_combinations(points, current_combo):
    # assumes existence of k, edge_combinations, original_edges, invalid_edges
    if len(points) == 1:
        print("make_edge_combinations: only one point given; malformed input.")
        sys.exit()
    tail = points[0]
    head = points[1:]
    for h in head:
        edge = make_edge(tail, h)
        if edge in original_edges:
            continue
        if edge in invalid_edges:
            continue
        new_combo = current_combo + [edge]
        if len(new_combo) == k:
            new_combo.sort()
            if new_combo not in edge_combinations:
                fixed_combo = convert_to_fixed_edge(new_combo)
                if not has_cycle(fixed_combo):
                    if not has_subk(new_combo):
                        edge_combinations.append(new_combo)
        else:
            remaining = head[:]
            remaining.remove(h)
            make_edge_combinations(remaining, new_combo)
make_edge_combinations(points, [])

edge_set = set()
combination_strings = []
for c in edge_combinations:
    formatted = []
    i = 0
    new_segment_strings = []
    for e in c:
        p1 = "b" if e[1] else "a"
        p2 = "b" if e[3] else "a"
        edge = str(e[0]) + p1 + str(e[2]) + p2
        edge_set.add(edge)
        formatted.append(edge)
        new_segment_strings.append("        new_segments[" + str(i) + "] = {s" + edge[0] + "." + edge[1] + ", s" + edge[2] + "." + edge[3] + ", edge_" + edge + "};")
        i += 1
    formatted = ["edge_" + x for x in formatted]
    formatted = " + ".join(formatted)
    combination_strings.append("    new_length = " + formatted + ";")
    combination_strings.append("    if (new_length < current.length)")
    combination_strings.append("    {")
    combination_strings.append("        minimum_length = new_length;")
    combination_strings += new_segment_strings
    combination_strings.append("    }")


print("#pragma once")
print("")
print("// Max possible edge configurations: " + str(max_combos))
print("// Valid edge configurations: " + str(len(edge_combinations)))
print("// " + str(len(edge_set)) + " edge lengths to compute.")
print("")
print("#include \"DistanceTable.h\"")
print("#include \"SearchState.h\"")
print("#include \"Segment.h\"")
print("#include \"primitives.h\"")
print("")
print("#include <vector>")
print("")
print("inline void _opt(SearchState& current")
print("    , SearchState& best")
print("    , const DistanceTable& dt")
print("    , const std::vector<Segment>& ordered_segments)")
print("{")
print("    auto& new_segments = current.new_segments;")
print("    auto minimum_length = current.length;")
print("    primitives::length_t new_length{0};")
for i in range(k):
    print("    const auto& s" + str(i + 1) + " = ordered_segments[" + str(i) + "];")
for e in edge_set:
    print("    auto edge_" + e + " = dt.compute_length(s" + e[0] + "." + e[1] + ", s" + e[2] + "." + e[3] + ");")
for s in combination_strings:
    print(s)
print("    if (minimum_length >= current.length)")
print("    {")
print("        return;")
print("    }")
print("    current.improvement = current.length - minimum_length;")
print("    if (current.improvement >= best.improvement)")
print("    {")
print("        best = current;")
print("    }")
print("}")

def point_angles(k):
    sections = 2 * k
    section_angle = 360.0 / sections
    return [x * section_angle * 3.14159 / 180.0 for x in range(sections)]
def point_coordinates(k):
    angles = point_angles(k)
    return [(math.cos(a), math.sin(a)) for a in angles]
def plot_preswap_edges(k):
    coordinates = point_coordinates(k)
    # original edges.
    for i in range(k):
        p1 = coordinates[2 * i]
        p2 = coordinates[2 * i + 1]
        x = [p1[0], p2[0]]
        y = [p1[1], p2[1]]
        plt.plot(x, y, ':k')
    # fixed edges.
    for i in range(k):
        p1 = coordinates[2 * i + 1]
        p2 = coordinates[(2 * i + 2) % (2 * k)]
        x = [p1[0], p2[0]]
        y = [p1[1], p2[1]]
        plt.plot(x, y, '-g')
def plot_edge_combination(combo):
    coordinates = point_coordinates(k)
    for edge in combo:
        tail_index = 2 * (edge[0] - 1)
        if edge[1]:
            tail_index += 1
        head_index = 2 * (edge[2] - 1)
        if edge[-1]:
            head_index += 1
        p1 = coordinates[tail_index]
        p2 = coordinates[head_index]
        x = [p1[0], p2[0]]
        y = [p1[1], p2[1]]
        plt.plot(x, y, '-k')

for combo in edge_combinations:
    print("Press enter to continue plot sequence; otherwise hit any key and press enter.")
    x = input()
    if x:
        break
    plot_preswap_edges(k)
    plot_edge_combination(combo)
    plt.axis("equal")
    plt.xticks([])
    plt.yticks([])
    plt.axis("off")
    plt.show()
