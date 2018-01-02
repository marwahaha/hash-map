CC=`brew --prefix llvm`/bin/clang
CFLAGS=-I. -g
DEPS=../log/log.c
BIN=test-hash test-key test-value test-kv test

all: $(BIN)

clean:
	rm -f $(BIN) *.o

test-hash: test-hash.c hash.c
	$(CC) -o test-hash test-hash.c hash.c $(CFLAGS)

test-key: test-key.c key.c hash.c
	$(CC) -o test-key test-key.c key.c hash.c $(DEPS) $(CFLAGS)

test-value: test-value.c value.c
	$(CC) -o test-value test-value.c value.c $(DEPS) $(CFLAGS)

test-kv: test-kv.c kv.c key.c hash.c value.c $(DEPS)
	$(CC) -o test-kv test-kv.c kv.c key.c hash.c value.c $(DEPS) $(CFLAGS)

test: test.c $(DEPS)
	$(CC) -o test test.c hash-map.c $(DEPS) $(CFLAGS)
