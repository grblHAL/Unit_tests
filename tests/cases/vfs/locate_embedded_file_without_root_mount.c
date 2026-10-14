#include "support/vfs_locate_host.h"
int main(void)
{
    mount_lookup_sources(false,false,true);
    embedded_found = true;
    const char *path = vfs_locate_file("panel.nc");
    CHECK(path && strcmp(path,"/embedded/panel.nc") == 0);
    CHECK(lookup_count == 1);
    unmount_lookup_sources(false,false,true);
    return EXIT_SUCCESS;
}
