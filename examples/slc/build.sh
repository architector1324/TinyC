#!/bin/bash

cp ../../src/{slc.h,vec.h,arr.h} ./
gcc -O2 -Wall main.c
rm ./{slc.h,vec.h,arr.h}