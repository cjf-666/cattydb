#include "delete.h"

tuple_buffer* tp;

void update_on_open(const char* fn)
{
    char tmp[TABLE_NAME_LEN];
    strcpy(tmp, fn);
    tp = update_buf_create(strcat(tmp, ".dat"));
    table_set(fn);
}

void update(char* new_val, char* pro)
{
    char item[4][STRING_LENGTH];
    memset(item,0,sizeof(item));
    sscanf(pro, "%s = %s", item[0], item[1]);
    sscanf(new_val, "%s = %s", item[2], item[3]);

    int updated = 0;
    int bef = get_bef_by_name(item[2]);
    int tot;

    while (!eobuf(tp)) {
        if (where_equal1(tp, item[0], item[1]))
        {
            buf_move_backward(tp, get_tot_bytes());
            int i = 0;
            for (; i < bef; i++) {
                buf_get_char(tp);
            }
            if (!strcmp(get_type_by_name(item[2]), "Int")) {
                buf_get_char(tp);
            }
            else {
                for (i = 0; i < get_by_name(item[2]); i++) {
                    buf_update_char(tp, item[3][i]);
                }
            }
            tot = get_tot_bytes() - bef - get_by_name(item[2]);
            buf_move_forward(tp, tot);
            updated = 1;
        }
    }
    if (updated)
        puts("CATTYDB : successfully updated");
    else puts("CATTYDB : nothing updated");

    update_buf_remove(tp);
}
