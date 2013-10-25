#ifndef _WHERE_EXT_H
#define _WHERE_EXT_H

#include "buffer.h"
#include "table_info.h"

int where_equal1(tuple_buffer* tp, char*, char*);
int where_bigger1(tuple_buffer* tp, char*, char*);
int where_smaller1(tuple_buffer* tp, char*, char*);
int where_equal1_n(tuple_buffer* tp, char*, char*);
int where_bigger1_n(tuple_buffer* tp, char*, char*);
int where_smaller1_n(tuple_buffer* tp, char*, char*);

#endif
