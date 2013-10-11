#include "errhdl.h"
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define STRING_LENGTH 100
#define COMAND_LENGTH 1

struct msg_st
{
  long msg_type;
  char text[STRING_LENGTH];
};

#define receive(x) msgrcv(msgqid, (void *)&string_item, STRING_LENGTH, 1, x)

int main(int args, char* argvs[])
{
    int result;
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
            printf("%d %s\n",msg_qnum, string_item.text);
            result = 0;
            while ((result = receive(IPC_NOWAIT)) != -1) {
                string_item.text[result]='\0';
                if (!strcmp(string_item.text, "TAIL"))
                    break;
                printf("%s\n", string_item.text);
            }
            if (-1 == result) ipc_msgrcv_failed(errno);
            break;
        }
    }

    return 0;
}

