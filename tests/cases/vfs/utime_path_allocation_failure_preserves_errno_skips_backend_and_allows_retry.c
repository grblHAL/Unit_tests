#include "support/vfs_resource_host.h"
int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    CHECK(vfs_chdir("/store/jobs") == 0);
    char previous_path[sizeof(operation_path)];
    strcpy(previous_path, operation_path);
    struct tm updated = {.tm_year = 126, .tm_mon = 9, .tm_mday = 24,
                         .tm_hour = 12, .tm_min = 34, .tm_sec = 56};
    rejected_size = strlen("part.nc") + 1;
    reject_malloc = 1;
    int result = vfs_utime("part.nc", &updated);
    int failure_errno = vfs_errno;
    CHECK(result == -1 && malloc_failures == 1);
    CHECK(captured_time.tm_year == 0 && strcmp(operation_path, previous_path) == 0);
    CHECK(vfs_utime("part.nc", &updated) == 0 && vfs_errno == 0);
    CHECK(strcmp(operation_path, "/jobs/part.nc") == 0);
    CHECK(captured_time.tm_year == 126 && captured_time.tm_mon == 9 && captured_time.tm_mday == 24);
    CHECK(captured_time.tm_hour == 12 && captured_time.tm_min == 34 && captured_time.tm_sec == 56);
    char cwd[32];
    CHECK(vfs_getcwd(cwd, sizeof(cwd)) == cwd && strcmp(cwd, "/store/jobs") == 0);
    cleanup_operations();
    fprintf(stderr, "utime path allocation: result=%d errno=%d expected=%d; backend retry succeeded\n",
        result, failure_errno, ENOMEM);
    CHECK(failure_errno == ENOMEM);
    return EXIT_SUCCESS;
}
