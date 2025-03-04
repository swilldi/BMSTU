import numpy as np
import matplotlib.pyplot as plt

func = lambda x: x**2
x = np.arange(-10, 10, 1)
plt.plot(x, func(x))

# plt.show()
plt.savefig("graph.png")


