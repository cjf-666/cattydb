#include "errhdl.h"

#include <stdio.h>
#include <string.h>

#define STR_MAX_LEN 100

int main(int args, char* argvs[])
{
  char cmd[STR_MAX_LEN];
  char db_info[3][STR_MAX_LEN];

  while (scanf("%s", cmd) != EOF) {
    if (!strcmp(cmd, "CREATE")) {
      fgets(db_info[0], STR_MAX_LEN, stdin);
      sscanf(db_info[0], " TABLE %s", db_info[1]);
      printf("%s\n", db_info[1]); //for test only
    }
    /* else if (!strcmp(cmd, "DESCRIBE")) { */
    /*   fgets(db_info[0]); */
    /*   printf("%s\n", db_info[0]); //for test only */

    /* } */
    /* else if (!strcmp(cmd, "INSERT")) { */
    /*   scanf(" INTO %s %s\n", db_info[0], db_info[1]); */
    /*   fgets() */
    /* 	printf("%s %s\n", db_info[0], db_info[1]); //for test only */
    /* } */
    /* else if (!strcmp(cmd, "DELETE")) { */
    /*   scanf(" FROM %s WHERE %s\n", db_info[0], db_info[1]); */
    /*   printf("%s %s\n", db_info[0], db_info[1]); //for test only */
    /* } */
    /* else if (!strcmp(cmd, "UPDATE")) { */
    /*   scanf("%s SET  %s WHERE %s\n", db_info[0], db_info[1], db_info[2]); */
    /*   printf("%s %s %s\n", db_info[0], db_info[1], db_info[2]); //for test only */
    /* } */
    /* else if (!strcmp(cmd, "SELECT")) { */
    /*   scanf("%s FROM %s\n", db_info[0], db_info[1]); */
    /*   printf("%s %s\n", db_info[0], db_info[1]); //for test only */
    /* } */
    /* else sql_syntax_error(); */
  }

  return 0;
}

