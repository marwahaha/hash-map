CC=/usr/local/Cellar/llvm/5.0.0/bin/clang
CFLAGS=-I. -g
DEPS=../log/log.c

all: test

clean:
	rm -f test *.o

test-hash: test-hash.c
	$(CC) -o test-hash test-hash.c hash.c $(CFLAGS)

test: test.c $(DEPS)
	$(CC) -o test test.c hash-map.c $(DEPS) $(CFLAGS)
