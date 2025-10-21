from func import *
from matr_func import *

sizes = [
    # (5, 5),
    # (5, 10),
    # (10, 10),
    # (10, 10),
    # (20, 20),
    # (20, 50),
    # (100, 20),
    # (100, 30),
    # (100, 40),
    # (100, 50),
    # (100, 100),
    # (500, 1000)
    # (20, 20)
    (10,3)
]

f = open("paths.txt", "w")
f.close()

for size in sizes:
    for razr in range(2, 6):
        file_name = f"test_matrix_{size[0]}x{size[1]}_{razr}.txt"
        print(f'"./test_files/{file_name}",')
        
        f = open(file_name, "w")
        
        mtr_1 = generate_matrix(*size, get_razr(razr))
        write_matrix(f, mtr_1)
        mtr_2 = generate_matrix(*size[::-1], get_razr(razr))
        write_matrix(f, mtr_2)
        
        f.close()
        
        f = open("paths.txt", "a")
        f.write(f'"./test_files/{file_name}",\n')
        # if (razr == 5):
        #     f.write("\n")
        f.close()
        
        # res = mult_matrix(mtr_1, mtr_2)
        # print_coord(res)
        break
        

