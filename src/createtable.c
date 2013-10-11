#include "createtable.h"

tuple_buffer* p;
void creat_table(char* table_name)
{
        int i;
        char file_name[MAXFILENAME];
        strcpy(table_name,file_name);
        strcat(file_name,".m");
        p = out_buf_create(file_name,"wb");
        for (i = 0; table_name[i]; ++i)
                buf_push_byte(p, table_name[i]);
        buf_push_byte(p, '\n');
}
void creat_col(char* col_name,char* col_type,int num)
{
        int i;
        for (i = 0; col_name[i]; ++i)
                buf_push_byte(p, col_name[i]);
        buf_push_byte(p, ' ');
        for (i = 0; col_type[i]; ++i)
                buf_push_byte(p, col_type[i]);
        buf_push_byte(p, ' ');
        buf_push_int(p, num);
        buf_push_byte(p, '\n');
}
void creat_table_on_close()
{
        buf_push_byte(p, '`');
        out_buf_remove(p);
}
