#!/bin/bash

nvc -g -fPIC -gpu=pinned -mp=gpu -fast -shared omp_crash.c -lm -o omp_crash.so
nvc -O3 -g -Wall main.c -ldl -o main
./main
