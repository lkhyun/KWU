CC = gcc
CFLAGS = -Wall -pthread -lrt

all: numgen fork thread

numgen: numgen.c
	$(CC) $(CFLAGS) -o numgen numgen.c

fork: fork.c
	$(CC) $(CFLAGS) -o fork fork.c

thread: thread.c
	$(CC) $(CFLAGS) -o thread thread.c

clean:
	rm -rf tmp*
	rm -f numgen fork thread temp.txt
	sync
	echo 3 | sudo tee /proc/sys/vm/drop_caches

