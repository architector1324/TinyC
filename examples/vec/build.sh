#!/bin/bash

cp ../../src/vec.h ./
gcc -O2 -Wall $1
rm ./vec.h