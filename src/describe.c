#include "describe.h"

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
    printf("%s\t\t\t%s\t\t\t\n","Field","Type");

    while(1) {
        i = 0;
        while(1) {
            ch = buf_get_char(p);
            if (ch == ' '||ch=='`') break;
            str[i++] = ch;
        }
        if (ch == '`') break;
        str[i] = 0;
        printf("%s\t\t\t ", str);
        i = 0;
        while(1) {
            ch = buf_get_char(p);
            if (ch == ' ') break;
            str[i++] = ch;
        }
        str[i] = 0;
        printf("%s(", str);
        num = buf_get_int(p);
        printf("%d)\t\t\t\n", num);
        ch = buf_get_char(p);
    }
}
