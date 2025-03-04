# функция в аналитическом виде, начало и конец отрезка
# a, b соответственно, шаг деления отрезка h, максимальное количество
# итераций Nmax, точность eps.
import numpy as np
class RootFinder:

    __num_eps = 1e-6

    def __init__(self, func, borders: (float, float), step: float, n_max: int, eps: float):
        self.__func = func
        self.__left_border = min(borders)
        self.__right_border = max(borders)
        self.__step = step
        self.__n_max = n_max
        self.__eps = eps

    def _get_segments(self):
        segments = np.arange(self.__left_border, self.__right_border, self.__step)

        if not(abs(segments[-1] - self.__right_border) < self.__num_eps):
            segments = np.append(segments, self.__right_border)

        return segments

    def print_segments(self):
        print(self._get_segments())

    def find_roots(self):
        pass

    def get_graph(self):
        pass

a = RootFinder(lambda x: 2 * x + 1, (0, 10), 0.1, 10, 0.001)
a.print_segments()


