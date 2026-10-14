#include "support/vfs_locate_host.h"
int main(void)
{
    mount_lookup_sources(false,false,false);
     CHECK(vfs_locate_file("panel.nc") == NULL);
    CHECK(lookup_count == 0);
    unmount_lookup_sources(false,false,false);
    return EXIT_SUCCESS;
}
