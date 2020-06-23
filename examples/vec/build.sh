#!/bin/bash

cp ../../src/vec.h ./
gcc -O2 $1
rm ./vec.h