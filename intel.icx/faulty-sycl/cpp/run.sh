#!/bin/bash

set -x

clear
rm -f *.so main
icpx -O3 -fPIC -Wall -fsycl -gline-tables-only -fdebug-info-for-profiling -shared kernel0.cpp -lm -o kernel0.so
icpx -O3 -fPIC -Wall -fsycl -gline-tables-only -fdebug-info-for-profiling -shared kernel1.cpp -lm -o kernel1.so
icpx -O3 -Wall main.cpp -ldl -o main
./main
