from typing import TextIO

def generate_file(f: TextIO, n: int):
    for i in range(1, n + 1):
        f.write(f"word_{i}\n")
        
    
words_count = [
    10,
    20, 
    50,
    100,
    500,
    1000,
    3000,
    5000,
    8000,
    10_000,
    30_000,
    50_000,
    70_000,
    80_000,
    90_000,
    100_000
]

paths = open("paths.txt", "w")
file_dir = "files_for_test"
for size in words_count:
    file_name = f"{file_dir}/test_word_{size}.txt"
    f = open(file_name, "w")
    generate_file(f, size)
    
    paths.write(f'"{file_name}"')
    if size != words_count[-1]:
        paths.write(',')
    paths.write('\n')
        
