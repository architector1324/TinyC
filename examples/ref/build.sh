#!/bin/bash

cp ../../src/{vec.h,ref.h} ./
gcc -O2 -Wall main.c
rm ./{vec.h,ref.h}