# функция в аналитическом виде, начало и конец отрезка
# a, b соответственно, шаг деления отрезка h, максимальное количество
# итераций Nmax, точность eps.
import numpy as np
from pprint import pprint
class RootFinder:

    __num_eps = 1e-6

    def __init__(self, func, borders: (float, float), step: float, n_max: int, eps: float):
        self.__func = func
        self.__left_border = min(borders)
        self.__right_border = max(borders)
        self.__step = step
        self.__n_max = n_max
        self.__eps = eps

    def __get_segments(self):
        segments = np.arange(self.__left_border, self.__right_border, self.__step)

        if not(abs(segments[-1] - self.__right_border) < self.__num_eps):
            segments = np.append(segments, self.__right_border)

        return segments

    def print_segments(self):
        print(self.__get_segments())

    def __update_dots(self, a, b, s):
        c = b
        if self.__func(b) * self.__func(s) < 0:
            a = s
        else:
            b = s
        return a, b, c

    def __obr_par(self, a, f_a, f_b, f_c):
        # print(a, f_a, f_b, f_c)
        # print((a * f_b * f_c) / (f_a - f_b) / (f_a - f_c))
        return (a * f_b * f_c) / (f_a - f_b) / (f_a - f_c)

    def find_roots(self):
        segments = self.__get_segments()
        finded_roots = []
        for i in range(len(segments) - 1):
            a = segments[i]
            b = segments[i + 1]

            # print(a, b, end=" | ")

            result_method = self.brant_method(a, b)
            if result_method[0] == False and result_method[1] == 1:
                finded_roots.append([(a, b), "", "", "", 1])
            elif result_method[0]:
                finded_roots.append([
                    (a, b), result_method[1], self.__func(result_method[1]), result_method[2], 0
                ])

            # вот это хорошо
        return finded_roots


    def brant_method(self, a, b):
        iter_count = 0
        c = a
        # f_b = self.__func(b)
        while abs(b - a) >= self.__eps:
            # превышен лимит операций
            if iter_count >= self.__n_max:
                return False, 1

            f_a = self.__func(a)
            f_b = self.__func(b)
            f_c = self.__func(c)

            # свапаем, чтобы была неубывающая
            if abs(f_a) < abs(f_b):
                a, b = b, a
                f_a, f_b = f_b, f_a

            # нет корня на отрезке
            if f_a * f_b > 0:
                return False, 2

            # если b – корень, то кайф
            if abs(f_b) < self.__eps:
                s = b
                return True, b, iter_count

            # обратную квадратичную интерполяцию
            if not (self.__float_equal(f_a, f_b) or self.__float_equal(f_c, f_b) or self.__float_equal(f_a, f_c)):
                s = self.__obr_par(a, f_a, f_b, f_c) \
                    + self.__obr_par(b, f_b, f_a, f_c) \
                    + self.__obr_par(c, f_c, f_a, f_b)
                if a <= s <= b and abs(s - b) < abs(c - b) / 2:
                    a, b, c = self.__update_dots(a, b, s)
                    iter_count += 1
                    continue

            # метод секущих
            if not self.__float_equal(f_b, f_a):
                s = b - f_b * (b - a) / (f_b - f_a)
                if a <= s <= b and abs(s - b) < abs(c - b) / 2:
                    a, b, c = self.__update_dots(a, b, s)
                    iter_count += 1
                    continue

            # бисекция
            s = (a + b) / 2

            # обновление интервала
            a, b, c = self.__update_dots(a, b, s)
            iter_count += 1

        # как будто бы это дикий костыль, ну пока ладно
        return True, b, iter_count


    def __float_equal(self, num_1: float, num_2: float):
        return abs(num_1 - num_2) < self.__num_eps


    def get_graph(self):
        pass

func = lambda x: x**3 - 2/10*x
a = RootFinder(func, (-1, 1), 0.3, 11, 1e-7)
for l in a.find_roots():
    print(l)



