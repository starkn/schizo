tests:=images
my:=myimages

numbers:=1 2 3 4 5

all:
	gcc -g -Wall -DDEBUG bmpFilter.c -o debug
	gcc -g -Wall bmpFilter.c -o main

	

	for number in ${numbers} ; \
	do \
		echo "Running input $$number" ; \
		./main < $(tests)/orig$$number.bmp > $(my)/threshold$$number.bmp ; \
		./main -g < $(tests)/orig$$number.bmp > $(my)/grayscale$$number.bmp ; \
		xxd $(my)/grayscale$$number.bmp > $(my)/grayscale$$number.txt ; \
		xxd $(my)/threshold$$number.bmp > $(my)/threshold$$number.txt ; \
		diff $(tests)/threshold$$number.txt $(my)/threshold$$number.txt > out.txt || (echo "diff failed on threshold $$number \n") ; \
		diff $(tests)/grayscale$$number.txt $(my)/grayscale$$number.txt > out.txt || (echo "diff failed on grayscale $$number \n") ; \
	done \