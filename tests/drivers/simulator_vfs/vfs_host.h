#pragma once
#include "misc_host.h"
#include "vfs.h"
#include "fs_posix.h"
#include <sys/stat.h>
#include <unistd.h>
extern char sim_backing[64];
extern unsigned sim_mounts, sim_changes;
void sim_prepare(const char *mount);
void sim_finish(const char *mount);
void sim_put(const char *path, const char *text);
void sim_expect(const char *path, const char *text);
