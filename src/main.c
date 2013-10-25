#include "errhdl.h"
#include "createtable.h"
#include "describe.h"
#include "insert.h"
#include "delete.h"
#include "showtable.h"
#include "select_col.h"
#include "select_where.h"
#include "update.h"

#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define COMAND_LENGTH 1
#define receive(x) msgrcv(msgqid, (void *)&string_item, STRING_LENGTH, 1, x)

struct msg_st
{
  long msg_type;
  char text[STRING_LENGTH];
};

int main(int args, char* argvs[])
{
    int result, col_length;
    char col_type[ITEM_TYPE_LEN], col_name[ITEM_NAME_LEN];
    struct msg_st string_item;
    int msgqid;
    char tb_name[TABLE_NAME_LEN];
    char tmp[10][ITEM_NAME_LEN];

    msgqid = msgget((key_t)3570, 0666 | IPC_CREAT);
    if (msgqid == -1) {
        ipc_msgget_failed(errno);
    }
    
    while (receive(0)) {
        switch (*string_item.text) {        
        case '0':
            result=receive(0);
            string_item.text[result]='\0';
            create_table(string_item.text);
            result = 0;
            while ((result = receive(0)) != -1) {
                string_item.text[result]='\0';
                if (!strcmp(string_item.text, "TAIL"))
                    break;
                sscanf(string_item.text, "%s %s %s %d", tmp[0], col_type, col_name, &col_length);
                if (tmp[0][0] == '0')
                    create_col(col_name, col_type, col_length, 0);
                else create_col(col_name, col_type, col_length, 1);
            }
            
            if (-1 == result)
                ipc_msgrcv_failed(errno);

            create_table_on_close();
            break;
        case '1':
            result=receive(0);
            string_item.text[result]='\0';
            //printf("%s\n", string_item.text);
            describe_table(string_item.text);
            break;
        case '2':
            result = receive(0);
            string_item.text[result]='\0';
            //printf("%s\n", string_item.text);
            insert_on_open(string_item.text);
            while ((result=receive(0)) != -1) {
                string_item.text[result]='\0';
                if (!strcmp(string_item.text, "TAIL"))
                    break;
                insert_item(string_item.text);
            }
            if (-1 == result)
                ipc_msgrcv_failed(errno);
            insert_on_close();
            break;
        case '3':
            result = receive(0);
            string_item.text[result]='\0';
            //printf("%s\n", string_item.text);
            delete_on_open(string_item.text);
            int i = 0;
            while ((result = receive(0)) != -1) {
                string_item.text[result]='\0';
                if (!strcmp(string_item.text, "TAIL"))
                    break;
                delete(string_item.text);
                //strcpy(tmp[i++], string_item.text);
                //puts(tmp[i-1]);
            }
            if (-1 == result)
                ipc_msgrcv_failed(errno);
            puts("del suc!");
            break;
        case '6':
            puts("bye");
            exit(0);
        case '7':
            result = receive(0);
            string_item.text[result]='\0';
            printf("%s\n", string_item.text);
            show_table(string_item.text);
            break;
        case '8':
            result=receive(0);
            string_item.text[result]='\0';
            select_where_on_open(string_item.text, "tmp");
            
            result=receive(0);
            string_item.text[result]='\0';
            select_where(string_item.text);
            select_where_on_close();

            select_col_on_open("tmp", "tmp2");
            
            result = 0;
            while ((result = receive(0)) != -1) {
                string_item.text[result]='\0';
                if (!strcmp(string_item.text, "TAIL"))
                    break;
                select_col_get_pos(string_item.text);
            }
            if (-1 == result)
                ipc_msgrcv_failed(errno);

            select_col();
            select_col_on_close();
            show_table("tmp2");
            break;
        case '9':
            result = receive(0);
            string_item.text[result]='\0';
            update_on_open(string_item.text);
            result = receive(0);
            string_item.text[result]='\0';
            strcpy(tmp[0], string_item.text);
            result = receive(0);
            string_item.text[result]='\0';
            update(tmp[0], string_item.text); 
            break;
        case 'a':
            result = receive(0);
            string_item.text[result]='\0';
            strcpy(tmp[0], string_item.text);
            result = receive(0);
            string_item.text[result]='\0';
            equijoins_on_open(tmp[0], string_item.text);
            result = receive(0);
            string_item.text[result]='\0';
            equijoins(string_item.text);
            equijoins_on_close();
        }
    }

    return 0;
}

