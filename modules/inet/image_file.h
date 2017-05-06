#ifndef __IMAGE_FILE_H__
#define __IMAGE_FILE_H__

#include <stdlib.h>
#include <stdio.h>
#include <png.h>

#pragma pack(1)
struct Timage{
int width;
int height;
png_byte color_type;
png_byte bit_depth;
png_bytep *row_pointers;
};
#pragma pack(0)

#ifdef __cplusplus
extern "C"{
#endif

void read_png_file(char *, struct Timage);
void write_png_file(char *, struct Timage);

#ifdef __cplusplus
}
#endif

#endif
