gcc -g -c main.c -o main.o
gcc -g -c insert.c -o insert.o
gcc -g -c buffer.c -o buffer.o
gcc -g -c createtable.c -o crea.o
gcc -g -c describe.c -o des.o
gcc -g -c select.c -o select.o
gcc -g -c table_info.c -o table_info.o
gcc -g -c errhdl.c -o errhdl.o
gcc -g -c delete.c -o delete.o
gcc -g -c where.c -o where.o
gcc -g errhdl.o buffer.o crea.o table_info.o where.o delete.o insert.o des.o select.o main.o
mv a.out ../test/
