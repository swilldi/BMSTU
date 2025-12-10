#include <stdio.h>

#include <stdlib.h>

#include "common_define.h"
#include "export_data.h"
#include "import_data.h"
#include "io_func.h"
#include "hash_type.h"
#include "hash_table_emulate.h"
#include "tree_emulate.h"

int main(void)
{
    // run_emulate_tree();
    run_emulate_hash_table();
}


#if 0
int main(void)
{
    // hash_table_open *table = hash_table_open_create(10);
    // table = hash_table_open_add(table, "123");
    // table = hash_table_open_add(table, "420");
    // table = hash_table_open_add(table, "060");
    // table = hash_table_open_add(table, "163");
    // table = hash_table_open_add(table, "543");
    // table = hash_table_open_add(table, "6578");
    // table = hash_table_open_add(table, "xcvcv");
    // hash_table_open_print(table);
    // printf("\n");
    // table = hash_table_open_add(table, "asdere");
    // hash_table_open_print(table);
    // printf("\n");
    // table = hash_table_open_add(table, "sdf");

    // // hash_table_open_restructuring(&table);
    
    FILE *f = fopen("test.txt", "r");
    // int rc;
    hash_table_close *table = file_to_hash_table_close(f);
    hash_table_close_print(table);
    printf("\n");

    hash_table_close_add(&table, "123");
    hash_table_close_print(table);
    printf("\n");

}
#endif
