#include "table_info.h"

struct item_st {
    char item_name[ITEM_NAME_LEN];
    char item_type[ITEM_TYPE_LEN];
    int  item_byte;
    int is_pr;
} item_arr[ITEM_NUM];

char table_name[TABLE_NAME_LEN];
int item_num;
int tot_bytes;

void table_set(const char* tb_name)
{
    if (!strcmp(table_name, tb_name))
        return;

    char tmp_name[TABLE_NAME_LEN];
    strcpy(table_name, tb_name);
    strcpy(tmp_name, tb_name);

    FILE* m_f = fopen(strcat(tmp_name, ".m"), "r");
    fscanf(m_f, "%s\n", tmp_name);

    item_num = 0;
    tot_bytes = 0;
    
    while (!feof(m_f)) {
        fscanf(m_f, "%d %s %s %d\n",
               &item_arr[item_num].is_pr,
               item_arr[item_num].item_name,
               item_arr[item_num].item_type,
               &item_arr[item_num].item_byte);
        tot_bytes += item_arr[item_num].item_byte;
        item_num++;
    }
    fclose(m_f);
}

int get_by_num(int num)
{
    if (num >= item_num)
        item_num_cross_bd();
    return item_arr[num].item_byte;
}

int get_by_name(const char* it_nm)
{
    int i = 0;
    for (;i < item_num; i++) {
        if (!strcmp(item_arr[i].item_name, it_nm))
            return item_arr[i].item_byte;
    }
    item_name_not_exist();
}

const char* get_type_by_num(int num)
{
    if (num >= item_num)
        item_num_cross_bd();
    return item_arr[num].item_type;
}

const char* get_type_by_name(const char* name)
{
    int i = 0;
    for (;i < item_num; i++) {
        if (!strcmp(item_arr[i].item_name, name))
            return item_arr[i].item_type;
    }
    item_name_not_exist();
}

int get_bef_by_name(const char* it_nm)
{
    int i = 0;
    int tot = 0;
    for (;i < item_num; i++) {
        if (!strcmp(item_arr[i].item_name, it_nm))
            return tot;
        tot += get_by_num(i);
    }
    item_name_not_exist();
}

int get_tot_bytes()
{
    return tot_bytes;
}
