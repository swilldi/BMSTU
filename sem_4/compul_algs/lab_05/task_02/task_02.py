import numpy as np
from GaussIntegral import gauss_integral

# polynom_legandro(10, 3)
# gauss_integral(np.sin, 0, 1, 4)

f = lambda x: (x - 2)**2 + 2 * np.sin(4 * (x - 2))
print(gauss_integral(f, -1, 1, 4, 1e-5))