# пусть выражение 4 / 2 ---1 = 4 / 2 - -(-1) = 1
expression = "pl 10 / 2 2 - 1"

def solve_expression(expression: str):
    result = None
    if "-" in expression and "/" in expression:
        # 4 | - 35/-7/5--1
        sign = 0

        ind = 0
        expression = expression.split("-")
        len_expression = len(expression)
        divide_result = 0
        while ind < len_expression:
            element = expression[ind]
            if not element:
                sign = (sign + 1) % 2
            elif result is None and "/" not in element:
                result = int(element) * (-1)**sign
            elif "/" in element:
                while ind + 1 < len_expression and  expression[ind][-1] == "/":
                    element += expression[ind + 1]
                    sign = (sign + 1) % 2
                    ind += 1

                element = element.split("/")
                divide_result = int(element[0]) * (-1)**sign
                for divider in element[1:]:
                    divide_result /= int(divider)
                if result is None:
                    result = divide_result
                    divide_result = 0
            else:
                if divide_result:
                    result -= divide_result
                    divide_result = 0
                result -= int(element)

            ind += 1

    elif "/" in expression:
        expression = expression.split("/")
        result = int(expression[0])

        for num in expression[1:]:
            result /= int(num)

    else:
        expression = expression.split("-")
        sign = 0
        result = int(expression[0])

        for num in expression[1:]:
            if not num:
                sign = (sign + 1) % 2
            else:
                result -= int(num) * (-1)**sign

    return f"{result:.3g}"


# вынимаем из текста выражения
l = len(expression)
ind = 0
all_expression = []
current_expression = ""
start_ind, end_ind = 0, 0
wasSpace = False
while ind < l:
    symbol = expression[ind]
    # символ – пробел
    if symbol.isspace():
        if current_expression and current_expression[-1].isdigit():
            end_ind = ind
            wasSpace = True
        else:
            wasSpace = False
    # символ операции
    elif symbol in "/-":
        # новый флаг правильной записи
        if current_expression and current_expression[-1].isdigit():
            end_ind = ind

        if symbol == "-":
            current_expression += symbol
        elif symbol == "/" and current_expression and current_expression[-1] != "/":
            current_expression += symbol
        else:
            if current_expression:
                all_expression.append((current_expression[:-1], start_ind, end_ind))

            current_expression = ""
    # символ число
    elif symbol.isdigit():
        if not current_expression:
            start_ind = ind
        if wasSpace:
            if current_expression:
                all_expression.append((current_expression, start_ind, end_ind))
            start_ind = ind
            current_expression = symbol
        else:
            current_expression += symbol
    # все остальное
    else:
        if current_expression:
            all_expression.append((current_expression, start_ind, end_ind))
        current_expression = ""

    ind += 1
else:
    if current_expression and current_expression[-1].isdigit():
        all_expression.append((current_expression, start_ind, ind))


print(all_expression)
for a in all_expression:
    print(f"{a[0]} =", solve_expression(a[0]))
print()

new = ""
last_ind = 0
for el in all_expression:
    print(f"\"{expression[last_ind:el[1]]}\"")
    new += expression[last_ind:el[1]] + solve_expression(el[0])
    last_ind = el[-1]
print(new)



