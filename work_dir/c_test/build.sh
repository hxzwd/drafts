
#!/bin/bash

gcc -c clib1.c -o clib1.o -std=c99 -fPIC
gcc -shared clib1.o -o libclib1.so


