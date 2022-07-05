#!/bin/bash

clear
OMP_TARGET_OFFLOAD=MANDATORY clang -Xopenmp-target -march=sm_70 -fopenmp -fopenmp-targets=nvptx64 gt32.c -O gt32
