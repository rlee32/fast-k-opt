#!/usr/bin/env python3

import file_reader
import distance_functions

import sys
import math

def compute_length(point_set, distance_function, tour):
    length = 0
    for i in range(len(tour) - 1):
        current_index = tour[i]
        next_index = tour[i + 1]
        current_length = distance_function(point_set[current_index], point_set[next_index])
        length += current_length
    last_index = tour[-1]
    first_index = tour[0]
    length += distance_function(point_set[last_index], point_set[first_index])
    return length

if len(sys.argv) < 2:
    print("Need file path of .tsp file")
    sys.exit()

point_set = file_reader.read_point_set(sys.argv[1])
if len(sys.argv) < 3:
    tour = [x for x in range(len(point_set))]
else:
    tour = file_reader.read_tour(sys.argv[2])
tour_length = compute_length(point_set, distance_functions.euclidean_2d, tour)
print("Tour length: " + str(tour_length))
