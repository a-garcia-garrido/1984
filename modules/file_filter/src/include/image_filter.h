#ifndef __IMAGE_FILTER_H__
#define __IMAGE_FILTER_H__

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF 0x4000

const char *filter_name = "image_filter";
const char *filter_desc = "image filetype filter";

#ifdef __cplusplus
extern "C" {
#endif

    bool filter_passes(void);
#ifndef NDEBUG
    void __attribute__ ((constructor)) on_load(void);
    void __attribute__ ((destructor)) on_unload(void);
#endif

#ifdef __cplusplus
}
#endif


#endif
