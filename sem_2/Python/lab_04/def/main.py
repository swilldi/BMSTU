import itertools
def is_parallelogram(points):
    p0, p1, p2, p3 = points
    # Проверяем три варианта диагоналей:
    # 1. (p0-p2) и (p1-p3)
    if ((p0[0] + p2[0], p0[1] + p2[1]) == (p1[0] + p3[0], p1[1] + p3[1])):
        return True
    # 2. (p0-p1) и (p2-p3)
    if ((p0[0] + p1[0], p0[1] + p1[1]) == (p2[0] + p3[0], p2[1] + p3[1])):
        return True
    # 3. (p0-p3) и (p1-p2)
    if ((p0[0] + p3[0], p0[1] + p3[1]) == (p1[0] + p2[0], p1[1] + p2[1])):
        return True
    return False

def count_parallelograms(points_list):
    count = 0
    for four_points in itertools.combinations(points_list, 4):
        if is_parallelogram(four_points):
            count += 1
    return count