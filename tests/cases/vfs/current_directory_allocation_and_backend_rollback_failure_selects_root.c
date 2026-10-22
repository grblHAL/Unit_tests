#include "support/vfs_resource_host.h"

static bool reject_rollback;
static char previous_directory[128];
static int change_with_failed_rollback(const char *path)
{
    if(reject_rollback && strcmp(path, previous_directory) == 0)
        return -1;
    return operation_chdir(path);
}
int main(void)
{
    operation_fs.fchdir = change_with_failed_rollback;
    prepare_operations((vfs_st_mode_t){0});
    char first[128] = "/store/", second[144] = "/store/";
    memset(first + 7, 'a', 110); first[117] = 0;
    memset(second + 7, 'b', 120); second[127] = 0;
    CHECK(vfs_chdir(first) == 0);
    strcpy(previous_directory, first + 6);
    rejected_size = strlen(second) + 1;
#ifdef HOST_STRSET_API
    rejected_size++;
#endif
    reject_rollback = true;
    reject_realloc = 1;
    CHECK(vfs_chdir(second) == -1 && realloc_failures == 1);
    CHECK(vfs_errno == EIO);
    char directory[144];
    CHECK(vfs_getcwd(directory, sizeof(directory)) == directory);
    CHECK(strcmp(directory, "/") == 0);
    unsigned previous_unlinks = unlink_calls;
    CHECK(vfs_unlink("part.nc") == -1);
    CHECK(unlink_calls == previous_unlinks);

    reject_rollback = false;
    CHECK(vfs_chdir(second) == 0);
    CHECK(vfs_getcwd(directory, sizeof(directory)) == directory);
    CHECK(strcmp(directory, second) == 0);
    CHECK(vfs_unlink("part.nc") == 0);
    CHECK(strcmp(unlink_directory, second + 6) == 0);
    cleanup_operations();
    return EXIT_SUCCESS;
}
