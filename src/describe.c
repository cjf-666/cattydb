#include "describe.h"
#include "table_info.h"

void describe_table(const char* table_name)
{
    char file_name[TABLE_NAME_LEN];
    char str[TABLE_NAME_LEN];
    strcpy(file_name,table_name);

    FILE* tb = fopen(strcat(file_name,".m"), "r");
    puts("");
    printf("Table: %s\n", table_name);
    printf("%s\t\t\t%s\t\t\t%s\n","Field","Type","Primary");
    printf("%s\t\t\t%s\t\t\t%s\n","-----","----","-------");
    table_set(table_name);
    int i;
    for (i = 0; i < item_num; ++i) {
        if (item_arr[i].item_type[0] == 'I')
            printf("%s\t\t\t%s\t\t\t%s\n",item_arr[i].item_name,item_arr[i].item_type,item_arr[i].is_pr?"No":"Yes");
        else
            printf("%s\t\t\t%s(%d)\t\t%s\n",item_arr[i].item_name,item_arr[i].item_type,item_arr[i].item_byte,item_arr[i].is_pr?"No":"Yes");
    }
    fclose(tb);
}
/*
  int main()
  {
  describe_table("product");
  }*/

