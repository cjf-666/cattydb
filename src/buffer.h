#ifndef _BUFFER_H
#define _BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 10

typedef struct tuple_buffer tuple_buffer;
tuple_buffer* in_buf_create(char* df_name);
tuple_buffer* out_buf_create(char* df_name, const char* modes);
tuple_buffer* update_buf_create(char* df_name);
char buf_get_char(tuple_buffer *tp);
int buf_get_int(tuple_buffer *tp);
void buf_push_byte(tuple_buffer *tp, char tmp);
void buf_push_int(tuple_buffer *tp, int tmp);
void buf_update_char(tuple_buffer *tp, char tmp);
void buf_update_int(tuple_buffer *tp, int tmp);
void out_buf_remove(tuple_buffer *tp);
void in_buf_remove(tuple_buffer *tp);
void update_buf_remove(tuple_buffer *tp);
void buf_move_forward(tuple_buffer *tp, int offset);
void buf_move_backward(tuple_buffer *tp, int offset);
int eobuf(tuple_buffer* tp);

#endif
