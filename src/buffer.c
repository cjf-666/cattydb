#include "buffer.h"

typedef struct tuple_buffer {
    unsigned char buf[BUF_SIZE];
    unsigned char *top;
    size_t byte_num;
    FILE* db_file;
};

int almosteof(FILE* fp)
{
    char x;
    int n = fread(&x, 1, 1, fp);
    if (!n) return -1;
    else {
        fseek(fp, -1, SEEK_CUR);
        return 0;
    }
}
int eobuf(tuple_buffer* tp)
{
    if (tp->top == tp->buf + tp->byte_num && (feof(tp->db_file) || almosteof(tp->db_file)))
        return -1;
    else 
        return 0;
}

tuple_buffer* in_buf_create(char* df_name)
{
    tuple_buffer *tp = (tuple_buffer*) malloc(sizeof(tuple_buffer));
    tp->db_file = fopen(df_name, "rb");
    tp->byte_num = fread(tp->buf, 1, BUF_SIZE, tp->db_file);
    tp->top = tp->buf;
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

tuple_buffer* update_buf_create(char* df_name)
{
    tuple_buffer *tp = (tuple_buffer*) malloc(sizeof(tuple_buffer));
    tp->db_file = fopen(df_name, "r+b");
    tp->byte_num = fread(tp->buf, 1, BUF_SIZE, tp->db_file);
    tp->top = tp->buf;
    return tp;
}

unsigned char* _get_byte(tuple_buffer *tp)
{
    if (tp->top == tp->buf + tp->byte_num) {
        tp->byte_num = fread(tp->buf, 1, BUF_SIZE, tp->db_file);
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
    int p = 1;
    for (p = 0; p < 4; p++)
        _push_byte(tp, *(((unsigned char*)&tmp)+p));
}

void _update_byte(tuple_buffer *tp, unsigned char tmp)
{
    if (tp->top == tp->buf + tp->byte_num) {
        fseek(tp->db_file, -tp->byte_num, SEEK_CUR);
        fwrite(tp->buf, 1, BUF_SIZE, tp->db_file);
        tp->byte_num = fread(tp->buf, 1, BUF_SIZE, tp->db_file);
        tp->top = tp->buf;
    }
    *tp->top++ = tmp;
}

void _update_byte_org(tuple_buffer *tp)
{
    if (tp->top == tp->buf + tp->byte_num) {
        fseek(tp->db_file, -tp->byte_num, SEEK_CUR);
        fwrite(tp->buf, 1, BUF_SIZE, tp->db_file);
        tp->byte_num = fread(tp->buf, 1, BUF_SIZE, tp->db_file);
        tp->top = tp->buf;
    }
    tp->top++;
}

void _get_byte_r(tuple_buffer *tp)
{
    if (tp->top == tp->buf - 1) {
        fseek(tp->db_file, -tp->byte_num, SEEK_CUR);
        fwrite(tp->buf, 1, tp->byte_num, tp->db_file);
        fseek(tp->db_file, -BUF_SIZE-(tp->byte_num), SEEK_CUR);
        tp->byte_num = fread(tp->buf, 1, BUF_SIZE, tp->db_file);
        tp->top = tp->buf+tp->byte_num-1;
    }
    tp->top--;
}

void buf_update_char(tuple_buffer *tp, char tmp)
{
    _update_byte(tp, (unsigned char) tmp);
}

void buf_update_int(tuple_buffer *tp, int tmp)
{
    int p = 1;
    for (p = 0; p < 4; p++)
        _update_byte(tp, *(((unsigned char*)&tmp)+p));
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

void update_buf_remove(tuple_buffer *tp)
{
    fseek(tp->db_file, -tp->byte_num, SEEK_CUR);
    fwrite(tp->buf, 1, tp->byte_num, tp->db_file);
    fclose(tp->db_file);
    free(tp);
}

void buf_move_forward(tuple_buffer *tp, int offset)
{
    int i = 0;
    for (; i < offset; i++)
        _update_byte_org(tp);
}

void buf_move_backward(tuple_buffer *tp, int offset)
{
    int i = 0;
    for (; i < offset; i++)
        _get_byte_r(tp);
}
