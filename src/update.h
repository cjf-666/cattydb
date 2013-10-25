#ifndef _UPDATE_H
#define _UPDATE_H

#include "buffer.h"
#include "table_info.h"
#include "where.h"

void update_on_open(const char* fn);
void update(char*val_name, char* item);

#endif
