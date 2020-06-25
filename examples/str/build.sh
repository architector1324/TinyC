#!/bin/bash

cp ../../src/{vec.h,str.h} ./
gcc -O2 main.c
rm ./{vec.h,str.h}