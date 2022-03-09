test_code.o: checksum.c encrypt.c test_code.c 
	gcc -c *.c 

test_code: checksum.o encrypt.o test_code.o
	gcc checksum.o encrypt.o test_code.o -o test_code
