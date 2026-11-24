#pragma once
#ifdef _WIN32
#include "../../include/windows_string_compat.h"
#include <windows.h>
#include <math.h>
// FatFs supplies its own Windows forms of these macros.
#undef isnan
#undef isinf
#endif
#include "ff.h"
#ifdef _WIN32
#undef NEAR
#endif
