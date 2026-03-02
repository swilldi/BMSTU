from io import TextIOWrapper


def read_1d_table(file: TextIOWrapper):
    line = file.readline()
    data = []
    while line and line[0] != '#':
        n, x, y = map(float, line.split())
        data.append((x, y))
        line = file.readline()

    return data

def read_2d_table(file: TextIOWrapper):
    line = file.readline()
    all_y = list(map(float, line.split()))

    data = []
    line = file.readline()
    while line != '' and line[0] != '#':
        float_line = list(map(float, line.split()))
        x = float_line[0]
        for y, z in zip(all_y, float_line[1:]):
            data.append((x, y, z))

        line = file.readline()

    return data


def read_data(file_name: str="in_data.txt"):
    f = open(file_name, "r")
    f.readline()

    I = read_1d_table(f)
    Nh = read_2d_table(f)
    G = read_2d_table(f)
    c = read_2d_table(f)
    q = read_2d_table(f)

    f.close()

    return (I, Nh, G, c, q)

