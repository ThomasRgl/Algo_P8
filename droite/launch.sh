#!/bin/bash
gcc  main.c -o main.out
./main.out data/test.txt 2>/dev/null
gnuplot droite.gplot