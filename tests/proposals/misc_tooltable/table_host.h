#pragma once
#include "check.h"
#include "grbl/hal.h"
#include "grbl/vfs.h"
extern bool file_exists, fail_read, fail_write;
extern char table_text[4096];
extern unsigned opens, closes, selections, changes, mount_calls, options, reports;
void start_table(void);
