#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char* argv[])
{
  int ch;

  // FIRST DLOPEN-DLCLOSE
  void *handle = dlopen("./omp_crash.so", RTLD_LAZY);
  void (*foo)();
  *(void**)(&foo) = dlsym(handle, "foo");
  foo();
  while ( (ch = getchar()) != '\n' && ch != EOF ) {}
  dlclose(handle);

  return 0;
}
