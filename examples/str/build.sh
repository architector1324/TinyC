#!/bin/bash

cp ../../src/{vec.h,str.h} ./
gcc -O2 -Wall main.c
rm ./{vec.h,str.h}