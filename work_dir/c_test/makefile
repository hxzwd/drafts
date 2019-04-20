
#!/bin/bash


#gcc sig_test.c -o bin_sig_test -std=c99

all:
	gcc -c sig_test_2.c -o siglib.o -std=c99 -fPIC
	gcc -shared siglib.o -o libsig_test.so


