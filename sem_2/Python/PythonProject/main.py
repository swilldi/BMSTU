from matplotlib import pyplot as plt
import numpy as np
from math import sqrt

# t = 201.1 * 10**-3
# d_t = 4.3 * 10**-3
# d_h = 0.5 * 10**-3
# h = 0.21
#
# g = sqrt(
#     (2 / t**2)**2 * d_h**2 + (4 * h / t**3)**2 * d_t**2
# )
#
# print(g)

a = [197.6, 197.8, 210.8, 195.2, 206.4, 197.3, 202.8]
s = sum(a)/len(a)
r = 0
for i in a:
    r += (i - s)**2
r = 1.943 * sqrt(r / 7 / 6)
print(r)

# h = np.array([0.12, 0.16, 0.21, 0.25, 0.30, 0.40, 0.45, 0.50, 0.55])
# t = np.array([147.6, 171.8, 197.1, 220.8, 241.1, 262.8, 284.1, 299.1, 316.6]) * 10**-3
# g = []
# v = []
#
# for i in range(len(h)):
#     g.append(2 * h[i] / (t[i])**2)
# print(g)
# print(sum(g)/len(g))
#
# plt.plot(t, h)
# plt.xlabel("t, s")
# plt.ylabel("h, m")
# plt.savefig("g_1.jpeg")
# plt.close()
#
# plt.plot(t**2, h)
# plt.xlabel("t^2, s^2")
# plt.ylabel("h, m")
# plt.savefig("g_2.jpeg")
# plt.close()
#
# plt.plot(h, g)
# plt.axhline(9.81, color="red")
# plt.xlabel("h, m")
# plt.ylabel("g, m/s^2")
# plt.ylim(0, 12)
# # plt.show()
# plt.savefig("g_3.jpeg")
# plt.close()
#
# for i in range(len(h)):
#     v.append(2 * h[i] / t[i])
# print(v)
#
# plt.plot(h, v)
# plt.xlabel("h, m")
# plt.ylabel("v, m/s")
# plt.savefig("g_4.jpeg")
# plt.close()
#
# plt.plot(h**0.5, v)
# plt.xlabel("h^(1/2), m^(1/2)")
# plt.ylabel("v, m/s")
# plt.savefig("g_5.jpeg")
# plt.close()





