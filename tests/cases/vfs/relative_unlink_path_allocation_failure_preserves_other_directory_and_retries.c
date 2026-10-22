#include "support/vfs_resource_host.h"
static bool job_file = true, root_file = true;
static int remove_file(const char *path)
{
    capture_path(path);
    if(strcmp(path, "/jobs/part.nc") == 0) job_file = false;
    else if(strcmp(path, "part.nc") == 0 || strcmp(path, "/part.nc") == 0) root_file = false;
    else CHECK(false);
    return 0;
}
int main(void)
{
    operation_fs.fchdir = NULL;
    operation_fs.fgetcwd = NULL;
    operation_fs.funlink = remove_file;
    prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_chdir("/store/jobs") == 0);
    rejected_size = strlen("part.nc") + 1;
    reject_malloc = 1;
    int status = vfs_unlink("part.nc");
    CHECK(malloc_failures == 1);
    bool unrelated_preserved = root_file;
    fprintf(stderr, "Failed path allocation: status=%d, backend path=%s, root file remains=%u\n",
            status, operation_path, unrelated_preserved);
    CHECK(vfs_unlink("part.nc") == 0);
    CHECK(!job_file && strcmp(operation_path, "/jobs/part.nc") == 0);
    cleanup_operations();
    CHECK(unrelated_preserved);
    return EXIT_SUCCESS;
}
