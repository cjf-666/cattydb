#ifndef _ERRHDL_H
#define _ERRHDL_H
#endif

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

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

