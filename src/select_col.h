#ifndef _SELECT_COL_H
#define _SELECT_COL_H

#include "table_info.h"
#include "buffer.h"
#include "createtable.h"

void show_table(const char* tb_name);
void select_col_on_open(const char* file, const char* file_new);
void select_col_get_pos(const char* col_name);
void select_col();
void select_col_on_close();


#endif
