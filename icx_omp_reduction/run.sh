#!/bin/bash

clear
source /opt/intel/oneapi/compiler/latest/env/vars.sh
# FAIL:
icx -qopenmp icx_reduction.c -lm -o icx_reduction.so
# PASS:
# icx -fopenmp icx_reduction.c -lm -o icx_reduction.so

