#include "exit_code.h"
#include <stdio.h>
#include "graph_matr.h"
#include <limits.h>
#include "test.h"
#include "io_func.h"
#include "graph_emulate.h"
#include "cmd_action.h"


int is_empty_file(FILE *f)
{
    fseek(f, 0, SEEK_END);
    return ftell(f) == 0;
    
}

int main(void)
{
    int rc = OK;
    FILE *f = NULL;
    int cmd = START;
    while (cmd != EXIT)
    {
        print_cmd_list();
        rc = cmd_input(&cmd, MAX_CMD_ACTION);
        if (rc != OK)
        {
            cmd = START;
        }

        char filename[STR_LEN];
        if (cmd == MATR_GRAPH_EMU || cmd == LIST_GRAPH_EMU)
        {
            rc = input_str(filename, "Введите название файла: ");
            if (rc != OK)
            {
                cmd = START;

            }
            else
            {
                f = fopen(filename, "r");
                if (!f)
                {
                    rc = FILE_OPEN_ERROR;
                    cmd = START;
                }
            }
            

            if (f && is_empty_file(f))
            {
                rc = EMPTY_FILE;
                cmd = START;
            }
        }

        switch (cmd)
        {
            case MATR_GRAPH_EMU:
                rc = run_emulate(f, GRAPH_TYPE_MATRIX);
                break;
            case LIST_GRAPH_EMU:
                rc = run_emulate(f, GRAPH_TYPE_LIST);
                break;
            case CMP_STRUCT:
                run_test();
                break;
            case EXIT:
            case START:
                break;
        }

        if (rc != OK)
        {
            print_err_msg(rc);
            rc = OK;
            cmd = START;
        }

        
        printf(SEPARATOR_LINE);
    }
}
