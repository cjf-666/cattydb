#include <stdio.h>
#include "buffer.c"

int main()
{
  FILE *tp = fopen("db_file.txt", "wb");
  fwrite("abcdBbcdaD", sizeof(unsigned char), 10, tp);
  fclose(tp);
  
  tuple_buffer* p = buf_create("db_file.txt");
  printf("%d\n", buf_get_int(p));
  printf("%c\n", buf_get_char(p));
  printf("%d\n", buf_get_int(p));
  printf("%c\n", buf_get_char(p));
  
  buf_remove(p);

  printf("%d\n",0x64636261);
  printf("%d\n", 0x61646362);
  return 0;
}
