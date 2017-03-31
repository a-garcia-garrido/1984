#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "filter.h"
#include "gsystem.h"

#define MAX_FILTER 0x20
#define MAX_LINE   0x200

struct TStack {
    void *data[MAX_FILTER];
    int summit;
};

#ifdef __cplusplus
extern "C"{
#endif

bool push(const char *filter_name, struct TStack *s);
bool pop(struct TStack *s);
void clear(struct TStack *s);
void *each( void *(*fn)(void *el, void *return_value), struct TStack *s );

bool pass_all(struct TStack *s);
bool pass_any(struct TStack *s);

#ifdef __cplusplus
}
#endif


#endif

