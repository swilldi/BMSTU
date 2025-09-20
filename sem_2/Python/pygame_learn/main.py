import math
from math import e, cos, sin, pi
from numpy import arange
import pygame as pg

A, B = 2, 0.1
WIDTH, HEIGHT = 1000, 1200
X_SHIFT = WIDTH // 2 - 100
Y_SHIFT = HEIGHT // 2

SCALE = 20

degree_step = 10

pg.init()
clock = pg.time.Clock()
screen = pg.display.set_mode((WIDTH, HEIGHT))


running = True

angle = 0
while running:
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False

    screen.fill((255, 255, 255))

    points_1 = []
    points_2 = []

    max_phi = 2 * pi  # Ограничиваем длину спирали
    steps = 200  # Количество точек
    distance = A * pow(e, B * 2 * pi) * 2 * SCALE - 35

    alpha = math.radians(angle)
    alpha_2 = math.radians(angle - 6)
    for fi in (max_phi * i / steps for i in range(steps + 1)):
        r = A * pow(e, B * fi)
        x = r * cos(fi)
        y = r * -sin(fi)

        rotated_x_1 = x * cos(alpha) - y * sin(alpha)
        rotated_y_1 = x * sin(alpha) + y * cos(alpha)

        y = r * -sin(fi)
        rotated_x_2 = x * cos(alpha_2) + y * sin(alpha_2)
        rotated_y_2 = -x * sin(alpha_2) + y * cos(alpha_2)

        # rotated_x = x
        # rotated_y = y

        points_1.append((rotated_x_1 * SCALE + X_SHIFT, rotated_y_1 * SCALE + Y_SHIFT))
        points_2.append((rotated_x_2 * SCALE + X_SHIFT, rotated_y_2 * SCALE + Y_SHIFT + distance))
    print(points_1)

    pg.draw.lines(screen, "black", True, points_1, 2)
    pg.draw.lines(screen, "black", True, points_2, 2)
    angle += 1

    pg.display.flip()
    clock.tick(60)

