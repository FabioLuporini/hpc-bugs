#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char* argv[])
{
  printf("START!\n");

  // Load and run first kernel
  void *handle = dlopen("./kernel0.so", RTLD_LAZY);
  void (*functor)();
  *(void**)(&functor) = dlsym(handle, "foo");
  functor();

  // Load and run second kernel
  void *handle2 = dlopen("./kernel1.so", RTLD_LAZY);
  void (*functor2)();
  *(void**)(&functor2) = dlsym(handle2, "foo");
  functor2();

  dlclose(handle);
  dlclose(handle2);

  printf("FINISH!\n");

  return 0;
}
