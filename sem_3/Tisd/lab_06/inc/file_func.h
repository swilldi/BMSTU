#ifndef FILE_FUNC_H__
#define FILE_FUNC_H__

#define _GNU_SOURCE

#include <stdio.h>
#include <tree.h>
#include <string.h>


// чтение из файла слов начинающихся на определенный символ
node_t *read_from_file_by_letter(FILE *f, char letter);
// чтение данных из файла в дерево
tree_node *read_from_file_to_tree(FILE *f);

#endif
