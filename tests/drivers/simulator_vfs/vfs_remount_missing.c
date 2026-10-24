#include "vfs_host.h"
int main(void)
{
 sim_prepare("/"); sim_finish("/");
 bool mounted = fs_posix_mount("/", sim_backing); CHECK(sim_mounts == 1); CHECK(!mounted); return 0;
}
