#!/bin/bash

cp ../../src/{vec.h,ref.h} ./
gcc -O2 main.c
rm ./{vec.h,ref.h}