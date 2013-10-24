#include "insert.h"

tuple_buffer* dat_file;
int tot;

void insert_on_open(char* file)
{
    char tmp_name[TABLE_NAME_LEN];
    strcpy(tmp_name, file);
    dat_file = out_buf_create(strcat(tmp_name, ".dat"), "ab");
    buf_push_char(dat_file, '\0');
    table_set(file);
    tot = 0;
}

void insert_item(const char* val)
{
    int b;
    if (!strcmp(get_type_by_num(tot), "Int")) {
        sscanf(val, "%d", &b);
        buf_push_int(dat_file, b);
    }
    else {
        b = get_by_num(tot);
        while (b--) {
            buf_push_char(dat_file, *val);
            if (*val != '\0') ++val;
        }
    }
    ++tot;
}

void insert_on_close()
{
    puts("CATTYDB : successfully inserted");
    out_buf_remove(dat_file);
}
