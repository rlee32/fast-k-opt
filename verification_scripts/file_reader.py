#!/usr/bin/env python3

def read_point_set(file_path):
    print("\nReading point set: " + file_path)
    points = []
    with open(file_path, "r") as f:
        # process header.
        edge_weight_type = None
        point_count = 0
        for line in f:
            if "EDGE_WEIGHT_TYPE" in line:
                value = line.strip().split()[-1]
                edge_weight_type = value
            if "DIMENSION" in line:
                value = line.strip().split()[-1]
                point_count = int(value)
            if "NODE_COORD_SECTION" in line:
                break
        print("Header edge weight type: " + str(edge_weight_type))
        print("Header point count: " + str(point_count))
        # extract point coordinates.
        for line in f:
            line = line.strip()
            if line == "" or line == "EOF":
                continue
            values = line.split()
            expected_value_count = 3
            if len(values) < expected_value_count:
                print("Skipping line: " + line.strip())
                continue
            coordinates = [float(x) for x in values[1:]]
            points.append(coordinates)
    print("Done reading point set.\n")
    if len(points) != point_count:
        print("ERROR! Header point count does not match number of extracted points.")
        print("Points read: " + str(len(points)))
    return points

def read_tour(file_path):
    ids = []
    with open(file_path, "r") as f:
        print("\nReading tour: " + file_path)
        # process header.
        point_count = 0
        for line in f:
            if "DIMENSION" in line:
                value = line.strip().split()[-1]
                point_count = int(value)
            if "TOUR_SECTION" in line:
                break
        print("Header point count: " + str(point_count))
        # extract point coordinates.
        for line in f:
            line = line.strip()
            if line == "" or line == "-1" or line == "EOF":
                continue
            values = line.split()
            expected_value_count = 1
            if len(values) < expected_value_count:
                print("Skipping line: " + line.strip())
                continue
            # the ids are offset by 1 due to start-from-1
            ids.append(int(values[0]) - 1)
    print("Done reading tour.\n")
    if len(ids) != point_count:
        print("ERROR! Header point count does not match number of extracted points.")
        print("Points read: " + str(len(ids)))
    return ids

