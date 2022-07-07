#!/bin/bash

clear
nvc++ -g -fPIC -std=c++11 -mp=gpu -gpu=pinned -shared mpiabort.c -o mpiabort.so
OMP_TARGET_OFFLOAD=MANDATORY python wrapper.py
