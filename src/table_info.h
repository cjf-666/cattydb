#ifndef _TABLE_INFO_H
#define _TABLE_INFO_H

#include "errhdl.h"
#include <string.h>
#include "buffer.h"

int item_num;

#define TABLE_NAME_LEN 50
#define ITEM_NAME_LEN 50
#define ITEM_TYPE_LEN 50
#define ITEM_NUM 50
#define STRING_LENGTH 100

struct item_st {
    char item_name[ITEM_NAME_LEN];
    char item_type[ITEM_TYPE_LEN];
    int  item_byte;
    int is_pr;
} item_arr[ITEM_NUM];


void table_set(const char* tb_name);
int get_by_num(int num);
int get_by_name(const char* it_nm);
const char* get_type_by_num(int);
const char* get_type_by_name(const char* name);
int get_bef_by_name(const char* it_nm);
int get_pos_by_name(const char* it_nm);

#endif
