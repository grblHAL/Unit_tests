#include "vfs.h"
#include <string.h>
#include "check.h"
static unsigned rename_calls;
static int rename_file(const char *from, const char *to) { (void)from; (void)to; rename_calls++; return 0; }
int main(void)
{
    vfs_t first = { .fs_name = "first", .frename = rename_file }, second = { .fs_name = "second", .frename = rename_file };
    CHECK(vfs_mount(NULL, "/one", &first, (vfs_st_mode_t){0}));
    CHECK(vfs_mount(NULL, "/two", &second, (vfs_st_mode_t){0}));
    CHECK(vfs_rename("/one/source", "/two/target") == -1);
    CHECK(rename_calls == 0);
    CHECK(vfs_unmount(NULL, "/one"));
    CHECK(vfs_unmount(NULL, "/two"));
    return EXIT_SUCCESS;
}
