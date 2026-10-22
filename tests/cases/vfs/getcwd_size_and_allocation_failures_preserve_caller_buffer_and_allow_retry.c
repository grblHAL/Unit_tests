#include "support/vfs_resource_host.h"
int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_chdir("/store/jobs") == 0);
    CHECK(vfs_getcwd(NULL, 1) == NULL && vfs_errno == ERANGE);
    char directory[64] = "unchanged";
    rejected_size = strlen("/store/") + strlen("/jobs") + 3;
    reject_malloc = 1;
    CHECK(vfs_getcwd(directory, sizeof(directory)) == NULL);
    CHECK(malloc_failures == 1 && vfs_errno == ENOMEM);
    CHECK(strcmp(directory, "unchanged") == 0);
    CHECK(vfs_getcwd(directory, sizeof(directory)) == directory && vfs_errno == 0);
    CHECK(strcmp(directory, "/store/jobs") == 0);
    cleanup_operations();
    return EXIT_SUCCESS;
}
