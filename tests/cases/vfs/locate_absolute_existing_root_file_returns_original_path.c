#include "support/vfs_locate_host.h"
int main(void)
{
    mount_lookup_sources(true,false,false);
    root_found = true;
    const char name[] = "/panel.nc";
    CHECK(vfs_locate_file(name) == name);
    CHECK(lookup_count == 1);
    unmount_lookup_sources(true,false,false);
    return EXIT_SUCCESS;
}
