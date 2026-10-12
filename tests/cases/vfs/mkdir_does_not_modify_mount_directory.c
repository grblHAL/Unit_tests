#include "vfs.h"
#include <errno.h>
#include <string.h>
#include "check.h"
static unsigned mkdir_calls;
static int make_directory(const char *path) { CHECK(strcmp(path, "/new") == 0); mkdir_calls++; return 0; }
int main(void)
{
    vfs_t fs = { .fs_name = "test", .fmkdir = make_directory };
    CHECK(vfs_mount(NULL, "/test", &fs, (vfs_st_mode_t){0}));
    CHECK(vfs_mkdir("/test") == -1);
    CHECK(vfs_errno == EISDIR && mkdir_calls == 0);
    CHECK(vfs_unmount(NULL, "/test"));
    return EXIT_SUCCESS;
}
