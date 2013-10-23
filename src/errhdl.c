#include "errhdl.h"

int sql_syntax_error()
{
    fprintf(stderr, "SQL syntax error!\n");
    exit(EXIT_FAILURE);
}

int ipc_msgget_failed(int errnum)
{
    fprintf(stderr, "msgget failed with error: %d\n", errnum);
    exit(EXIT_FAILURE);
}

int ipc_msgrcv_failed(int errnum)
{
    fprintf(stderr, "msgrcv failed with error: %d\n", errnum);
    exit(EXIT_FAILURE);
}

int item_num_cross_bd()
{
    fprintf(stderr, "item number cross upper boundary\n");
    exit(EXIT_FAILURE);
}

int item_name_not_exist()
{
    fprintf(stderr, "item name doesn't exist!\n");
    exit(EXIT_FAILURE);
}
