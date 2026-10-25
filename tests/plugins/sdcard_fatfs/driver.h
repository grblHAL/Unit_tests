#pragma once
#include <string.h>
#include "grbl/hal.h"
#include "grbl/driver_opts.h"
#undef FS_ENABLE
#if TEST_SDCARD
#define FS_ENABLE (FS_FATFS | FS_SDCARD)
#else
#define FS_ENABLE FS_FATFS
#endif
