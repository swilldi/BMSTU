#include "exit_code.h"
#include <stdio.h>
#include "graph_matr.h"
#include <limits.h>
#include "test.h"
#include "io_func.h"
#include "graph_emulate.h"
#include "cmd_action.h"

int main(void)
{
    int rc = OK;
    int cmd = START;
    while (cmd != EXIT)
    {
        print_cmd_list();
        rc = cmd_input(&cmd, MAX_CMD_ACTION);
        if (rc != OK)
        {
            cmd = START;
        }
            

        switch (cmd)
        {
            case MATR_GRAPH_EMU:
                rc = run_emulate(GRAPH_TYPE_MATRIX);
                break;
            case LIST_GRAPH_EMU:
                rc = run_emulate(GRAPH_TYPE_LIST);
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
