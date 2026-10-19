#pragma once
/* The Windows CRT declares a legacy two-argument strset(). Hide only that
   unused declaration so the core's string_t API keeps its original name. */
#ifdef _WIN32
#define strset windows_crt_legacy_strset
#include <string.h>
#undef strset
#endif
