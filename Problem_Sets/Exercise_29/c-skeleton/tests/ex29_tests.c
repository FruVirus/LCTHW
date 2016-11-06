#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>

typedef int (*lib_function)(const char *data);

int main(int argc,char *argv[])
{
    int rc = 0;
    check(argc == 4,"USAGE: ex29 libex29.so function data");

    char *lib_file = argv[1];
    char *func_to_run = argv[2];
    char *data = argv[3];

    // Load and link a dynamic library or bundle.
    // 'RTLD_NOW': All external function references are bound immediately during the call to 'dlopen'. This is useful to ensure that any undefined symbols are discovered during the call to 'dlopen'.
    void *lib = dlopen(lib_file,RTLD_NOW);
    check(lib != NULL,"Failed to open the library %s: %s",lib_file,dlerror());

    // Return the address of the code or data location specified by the null-terminated character string 'func_to_run'.
    // Which libraries and bundles are searched depends on the 'lib' parameter.
    lib_function func = dlsym(lib,func_to_run);
    check(func != NULL,"Did not find %s function in the library %s: %s",func_to_run,lib_file,dlerror());

    rc = func(data);
    check(rc == 0,"Function %s return %d for data: %s",func_to_run,rc,data);

    // Close a dynamic library or bundle.
    rc = dlclose(lib);
    check(rc == 0,"Failed to close %s",lib_file);

    return 0;

error:
    return 1;
}
