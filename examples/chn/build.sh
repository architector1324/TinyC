#!/bin/bash

cp ../../src/{chn.h,vec.h} ./
gcc -O2  main.c
rm ./{chn.h,vec.h}