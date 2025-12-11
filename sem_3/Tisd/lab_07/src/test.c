





















#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "exit_code.h"
#include "common_define.h"

#include "avl_tree.h"
#include "bin_search_tree.h"
#include "hash_table_close.h"
#include "hash_table_open.h"
#include "import_data.h"


char *bst_test_file_path[] = 
{
    "tree_test_file/bst_10_100_0.txt",
    "tree_test_file/bst_10_70_30.txt",
    "tree_test_file/bst_10_50_50.txt",
    "tree_test_file/bst_10_30_70.txt",
    "tree_test_file/bst_10_0_100.txt",
    "tree_test_file/bst_20_100_0.txt",
    "tree_test_file/bst_20_70_30.txt",
    "tree_test_file/bst_20_50_50.txt",
    "tree_test_file/bst_20_30_70.txt",
    "tree_test_file/bst_20_0_100.txt",
    "tree_test_file/bst_50_100_0.txt",
    "tree_test_file/bst_50_70_30.txt",
    "tree_test_file/bst_50_50_50.txt",
    "tree_test_file/bst_50_30_70.txt",
    "tree_test_file/bst_50_0_100.txt",
    "tree_test_file/bst_100_100_0.txt",
    "tree_test_file/bst_100_70_30.txt",
    "tree_test_file/bst_100_50_50.txt",
    "tree_test_file/bst_100_30_70.txt",
    "tree_test_file/bst_100_0_100.txt",
    "tree_test_file/bst_200_100_0.txt",
    "tree_test_file/bst_200_70_30.txt",
    "tree_test_file/bst_200_50_50.txt",
    "tree_test_file/bst_200_30_70.txt",
    "tree_test_file/bst_200_0_100.txt",
    "tree_test_file/bst_500_100_0.txt",
    "tree_test_file/bst_500_70_30.txt",
    "tree_test_file/bst_500_50_50.txt",
    "tree_test_file/bst_500_30_70.txt",
    "tree_test_file/bst_500_0_100.txt",
    "tree_test_file/bst_1000_100_0.txt",
    "tree_test_file/bst_1000_70_30.txt",
    "tree_test_file/bst_1000_50_50.txt",
    "tree_test_file/bst_1000_30_70.txt",
    "tree_test_file/bst_1000_0_100.txt",
    "tree_test_file/bst_5000_100_0.txt",
    "tree_test_file/bst_5000_70_30.txt",
    "tree_test_file/bst_5000_50_50.txt",
    "tree_test_file/bst_5000_30_70.txt",
    "tree_test_file/bst_5000_0_100.txt",
    "tree_test_file/bst_10000_100_0.txt",
    "tree_test_file/bst_10000_70_30.txt",
    "tree_test_file/bst_10000_50_50.txt",
    "tree_test_file/bst_10000_30_70.txt",
    "tree_test_file/bst_10000_0_100.txt",
};

void get_file_info(char *filename, int *n, int *l, int *r)
{
    char *temp_str = strdup(filename);
    char *info = strtok(temp_str, "_");
    info = strtok(NULL, "_");
    info = strtok(NULL, "_");

    info = strtok(NULL, "_");
    *n = atol(info);
    info = strtok(NULL, "_");
    *l = atol(info);
    info = strtok(NULL, "_");
    *r = atol(info);

    free(temp_str);
}

int test_avg_cmp(void)
{
    int n, l, r;

    printf(
        "-------------------------------------------------------------------------------------------------------------------\n"
        "| Кол-во элементов| Соотношение бин.дерева | Бин. дерево | Баланс. дерево | Открытое хэшир.-е | Закрытое хэшир.-е |\n"
        "-------------------------------------------------------------------------------------------------------------------\n"
    );
    for (size_t i = 0; i < sizeof(bst_test_file_path) / sizeof(bst_test_file_path[0]); i++)
    {
        if (i != 0 && i % 5 == 0)
            printf("-------------------------------------------------------------------------------------------------------------------\n");
        FILE *f = fopen(bst_test_file_path[i], "r");
        get_file_info(bst_test_file_path[i], &n, &l, &r);
        // printf("%d %d %d\n", n, l, r);

        // создание данных
        bin_tree_node *bin_tree = file_to_bin_tree(f);
        avl_tree_node *avl_tree = file_to_avl_tree(f);
        hash_table_open *open_table = file_to_hash_table_open(f);
        hash_table_close *close_table = file_to_hash_table_close(f);
        fclose(f);
        
        // Средние количества для деревьев
        double avg_cmp_bin_tree = bin_tree_avg_cmp(bin_tree, TEST_COUNT_FOR_AVG_CMP);
        double avg_cmp_avl_tree = avl_tree_avg_cmp(avl_tree, TEST_COUNT_FOR_AVG_CMP);
        double avg_cmp_open_hash = hash_table_open_avg_cmp(open_table, TEST_COUNT_FOR_AVG_CMP);
        double avg_cmp_close_hash = hash_table_close_avg_cmp(close_table, TEST_COUNT_FOR_AVG_CMP);

        // освобождение памяти
        bin_tree_destroy(bin_tree);
        avl_tree_destroy(avl_tree);
        hash_table_open_destroy(open_table);
        hash_table_close_destroy(close_table);

        // вывод информации
        printf(
            "| %15d | %17d/%3d | %12.3lf | %14.3lf | %17.3lf | %17.3lf |\n",
            n, l, r, avg_cmp_bin_tree, avg_cmp_avl_tree, avg_cmp_open_hash, avg_cmp_close_hash            
        );
    }
    printf("-------------------------------------------------------------------------------------------------------------------\n");

        
    return OK;
}
