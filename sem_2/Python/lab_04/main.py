# geometry_module.py
import itertools


def is_point_inside_triangle(p, a, b, c):
    def sign(p1, p2, p3):
        return (p1[0] - p3[0]) * (p2[1] - p3[1]) - (p2[0] - p3[0]) * (p1[1] - p3[1])

    b1 = sign(p, a, b) < 0
    b2 = sign(p, b, c) < 0
    b3 = sign(p, c, a) < 0
    return (b1 == b2) and (b2 == b3)


def find_min_diff_triangle(points):
    min_diff = float('inf')
    best_triangle = None

    for triangle in itertools.combinations(points, 3):
        a, b, c = triangle
        inside = 0

        for p in points:
            if p not in triangle and is_point_inside_triangle(p, a, b, c):
                inside += 1

        outside = len(points) - 3 - inside
        current_diff = abs(inside - outside)

        if current_diff < min_diff:
            min_diff = current_diff
            best_triangle = triangle

    return best_triangle, min_diff