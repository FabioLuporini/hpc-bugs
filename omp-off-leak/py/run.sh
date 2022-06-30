#!/bin/bash

clear
aompcc -O3 -g -fPIC -Wall -Wno-unused-result -Wno-unused-variable -ffast-math -shared omp_off_leak_mfe.c  -lm -o omp_off_leak_mfe.so
cp omp_off_leak_mfe.so omp_off_leak_mfe_1.so
cp omp_off_leak_mfe.so omp_off_leak_mfe_2.so
python wrapper.py
