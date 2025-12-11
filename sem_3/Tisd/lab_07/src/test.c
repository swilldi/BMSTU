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
    "hash_data_collision/10_0.txt",
    "hash_data_collision/10_10.txt",
    "hash_data_collision/10_30.txt",
    "hash_data_collision/10_50.txt",
    "hash_data_collision/10_70.txt",
    "hash_data_collision/10_90.txt",
    "hash_data_collision/20_0.txt",
    "hash_data_collision/20_10.txt",
    "hash_data_collision/20_30.txt",
    "hash_data_collision/20_50.txt",
    "hash_data_collision/20_70.txt",
    "hash_data_collision/20_90.txt",
    "hash_data_collision/50_0.txt",
    "hash_data_collision/50_10.txt",
    "hash_data_collision/50_30.txt",
    "hash_data_collision/50_50.txt",
    "hash_data_collision/50_70.txt",
    "hash_data_collision/50_90.txt",
    "hash_data_collision/100_0.txt",
    "hash_data_collision/100_10.txt",
    "hash_data_collision/100_30.txt",
    "hash_data_collision/100_50.txt",
    "hash_data_collision/100_70.txt",
    "hash_data_collision/100_90.txt",
    "hash_data_collision/200_0.txt",
    "hash_data_collision/200_10.txt",
    "hash_data_collision/200_30.txt",
    "hash_data_collision/200_50.txt",
    "hash_data_collision/200_70.txt",
    "hash_data_collision/200_90.txt",
    "hash_data_collision/500_0.txt",
    "hash_data_collision/500_10.txt",
    "hash_data_collision/500_30.txt",
    "hash_data_collision/500_50.txt",
    "hash_data_collision/500_70.txt",
    "hash_data_collision/500_90.txt",
    "hash_data_collision/1000_0.txt",
    "hash_data_collision/1000_10.txt",
    "hash_data_collision/1000_30.txt",
    "hash_data_collision/1000_50.txt",
    "hash_data_collision/1000_70.txt",
    "hash_data_collision/1000_90.txt",
    "hash_data_collision/5000_0.txt",
    "hash_data_collision/5000_10.txt",
    "hash_data_collision/5000_30.txt",
    "hash_data_collision/5000_50.txt",
    "hash_data_collision/5000_70.txt",
    "hash_data_collision/5000_90.txt",
    "hash_data_collision/10000_0.txt",
    "hash_data_collision/10000_10.txt",
    "hash_data_collision/10000_30.txt",
    "hash_data_collision/10000_50.txt",
    "hash_data_collision/10000_70.txt",
    "hash_data_collision/10000_90.txt",
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

// ============================================================================
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ ЗАМЕРОВ
// ============================================================================


#define MAX_TEST_WORDS 20000
// Количество прогревочных и основных прогонов для замеров
#define WARMUP_RUNS 3
#define MEASURE_RUNS 5

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
    
    // Память элементов в списках: каждый элемент - данные (STR_LEN) плюс память на указатель в списке
    size_t elem_count = hash_table_open_size(table);
    // При коэффициенте 0.7, len примерно = elem_count / 0.7
    size_t approx_len = (elem_count > 0) ? (size_t)(elem_count / OPEN_HASH_TABLE_K) : 0;
    size_t array_size = approx_len * sizeof(node_t *);
    // Память элементов: каждый элемент STR_LEN + размер узла списка
    size_t list_elements_size = elem_count * STR_LEN;
    
    return array_size + list_elements_size;
}

static size_t calculate_hash_table_close_memory(hash_table_close *table)
{
    if (!table)
        return 0;
    
    // Массив ячеек (каждая содержит строку + статус)
    size_t elem_count = hash_table_close_size(table);
    // На основе load factor восстанавливаем размер таблицы
    // len = elem_count / CLOSE_HASH_TABLE_K примерно
    size_t approx_len = (elem_count > 0) ? (size_t)(elem_count / CLOSE_HASH_TABLE_K) : 0;
    
    return approx_len * (STR_LEN + sizeof(int));
}

// ============================================================================
// 2) Оценка эффективности (время построения и время удаления всех элементов)
// ============================================================================

int test_time_del(void)
{
    int n, l, r;
    static char words[MAX_TEST_WORDS][STR_LEN];

    printf(
        "--------------------------------------------------------------------------------------------------------------------------------------\n"
        "| Кол-во элементов| Соотношение |                 Время, мкс                  |                         Память, байт                  |\n"
        "|                 |     BST     |----------------------------------------------------------------------------------------------------|\n"
        "|                 |             |   BST   |   AVL   | Hash open | Hash close |    BST    |    AVL    |   Hash open   |   Hash close  |\n"
        "======================================================================================================================================\n"
    );

    size_t files_count = sizeof(bst_test_file_path) / sizeof(bst_test_file_path[0]);

    for (size_t i = 0; i < files_count; i++)
    {
        if (i != 0 && i % 5 == 0)
            printf("--------------------------------------------------------------------------------------------------------------------------------------\n");

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

            hash_table_open *open_table = file_to_hash_table_open(f);
            fclose(f);

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

            hash_table_close *close_table = file_to_hash_table_close(f);
            fclose(f);

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
            "| %15d | %7d/%3d | %7.3lf | %7.3lf | %9.3lf | %10.3lf | %9lu | %9lu | %13lu | %13lu |\n",
            n, l, r, bst_avg, avl_avg, open_avg, close_avg, bst_memory, avl_memory, open_hash_memory, close_hash_memory
        );
    }

    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");

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
        "--------------------------------------------------------------------------------------------------------------------------------------\n"
        "| Кол-во элементов| Соотношение |              Среднее время поиска, мкс     |                         Память, байт                  |\n"
        "|                 |     BST     |----------------------------------------------------------------------------------------------------|\n"
        "|                 |             |   BST   |   AVL   | Hash open | Hash close |    BST    |    AVL    |   Hash open   |   Hash close  |\n"
        "======================================================================================================================================\n"
    );

    size_t files_count = sizeof(bst_test_file_path) / sizeof(bst_test_file_path[0]);

    for (size_t i = 0; i < files_count; i++)
    {
        if (i != 0 && i % 5 == 0)
            printf("--------------------------------------------------------------------------------------------------------------------------------------\n");

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

            hash_table_open *open_table = file_to_hash_table_open(f);
            fclose(f);

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

            hash_table_close *close_table = file_to_hash_table_close(f);
            fclose(f);

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
            "| %15d | %7d/%3d | %7.3lf | %7.3lf | %9.3lf | %10.3lf | %9lu | %9lu | %13lu | %13lu |\n",
            n, l, r, bst_avg, avl_avg, open_avg, close_avg, bst_memory, avl_memory, open_hash_memory, close_hash_memory
        );
    }

    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");

    return OK;
}


// ============================================================================
// 3) Тест эффективности с разными процентами коллизий (простая хэш-функция)
// ============================================================================

int test_hash_efficiency_collision(void)
{
    int count, collision_percent;
    static char words[MAX_TEST_WORDS][STR_LEN];

    printf(
        "=======================================================================\n"
        "| Кол-во элементов| Процент коллизий |       Время поиска, мкс        |\n"
        "|                 |                  |--------------------------------|\n"
        "|                 |                  |    Открытое    |    Закрытое   |\n"
        "=======================================================================\n"
    );

    size_t files_count = sizeof(hash_collision_test_file_path) / sizeof(hash_collision_test_file_path[0]);

    for (size_t i = 0; i < files_count; i++)
    {
        if (i != 0 && i % 6 == 0)
            printf("-----------------------------------------------------------------------\n");

        get_collision_file_info(hash_collision_test_file_path[i], &count, &collision_percent);

        size_t word_count = load_words_from_file(hash_collision_test_file_path[i],
                                                 words, MAX_TEST_WORDS);
        if (word_count == 0)
            continue;

        double open_time_sum = 0.0;
        double close_time_sum = 0.0;

        clock_t start, end;

        for (int run = 0; run < WARMUP_RUNS + MEASURE_RUNS; run++)
        {
            int do_measure = (run >= WARMUP_RUNS);

            // ----------- ОТКРЫТОЕ ХЭШИРОВАНИЕ (простая функция) -----------
            FILE *f = fopen(hash_collision_test_file_path[i], "r");
            if (!f)
                continue;

            hash_table_open *open_table = file_to_hash_table_open_simple(f);
            fclose(f);

            start = clock();
            for (size_t k = 0; k < word_count; k++)
                (void)hash_table_open_contain_simple(open_table, words[k]);
            end = clock();

            double t_search_open = ticks_to_us(start, end) / word_count;

            if (do_measure)
            {
                open_time_sum += t_search_open;
            }

            hash_table_open_destroy(open_table);

            // ----------- ЗАКРЫТОЕ ХЭШИРОВАНИЕ (простая функция) -----------
            f = fopen(hash_collision_test_file_path[i], "r");
            if (!f)
                continue;

            hash_table_close *close_table = file_to_hash_table_close_simple(f);
            fclose(f);

            start = clock();
            for (size_t k = 0; k < word_count; k++)
                (void)hash_table_close_contain_simple(close_table, words[k]);
            end = clock();

            double t_search_close = ticks_to_us(start, end) / word_count;

            if (do_measure)
            {
                close_time_sum += t_search_close;
            }

            hash_table_close_destroy(close_table);
        }

        double open_time_avg  = open_time_sum  / MEASURE_RUNS;
        double close_time_avg = close_time_sum / MEASURE_RUNS;

        printf(
            "| %15d | %15d%% | %14.4lf | %12.4lf |\n",
            count, collision_percent, open_time_avg, close_time_avg
        );
    }

    printf("=======================================================================\n");

    return OK;
}
