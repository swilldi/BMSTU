from random import choices

def random_list(elements_template=range(1, 20), elements_count=10):
    return choices(elements_template, k=elements_count)

for _ in range(4):
    a = random_list()
    print(len(a))
    for el in a:
        print(el)
    print()
