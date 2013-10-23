#ifndef _INSERT_H
#define _INSERT_H

#include <stdio.h>
#include <string.h>
#include "buffer.h"
#include "table_info.h"

void insert_on_open(char*);
void insert_item(const char*);
void insert_on_close();
#endif
