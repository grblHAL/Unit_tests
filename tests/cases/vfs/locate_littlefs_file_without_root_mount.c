#include "support/vfs_locate_host.h"
int main(void)
{
    mount_lookup_sources(false,true,false);
    little_found = true;
    const char *path = vfs_locate_file("panel.nc");
    CHECK(path && strcmp(path,"/littlefs/panel.nc") == 0);
    CHECK(lookup_count == 1);
    unmount_lookup_sources(false,true,false);
    return EXIT_SUCCESS;
}
