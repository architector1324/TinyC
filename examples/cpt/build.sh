#!/bin/bash

cp ../../src/{cpt.h,arr.h,vec.h,chn.h,tup.h} ./
gcc -O2 $1 -lgmp
rm ./{cpt.h,arr.h,vec.h,chn.h,tup.h}
