import numpy.ctypeslib as npct

print("Starting... open up `htop` in another terminal to keep an eye on mem growth")

for libname in ('omp_off_leak_mfe.so',
                'omp_off_leak_mfe_1.so',
                'omp_off_leak_mfe_2.so'):
    lib = npct.load_library(libname, '.')
    lib.name = libname

    # `foo` name of entry point in `omp_off_leak_mfe.c`
    cfunction = lib.foo
    cfunction.argtypes = []

    cfunction()

    print("Check htop !! Then type `exit` to step to the next iteration...")
    from IPython import embed; embed()
