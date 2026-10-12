#include "vfs.h"
#include <string.h>
#include "check.h"
static unsigned rename_calls, change_calls;
static const vfs_t *changed_fs;
static int rename_file(const char *from, const char *to) { CHECK(strcmp(from, "/source") == 0); CHECK(strcmp(to, "/target") == 0); rename_calls++; return 0; }
static void changed(const vfs_t *fs) { changed_fs = fs; change_calls++; }
int main(void)
{
    vfs_t fs = { .fs_name = "test", .frename = rename_file };
    CHECK(vfs_mount(NULL, "/test", &fs, (vfs_st_mode_t){0}));
    vfs.on_fs_changed = changed;
    CHECK(vfs_rename("/test/source", "/test/target") == 0);
    CHECK(rename_calls == 1 && change_calls == 1);
    CHECK(changed_fs == &fs);
    CHECK(vfs_unmount(NULL, "/test"));
    return EXIT_SUCCESS;
}
