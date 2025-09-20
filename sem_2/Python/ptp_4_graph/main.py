def read_data():
    LABELS = ["N", "iter", "t_avg", "rse", "t_min", "t_max"]

    main_data = []
    for i in range(3):
        with open(f"dataout_{i}_us_04.txt", "r") as f:


            data = {
                LABELS[0]: [],
                LABELS[1]: [],
                LABELS[2]: [],
                LABELS[3]: [],
                LABELS[4]: [],
                LABELS[5]: []
            }
            for _ in range(19):
                line = f.readline().split()
                for i in range(6):
                    data[LABELS[i]].append(float(line[i]))
            main_data.append(data)

    return main_data, len(data[LABELS[0]])


data, count = read_data()


for i in range(19):
    s = f"{int(data[0]["N"][i]):<10}|"
    for j in range(3):
        s += f"{int(data[j]["iter"][i]):^8}|{data[j]["t_avg"][i]:^12}|{data[j]["rse"][i]:^12}\t"
    print(s)
print()

for i in range(19):
    s = f"{int(data[0]["N"][i]):<10}|"
    k_1 = (data[1]["t_avg"][i] - data[0]["t_avg"][i]) / data[0]["t_avg"][i] * 100
    k_2 = (data[2]["t_avg"][i] - data[1]["t_avg"][i]) / data[1]["t_avg"][i] * 100

    s += f"{k_1:^12.4}|{k_2:^12.4}"
    print(s)


