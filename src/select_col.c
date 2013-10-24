#include "table_info.h"

tuple_buffer* dat_file;
tuple_buffer* new_file;
int tot;
int pos[100];
void select_col_on_open(const char* file, const char* file_new)
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
        dat_file = in_buf_create(tb_d);
        new_file = out_buf_create(tb_d_s, "wb");
        tot = 0;
        create_table(file_new);
}
void select_col_get_pos(const char* col_name)
{
        pos[tot] = get_pos_by_name(col_name);
        create_col(item_arr[pos[tot]].item_name, item_arr[pos[tot]].item_type, item_arr[pos[tot]].item_byte, item_arr[pos[tot]].is_pr);
        pos[++tot] = -1;
}
void select_col()
{
        int i, j;
        while(!eobuf(dat_file)) {
                j = 0;
                int is_in;
                int exist = !buf_get_char(dat_file);
                if (exist) buf_push_char(new_file, 0);
                for (i = 0; i < item_num; ++i) {
                        if (pos[j] == i) {
                                if (j < tot) ++j;
                                is_in = 1;
                        } else  is_in = 0;

                        if (item_arr[i].item_type[0] == 'I') {
                                int val = buf_get_int(dat_file);
                                if (is_in && exist)
                                        buf_push_int(new_file, val);
                        }
                        else {
                                int k = 0;
                                for (; k < item_arr[i].item_byte; ++k) {
                                        char val = buf_get_char(dat_file);
                                        if (is_in && exist)
                                                buf_push_char(new_file, val);
                                }
                        }
                }
        }
}

void select_col_on_close()
{
        create_table_on_close();
        out_buf_remove(new_file);
        in_buf_remove(dat_file);
}

//int main()
//{
//        select_col_on_open("product","tmp");
//        select_col_get_pos("ID");
//        select_col_get_pos("Type");
//        select_col();
//        select_col_on_close();
//        show_table("tmp");
//        return 0;
//}
