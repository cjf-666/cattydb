#include "delete.h"

tuple_buffer* tp;

void delete_on_open(const char* fn)
{
    char tmp[TABLE_NAME_LEN];
    strcpy(tmp, fn);
    tp = update_buf_create(strcat(tmp, ".dat"));
    table_set(fn);
}

void delete(char* pro)
{
    char item[2][STRING_LENGTH];
    sscanf(pro, "%s = %s", item[0], item[1]);
    
    int deleted = 0;
    while (!eobuf(tp)) {
        if (where_equal1(tp, item[0], item[1]))
        {
            buf_move_backward(tp, get_tot_bytes()+1);
            buf_update_char(tp, '\xff');
            buf_move_forward(tp, get_tot_bytes());
            deleted = 1;
        }
    }
    if (deleted)
        puts("CATTYDB : successfully deleted");
    else puts("CATTYDB : nothing deleted");

    update_buf_remove(tp);
}
