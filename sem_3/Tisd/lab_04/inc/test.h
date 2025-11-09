#include "stack_type.h"
#include "stack_func.h"
#include "stack_list_func.h"
#include <stdio.h>
#include "io_func.h"
#include <stdio.h>
#include "exit_code.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 128  // максимально допустимая длина слова

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Подсчёт строк в файле
size_t count_lines_in_file(FILE *f);

// Считывание слов в двумерный массив
char **read_words_from_file(const char *filename, size_t *count);

// Освобождение памяти
void free_words(char **words, size_t count);

#define PATH_LEN 128

error run_tests(void);
