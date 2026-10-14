#include "support/vfs_locate_host.h"
int main(void)
{
    mount_lookup_sources(true,true,true);
     CHECK(vfs_locate_file("panel.nc") == NULL);
    CHECK(lookup_count == 3);
    unmount_lookup_sources(true,true,true);
    return EXIT_SUCCESS;
}
