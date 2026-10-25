#pragma once
#include <string.h>
#include "grbl/hal.h"
#include "grbl/driver_opts.h"
#undef FS_ENABLE
#if TEST_FATFS_STREAM
#define FS_ENABLE FS_FATFS
#else
#define FS_ENABLE FS_POSIX
#endif
