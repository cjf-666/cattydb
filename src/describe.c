#include <stdio.h>
#include <string.h>
#include "buffer.c"

#define MAXFILENAME 256

void describe_table(char* table_name)
{
        int i, num;
        char ch = 0;
        char file_name[MAXFILENAME];
        char str[MAXFILENAME];
        strcpy(file_name,table_name);
        strcat(file_name,".m");
        tuple_buffer* p = in_buf_create(file_name);
        do {
                ch = buf_get_char(p);
        } while(ch != '\n');
        printf("Table: %s\n", table_name);
        printf("%10s %10s\n","Field","Type");

        while(1) {
                i = 0;
                while(1) {
                        ch = buf_get_char(p);
                        if (ch == ' '||ch=='`') break;
                        str[i++] = ch;
                }
                if (ch == '`') break;
                str[i] = 0;
                printf("%10s ", str);
                i = 0;
                while(1) {
                        ch = buf_get_char(p);
                        if (ch == ' ') break;
                        str[i++] = ch;
                }
                str[i] = 0;
                printf("%10s(", str);
                num = buf_get_int(p);
                printf("%d)\n", num);
                ch = buf_get_char(p);
        }
}


