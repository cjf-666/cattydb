#ifndef _DELETE_H
#define _DELETE_H

#include "buffer.h"
#include "table_info.h"
#include "where.h"

void delete_on_open(const char* fn);
void delete(char* item);

#endif
