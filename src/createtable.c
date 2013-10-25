#include "createtable.h"

FILE* tb;
void create_table(const char* table_name)
{
        char tb_name[TABLE_NAME_LEN];
        strcpy(tb_name, table_name);
        tb = fopen(strcat(tb_name, ".m"), "w");
        fprintf(tb, "%s\n", table_name);

}
void create_col(const char* col_name, const char* col_type, int num, int is_primary)
{
        fprintf(tb, is_primary?"0 %s %s %d\n":"1 %s %s %d\n", col_name, col_type, num);
}
void create_table_on_close()
{
        fclose(tb);
}
/*
int main()
{
        create_table("product");
        create_col("ID","Int",4,1);
        create_col("Name","Char",10,0);
        create_col("Type","Char",10,0);
        create_table_on_close();
        return 0;
}*/

