#pragma once
#include "driver.h"
#include "ff.h"
#include "diskio.h"
#ifdef _WIN32
#undef NEAR
#endif
#include "check.h"
#include "grbl/vfs.h"
#include "fs_fatfs.h"
extern unsigned fatfs_reads, fatfs_writes;
extern bool fatfs_read_error;
void fatfs_prepare(void);
void fatfs_put_file(const char *name, const void *data, size_t size);
