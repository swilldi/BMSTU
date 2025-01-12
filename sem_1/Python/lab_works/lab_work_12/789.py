text = ["вот текс иkjhk,h khkl kh ли н",
        "много очень68  много и очень    много текста",
        "не меньше 10. В комнате царила отто тишина,",
        "нарушаемая лишь тиканием часов. Я сделал",
        "  5/2 шагов к окну и замер."
        ]

m = max(text, key=len)

for line in text:
    d = len(m) - len(line)
    line = line.split(" ")
    a, b = divmod(d, len(line) - 1)
    new_line = ""
    for i in range(len(line) - 1):
        if i < b:
            new_line += line[i] + " " * (a + 2)
        else:
            new_line += line[i] + " " * (a + 1)
    else:
        new_line += line[i + 1]
    print(new_line)