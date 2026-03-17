from NewtonPolynomialMethod import newton_polynomial
from Reader import read_data_from_file
from SplineMethod import spline


class Solver:
    def __init__(self):
        self.data = read_data_from_file()

    def solve(self, params: dict) -> float:
        target_x = params["x_value"]
        target_y = params["y_value"]
        target_z = params["z_value"]

        x_degree = params["x_degree"]
        y_degree = params["y_degree"]
        z_degree = params["z_degree"]

        x_method = params["x_method"]
        y_method = params["y_method"]
        z_method = params["z_method"]

        y_values = sorted({y for _, y, _, _ in self.data})
        z_values = sorted({z for _, _, z, _ in self.data})

        g_values: list[float] = []
        for fixed_y in y_values:
            for fixed_z in z_values:
                xu_values = [(x, u) for x, y, z, u in self.data if y == fixed_y and z == fixed_z]
                if x_method == "newton":
                    g_values.append(newton_polynomial(xu_values, target_x, x_degree))
                else:
                    g_values.append(spline(xu_values, target_x))

        v_values = []
        for fixed_z in z_values:
            yg_values = []
            z_idx = z_values.index(fixed_z)
            for j, fixed_y in enumerate(y_values):
                g_idx = j * len(z_values) + z_idx
                yg_values.append((fixed_y, g_values[g_idx]))

            if y_method == "newton":
                v_values.append(newton_polynomial(yg_values, target_y, y_degree))
            else:
                v_values.append(spline(yg_values, target_y))

        u: float
        if z_method == "newton":
            u = newton_polynomial(list(zip(z_values, v_values)), target_z, z_degree)
        else:
            u = spline(list(zip(z_values, v_values)), target_z)

        return u

