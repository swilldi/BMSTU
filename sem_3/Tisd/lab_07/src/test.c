#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "exit_code.h"
#include "common_define.h"
#include "io_func.h"
#include <time.h>

#include "compare_func.h"
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

char *hash_collision_test_file_path[] =
{
    "collision_data/words_100_0.txt",
    "collision_data/words_100_10.txt",
    "collision_data/words_100_50.txt",
    "collision_data/words_100_100.txt",
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

// Парсинг имён файлов вида: hash_data_collision/10_0.txt -> n=10, collision_percent=0
void get_collision_file_info(char *filename, int *count, int *collision_percent)
{
    char *temp_str = strdup(filename);
    char *info = strtok(temp_str, "/");
    info = strtok(NULL, "/");
    
    // Парсим "10_0.txt"
    char *count_str = strtok(info, "_");
    *count = atol(count_str);
    
    char *collision_str = strtok(NULL, ".");
    *collision_percent = atol(collision_str);
    
    free(temp_str);
}

int test_avg_cmp(void)
{
    int n, l, r;

    printf(
        "-------------------------------------------------------------------------------------------------------------\n"
        "| Кол-во элементов| Соотношение BST |    BST    |    AVL    |  Open + R | Open - R  | Close + R | Close - R |\n"
        "-------------------------------------------------------------------------------------------------------------\n"
    );
    for (size_t i = 0; i < sizeof(bst_test_file_path) / sizeof(bst_test_file_path[0]); i++)
    {
        if (i != 0 && i % 5 == 0)
            printf("-------------------------------------------------------------------------------------------------------------\n");
        FILE *f = fopen(bst_test_file_path[i], "r");
        if (!f)
            continue;
        get_file_info(bst_test_file_path[i], &n, &l, &r);

        // создание данных
        bin_tree_node *bin_tree = file_to_bin_tree(f);
        avl_tree_node *avl_tree = file_to_avl_tree(f);
        hash_table_open *open_table = file_to_hash_table_open_test(f, get_str_hash);
        hash_table_close *close_table = file_to_hash_table_close_test(f, get_str_hash);
        hash_table_open *open_table_no_rest = file_to_hash_table_open_no_rest(f, get_str_hash);
        hash_table_close *close_table_no_rest = file_to_hash_table_close_no_rest(f, get_str_hash);
        fclose(f);

        if (!bin_tree || !avl_tree || !open_table || !close_table ||
            !open_table_no_rest || !close_table_no_rest)
        {
            bin_tree_destroy(bin_tree);
            avl_tree_destroy(avl_tree);
            hash_table_open_destroy(open_table);
            hash_table_close_destroy(close_table);
            hash_table_open_destroy(open_table_no_rest);
            hash_table_close_destroy(close_table_no_rest);
            continue;
        }
        
        // Средние количества для деревьев
        double avg_cmp_bin_tree = bin_tree_avg_cmp(bin_tree, TEST_COUNT_FOR_AVG_CMP);
        double avg_cmp_avl_tree = avl_tree_avg_cmp(avl_tree, TEST_COUNT_FOR_AVG_CMP);
        double avg_cmp_open_hash = hash_table_open_avg_cmp(open_table);
        double avg_cmp_close_hash = hash_table_close_avg_cmp(close_table);
        double avg_cmp_open_hash_no_rest = hash_table_open_avg_cmp(open_table_no_rest);
        double avg_cmp_close_hash_no_rest = hash_table_close_avg_cmp(close_table_no_rest);

        // освобождение памяти
        bin_tree_destroy(bin_tree);
        avl_tree_destroy(avl_tree);
        hash_table_open_destroy(open_table);
        hash_table_close_destroy(close_table);
        hash_table_open_destroy(open_table_no_rest);
        hash_table_close_destroy(close_table_no_rest);

        // вывод информации
        printf(
            "| %15d | %11d/%3d | %9.2lf | %9.2lf | %9.2lf | %9.2lf | %9.2lf | %9.2lf |\n",
            n, l, r, 
            avg_cmp_bin_tree, avg_cmp_avl_tree, 
            avg_cmp_open_hash, avg_cmp_open_hash_no_rest,
            avg_cmp_close_hash, avg_cmp_close_hash_no_rest
        );
    }
    printf("-------------------------------------------------------------------------------------------------------------\n");

    return OK;
}

// ============================================================================
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ ЗАМЕРОВ
// ============================================================================


#define MAX_TEST_WORDS 20000
// Количество прогревочных и основных прогонов для замеров
#define WARMUP_RUNS 10
#define MEASURE_RUNS 10

static size_t load_words_from_file(const char *filename,
                                   char words[][STR_LEN],
                                   size_t max_count)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        return 0;

    size_t count = 0;
    while (count < max_count && fscanf(f, "%s", words[count]) == 1)
        count++;

    fclose(f);
    return count;
}

// static double ticks_to_ms(clock_t start, clock_t end)
// {
//     return (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
// }

static double ticks_to_us(clock_t start, clock_t end)
{
    return (double)(end - start) * 1000000.0 / CLOCKS_PER_SEC;
}

// ============================================================================
// ФУНКЦИИ ДЛЯ РАСЧЕТА ПОТРЕБЛЯЕМОЙ ПАМЯТИ
// ============================================================================

static size_t count_bst_nodes(bin_tree_node *node)
{
    if (!node)
        return 0;
    return 1 + count_bst_nodes(bin_tree_left_child(node)) + 
             count_bst_nodes(bin_tree_right_child(node));
}

static size_t calculate_bst_memory(bin_tree_node *tree)
{
    if (!tree)
        return 0;
    
    // Каждый узел: STR_LEN байт (value) + 2 указателя (8 байт каждый на 64-bit системе)
    size_t node_count = count_bst_nodes(tree);
    return node_count * (STR_LEN + 2 * sizeof(bin_tree_node *));
}

static size_t count_avl_nodes(avl_tree_node *node)
{
    if (!node)
        return 0;
    return 1 + count_avl_nodes(avl_tree_left_child(node)) + 
             count_avl_nodes(avl_tree_right_child(node));
}

static size_t calculate_avl_memory(avl_tree_node *tree)
{
    if (!tree)
        return 0;
    
    // Каждый узел: STR_LEN байт (value) + 2 указателя + 1 int (высота)
    size_t node_count = count_avl_nodes(tree);
    return node_count * (STR_LEN + 2 * sizeof(avl_tree_node *) + sizeof(int));
}

static size_t calculate_hash_table_open_memory(hash_table_open *table)
{
    if (!table)
        return 0;
    
    size_t elem_count = hash_table_open_size(table);
    size_t capacity   = hash_table_open_capacity(table);

    size_t array_size = capacity * sizeof(node_t *);
    size_t list_elements_size = elem_count * list_node_size();

    return array_size + list_elements_size;
}

static size_t calculate_hash_table_close_memory(hash_table_close *table)
{
    if (!table)
        return 0;
    
    size_t capacity = hash_table_close_capacity(table);

    return capacity * hash_table_close_cell_size();
}

// ============================================================================
// 2) Оценка эффективности (время построения и время удаления всех элементов)
// ============================================================================

int test_time_del(void)
{
    int n, l, r;
    static char words[MAX_TEST_WORDS][STR_LEN];

    printf(
        "-----------------------------------------------------------------------------------------------------------------------------------\n"
        "| Кол-во элементов| Соотношение |                 Время, мкс                  |                  Память, байт                     |\n"
        "|                 |     BST     |-------------------------------------------------------------------------------------------------|\n"
        "|                 |             |    BST    |    AVL    |   Open   |   Close  |    BST    |    AVL    |     Open    |    Close    |\n"
        "===================================================================================================================================\n"
    );

    size_t files_count = sizeof(bst_test_file_path) / sizeof(bst_test_file_path[0]);

    for (size_t i = 0; i < files_count; i++)
    {
        if (i != 0 && i % 5 == 0)
            printf("-----------------------------------------------------------------------------------------------------------------------------------\n");

        get_file_info(bst_test_file_path[i], &n, &l, &r);

        size_t word_count = load_words_from_file(bst_test_file_path[i],
                                                 words, MAX_TEST_WORDS);
        if (word_count == 0)
            continue;

        double bst_sum = 0.0;
        double avl_sum = 0.0;
        double open_sum = 0.0;
        double close_sum = 0.0;
        
        size_t bst_memory = 0;
        size_t avl_memory = 0;
        size_t open_hash_memory = 0;
        size_t close_hash_memory = 0;

        clock_t start, end;

        for (int run = 0; run < WARMUP_RUNS + MEASURE_RUNS; run++)
        {
            int do_measure = (run >= WARMUP_RUNS);

            // ----------------- BST -----------------
            FILE *f = fopen(bst_test_file_path[i], "r");
            if (!f)
                continue;

            bin_tree_node *bin_tree = file_to_bin_tree(f);
            fclose(f);
            if (!bin_tree)
                continue;

            if (do_measure)
                bst_memory = calculate_bst_memory(bin_tree);

            start = clock();
            for (size_t k = 0; k < word_count; k++)
                bin_tree = bin_tree_remove(bin_tree, words[k], cmp_str);
            end = clock();

            if (do_measure)
                bst_sum += ticks_to_us(start, end);

            bin_tree_destroy(bin_tree);

            // ----------------- AVL -----------------
            f = fopen(bst_test_file_path[i], "r");
            if (!f)
                continue;

            avl_tree_node *avl_tree = file_to_avl_tree(f);
            fclose(f);
            if (!avl_tree)
                continue;

            if (do_measure)
                avl_memory = calculate_avl_memory(avl_tree);

            start = clock();
            for (size_t k = 0; k < word_count; k++)
                avl_tree = avl_tree_remove(avl_tree, words[k], cmp_str);
            end = clock();

            if (do_measure)
                avl_sum += ticks_to_us(start, end);

            avl_tree_destroy(avl_tree);

            // ------------- Hash table (open) -------------
            f = fopen(bst_test_file_path[i], "r");
            if (!f)
                continue;

            hash_table_open *open_table = file_to_hash_table_open_test(f, get_str_hash);
            fclose(f);
            if (!open_table)
                continue;

            if (do_measure)
                open_hash_memory = calculate_hash_table_open_memory(open_table);

            start = clock();
            for (size_t k = 0; k < word_count; k++)
                hash_table_open_del(open_table, words[k]);
            end = clock();

            if (do_measure)
                open_sum += ticks_to_us(start, end);

            hash_table_open_destroy(open_table);

            // ------------- Hash table (close) -------------
            f = fopen(bst_test_file_path[i], "r");
            if (!f)
                continue;

            hash_table_close *close_table = file_to_hash_table_close_test(f, get_str_hash);
            fclose(f);
            if (!close_table)
                continue;

            if (do_measure)
                close_hash_memory = calculate_hash_table_close_memory(close_table);

            start = clock();
            for (size_t k = 0; k < word_count; k++)
                hash_table_close_del(close_table, words[k]);
            end = clock();

            if (do_measure)
                close_sum += ticks_to_us(start, end);

            hash_table_close_destroy(close_table);
        }

        double bst_avg   = bst_sum   / MEASURE_RUNS;
        double avl_avg   = avl_sum   / MEASURE_RUNS;
        double open_avg  = open_sum  / MEASURE_RUNS;
        double close_avg = close_sum / MEASURE_RUNS;

        printf(
            "| %15d | %7d/%3d | %9.1lf | %9.1lf | %8.1lf | %8.1lf | %9lu | %9lu | %11lu | %11lu |\n",
            n, l, r, bst_avg, avl_avg, open_avg, close_avg, bst_memory, avl_memory, open_hash_memory, close_hash_memory
        );
    }

    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");

    return OK;
}

// ============================================================================
// 2б) Оценка эффективности поиска (среднее время поиска одного элемента)
// ============================================================================

int test_time_search(void)
{
    int n, l, r;
    static char words[MAX_TEST_WORDS][STR_LEN];

    printf(
        "-----------------------------------------------------------------------------------------------------------------------------------\n"
        "| Кол-во элементов| Соотношение |                 Время, мкс                  |                  Память, байт                     |\n"
        "|                 |     BST     |-------------------------------------------------------------------------------------------------|\n"
        "|                 |             |    BST    |    AVL    |   Open   |   Close  |    BST    |    AVL    |     Open    |    Close    |\n"
        "===================================================================================================================================\n"
    );

    size_t files_count = sizeof(bst_test_file_path) / sizeof(bst_test_file_path[0]);

    for (size_t i = 0; i < files_count; i++)
    {
        if (i != 0 && i % 5 == 0)
            printf("-----------------------------------------------------------------------------------------------------------------------------------\n");

        get_file_info(bst_test_file_path[i], &n, &l, &r);

        size_t word_count = load_words_from_file(bst_test_file_path[i],
                                                 words, MAX_TEST_WORDS);
        if (word_count == 0)
            continue;

        double bst_sum = 0.0;
        double avl_sum = 0.0;
        double open_sum = 0.0;
        double close_sum = 0.0;
        
        size_t bst_memory = 0;
        size_t avl_memory = 0;
        size_t open_hash_memory = 0;
        size_t close_hash_memory = 0;

        clock_t start, end;

        for (int run = 0; run < WARMUP_RUNS + MEASURE_RUNS; run++)
        {
            int do_measure = (run >= WARMUP_RUNS);

            // ----------------- BST -----------------
            FILE *f = fopen(bst_test_file_path[i], "r");
            if (!f)
                continue;

            bin_tree_node *bin_tree = file_to_bin_tree(f);
            fclose(f);
            if (!bin_tree)
                continue;

            if (do_measure)
                bst_memory = calculate_bst_memory(bin_tree);

            start = clock();
            for (size_t k = 0; k < word_count; k++)
                (void)bin_tree_lookup(bin_tree, words[k], cmp_str);
            end = clock();

            if (do_measure)
                bst_sum += ticks_to_us(start, end);

            bin_tree_destroy(bin_tree);

            // ----------------- AVL -----------------
            f = fopen(bst_test_file_path[i], "r");
            if (!f)
                continue;

            avl_tree_node *avl_tree = file_to_avl_tree(f);
            fclose(f);
            if (!avl_tree)
                continue;

            if (do_measure)
                avl_memory = calculate_avl_memory(avl_tree);

            start = clock();
            for (size_t k = 0; k < word_count; k++)
                (void)avl_tree_lookup(avl_tree, words[k], cmp_str);
            end = clock();

            if (do_measure)
                avl_sum += ticks_to_us(start, end);

            avl_tree_destroy(avl_tree);

            // ------------- Hash table (open) -------------
            f = fopen(bst_test_file_path[i], "r");
            if (!f)
                continue;

            hash_table_open *open_table = file_to_hash_table_open_test(f, get_str_hash);
            fclose(f);
            if (!open_table)
                continue;

            if (do_measure)
                open_hash_memory = calculate_hash_table_open_memory(open_table);

            start = clock();
            for (size_t k = 0; k < word_count; k++)
                (void)hash_table_open_contain(open_table, words[k]);
            end = clock();

            if (do_measure)
                open_sum += ticks_to_us(start, end);

            hash_table_open_destroy(open_table);

            // ------------- Hash table (close) -------------
            f = fopen(bst_test_file_path[i], "r");
            if (!f)
                continue;

            hash_table_close *close_table = file_to_hash_table_close_test(f, get_str_hash);
            fclose(f);
            if (!close_table)
                continue;

            if (do_measure)
                close_hash_memory = calculate_hash_table_close_memory(close_table);

            start = clock();
            for (size_t k = 0; k < word_count; k++)
                (void)hash_table_close_contain(close_table, words[k]);
            end = clock();

            if (do_measure)
                close_sum += ticks_to_us(start, end);

            hash_table_close_destroy(close_table);
        }

        double bst_avg   = (bst_sum   / MEASURE_RUNS) / word_count;
        double avl_avg   = (avl_sum   / MEASURE_RUNS) / word_count;
        double open_avg  = (open_sum  / MEASURE_RUNS) / word_count;
        double close_avg = (close_sum / MEASURE_RUNS) / word_count;

        printf(
            "| %15d | %7d/%3d | %9.3lf | %9.3lf | %8.3lf | %8.3lf | %9lu | %9lu | %11lu | %11lu |\n",
            n, l, r, bst_avg, avl_avg, open_avg, close_avg, bst_memory, avl_memory, open_hash_memory, close_hash_memory
        );
    }

    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");

    return OK;
}


// ============================================================================
// 3) Тест эффективности с разными процентами коллизий (простая хэш-функция)
// ============================================================================

// int test_hash_efficiency_collision(void)
// {
//     int n, percent;
//     static char words[MAX_TEST_WORDS][STR_LEN];

//     printf(
//         "--------------------------------------------------------------------------------------------------------------------------------------------\n"
//         "|  Количество     |  Процент    |                            Количество сравнений     |                    Время работы, мкс                |\n"
//         "|  элементов      |  данных     |-----------------------------------------------------------------------------------------------------------|\n"
//         "|                 |  коллизий   |  Open + R  |  Open - R  |  Close + R  |  Close - R  |  Open + R  |  Open - R  |  Close + R  |  Close - R  |\n"
//         "=============================================================================================================================================\n"
//     );

//     size_t files_count = sizeof(hash_collision_test_file_path) / sizeof(hash_collision_test_file_path[0]);

//     for (size_t i = 0; i < files_count; i++)
//     {
//         get_collision_file_info(hash_collision_test_file_path[i], &n, &percent);

//         size_t word_count = load_words_from_file(hash_collision_test_file_path[i], words, MAX_TEST_WORDS);
//         if (word_count == 0)
//             continue;

//         FILE *f = fopen(hash_collision_test_file_path[i], "r");
//         if (!f)
//             continue;

//         hash_table_open *open_table = file_to_hash_table_open_test(f, get_str_hash);
//         hash_table_open *open_table_no_rest = file_to_hash_table_open_no_rest(f, get_str_hash);
//         hash_table_close *close_table = file_to_hash_table_close_test(f, get_str_hash);
//         hash_table_close *close_table_no_rest = file_to_hash_table_close_no_rest(f, get_str_hash);
//         fclose(f);

//         if (!open_table || !open_table_no_rest || !close_table || !close_table_no_rest)
//         {
//             hash_table_open_destroy(open_table);
//             hash_table_open_destroy(open_table_no_rest);
//             hash_table_close_destroy(close_table);
//             hash_table_close_destroy(close_table_no_rest);
//             continue;
//         }

//         double avg_count_open = hash_table_open_avg_cmp(open_table);
//         double avg_count_open_no_rest = hash_table_open_avg_cmp(open_table_no_rest);
//         double avg_count_close = hash_table_close_avg_cmp(close_table);
//         double avg_count_close_no_rest = hash_table_close_avg_cmp(close_table_no_rest);

//         double avg_time_open = 0.0;
//         double avg_time_open_no_rest = 0.0;
//         double avg_time_close = 0.0;
//         double avg_time_close_no_rest = 0.0;

//         for (int run = 0; run < WARMUP_RUNS + MEASURE_RUNS; run++)
//         {
//             int do_measure = (run >= WARMUP_RUNS);
//             clock_t start, end;

//             start = clock();
//             for (size_t k = 0; k < word_count; k++)
//                 (void)hash_table_open_contain(open_table, words[k]);
//             end = clock();
//             if (do_measure)
//                 avg_time_open += ticks_to_us(start, end);

//             start = clock();
//             for (size_t k = 0; k < word_count; k++)
//                 (void)hash_table_open_contain(open_table_no_rest, words[k]);
//             end = clock();
//             if (do_measure)
//                 avg_time_open_no_rest += ticks_to_us(start, end);

//             start = clock();
//             for (size_t k = 0; k < word_count; k++)
//                 (void)hash_table_close_contain(close_table, words[k]);
//             end = clock();
//             if (do_measure)
//                 avg_time_close += ticks_to_us(start, end);

//             start = clock();
//             for (size_t k = 0; k < word_count; k++)
//                 (void)hash_table_close_contain(close_table_no_rest, words[k]);
//             end = clock();
//             if (do_measure)
//                 avg_time_close_no_rest += ticks_to_us(start, end);
//         }

//         avg_time_open = (avg_time_open / MEASURE_RUNS) / word_count;
//         avg_time_open_no_rest = (avg_time_open_no_rest / MEASURE_RUNS) / word_count;
//         avg_time_close = (avg_time_close / MEASURE_RUNS) / word_count;
//         avg_time_close_no_rest = (avg_time_close_no_rest / MEASURE_RUNS) / word_count;

//         printf(
//             "| %15d | %11d%% | %10.2lf | %10.2lf | %11.2lf | %11.2lf | %10.2lf | %10.2lf | %11.2lf | %11.2lf |\n",
//             n, percent,
//             avg_count_open, avg_count_open_no_rest,
//             avg_count_close, avg_count_close_no_rest,
//             avg_time_open, avg_time_open_no_rest,
//             avg_time_close, avg_time_close_no_rest
//         );

//         hash_table_open_destroy(open_table);
//         hash_table_open_destroy(open_table_no_rest);
//         hash_table_close_destroy(close_table);
//         hash_table_close_destroy(close_table_no_rest);
//     }

//     printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");

//     return OK;
// }

int test_hash_efficiency_collision(void)
{
        char words[MAX_TEST_WORDS][STR_LEN];
        char *filepath = "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_07/collision_data/words_100_50.txt";
        size_t word_count = load_words_from_file(filepath, words, MAX_TEST_WORDS);
        if (word_count == 0)
            return 1;

        FILE *f = fopen(filepath, "r");
        hash_table_open *open_table_no_rest = file_to_hash_table_open_no_rest(f, get_str_hash);
        hash_table_close *close_table_no_rest = file_to_hash_table_close_no_rest(f, get_str_hash);
        fclose(f);  

        (void) close_table_no_rest;

        printf("Среднее кол-во сравнений: %lf\nРазмер: %lu", hash_table_open_avg_cmp(open_table_no_rest), hash_table_open_capacity(open_table_no_rest)); 

        hash_table_open_restructuring(&open_table_no_rest);
        hash_table_open_restructuring(&open_table_no_rest);

        printf("\n");
        // hash_table_open_print(open_table_no_rest);

        printf("Среднее кол-во сравнений: %lf\nРазмер: %lu\n", hash_table_open_avg_cmp(open_table_no_rest), hash_table_open_capacity(open_table_no_rest)); 


        printf("");
        return 1;
}
