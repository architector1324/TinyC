#!/bin/bash

cp ../../src/tup.h ./
gcc -O2 main.c
rm ./tup.h