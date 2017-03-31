#ifndef __GSYSTEM_H__
#define __GSYSTEM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 0x4000

#ifdef __cplusplus
extern "C"{
#endif

void prerror(const char *mssg, const char *origin);
int load_file(char **mf);

#ifdef __cplusplus
}
#endif


#endif

