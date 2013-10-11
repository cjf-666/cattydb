#ifndef _CREATETABLE_H
#define _CREATETABLE_H
#endif

#include <stdio.h>
#include <string.h>
#include "buffer.h"

#define MAXFILENAME 256

void create_table(char* table_name);
void create_col(char* col_name,char* col_type,int num);
void create_table_on_close();
