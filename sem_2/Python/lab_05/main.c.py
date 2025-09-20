import pygame
import math
import sys

# Инициализация Pygame
pygame.init()

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Анимация автомобиля - Лабораторная работа №5")

SKY_BLUE = (135, 206, 235)
ROAD_GRAY = (80, 80, 80)
CAR_RED = (220, 60, 50)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
YELLOW = (255, 255, 0)
GREEN = (50, 180, 70)
BROWN = (139, 69, 19)

car_x = 100
car_width = 150
car_height = 50
wheel_radius = 15
wheel_rotation = 0

car_speed = 2.0
wheel_rotation_speed = 0.1

t = - math.pi / 2
sun_speed = 0.01
sun_scale = 1.005
sun_r = 50


def rotate_point(point, center, angle):
    x, y = point
    cx, cy = center

    x_temp = x - cx
    y_temp = y - cy

    x_rot = x_temp * math.cos(angle) - y_temp * math.sin(angle)
    y_rot = x_temp * math.sin(angle) + y_temp * math.cos(angle)

    return (x_rot + cx, y_rot + cy)

def draw_cloud(x, y):
    r_cloud = 32
    cloud_color = (240, 240, 250)
    pygame.draw.circle(screen, cloud_color, (x, y), r_cloud)
    for i in range(20, 61, 20):
        pygame.draw.circle(screen, cloud_color, (x + i, y + 30), r_cloud)
        pygame.draw.circle(screen, cloud_color, (x + i, y - 30), r_cloud)
    pygame.draw.circle(screen, cloud_color, (x + 80, y), r_cloud)

def draw_scene(t, sun_r):
    screen.fill(SKY_BLUE)

    x = 500 * math.cos(t) + 800
    y = 270 * math.sin(t) + 400
    # print(x, y)

    pygame.draw.circle(screen, YELLOW, (x, y), sun_r)

    pygame.draw.rect(screen, ROAD_GRAY, (0, 400, SCREEN_WIDTH, 200))

    # Деревья (статичные объекты)
    tree_x = [31, 80, 110, 140, 180, 200, 264, 348, 396, 434, 480, 530, 644, 685, 724, 773]
    for x in tree_x:
        pygame.draw.rect(screen, BROWN, (x, 350, 20, 50))
        pygame.draw.circle(screen, GREEN, (x + 10, 330), 30)



def draw_car(x, wheel_angle):
    y = 450

    car_points = [
        (x, y + car_height),
        (x, y + car_height * 0.3),
        (x + car_width * 0.2, y),
        (x + car_width * 0.3, y - 20),
        (x + car_width * 0.7, y - 20),
        (x + car_width * 0.75, y),
        (x + car_width * 0.9, y),
        (x + car_width, y + car_height * 0.1),
        (x + car_width, y + car_height * 0.9),
        (x + car_width * 0.85, y + car_height),
        (x + car_width, y + car_height),
        (x, y + car_height)
    ]

    pygame.draw.polygon(screen, CAR_RED, car_points)

    pygame.draw.polygon(screen, (170, 220, 255), [
        (x + car_width * 0.32, y + 5),
        (x + car_width * 0.35, y - 15),
        (x + car_width * 0.65, y - 15),
        (x + car_width * 0.68, y + 5)
    ])

    pygame.draw.circle(screen, YELLOW, (x + car_width - 5, y + car_height * 0.4), 5)

    front_wheel_center = (x + car_width * 0.8, y + car_height * 0.9)
    back_wheel_center = (x + car_width * 0.2, y + car_height * 0.9)

    pygame.draw.circle(screen, BLACK, front_wheel_center, wheel_radius)
    pygame.draw.circle(screen, BLACK, back_wheel_center, wheel_radius)

    for i in range(4):
        spoke_end_front = (front_wheel_center[0], front_wheel_center[1] - wheel_radius)
        rotated_front = rotate_point(
            spoke_end_front,
            front_wheel_center,
            wheel_angle + i * math.pi / 2
        )
        pygame.draw.line(
            screen,
            WHITE,
            front_wheel_center,
            rotated_front,
            2
        )

        spoke_end_back = (back_wheel_center[0], back_wheel_center[1] - wheel_radius)
        rotated_rear = rotate_point(
            spoke_end_back,
            back_wheel_center,
            wheel_angle + i * math.pi / 2
        )
        pygame.draw.line(
            screen,
            WHITE,
            back_wheel_center,
            rotated_rear,
            2
        )

clock = pygame.time.Clock()
while True:
    screen.fill(SKY_BLUE)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    car_x += car_speed
    if car_x > SCREEN_WIDTH:
        car_x = -car_width * 1.5

    t -= sun_speed
    sun_r *= sun_scale
    if t < -math.pi - math.radians(40):
        t = - math.pi / 2
        sun_r = 50

    # Обновление угла поворота колёс
    wheel_rotation += wheel_rotation_speed

    # Отрисовка сцены
    draw_scene(t, sun_r)
    draw_cloud(100, 100)
    draw_cloud(240, 150)
    draw_cloud(370, 70)
    draw_car(car_x, wheel_rotation)

    pygame.display.flip()
    clock.tick(60)