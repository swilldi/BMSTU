from figure import Point

def is_parallelogram(points, eps=1e-9):
    if len(points) != 4:
        raise ValueError("Нужно передать ровно 4 точки")

    p = points

    def eq(a, b):
        return abs(a - b) <= eps

    # Проверка середин диагоналей:
    def same_midpoint(i, j, k, l):
        return (
            eq(p[i].x + p[j].x, p[k].x + p[l].x) and
            eq(p[i].y + p[j].y, p[k].y + p[l].y)
        )

    # 3 возможных разбиения диагоналей
    pairings = [
        ((0, 1), (2, 3)),
        ((0, 2), (1, 3)),
        ((0, 3), (1, 2)),
    ]

    for (i, j), (k, l) in pairings:
        if same_midpoint(i, j, k, l):
            # площадь != 0
            A = p[i]
            B = p[k]
            D = p[l]

            abx = B.x - A.x
            aby = B.y - A.y
            adx = D.x - A.x
            ady = D.y - A.y

            cross = abx * ady - aby * adx
            if abs(cross) > eps:
                return [p[i], p[k], p[j], p[l]]

    return []


def solve_parallelograms(points, dx, dy):
    parallelograms_dots = []

    d = Point(-1, dx, dy)
    for i in range(len(points) - 2):
        for j in range(i + 1, len(points) - 1):
            for k in range(j + 1, len(points)):
                a, b, c = points[i], points[j], points[k]
                res = is_parallelogram([a, b, c, d])
                if res != []:
                        parallelograms_dots.append(res)
                        continue

    return parallelograms_dots
