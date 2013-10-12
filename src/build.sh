gcc -g -c main.c -o main.o
gcc -g -c insert.c -o insert.o
gcc -g -c buffer.c -o buffer.o
gcc -g -c createtable.c -o crea.o
gcc -g -c describe.c -o des.o
gcc -g -c select.c -o select.o
gcc -g buffer.o crea.o insert.o des.o select.o main.o
