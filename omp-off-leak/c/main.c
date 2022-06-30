#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char* argv[])
{
  int ch;

  // FIRST DLOPEN-DLCLOSE
  void *handle = dlopen("./omp_off_leak_mfe.so", RTLD_LAZY);
  void (*func_print_name)();
  *(void**)(&func_print_name) = dlsym(handle, "foo");
  func_print_name();
  while ( (ch = getchar()) != '\n' && ch != EOF ) {}
  dlclose(handle);

  // SECOND DLOPEN-DLCLOSE
  void *handle2 = dlopen("./omp_off_leak_mfe_1.so", RTLD_LAZY);
  void (*func_print_name2)();
  *(void**)(&func_print_name2) = dlsym(handle2, "foo");
  func_print_name2();
  while ( (ch = getchar()) != '\n' && ch != EOF ) {}
  dlclose(handle2);

  // THIRD DLOPEN-DLCLOSE
  void *handle3 = dlopen("./omp_off_leak_mfe_2.so", RTLD_LAZY);
  void (*func_print_name3)();
  *(void**)(&func_print_name3) = dlsym(handle3, "foo");
  func_print_name3();
  while ( (ch = getchar()) != '\n' && ch != EOF ) {}
  dlclose(handle3);

  return 0;
}
