#!/bin/bash

cp ../../src/{thrd.h,vec.h} ./
gcc -O2 -Wall $1 -pthread
rm ./{thrd.h,vec.h}