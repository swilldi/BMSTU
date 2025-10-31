#include "test.h"
#include "time.h"
#include "str_func.h"



char test_file_paths[][PATH_LEN] = {
    "files_for_test/test_word_10.txt",
    "files_for_test/test_word_20.txt",
    "files_for_test/test_word_50.txt",
    "files_for_test/test_word_100.txt",
    "files_for_test/test_word_500.txt",
    "files_for_test/test_word_1000.txt",
    "files_for_test/test_word_3000.txt",
    "files_for_test/test_word_5000.txt",
    "files_for_test/test_word_8000.txt",
    "files_for_test/test_word_10000.txt",
    "files_for_test/test_word_100000.txt"

};

// Подсчёт строк в файле
size_t count_lines_in_file(FILE *f)
{
    size_t count = 0;
    char buffer[STR_MAX_LEN];
    while (fgets(buffer, sizeof(buffer), f))
        count++;
    rewind(f);
    return count;
}

// Считывание слов в двумерный массив
char **read_words_from_file(const char *filename, size_t *count)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        return NULL;
    }

    *count = count_lines_in_file(f);
    if (*count == 0) {
        fclose(f);
        return NULL;
    }

    // Выделяем память под массив строк фиксированной длины
    char **words = malloc(*count * sizeof(char *));
    if (!words) {
        fclose(f);
        return NULL;
    }

    for (size_t i = 0; i < *count; i++) {
        words[i] = malloc(STR_MAX_LEN * sizeof(char));
        if (!words[i]) {
            // чистим уже выделенные
            for (size_t j = 0; j < i; j++)
                free(words[j]);
            free(words);
            fclose(f);
            return NULL;
        }

        if (!fgets(words[i], STR_MAX_LEN, f)) {
            words[i][0] = '\0';
        }

        // убираем '\n', если есть
        words[i][strcspn(words[i], "\n")] = '\0';
    }

    fclose(f);
    return words;
}

// Освобождение памяти
void free_words(char **words, size_t count)
{
    for (size_t i = 0; i < count; i++)
        free(words[i]);
    free(words);
}


#define PRE_TEST_COUNT  100
#define MAIN_TEST_COUNT 100
#define STACK_LEN_TEST 100000

error run_static(char **words, size_t n, double *work_time)
{
    error rc; 
    char data[STACK_LEN_TEST][STR_MAX_LEN];
    my_stack_t stack = { .sp = data - 1, .down_p = data };
    char tmp_str[STR_MAX_LEN];


    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        for (size_t i = 0; i < n; i++)
        {
            reverse_str(tmp_str, words[i]);
            rc = push(&stack, tmp_str);
            if (rc != OK)
                return rc;
        }

        for (size_t i = 0; i < n; i++)
        {
            rc = pop(&stack, tmp_str);
            if (rc != OK)
                return rc;
        }
        
    }

    clock_t start, end;
    long long time_res = 0;
    for (size_t i = 0; i < MAIN_TEST_COUNT; i++)
    {
        start = clock();
        for (size_t i = 0; i < n; i++)
        {
            reverse_str(tmp_str, words[i]);
            rc = push(&stack, tmp_str);
            if (rc != OK)
                return rc;
        }

        for (size_t i = 0; i < n; i++)
        {
            rc = pop(&stack, tmp_str);
            if (rc != OK)
                return rc;
        }
        end = clock();
        time_res += end - start;
    }

    *work_time = (double)time_res / MAIN_TEST_COUNT / CLOCKS_PER_SEC;
    return OK;
}

error run_list(char **words, size_t n, double *work_time)
{
    error rc; 
    stack_list_t *stack = NULL;
    char tmp_str[STR_MAX_LEN];

    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        for (size_t i = 0; i < n; i++)
        {
            reverse_str(tmp_str, words[i]);
            rc = push_l(&stack, tmp_str);
            if (rc != OK)
            {
                free_stack_list(stack);
                return rc;
            }
        }

        for (size_t i = 0; i < n; i++)
        {
            rc = pop_l(&stack, tmp_str);
            if (rc != OK)
            {
                free_stack_list(stack);
                return rc;
            }
        }
        
    }

    clock_t start, end;
    long long time_res = 0;
    for (size_t i = 0; i < MAIN_TEST_COUNT; i++)
    {
        start = clock();
        for (size_t i = 0; i < n; i++)
        {
            reverse_str(tmp_str, words[i]);
            rc = push_l(&stack, tmp_str);
            if (rc != OK)
            {
                free_stack_list(stack);
                return rc;
            }
        }

        for (size_t i = 0; i < n; i++)
        {
            rc = pop_l(&stack, tmp_str);
            if (rc != OK)
            {
                free_stack_list(stack);
                return rc;
            }
        }
        end = clock();
        time_res += end - start;
    }

    *work_time = (double)time_res / MAIN_TEST_COUNT / CLOCKS_PER_SEC;
    free_stack_list(stack);
    return OK;
}

error run_tests(void)
{
    // char *words = NULL;
    // size_t size = 0;
    error rc = OK;
    size_t n;
    
    printf(
        "|------------------------------------------------------------------------------------------|\n"
        "|        |     Статический массив     |           Список           |       Результаты      |\n"
        "|   N    |-------------|--------------|-------------|--------------|-----------|-----------|\n"
        "|        |  Время, сек | Память, байт |  Время, сек | Память, байт |   Время   |   Память  |\n"
        "|--------|-------------|--------------|-------------|--------------|-----------|-----------|\n"


    );
    for (size_t i = 0; i < sizeof(test_file_paths) / sizeof(test_file_paths[0]); i++)
    {
        char **words = read_words_from_file(test_file_paths[i], &n);
        if (!words) {
            printf("Ошибка чтения слов из файла\n");
            return 1;
        }
        
        double t_static, t_list;
        long m_static = STACK_LEN_TEST * sizeof(char[STR_MAX_LEN]) + sizeof(my_stack_t);
        long m_list = n * sizeof(stack_list_t);
        double k_mem = (double)(m_static - m_list) / m_static * 100;
        rc = run_static(words, n, &t_static);
        rc = run_list(words, n, &t_list);
        double k_time = (t_list - t_static) / t_list * 100;
        
        printf(
            "| %6lu | %11lf | %12lu | %11lf | %12lu | %8.2lf%% | %8.2lf%% |\n",
            n, t_static, m_static, t_list, m_list, k_time, k_mem
        );
        

        free_words(words, n);
    }
    printf("|------------------------------------------------------------------------------------------|\n");
    return rc;
}
