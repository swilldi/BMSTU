#define _GNU_SOURCE
#include <stdio.h>
#include <tree.h>
#include <string.h>

// чтение из файла слов начинающихся на определенный символ
node_t *read_from_file_by_letter(FILE *f, char letter)
{
    char *tmp_str = NULL;
    node_t *list = NULL;
    node_t *tmp_node = NULL;

    size_t len;
    ssize_t s = getline(&tmp_str, &len, f);
    while (s != -1)
    {
        tmp_str[strlen(tmp_str) - 1] = '\0';
        if (tmp_str[0] == letter)
        {
            tmp_node = create_node(tmp_str);
            list = add_node(list, tmp_node);
        }
        s = getline(&tmp_str, &len, f);
    }

    return list;
}

// чтение данных из файла в дерево
tree_node *read_from_file_to_tree(FILE *f)
{
    char *tmp_str = NULL;
    tree_node *tree = NULL;
    tree_node *tmp_node = NULL;

    size_t len;
    ssize_t s = getline(&tmp_str, &len, f);
    while (s != -1)
    {
        tmp_str[strlen(tmp_str) - 1] = '\0';
        tmp_node = tree_node_create(tmp_str);
        tree = tree_insert(tree, tmp_node);
        s = getline(&tmp_str, &len, f);
    }
    free(tmp_str);

    return tree;
}
