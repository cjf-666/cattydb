#include "select.h"
FILE* dat_file;
FILE* mod_file;
FILE* tmp_file;
char buf[512];
char col_name[100][100];
char col_typ[100][100];
int col_num ;
char tb_name0[100];
char tb_name1[100];

void select_on_open(const char* tb_name)
{
    strcpy(tb_name0, tb_name);
    strcpy(tb_name1, tb_name);
    dat_file = fopen(strcat(tb_name0, ".dat"), "r");
    mod_file = fopen(strcat(tb_name1, ".m"), "r");
    fscanf(mod_file, "%s\n", buf);
    col_num=0;
    int tmp;
    while (fscanf(mod_file, "%s %s %d\n", col_name[col_num], col_typ[col_num], &tmp) == 3) ++col_num;
    for (tmp=0;tmp<col_num;tmp++)
        printf("%s\t\t\t", col_name[tmp]);
    printf("\n");
}

void pretty_print()
{
    int i;
    char* cur = buf;
    for (i=0;i<col_num;i++) {
        if (!strcmp(col_typ[i], "Char")) {
            printf("%s\t\t\t", cur);
            cur += 10;
        }
        else {
            printf("%d\t\t\t", *((int*)cur));
            cur += 4;
        }
    }
    printf("\n");
}

void select_all()
{
    while (!feof(dat_file)) {
        fread(buf, 1, 512, dat_file);
        if (feof(dat_file))
            break;
        pretty_print();
    }
}

void select_on_close(const char* tb_name)
{
    fclose(dat_file);
    fclose(mod_file);
}
