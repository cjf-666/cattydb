#ifndef _ERRHDL_H
#define _ERRHDL_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int sql_syntax_error();
int ipc_msgget_failed(int errnum);
int ipc_msgrcv_failed(int errnum);
int item_num_cross_bd();
int item_name_not_exist();

#endif
