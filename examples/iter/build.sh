#!/bin/bash

cp ../../src/{iter.h,tup.h} ./
gcc -O2 $1
rm ./{iter.h,tup.h}