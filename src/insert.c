#include "insert.h"

FILE* dat_file;

void insert_on_open(const char* file)
{
    dat_file = fopen(file, "a+b");
}

char buf[512];
char* cur = buf;

void insert_item(const char* val)
{
    if (*val == '\"') {
        sscanf(val, "\"%s", cur);
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
