import pygame as pg
from math import cos, sin, radians, pi
import numpy as np

pg.init()
W, H = 600, 600
SCALE = 10
Y_SHIFT = 300
X_SHIFT = 0

screen = pg.display.set_mode((W, H))
clock = pg.time.Clock()

running = True

vertoletik_w = 30
vertoletik_h = 60


def my_sin(x):
    return 10 * sin(1 / 2 * x)


def vertoletik(center, angle=0, blade_angle=0):
    cx, cy = center
    angle_rad = radians(angle)

    # Корпус вертолета (прямоугольник)
    half_w = vertoletik_w / 2
    half_h = vertoletik_h / 2
    # Углы корпуса относительно центра
    points = [
        (-half_w, -half_h),
        (half_w, -half_h),
        (half_w, half_h),
        (-half_w, half_h)
    ]
    # Поворот точек корпуса
    rotated_body = []
    for x, y in points:
        x_rot = x * cos(angle_rad) - y * sin(angle_rad) + cx
        y_rot = x * sin(angle_rad) + y * cos(angle_rad) + cy
        rotated_body.append((x_rot, y_rot))
    pg.draw.polygon(screen, "black", rotated_body)

    # Верхняя линия (хвост)
    tail_length = 20
    tail_x = cx + tail_length * sin(angle_rad)
    tail_y = cy - tail_length * cos(angle_rad)
    pg.draw.line(screen, "black", (cx, cy), (tail_x, tail_y), 2)

    # Лопасти (вращаются вокруг хвоста)
    blade_length = vertoletik_w * 2
    blade_angle_rad = radians(blade_angle)
    # Горизонтальная лопасть
    blade1_x1 = tail_x - blade_length * cos(blade_angle_rad)
    blade1_y1 = tail_y - blade_length * sin(blade_angle_rad)
    blade1_x2 = tail_x + blade_length * cos(blade_angle_rad)
    blade1_y2 = tail_y + blade_length * sin(blade_angle_rad)
    pg.draw.line(screen, "black", (blade1_x1, blade1_y1), (blade1_x2, blade1_y2), 2)
    # Вертикальная лопасть
    blade2_x1 = tail_x - blade_length * cos(blade_angle_rad + pi / 2)
    blade2_y1 = tail_y - blade_length * sin(blade_angle_rad + pi / 2)
    blade2_x2 = tail_x + blade_length * cos(blade_angle_rad + pi / 2)
    blade2_y2 = tail_y + blade_length * sin(blade_angle_rad + pi / 2)
    pg.draw.line(screen, "black", (blade2_x1, blade2_y1), (blade2_x2, blade2_y2), 2)


all_x = np.arange(0, W, 0.5)
all_x_2 = np.arange(0, W, 0.5 / 2)
ind = 0

add_degree = -5
alpha = 0
blade_angle = 0

while running:
    screen.fill("white")
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False

    points = []
    for i in all_x:
        coord = i * SCALE, my_sin(i) * SCALE + Y_SHIFT
        points.append(coord)

    x = all_x_2[ind % len(all_x_2)]
    current_pos = (x * SCALE, my_sin(x) * SCALE + Y_SHIFT)
    vertoletik(current_pos, alpha, blade_angle)

    ind += 1
    alpha += add_degree
    if alpha == -180:
        alpha = 0
        add_degree = 5
    elif alpha == 180:
        alpha = 0
        add_degree = -5


    blade_angle = (blade_angle + 20) % 180  # Увеличиваем угол лопастей

    pg.draw.lines(screen, "black", False, points)
    pg.display.flip()
    clock.tick(60)

pg.quit()
print("Вертолет улетел, но теперь он крутится! =)")