#include "table_info.h"
#include "buffer.h"

void show_table(const char* tb_name)
{
        table_set(tb_name);
        char data_name[TABLE_NAME_LEN];
        strcpy(data_name, tb_name);
        strcat(data_name, ".dat");
        tuple_buffer* buf = in_buf_create(data_name);
        int i;
        for (i = 0; i < item_num; ++i)
                printf("%s\t\t\t", item_arr[i].item_name);
        putchar('\n');
        while(!eobuf(buf)) {
                int is_in = !buf_get_char(buf);
                for (i = 0; i < item_num; ++i) {
                        if (item_arr[i].item_type[0] == 'I') {
                                int val = buf_get_int(buf);
                                if (is_in)
                                        printf("%d\t\t\t", val);
                        }
                        else {
                                int j;
                                for (j = 0; j < item_arr[i].item_byte; ++j) {
                                        char val = buf_get_char(buf);
                                        if (is_in && val)
                                                printf("%c", val);
                                }
                                if (is_in)
                                        printf("\t\t\t");
                        }
                }
                putchar('\n');
        }
}
int main()
{
        show_table("product");
        return 0;
}
