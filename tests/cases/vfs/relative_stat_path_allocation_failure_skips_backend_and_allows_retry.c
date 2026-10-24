#include "support/vfs_resource_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_chdir("/store/jobs") == 0);
    unsigned previous_stats = stat_calls;
    vfs_stat_t st = {0};
    rejected_size = strlen("part.nc") + 1;
    reject_malloc = 1;
    CHECK(vfs_stat("part.nc", &st) == -1);
    CHECK(vfs_errno == ENOMEM && malloc_failures == 1);
    CHECK(stat_calls == previous_stats);
    CHECK(vfs_stat("part.nc", &st) == 0);
    CHECK(vfs_errno == 0 && malloc_failures == 1);
    CHECK(stat_calls == previous_stats + 1);
    CHECK(strcmp(operation_path, "/jobs/part.nc") == 0);
    CHECK(st.st_size == 123);
    cleanup_operations();
    return EXIT_SUCCESS;
}
