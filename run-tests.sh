#!/bin/bash

make clean
make all
./test-hash && \
    ./test-kv && \
    echo 'ok'
