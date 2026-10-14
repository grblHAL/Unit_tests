#include "support/vfs_operations_host.h"
int main(void)
{
    CHECK(vfs_mount(NULL, "/", &operation_fs, (vfs_st_mode_t){0}));
    const char *path = vfs_locate_file("workbee_panel_fixture_01.nc");
    CHECK(path && strcmp(path, "/workbee_panel_fixture_01.nc") == 0);
    CHECK(stat_calls == 1);
    CHECK(vfs_unmount(NULL, "/"));
    return EXIT_SUCCESS;
}
