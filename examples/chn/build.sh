#!/bin/bash

cp ../../src/{chn.h,vec.h} ./
gcc -O2 -Wall main.c
rm ./{chn.h,vec.h}