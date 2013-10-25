#ifndef _EQUIJOINS_H_
#define _EQUIJOINS_H_

#include "table_info.h"
#include "createtable.h"
#include "where.h"

void equijoins_on_open(const char* file_1, const char* file_2, const char* file_new);
void equijoins(const char* pro);
void equijoins_on_close();

#endif
