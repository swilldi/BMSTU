"""
Генерация порядка вставки ключей в BST так, чтобы форма дерева
имела заданное соотношение левого/правого поддерева.

Для каждого набора записываем последовательность в текстовый файл:
каждая строка — один ключ, первая строка — корень.
"""

from typing import List, Iterable, Any
import os
import sys
sys.setrecursionlimit(100_000)  # или сколько тебе нужно


def gen_bst_order(values: Iterable[Any], left_percent: int) -> List[Any]:
    """
    values — отсортированный по возрастанию (по твоему cmp) список значений.
    left_percent — сколько процентов (0–100) элементов (кроме корня)
                   должно уйти в левое поддерево.

    Возвращает список значений в том порядке, в котором их надо вставлять
    в пустое BST, чтобы получить дерево с заданным перекосом.
    """
    vals = list(values)  # на всякий случай, чтобы можно было передавать генераторы и т.п.
    result: List[Any] = []

    def rec(sub: List[Any]) -> None:
        n = len(sub)
        if n == 0:
            return
        if n == 1:
            # один элемент — он и есть корень
            result.append(sub[0])
            return

        # сколько элементов идёт в левое поддерево
        # (из n-1 элементов, не считая корня)
        left_count = (n - 1) * left_percent // 100
        if left_count < 0:
            left_count = 0
        if left_count > n - 1:
            left_count = n - 1

        root_index = left_count
        root = sub[root_index]

        # префиксный обход: сначала корень, потом левая и правая части
        result.append(root)

        left_part = sub[:root_index]
        right_part = sub[root_index + 1:]

        rec(left_part)
        rec(right_part)

    rec(vals)
    return result


def write_order_to_file(filename: str, order: List[Any]) -> None:
    """Записываем последовательность в файл: по одному значению на строку."""
    with open(filename, "w", encoding="utf-8") as f:
        for item in order:
            f.write(f"{item}\n")

import math
def words_gen(numbers):
    temp_str = "str"
    max_len = int(math.log10(max(numbers))) + 1
    words = [ temp_str + f"{num}".rjust(max_len, "0") for num in numbers]
    return words
    

def main():
    
    counts = [ 10, 20, 50, 100, 200, 500, 1000, 5000, 10_000 ]
    ratios = [
            ("100_0", 100),
            ("70_30", 70),
            ("50_50", 50),
            ("30_70", 30),
            ("0_100", 0),
        ]
    
    for N in counts:
        # Сколько элементов хотим в дереве

        # Набор значений. Здесь просто числа 1..N.
        # Если хочешь использовать слова — сделай здесь список строк.
        # values = list(range(1, N + 1))
        values = words_gen(range(1, N + 1))

        # Наборы соотношений (имя для файла, процент левого поддерева)
        
        for name, left_percent in ratios:
            filename = f"bst_{N}_{name}.txt"
            order = gen_bst_order(values, left_percent)
            test_dir_name = "tree_test_file"
            if not os.path.exists(test_dir_name):
                os.mkdir(test_dir_name)
            filepath = f"{test_dir_name}/{filename}"
            write_order_to_file(filepath, order)
            # print(f"{name}: записано {len(order)} элементов в {filename}")
            print(f'"{filepath}",')


if __name__ == "__main__":
    main()