#!/bin/bash

cp ../../src/arr.h ./
gcc -O2 main.c
rm ./arr.h