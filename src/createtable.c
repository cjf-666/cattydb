#include <stdio.h>
#include <string.h>
#include "buffer.c"

#define MAXFILENAME 256

tuple_buffer* p;
void create_table(char* table_name)
{
        int i;
        char file_name[MAXFILENAME];
        strcpy(file_name,table_name);
        strcat(file_name,".m");
        p = out_buf_create(file_name,"wb");
        for (i = 0; table_name[i]; ++i)
                buf_push_char(p, table_name[i]);
        buf_push_char(p, '\n');

}
void create_col(char* col_name,char* col_type,int num)
{
        int i;
        for (i = 0; col_name[i]; ++i)
                buf_push_char(p, col_name[i]);
        buf_push_char(p, ' ');
        for (i = 0; col_type[i]; ++i)
                buf_push_char(p, col_type[i]);
        buf_push_char(p, ' ');
        buf_push_int(p, num);
        buf_push_char(p, '\n');
}
void create_table_on_close()
{
        buf_push_char(p, '`');
        out_buf_remove(p);
}
