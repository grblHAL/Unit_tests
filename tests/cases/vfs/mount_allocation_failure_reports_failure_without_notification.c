#include "support/vfs_resource_host.h"
static unsigned mounted_events;
static void mounted(const char *path, const vfs_t *fs, vfs_st_mode_t mode)
{ (void)path; (void)fs; (void)mode; mounted_events++; }
int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    vfs.on_mount = mounted; reject_calloc = 1;
    vfs_t other = operation_fs; other.fs_name = "second";
    bool result = vfs_mount(NULL, "/second", &other, (vfs_st_mode_t){0});
    CHECK(calloc_failures == 1);
    fprintf(stderr, "mount allocation rejected: result=%u, notifications=%u\n", result, mounted_events);
    CHECK(!result && mounted_events == 0);
    vfs.on_mount = NULL; cleanup_operations();
    return EXIT_SUCCESS;
}
