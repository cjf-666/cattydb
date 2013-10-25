#include "select_where.h"

tuple_buffer* dat_file;
tuple_buffer* new_file;

void select_where_on_open(const char* file, const char* file_new)
{
    char tb_m[TABLE_NAME_LEN];
    char tb_m_s[TABLE_NAME_LEN];
    char tb_d[TABLE_NAME_LEN];
    char tb_d_s[TABLE_NAME_LEN];
    strcpy(tb_m, file);
    strcat(tb_m, ".m");
    strcpy(tb_d, file);
    strcat(tb_d, ".dat");

    strcpy(tb_m_s, file_new);
    strcat(tb_m_s, ".m");
    strcpy(tb_d_s, file_new);
    strcat(tb_d_s, ".dat");

    table_set(file);
    dat_file = update_buf_create(tb_d);
    new_file = out_buf_create(tb_d_s, "wb");
    create_table(file_new);
    int i;
    for (i = 0; i < item_num; ++i)
        create_col(item_arr[i].item_name, item_arr[i].item_type, item_arr[i].item_byte, item_arr[i].is_pr);
    create_table_on_close();
}
void select_where(const char* pro)
{
    char item[2][STRING_LENGTH];
    int (*f)();
    int flag_not = 0, i;
    char pro_t[STRING_LENGTH];
    if (strstr(pro,"not ") != NULL) {
        flag_not = 1;
        for (i = 4; pro[i]; ++i)
            pro_t[i-4] = pro[i];
        pro_t[i] = 0;
    } else strcpy(pro_t,pro);
    //printf("%d\n",flag_not);
    if (strchr(pro_t,'=') != NULL) {
        sscanf(pro_t, "%s = %s", item[0], item[1]);
        if (flag_not) f = where_equal1;
        else f = where_equal1_n;
    }
    if (strchr(pro_t,'>') != NULL) {
        sscanf(pro_t, "%s > %s", item[0], item[1]);
        if (flag_not) f = where_bigger1;
        else f = where_bigger1_n;
    }
    if (strchr(pro_t,'<') != NULL) {
        sscanf(pro_t, "%s < %s", item[0], item[1]);
        if (flag_not) f = where_smaller1;
        else f = where_smaller1_n;
    }
    while (!eobuf(dat_file)) {
        if (f(dat_file, item[0], item[1])) {
            buf_move_backward(dat_file, get_tot_bytes()+1);
            int i;
            for (i = 0; i <= get_tot_bytes(); ++i)
                buf_push_char(new_file, buf_get_char(dat_file));
        }
    }
}


void select_where_on_close()
{
    out_buf_remove(new_file);
    update_buf_remove(dat_file);
}/*
   int main()
   {
   select_where_on_open("product","tmp");
   select_where("name = aa");
   select_where_on_close();
   show_table("tmp");
   return 0;
   }*/

