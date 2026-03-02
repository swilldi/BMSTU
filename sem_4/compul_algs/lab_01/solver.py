from math import pi
from interpolation import newton_polynomial2D, newton_polynomial

EPS = 1e-5
TIME_SCALE = 1e-6
TIME_EPS_FACTOR = 0.5
R_SCALE = L_SCALE = 1e-2

class Solver:
    def __init__(self, I_table, Nh_table, sigma_tabe, c_table, q_table):
        self.I_table = I_table
        self.Nh_table = Nh_table
        self.sigma_table = sigma_tabe
        self.c_table = c_table
        self.q_table = q_table

        self.n = 3
        self.solve_p_right: float | None = None

    def I_of(self, t: float) -> float:
        return newton_polynomial(self.I_table, t, self.n)

    def c_of(self, T: float, p: float) -> float:
        return newton_polynomial2D(self.c_table, T, p, self.n)

    def q_of(self, T: float, p: float) -> float:
        return newton_polynomial2D(self.q_table, T, p, self.n)

    def sigma_of(self, T: float, p: float) -> float:
        return newton_polynomial2D(self.sigma_table, T, p, self.n)

    def Nh_of(self, T: float, p: float) -> float:
        return newton_polynomial2D(self.Nh_table, T, p, self.n)

    def phi(self, t: float, T: float, p: float) -> float:
        I = self.I_of(t)
        j = I / (pi * self.R**2)
        sigma = self.sigma_of(T, p)
        q = self.q_of(T, p)
        c = self.c_of(T, p)

        return (j**2 / sigma - q) / c

    def p_of(self, T: float) -> float:
        if self.solve_p_right is None:
            raise ValueError("solve_p_right is not initialized")

        # диапазон поиска корня
        a, b = 0.3, 2.5

        # функция вычисления корня
        def f(p: float) -> float:
            return self.Nh_of(T, p) - self.solve_p_right

        # поиск половинным делением
        fa = f(a)
        fb = f(b)
        if fa == 0:
            return a
        if fb == 0:
            return b

        # if fa * fb < 0:
        #     print("=)")

        while b - a > EPS:
            p = (b + a) / 2
            fc = f(p)
            if abs(fc) <= EPS:
                return p
            if fa * fc < 0:
                b = p
            else:
                a = p
                fa = fc

        return (a + b) / 2

    def Rd_of(self, l: float, sigma: float, R: float) -> float:
        return l / (pi * sigma * R**2)

    def Fr_of(self, q: float, R: float) -> float:
        return q * R / 2

    def solve(self, t0: float, t_end: float, t_step: float, T0: float, R: float, l: float, px: float):
        Tx = 300
        self.R = R
        self.solve_p_right = 7.242 * 10 ** 4 * px / Tx
        t = t0 * TIME_SCALE
        t_end *= TIME_SCALE
        t_step *= TIME_SCALE
        T = T0
        time_eps = t_step * TIME_EPS_FACTOR

        data: dict[str, list[float]] = { "t": [], "T": [], "p": [], "sigma": [], "q": [], "Rd": [], "Fr": [] }
        while t <= t_end + time_eps:
            p = self.p_of(T)

            sigma = self.sigma_of(T, p)
            q = self.q_of(T, p)
            Rd = self.Rd_of(l, sigma, R)
            Fr = self.Fr_of(q, R)

            data["t"].append(round(t / TIME_SCALE, 10))
            data["T"].append(T)
            data["p"].append(p)
            data["sigma"].append(sigma)
            data["q"].append(q)
            data["Rd"].append(Rd)
            data["Fr"].append(Fr)

            # полушаг T -> T_n+1/2
            k1 = self.phi(t, T, p)
            T_half = T + (t_step / 2) * k1
            p_half = self.p_of(T_half)
            k2 = self.phi(t + t_step / 2, T_half, p_half)
            T = T + t_step * k2

            # переход к временному моменту
            t += t_step

        return data
