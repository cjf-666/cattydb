gcc -g -c main.c -o main.o
gcc -g -c insert.c -o insert.o
gcc -g -c buffer.c -o buffer.o
gcc -g -c createtable.c -o crea.o
gcc -g -c describe.c -o des.o
gcc -g -c select_col.c -o select_col.o
gcc -g -c select_where.c -o select_where.o
gcc -g -c table_info.c -o table_info.o
gcc -g -c errhdl.c -o errhdl.o
gcc -g -c delete.c -o delete.o
gcc -g -c where.c -o where.o
gcc -g -c showtable.c -o showtable.o
gcc -g -c update.c -o update.o
gcc -g errhdl.o buffer.o crea.o table_info.o showtable.o where.o update.o delete.o insert.o des.o select_col.o select_where.o main.o
mv a.out ../test/
