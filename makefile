CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LDFLAGS = -lrt

worker: worker.c
	$(CC) $(CFLAGS) -o worker worker.c $(LDFLAGS)

.PHONY: clean
clean:
	rm -f worker
