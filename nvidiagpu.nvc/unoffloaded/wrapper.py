import numpy.ctypeslib as npct

print("Loading shared object from Python ...")

libname = 'unoffloaded.so'
lib = npct.load_library(libname, '.')
lib.name = libname

# `foo` name of entry point in `unoffloaded.c`
cfunction = lib.foo
cfunction.argtypes = []

print("Calling into shared object entry point (foo function) ...")

cfunction()

print("Done!")
