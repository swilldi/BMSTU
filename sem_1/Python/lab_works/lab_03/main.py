# Дудырев Дмитрий Сергеевич ИУ7-12Б
# Данная программа считывает координаты четырех точек. Первые три образуют треугольник.
# Программа определяется может ли существовать треугольник с введеными вершинами, если ответ положительный,
# определяет длину бисектрисы проведнной из наименьшего угла и является ли треугольник равнобедренным

import math

# Блок ввода координат вершин треугольника
print("Далее будет предложено ввести вершины треугольника ABC")
# Принимаем на вход координаты точек
a_x, a_y = int(input("Введите координату x для точки A: ")), int(input("Введите координату y для точки A: "))
print(f"Введена точка A ({a_x};{a_y})", end="\n\n")
b_x, b_y = int(input("Введите координату x для точки B: ")), int(input("Введите координату y для точки B: "))
print(f"Введена точка B ({b_x};{b_y})", end="\n\n")
c_x, c_y = int(input("Введите координату x для точки C: ")), int(input("Введите координату y для точки C: "))
print(f"Введена точка C ({c_x};{c_y})", end="\n\n")

# находим вектора сторон
vector_ab_x, vector_ab_y = b_x - a_x, b_y - a_y
vector_bc_x, vector_bc_y = c_x - b_x, c_y - b_y
vector_ac_x, vector_ac_y = c_x - a_x, c_y - a_y

# находим длины строн треугольника
ab = math.sqrt(vector_ab_x ** 2 + vector_ab_y ** 2)
bc = math.sqrt(vector_bc_x ** 2 + vector_bc_y ** 2)
ac = math.sqrt(vector_ac_x ** 2 + vector_ac_y ** 2)

# наименьшая и наибольшая стороны
max_side_length = max(ab, bc, ac)
min_side_length = min(ab, bc, ac)

# Проверка на вырождение треугольника
if ab + bc + ac - 2 * max_side_length <= 0:
    print("треугольник вырожденный")
else:
    info_triangle = f"\nAB = {format(ab, "g")}, BC = {format(bc, "g")}, AC = {format(ac, "g")}"
    type_triangle = ""
    # определяем длину биссектрисы проведенной из меньшего угла
    if min_side_length == ab:
        # наименьшая стороная ab
        length_of_bisector = math.sqrt(ac * bc * ((ac + bc) ** 2 - ab ** 2)) / (ac + bc)
    elif min_side_length == bc:
        # наименьшая стороная bc
        length_of_bisector = math.sqrt(ab * ac * ((ab + ac) ** 2 - bc ** 2)) / (ab + ac)
    else:
        # наименьшая стороная ac
        length_of_bisector = math.sqrt(ab * bc * ((ab + bc) ** 2 - ac ** 2)) / (ab + bc)
    info_bisector = f"Длина биссекриcы проведенной из меньшего угла равна {format(length_of_bisector, "g")}"

    # проверяем является ли треугольник равнобедренным
    if ab == bc != ac or ab == ac != bc or bc == ac != ab:
        type_triangle = f"Данный треугольник является равнобедренным"
    else:
        type_triangle = f"Данный треугольник не является равнобедренным"

    # принимаем на вход координаты точки O
    print("\nДалее будет предложено ввести координаты для точки P")
    point_x, point_y = int(input("Введите координату x для P: ")), int(input("Введите координату y для P: "))
    print(f"Введена точка P ({point_x};{point_y})", end="\n\n")

    # векторное произведение AO AB
    vector_product_ao = (a_x - point_x) * (b_y - a_y) - (b_x - a_x) * (a_y - point_y)
    # векторное произведение BO BC
    vector_product_bo = (b_x - point_x) * (c_y - b_y) - (c_x - b_x) * (b_y - point_y)
    # векторное произведение CO AC
    vector_product_co = (c_x - point_x) * (a_y - c_y) - (a_x - c_x) * (c_y - point_x)

    # все ли значения произведения векторов <= 0 или >= 0
    all_less_zero = vector_product_ao < 0 and vector_product_bo < 0 and vector_product_co < 0
    all_more_zero = vector_product_ao > 0 and vector_product_bo > 0 and vector_product_co > 0

    if all_less_zero or all_more_zero:
        # определение растояний от точки про сторон треугольника
        distance_to_ab = abs(point_x * vector_ab_y - point_y * vector_ab_x + b_x * a_y - a_x * b_y) / ab
        distance_to_bc = abs(point_x * vector_bc_y - point_y * vector_bc_x + c_x * b_y - b_x * c_y) / bc
        distance_to_ac = abs(point_x * vector_ac_y - point_y * vector_ac_x + c_x * a_y - a_x * c_y) / ac
        # минимальное расстоние
        minimal_distance = min(distance_to_ab, distance_to_bc, distance_to_ac)

        info_point = ("Данная точка находиться внутрия треугольника\n"
                      f"Растояние от близжайшей стороны до точки {format(minimal_distance, "f")}")
    else:
        info_point = "Введенная точка не находиться внутри треугольника"

    # вывод итоговой информации о треугольнике
    print(info_triangle, type_triangle, info_bisector, info_point, sep="\n")
