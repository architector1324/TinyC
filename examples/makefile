run:
	if [[ -L makefile ]]; then cd .. && make $(addprefix $(shell pwd)/,$(addsuffix .out,$(basename $(wildcard *.c)))); else make all; fi

all: $(wildcard ../src/*) $(addsuffix .out,$(basename $(shell find -name *.c)))

%.out: %.c
	gcc -I ../src $^ -O2 -Wall -o $@ -lgmp -pthread

clean:
	if [[ -L makefile ]]; then cd .. && make $(shell pwd)/clean; else make clean_all; fi

clean_all:
	rm -r */*.out

%/clean:
	rm $(@:/clean=/*.out)