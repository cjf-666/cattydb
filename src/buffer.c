#include "buffer.h"

typedef struct tuple_buffer {
    unsigned char buf[BUF_SIZE];
    unsigned char *top;
    FILE* db_file;
};

tuple_buffer* in_buf_create(char* df_name)
{
    tuple_buffer *tp = (tuple_buffer*) malloc(sizeof(tuple_buffer));
    tp->db_file = fopen(df_name, "rb");
    tp->top = tp->buf + BUF_SIZE;
    return tp;
}
tuple_buffer* out_buf_create(char* df_name, const char* modes)
{
    tuple_buffer *tp = (tuple_buffer*) malloc(sizeof(tuple_buffer));
    tp->db_file = fopen(df_name, modes);
    tp->top = tp->buf;
    memset(tp->buf, 0, sizeof(tp->buf));
    return tp;
}

unsigned char* _get_byte(tuple_buffer *tp)
{
    if (tp->top == BUF_SIZE + tp->buf) {
        fread(tp->buf, 1, BUF_SIZE, tp->db_file);
        tp->top = tp->buf;
    }
    return tp->top++;
}

char buf_get_char(tuple_buffer *tp)
{
    return *(char*)(_get_byte(tp));
}

int buf_get_int(tuple_buffer *tp)
{
    unsigned char *i = _get_byte(tp);
    _get_byte(tp);
    _get_byte(tp);
    _get_byte(tp);

    return *((int*)i);
}

void _push_byte(tuple_buffer *tp, unsigned char tmp)
{
    if (tp->top == BUF_SIZE+tp->buf) {
        fwrite(tp->buf, 1, BUF_SIZE, tp->db_file);
        memset(tp->buf, 0, sizeof(tp->buf));
        tp->top = tp->buf;
    }
    *(tp->top++) = tmp;

}
void buf_push_char(tuple_buffer *tp, char tmp)
{
    _push_byte(tp,(unsigned char)tmp);
}
void buf_push_int(tuple_buffer *tp, int tmp)
{
    _push_byte(tp,(unsigned char)*(&tmp));
    _push_byte(tp,(unsigned char)*((unsigned char*)&tmp+1));
    _push_byte(tp,(unsigned char)*((unsigned char*)&tmp+2));
    _push_byte(tp,(unsigned char)*((unsigned char*)&tmp+3));
}
void out_buf_remove(tuple_buffer *tp)
{
    fwrite(tp->buf, 1, (tp->top)-(tp->buf), tp->db_file);
    fclose(tp->db_file);
    free(tp);
}
void in_buf_remove(tuple_buffer *tp)
{
    fclose(tp->db_file);
    free(tp);
}

