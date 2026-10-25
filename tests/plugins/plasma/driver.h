#pragma once
#include "grbl/hal.h"
#include <string.h>
#ifdef _WIN32
/* MinGW exports this POSIX spelling without declaring it in math.h. */
int isnanf(float value);
#endif
