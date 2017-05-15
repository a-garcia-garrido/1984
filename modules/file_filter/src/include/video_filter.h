#ifndef __VIDEO_FILTER_H__
#define __VIDEO_FILTER_H__

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF 0x4000

const char *filter_name = "video_filter";
const char *filter_desc = "video filetype filter";

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
