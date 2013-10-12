#include "insert.h"

FILE* dat_file;
char buf[512];
char* cur;

void insert_on_open(const char* file)
{
    dat_file = fopen(file, "ab");
    memset(buf, 0, sizeof(buf));
    cur = buf;
}

void insert_item(const char* val)
{
    if (*val == '\"') {
        strcpy(cur, val+1);
        cur += 10;
    }
    else {
        sscanf(val, "%d", (int*)cur);
        cur += 4;
    }
}

void insert_on_close()
{
    fwrite(buf, 1, 512, dat_file);
    fclose(dat_file);
}
