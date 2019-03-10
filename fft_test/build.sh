
#!/bin/bash

#gcc main.c -I/usr/include/gsl -L/usr/lib -lgsl -lgslcblas -lm -o bin_fft
gcc main.c -L/usr/local/lib -lgsl -lgslcblas -lm -o bin_fft

