#include "vfs.h"
#include "check.h"
static unsigned change_calls;
static int rename_file(const char *from, const char *to) { (void)from; (void)to; return -1; }
static void changed(const vfs_t *fs) { (void)fs; change_calls++; }
int main(void)
{
    vfs_t fs = { .fs_name = "test", .frename = rename_file };
    CHECK(vfs_mount(NULL, "/test", &fs, (vfs_st_mode_t){0}));
    vfs.on_fs_changed = changed;
    CHECK(vfs_rename("/test/source", "/test/target") == -1);
    CHECK(change_calls == 0);
    CHECK(vfs_unmount(NULL, "/test"));
    return EXIT_SUCCESS;
}
