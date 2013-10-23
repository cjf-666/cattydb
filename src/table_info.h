#ifndef _TABLE_INFO_H
#define _TABLE_INFO_H

#include "errhdl.h"
#include <string.h>

#define TABLE_NAME_LEN 50
#define ITEM_NAME_LEN 50
#define ITEM_TYPE_LEN 50
#define ITEM_NUM 50

void table_set(const char* tb_name);
int get_by_num(int num);
int get_by_name(const char* it_nm);
const char* get_type_by_num(int);

#endif
