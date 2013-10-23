#include "errhdl.h"
#include "createtable.h"
#include "describe.h"
#include "insert.h"

#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define STRING_LENGTH 100
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
                sscanf(string_item.text, "%s %s %d", col_type, col_name, &col_length);
                create_col(col_name, col_type, col_length);
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
            printf("%s\n", string_item.text);
            strcpy(tb_name, string_item.text);
            int i = 0;
            while ((result = receive(0)) != -1) {
                string_item.text[result]='\0';
                if (!strcmp(string_item.text, "TAIL"))
                    break;
                //strcpy(tmp[i++], string_item.text);
            }
            if (-1 == result)
                ipc_msgrcv_failed(errno);
            //delete();
            break;
        case '6':
            puts("hey!\n");
            exit(0);
        case '7':
            result = receive(0);
            string_item.text[result]='\0';
            printf("%s\n", string_item.text);
            select_on_open(string_item.text);
            select_all();
            select_on_close();
            break;
        }
    }

    return 0;
}

