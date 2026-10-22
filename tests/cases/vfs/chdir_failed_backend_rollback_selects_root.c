#include "support/vfs_operations_host.h"
#include "check.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_chdir("/store/dir") == 0);
    operation_result = -1;
    CHECK(vfs_chdir("/store/other") == -1);
    CHECK(vfs_errno == EIO);
    char cwd[16];
    CHECK(vfs_getcwd(cwd, sizeof(cwd)) == cwd);
    CHECK(strcmp(cwd, "/") == 0);
    unsigned previous_unlinks = unlink_calls;
    CHECK(vfs_unlink("file") == -1);
    CHECK(unlink_calls == previous_unlinks);
    cleanup_operations();
    return EXIT_SUCCESS;
}
