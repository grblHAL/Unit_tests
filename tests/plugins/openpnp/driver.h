#pragma once
#include <string.h>
#include "grbl/hal.h"
#ifndef _WIN32
/* Decimal conversion supplied by embedded SDKs, absent from POSIX libc. */
char *itoa(int value, char *string, int radix);
#endif
