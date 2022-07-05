#!/bin/bash

clear
nvc++ -g -fPIC -std=c++11 -mp=gpu -gpu=pinned -shared unoffloaded.c -o unoffloaded.so
OMP_TARGET_OFFLOAD=MANDATORY python wrapper.py
