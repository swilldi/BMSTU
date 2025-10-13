from random import randint, choice

def get_razr(prm):
    if prm == 1:
        start, end = 75, 100
    elif prm == 2:
        start, end = 50, 74
    elif prm == 3:
        start, end = 25, 49
    elif prm == 4:
        start, end = 1, 24
    
    return randint(start, end)

def write_matrix(f, mtr):
    
    f.write(f"{len(mtr)} {len(mtr[0])}\n")
    
    for i, row in enumerate(mtr):
        for j, el in enumerate(row):
            if el:
                f.write(f"{i} {j} {el}\n")
                
#  def generate_matrix(n, m, razr):

def print_matrix(mtr):
    for row in mtr:
        for el in row:
            print(f"{el:^4}", end=" ")
        print("")
        
    

def generate_matrix(n, m, razr):
    mtr = [[0] * m for _ in range(n)]
    mtr_values = list(range(-5, 0)) + list(range(1, 10))

    for i in range(n):
        for j in range(m):
            r = randint(0, 100)
            if r < razr:
                mtr[i][j] = choice(mtr_values)
    
    return mtr
    
