#include "support/vfs_operations_host.h"
static unsigned target_unlink_calls;
static int target_unlink(const char *path) { capture_path(path); target_unlink_calls++; return 0; }
int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    vfs_t target = operation_fs; target.funlink = target_unlink;
    CHECK(vfs_mount(NULL, "/elsewhere", &target, (vfs_st_mode_t){0}));
    vfs.on_fs_changed = NULL;
    CHECK(vfs_unlink("/store/../elsewhere/file") == 0);
    CHECK(target_unlink_calls == 1 && unlink_calls == 0);
    fprintf(stderr, "target local path=%s, expected /file\n", operation_path);
    CHECK(strcmp(operation_path, "/file") == 0);
    CHECK(vfs_unmount(NULL, "/elsewhere")); cleanup_operations();
    return EXIT_SUCCESS;
}
