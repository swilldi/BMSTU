import os

dir_name = "./files_for_tests"
if not os.path.exists(dir_name):
    os.mkdir("./files_for_tests")

elem_counts_in_file = [
    10,
    50,
    100,
    500,
    1_000,
    2_000,
    2_500,
    3_000,
    5_000,
    6_000,
    7_000,
    8_000,
    9_000,
    10_000,
    1_000_000
]


paths_file = open("paths.txt", "w")
for elem_count in elem_counts_in_file:
    file_name = f"{dir_name}/elems_{elem_count}.txt"
    
    if (elem_count != elem_counts_in_file[-1]):
        paths_file.write(f'"{file_name}",\n')
    else:
        paths_file.write(f'"{file_name}"')
    
    f = open(file_name, "w")
    for i in range(1, elem_count + 1):
        f.write(f"{i}\n")
    f.close()
