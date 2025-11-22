import random
import math
import sys
sys.setrecursionlimit(10000)  # например, устанавливает лимит в 10000



# def tree_list(words, left):
#     lw = []
#     rw = []
    
#     mid_i = int(len(words) * left / 100)
#     i = 0
#     # левая часть
#     while (i < mid_i):
#         lw.append(words[i])
#         i += 1
    
#     i += 1
#     # правая часть
#     while (i < len(words)):
#         rw.append(words[i])
#         i += 1
        
#     random.shuffle(lw)
#     random.shuffle(rw)
        
#     return [words[mid_i]] + lw + rw
    

# left_percent = 99
# words = list_generate(11)
# tlist = tree_list(words, left_percent)

# f = open("t.txt", "w")
# for value in tlist:
#     f.write(f"{value}\n")
# f.close()



class TreeNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def insert_balanced(arr, branch_bias):
    '''
    arr - упорядоченный массив
    branch_bias - от 0 (всё слева) до 100 (всё справа), 50 - стабилизированное дерево
    '''
    if not arr:
        return None
    if branch_bias <= 0:
        root_index = 0
    elif branch_bias >= 100:
        root_index = len(arr) - 1
    else:
        bias = branch_bias / 100.0
        root_index = int(round((len(arr) - 1) * bias))
    root = TreeNode(arr[root_index])
    root.left = insert_balanced(arr[:root_index], branch_bias)
    root.right = insert_balanced(arr[root_index+1:], branch_bias)
    return root

def preorder_write(node, out_lines):
    if node is None:
        return
    out_lines.append(str(node.value))
    preorder_write(node.left, out_lines)
    preorder_write(node.right, out_lines)

def generate_tree_file(filename, arr, branch_bias):
    '''
    filename - строка, имя файла для сохранения
    arr - упорядоченный массив
    branch_bias - от 0 до 100
    '''
    tree = insert_balanced(arr, branch_bias)
    out_lines = []
    preorder_write(tree, out_lines)
    out_lines = list(map(lambda x: str(x).rjust(2, "0"), out_lines))
    with open(filename, 'w', encoding="utf-8") as f:
        f.write('\n'.join(out_lines))
        f.write('\n')
        
def list_generate(n):
    words = []
    max_len = int(math.log10(n)) + 1
    for i in range(1, n + 1):
        words.append(f"str{str(i).rjust(max_len, "0")}")
    return words

# Пример использования:
arr = list(range(1, 16))
generate_tree_file('tree.txt', arr, 50) # сбалансированное дерево
generate_tree_file('tree_left.txt', arr, 0) # всё влево
generate_tree_file('tree_right.txt', arr, 100) # всё вправо
generate_tree_file('tree_70.txt', arr, 70) # всё вправо



elem_counts = [10, 20, 50, 100, 500, 1000, 5000]
balanses = [0, 20, 50, 70, 100]

f = open("paths.txt", "w")
for elem in elem_counts:
    for b in balanses:
        arr = list_generate(elem)
        generate_tree_file(f"test_trees/tree_{elem}_{b}.txt", arr, b)
        f.write(f"\"test_trees/tree_{elem}_{b}.txt\",\n")
        
