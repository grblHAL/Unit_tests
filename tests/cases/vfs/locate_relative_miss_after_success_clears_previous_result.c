#include "support/vfs_locate_host.h"
int main(void)
{
    mount_lookup_sources(true,false,false);
    root_found = true;
    CHECK(vfs_locate_file("panel.nc") != NULL);
    root_found = false;
    CHECK(vfs_locate_file("missing.nc") == NULL);
    CHECK(lookup_count == 2);
    unmount_lookup_sources(true,false,false);
    return EXIT_SUCCESS;
}
