EXEC = D_recompile
cc = gcc

default:
	$(CC) -c D_recompile_test.c
	$(CC) -o test2 D_recompile_test.c
	$(CC) -o drecompile D_recompile.c -lrt
	objdump -d D_recompile_test.o > test
	./test2
	./drecompile

dynamic:
	$(CC) -c D_recompile_test.c
	$(CC) -o test2 D_recompile_test.c
	$(CC) -Ddynamic -o drecompile D_recompile.c -lrt
	objdump -d D_recompile_test.o > test
	./test2
	./drecompile

clean:
	sync
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	$(RM) D_recompile_test D_recompile_test.o 
	$(RM) D_recompile D_recompile.o
	$(RM) test2 test
	$(RM) drecompile
