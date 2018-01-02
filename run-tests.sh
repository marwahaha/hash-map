#!/bin/bash

make clean
make all
./test-hash && \
    ./test-value && \
    ./test-key && \
    ./test-kv && \
    ./test-list && \
    echo 'ok'
