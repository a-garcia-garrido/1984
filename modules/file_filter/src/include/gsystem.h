#ifndef __GSYSTEM_H__
#define __GSYSTEM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <unistd.h>


#define MAX_BUFFER 0x4000
#define MAX_FN     0x400

#ifdef __cplusplus
extern "C"{
#endif

void prerror(const char *mssg, ...);
int load_file(char **mf);
char *get_self_executable_dir();

#ifdef __cplusplus
}
#endif


#endif

