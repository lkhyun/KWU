CC = gcc
CFLAGS = -Wall

all: filegen schedtest

filegen: filegen.c
	$(CC) $(CFLAGS) -o filegen filegen.c

schedtest: schedtest.c
	$(CC) $(CFLAGS) -o schedtest schedtest.c

clean:
	rm -f filegen schedtest
	rm -rf tmp* temp
	sync
	echo 3 | sudo tee /proc/sys/vm/drop_caches

