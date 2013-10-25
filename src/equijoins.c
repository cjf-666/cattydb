#include "equijoins.h"

tuple_buffer* dat_file_1;
tuple_buffer* dat_file_2;
tuple_buffer* new_file;
int tot;
int pos[100];

typedef struct item_set {
    char item_name[ITEM_NAME_LEN];
    char item_type[ITEM_TYPE_LEN];
    int  item_byte;
    int is_pr;
} item_set;
item_set item_1[50], item_2[50];
int item_num_1, item_num_2;
char file_n_1[TABLE_NAME_LEN];
char file_n_2[TABLE_NAME_LEN];
char tb_m_1[TABLE_NAME_LEN];
char tb_m_2[TABLE_NAME_LEN];
char tb_m_s[TABLE_NAME_LEN];
char tb_d_1[TABLE_NAME_LEN];
char tb_d_2[TABLE_NAME_LEN];
char tb_d_s[TABLE_NAME_LEN];

void equijoins_on_open(const char* file_1, const char* file_2, const char* file_new)
{
    strcpy(file_n_1, file_1);
    strcpy(file_n_2, file_2);
    strcpy(tb_m_1, file_1);
    strcat(tb_m_1, ".m");
    strcpy(tb_d_1, file_1);
    strcat(tb_d_1, ".dat");
    strcpy(tb_m_2, file_2);
    strcat(tb_m_2, ".m");
    strcpy(tb_d_2, file_2);
    strcat(tb_d_2, ".dat");
    strcpy(tb_m_s, file_new);
    strcat(tb_m_s, ".m");
    strcpy(tb_d_s, file_new);
    strcat(tb_d_s, ".dat");
    dat_file_1 = update_buf_create(tb_d_1);
    new_file = out_buf_create(tb_d_s,"wb");
    int i;
	
    table_set(file_1);
    item_num_1 = item_num;
    for (i = 0; i < item_num_1; ++i) {
        strcpy(item_1[i].item_name, item_arr[i].item_name);
        strcpy(item_1[i].item_type, item_arr[i].item_type);
        item_1[i].item_byte = item_arr[i].item_byte;
        item_1[i].is_pr = item_arr[i].is_pr;
    }
    table_set(file_2);
    item_num_2 = item_num;
    for (i = 0; i < item_num_2; ++i) {
        strcpy(item_2[i].item_name, item_arr[i].item_name);
        strcpy(item_2[i].item_type, item_arr[i].item_type);
        item_2[i].item_byte = item_arr[i].item_byte;
        item_2[i].is_pr = item_arr[i].is_pr;
    }
    create_table(file_new);
    for (i = 0; i < item_num_1; ++i)
        create_col(item_1[i].item_name, item_1[i].item_type, item_1[i].item_byte, item_1[i].is_pr);
    for (i = 0; i < item_num_2; ++i)
        create_col(item_2[i].item_name, item_2[i].item_type, item_2[i].item_byte, item_2[i].is_pr);
    create_table_on_close();
}
void swapstr(char* a, char* b)
{
    char c[TABLE_NAME_LEN];
    strcpy(c, a);
    strcpy(a, b);
    strcpy(b, c);
}
void equijoins(const char* pro)
{
    char tb_name_1[TABLE_NAME_LEN];
    char col_name_1[TABLE_NAME_LEN];
    char tb_name_2[TABLE_NAME_LEN];
    char col_name_2[TABLE_NAME_LEN];
    sscanf(pro, "%[^.]%*c%s = %[^.]%*c%s", tb_name_1, col_name_1, tb_name_2, col_name_2);
    if (strcmp(tb_name_2,file_n_1) == 0) {
        swapstr(tb_name_1, tb_name_2);
        swapstr(col_name_1, col_name_2);
    }
    table_set(tb_name_1);
    int is_i = (item_1[get_pos_by_name(col_name_1)].item_type[0] == 'I');
    int col_byte = item_1[get_pos_by_name(col_name_1)].item_byte;
    int bef = get_bef_by_name(col_name_1);
    int val_i;
    int tot_b = get_tot_bytes();
    char val_s[TABLE_NAME_LEN];
    while(!eobuf(dat_file_1)) {
        if (buf_get_char(dat_file_1) != '\0') {
            buf_move_forward(dat_file_1, tot_b);
            continue;
        }
        buf_move_forward(dat_file_1, bef);
        if (is_i) {
            val_i = buf_get_int(dat_file_1);
            sprintf(val_s,"%d",val_i);
        } else {
            int j = 0;
            for (j = 0; j < col_byte; ++j)
                val_s[j] = buf_get_char(dat_file_1);
            val_s[j] = '0';
        }
        buf_move_backward(dat_file_1, bef+col_byte+1);
        dat_file_2 = update_buf_create(tb_d_2);
        table_set(tb_name_2);
        while(!eobuf(dat_file_2)) {
            if (where_equal1(dat_file_2, col_name_2, val_s)) {
                buf_move_backward(dat_file_2, get_tot_bytes());
                int i;
                for (i = 0; i <= tot_b; ++i)
                    buf_push_char(new_file, buf_get_char(dat_file_1));
                for (i = 0; i < get_tot_bytes(); ++i)
                    buf_push_char(new_file, buf_get_char(dat_file_2));
            }
        }
        update_buf_remove(dat_file_2);
    }
}

void equijoins_on_close()
{
    update_buf_remove(dat_file_1);
    out_buf_remove(new_file);
}
/*
  int main()
  {
  show_table("test");
  show_table("product");
  equijoins_on_open("test","product","tmp");
  equijoins("test.cx = product.name");
  equijoins_on_close();
  show_table("tmp");
  return 0;
  }*/
