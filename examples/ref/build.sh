#!/bin/bash

cp ../../src/{vec.h,wrap.h} ./
gcc -O2 -Wall main.c
rm ./{vec.h,wrap.h}