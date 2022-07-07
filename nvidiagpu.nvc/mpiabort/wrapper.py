try:
    from mpi4py import MPI
except ImportError:
    print("You must install mpi4py before running this reproducer")
    import sys
    sys.exit(0)

import numpy.ctypeslib as npct

print("Loading shared object from Python ...")

libname = 'mpiabort.so'
lib = npct.load_library(libname, '.')
lib.name = libname

# `foo` name of entry point in `mpiabort.c`
cfunction = lib.foo
cfunction.argtypes = []

print("Calling into shared object entry point (foo function) ...")

cfunction()

print("Done!")
