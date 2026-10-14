#pragma once
#include "vfs.h"
#include "check.h"
#include <errno.h>
#include <string.h>
static vfs_file_t operation_file;
static unsigned open_calls, close_calls, change_calls, unlink_calls, mkdir_calls, rmdir_calls, chdir_calls, stat_calls;
static int operation_result, stat_result;
static bool stat_directory = true;
static char operation_path[256], operation_mode[16], backend_directory[256] = "/", unlink_directory[256];
static vfs_st_mode_t chmod_attr, chmod_mask;
static struct tm captured_time;
static void capture_path(const char *path) { CHECK(strlen(path) < sizeof(operation_path)); strcpy(operation_path, path); }
static vfs_file_t *operation_open(const char *path, const char *mode)
{ capture_path(path); strcpy(operation_mode, mode); open_calls++; memset(&operation_file, 0, sizeof(operation_file)); return &operation_file; }
static void operation_close(vfs_file_t *file) { CHECK(file == &operation_file); close_calls++; }
static int operation_unlink(const char *path) { capture_path(path); strcpy(unlink_directory, backend_directory); unlink_calls++; return operation_result; }
static int operation_mkdir(const char *path) { capture_path(path); mkdir_calls++; return operation_result; }
static int operation_rmdir(const char *path) { capture_path(path); rmdir_calls++; return operation_result; }
static int operation_chdir(const char *path) { capture_path(path); chdir_calls++; if(operation_result == 0) strcpy(backend_directory, path); return operation_result; }
static int operation_stat(const char *path, vfs_stat_t *st)
{ capture_path(path); stat_calls++; st->st_mode.directory = stat_directory; st->st_size = 123; return stat_result; }
static int operation_chmod(const char *path, vfs_st_mode_t attr, vfs_st_mode_t mask)
{ capture_path(path); chmod_attr = attr; chmod_mask = mask; return operation_result; }
static int operation_utime(const char *path, struct tm *time)
{ capture_path(path); captured_time = *time; return operation_result; }
static vfs_t operation_fs = {.fs_name = "store", .fopen = operation_open, .fclose = operation_close,
 .funlink = operation_unlink, .fmkdir = operation_mkdir, .frmdir = operation_rmdir,
 .fchdir = operation_chdir, .fstat = operation_stat, .fchmod = operation_chmod, .futime = operation_utime};
static void operation_changed(const vfs_t *fs) { CHECK(fs == &operation_fs); change_calls++; }
static inline void prepare_operations(vfs_st_mode_t mode)
{ CHECK(vfs_mount(NULL, "/store", &operation_fs, mode)); vfs.on_fs_changed = operation_changed; }
static inline void cleanup_operations(void)
{ vfs.on_fs_changed = NULL; CHECK(vfs_unmount(NULL, "/store")); }
