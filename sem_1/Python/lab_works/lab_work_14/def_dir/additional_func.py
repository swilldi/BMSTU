def generate_bin_number(file: str, n: int, /, negative: bool =True):
    with open(file, "wb+") as f:
        for _ in range(n):
            if negative:
                num = randint(-10**2, 10**2)
            else:
                num = randint(1, 10**2)
            f.write(pack(FMT, int(num)))