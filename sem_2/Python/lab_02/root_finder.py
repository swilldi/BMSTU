# функция в аналитическом виде, начало и конец отрезка
# a, b соответственно, шаг деления отрезка h, максимальное количество
# итераций Nmax, точность eps.
import numpy as np
from copy import deepcopy
import sympy as sp
from sympy.calculus.util import continuous_domain
class RootFinder:

    __num_eps = 1e-6

    def __init__(self, func: str, segments, n_max: int, eps: float):
        self.string_func = sp.simplify(func)
        self.x_symbol = sp.symbols("x")
        self.func = lambda x: self.string_func.subs(self.x_symbol, x)
        self.segments = segments
        self.n_max = n_max
        self.eps = eps
        self.last_roots = []


        self.domain = continuous_domain(self.string_func, self.x_symbol, sp.S.Reals)


    def print_segments(self):
        print(self.segments)

    def __update_dots(self, a, b, s):
        c = b
        if self.func(b) * self.func(s) < 0:
            a = s
        else:
            b = s
        return a, b, c

    def __obr_par(self, a, f_a, f_b, f_c):
        return (a * f_b * f_c) / (f_a - f_b) / (f_a - f_c)

    def find_roots(self):
        segments = self.segments
        new_segments = []
        finded_roots = []
        for i in range(len(segments) - 1):
            a = segments[i]
            b = segments[i + 1]

            if not self.domain.contains(a):
                continue
            else:
                new_segments.append(a)

            # print(a, b, end=" | ")

            result_method = self.brant_method(a, b)
            if result_method[0] == False and result_method[1] == 1:
                finded_roots.append([(a, b), "", "", "", 1])
            elif result_method[0]:
                print(self.func(result_method[1]))
                finded_roots.append([
                    a, b,
                    result_method[1],
                    self.func(result_method[1]),
                    result_method[2],
                    0
                ])
        if self.domain.contains(segments[-1]):
            new_segments.append(segments[-1])

            # вот это хорошо
        self.last_roots = deepcopy(finded_roots)
        self.segments = new_segments

        return finded_roots

    def brant_method(self, a, b):
        iter_count = 0
        c = a
        # f_b = self.__func(b)
        while abs(b - a) >= self.eps:
            # превышен лимит операций
            if iter_count >= self.n_max:
                return False, 1

            f_a = self.func(a)
            f_b = self.func(b)
            f_c = self.func(c)

            # свапаем, чтобы была неубывающая
            if abs(f_a) < abs(f_b):
                a, b = b, a
                f_a, f_b = f_b, f_a

            # нет корня на отрезке
            if f_a * f_b > 0:
                return False, 2

            # если b – корень, то кайф
            if abs(f_b) < self.eps:
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
        GraphMaker(self).make_graph()


import matplotlib.pyplot as plt

class GraphMaker:
    def __init__(self, root_finder: RootFinder):
        self.prime_finder = root_finder
        self.func = root_finder.string_func
        self.x_symbol = root_finder.x_symbol
        self.f = lambda x: self.func.subs(self.x_symbol, x)


    def get_roots(self, func):
        root_finder = RootFinder(
            func, self.prime_finder.segments, self.prime_finder.n_max, self.prime_finder.eps
        )
        res = root_finder.find_roots()
        return res

    def get_coords_x(self, dots):
        return [data[1] for data in dots if data[1]]

    def get_round_coords(self, x):
        new_x = []
        y = []
        for v in x:
            if v is not sp.zoo and v:
                # new_x.append(round(float(v), 5))
                # y.append(round(self.f(v), 5))
                new_x.append(float(v))
                y.append(self.f(v))

        return new_x, y

    def make_graph(self):
        plt.clf()
        # print(self.func)
        # print(self.prime_finder.segments)
        # print([self.f(x) for x in self.prime_finder.segments])

        # plt.plot(self.prime_finder.segments, [self.f(x) for x in self.prime_finder.segments])
        x = self.prime_finder.segments
        x, y = self.get_round_coords(x)
        plt.plot(x, y, "b", label=self.prime_finder.string_func)

        # первая и вторая производные
        d_1 = self.func.diff(self.x_symbol)
        d_2 = d_1.diff(self.x_symbol).as_numer_denom()
        d_1 = d_1.as_numer_denom()

        x_root, y_root = self.get_round_coords(list(map(lambda x: x[2], self.prime_finder.last_roots)))
        plt.plot(x_root, y_root, "bo", label="Корни")

        # x-ы 1-й производной
        # числитель
        x_d_1 = self.get_coords_x(self.get_roots(d_1[0]))
        x_d_1, y_d_1 = self.get_round_coords(x_d_1)
        plt.plot(x_d_1, y_d_1, "ro", label="Экстремум")
        # Знаменатель
        x_d_1 = self.get_coords_x(self.get_roots(d_1[1]))
        x_d_1, y_d_1 = self.get_round_coords(x_d_1)
        plt.plot(x_d_1, y_d_1, "ro", label="_nolegend_")

        # x-ы 2-й производной
        x_d_2 = self.get_coords_x(self.get_roots(d_2[0]))
        x_d_2, y_d_2 = self.get_round_coords(x_d_2)
        plt.plot(x_d_2, y_d_2, "go", label="Перегиб")
        # Знаменатель
        x_d_2 = self.get_coords_x(self.get_roots(d_2[1]))
        x_d_2, y_d_2 = self.get_round_coords(x_d_2)
        plt.plot(x_d_2, y_d_2, "go", label="_nolegend_")

        # print("x =", x)
        # print("y =", y)
        # print("x_d_1 =", x_d_1)
        # print("y_d_1 =", y_d_1)
        # print("x_d_2 =", x_d_2)
        # print("y_d_2 =", y_d_2)

        plt.ylim(-50, 50)
        plt.grid()


        plt.legend(
            title='Легенда',
            loc='lower left',
            fontsize='small',
            shadow=True,
            framealpha=1,
            edgecolor='black'
        )

        plt.savefig("graph.png")
        # plt.show()




