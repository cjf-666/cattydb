#ifndef _CREATETABLE_H
#define _CREATETABLE_H
#endif

#include <stdio.h>
#include <string.h>
#include "buffer.h"

#define MAXFILENAME 256

void creat_table(char* table_name);
void creat_col(char* col_name,char* col_type,int num);
void creat_table_on_close();
