#include "errhdl.h"
#include "createtable.h"

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
    char col_type[10], col_name[10];
    struct msg_st string_item;
    int msgqid;

    msgqid = msgget((key_t)3570, 0666 | IPC_CREAT);
    if (msgqid == -1) {
        ipc_msgget_failed(errno);
    }
    
    while (receive(0)) {
        switch (*string_item.text) {        
        case '0':
            result=receive(IPC_NOWAIT);
            string_item.text[result]='\0';
            creat_table(string_item.text);
            result = 0;
            while ((result = receive(IPC_NOWAIT)) != -1) {
                string_item.text[result]='\0';
                if (!strcmp(string_item.text, "TAIL"))
                    break;
                sscanf(string_item.text, "%s %s %d", col_type, col_name, &col_length);
                creat_col(col_name, col_type, col_length);
            }
            if (-1 == result)
                ipc_msgrcv_failed(errno);

            creat_table_on_close();
            break;
        }
    }

    return 0;
}

