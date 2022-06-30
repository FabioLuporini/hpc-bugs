#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char* argv)
{
  void *handle = dlopen("./libdog.so", RTLD_LAZY);

  void (*func_print_name)();

  *(void**)(&func_print_name) = dlsym(handle, "foo");
  if (!func_print_name) {
      /* no such symbol */
      printf("Error: %s\n", dlerror());
      dlclose(handle);
      return 0;
  }

  func_print_name();
  dlclose(handle);

  return 0;
}
