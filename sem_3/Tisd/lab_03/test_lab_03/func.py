from random import randint, choice, choices

def get_razr(prm):
    if prm == 1:
        return 10
    elif prm == 2:
        return  30
    elif prm == 3:
        return  50
    elif prm == 4:
        return 75
    elif prm == 5:
        return 100

def write_matrix(f, mtr):
    
    f.write(f"{len(mtr)} {len(mtr[0])}\n")
    
    for i, row in enumerate(mtr):
        for j, el in enumerate(row):
            if el:
                f.write(f"{i + 1} {j + 1} {el}\n")
    f.write("\n")
                
#  def generate_matrix(n, m, razr):

def print_matrix(mtr):
    for row in mtr:
        for el in row:
            print(f"{el:^4}", end=" ")
        print("")
        
    

from random import choice, sample

def generate_matrix(n, m, razr):
    """
    Генерирует матрицу n×m с разреженностью 'razr' (0–100).
    Количество ненулевых элементов строго соответствует проценту.
    """
    total = n * m
    non_zero_count = round(total * razr / 100)  # округляем до ближайшего целого

    # создаём список всех возможных позиций (i, j)
    positions = [(i, j) for i in range(n) for j in range(m)]
    # выбираем случайные ячейки для ненулевых значений
    non_zero_positions = sample(positions, non_zero_count)

    mtr_values = list(range(-5, 0)) + list(range(1, 10))
    mtr = [[0 for _ in range(m)] for _ in range(n)]

    for i, j in non_zero_positions:
        mtr[i][j] = choice(mtr_values)

    return mtr
    
