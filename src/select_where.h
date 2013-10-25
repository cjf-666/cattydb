#ifndef _SELECT_WHERE_H
#define _SELECT_WHERE_H
#include "table_info.h"
#include "buffer.h"
#include "createtable.h"
#include "showtable.h"
#include "insert.h"
#include "where.h"
#include "errhdl.h"

void select_where_on_open(const char* file, const char* file_new);
void select_where(const char* pro);
void select_where_on_close();

#endif
