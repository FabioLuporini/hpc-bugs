#!/bin/bash

clear
OMP_TARGET_OFFLOAD=MANDATORY clang -Xopenmp-target -march=sm_86 -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda gt32.c -o gt32
./gt32
