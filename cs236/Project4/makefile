
# makefile for project 4 pass-off tests

NUM:=4

buckets:=20 40 60 80 100
numbers_20:=21 22 23 24
numbers_40:=41 42 44
numbers_60:=61 62
numbers_80:=81 82 84
numbers_100:=101 102 103 104 105 108

tests:=project$(NUM)-passoff

.SILENT: all $(buckets)

all: $(buckets)

$(buckets):
	echo "Bucket $@"; \
	for number in ${numbers_$@} ; \
	do \
		echo "Running input $$number" ; \
		./lab$(NUM) $(tests)/$@/input$$number.txt > $(tests)/myout$$number.txt ; \
		diff $(tests)/$@/answer$$number.txt $(tests)/myout$$number.txt || (echo "diff failed on test $$number \n") ; \
	done \

compile:
	g++ -Wall -Werror -std=c++17 -g main.cpp -o lab$(NUM)

