#pragma once
#include "vfs.h"
#include "check.h"
#include <string.h>
static vfs_dir_t directory_handle;
static unsigned directory_close_calls;
static inline vfs_dir_t *open_directory(const char *path) { CHECK(strcmp(path, "/") == 0); return &directory_handle; }
static inline char *read_empty_directory(vfs_dir_t *dir, vfs_dirent_t *entry) { CHECK(dir == &directory_handle); entry->name[0] = 0; return NULL; }
static inline void close_directory(vfs_dir_t *dir) { CHECK(dir == &directory_handle); directory_close_calls++; }
static vfs_t directory_fs = { .fs_name = "root", .fopendir = open_directory, .readdir = read_empty_directory, .fclosedir = close_directory };
static inline void prepare_directory_root(void) { CHECK(vfs_mount(NULL, "/", &directory_fs, (vfs_st_mode_t){0})); }
