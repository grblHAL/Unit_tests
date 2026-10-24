#pragma once
#include "embroidery.h"
#include "grbl/fs_embedded.h"
#include "check.h"
#include <string.h>
extern grbl_t grbl;
extern uint8_t pattern[4096];
extern embroidery_t pattern_api;
extern vfs_file_t *pattern_file;
bool tajima_open_file(vfs_file_t *file, embroidery_t *api);
bool brother_open_file(vfs_file_t *file, embroidery_t *api);
void pattern_mount(size_t length);
void dst_header(const char *name);
void dst_open(const uint8_t *stitches, size_t length);
void pes_open(const uint8_t *stitches, size_t length);
stitch_t next_stitch(stich_type_t type, float x, float y);
void pattern_close(void);
