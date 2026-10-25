#pragma once
#include <string.h>
#include "grbl/hal.h"
#include "grbl/driver_opts.h"
#undef FS_ENABLE
#define FS_ENABLE FS_FATFS
