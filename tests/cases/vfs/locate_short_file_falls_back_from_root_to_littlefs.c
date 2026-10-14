#include "support/vfs_locate_host.h"
int main(void)
{
    mount_lookup_sources(true,true,true);
    little_found = embedded_found = true;
    const char *path = vfs_locate_file("panel.nc");
    CHECK(path && strcmp(path,"/littlefs/panel.nc") == 0);
    CHECK(strcmp(lookup_trace,"root:/panel.nc;little:/panel.nc;") == 0);
    unmount_lookup_sources(true,true,true);
    return EXIT_SUCCESS;
}
