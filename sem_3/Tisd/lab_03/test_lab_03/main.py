from func import *

sizes = [
    (5, 5),
    (5, 10),
    (10, 10),
    (20, 20),
    (100, 50),
    (100, 100),
    (1000, 1000)
]

for size in sizes:
    for razr in range(1, 5):
        file_name = f"test_matrix_{size[0]}x{size[1]}_{razr}.txt"
        print(f'"./test_files/{file_name}",')
        
        # f = open(file_name, "w")
        
        # mtr = generate_matrix(*size, get_razr(razr))
        # write_matrix(f, mtr)
        # mtr = generate_matrix(*(size[::-1]), get_razr(razr))
        # write_matrix(f, mtr)
        
        # f.close()

