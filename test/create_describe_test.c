#include <stdio.h>
#include <string.h>
#include "creattable.c"
#include "buffer.c"
#include "describe.c"

int main()
{
        create_table("student");
        create_col("ID","Int",4);
        create_col("Name","Char",6);
        create_table_on_close();
        describe_table("student");
        return 0;
}
