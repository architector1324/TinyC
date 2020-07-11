#!/bin/bash

cp ../../src/tup.h ./
gcc -O2 -Wall main.c
rm ./tup.h