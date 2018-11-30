#!/usr/bin/env python3

# this is the world.tsp-specific geom distance function.
def world_geom(point1, point2):
    # each point is (latitude, longitude) in degrees.
    pi = 3.14159265358979323846264
    deg_to_rad = pi / 180.0
    point1[0] *= deg_to_rad
    point1[1] *= deg_to_rad
    point2[0] *= deg_to_rad
    point2[1] *= deg_to_rad
    longitude_diff = point1[1] - point2[1]
    q1 = math.cos(point2[0]) * math.sin(longitude_diff);
    q3 = math.sin(longitude_diff / 2.0);
    q4 = math.cos(longitude_diff / 2.0);
    latitude_diff = point1[0] - point2[0]
    latitude_sum = point1[0] + point2[0]
    q2 = math.sin(latitude_sum) * q3 * q3 - math.sin(latitude_diff) * q4 * q4;
    q5 = math.cos(latitude_diff) * q4 * q4 - math.cos(latitude_sum) * q3 * q3;
    return int(6378388.0 * math.atan2((q1 ** 2 + q2 ** 2) ** 0.5, q5) + 1.0);

def euclidean_2d(point1, point2):
    dx = point1[0] - point2[0]
    dy = point1[1] - point2[1]
    return round((dx ** 2 + dy ** 2) ** 0.5)

