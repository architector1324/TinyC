#!/bin/bash

cp ../../src/arr.h ./
gcc -O2 -Wall main.c
rm ./arr.h