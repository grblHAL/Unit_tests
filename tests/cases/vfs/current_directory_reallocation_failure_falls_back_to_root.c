#define TRACK_FAILED_REALLOC 1
#include "support/vfs_resource_host.h"
int main(void)
{
    prepare_operations((vfs_st_mode_t){0});
    char first[128] = "/store/", second[144] = "/store/";
    memset(first + 7, 'a', 110); first[117] = 0;
    memset(second + 7, 'b', 120); second[127] = 0;
    CHECK(vfs_chdir(first) == 0);
    rejected_size = strlen(second) + 1;
#ifdef HOST_STRSET_API
    rejected_size++; /* strset reserves capacity plus its terminator. */
#endif
    reject_realloc = 1;
    CHECK(vfs_chdir(second) == -1 && realloc_failures == 1);
    char cwd[16]; CHECK(vfs_getcwd(cwd, sizeof(cwd)) != NULL);
    CHECK(strcmp(cwd, "/") == 0);
    /* The current core retains reachable owned storage when growth fails. */
    CHECK(!failed_realloc_released);
    CHECK(vfs_chdir(first) == 0);
    char recovered[128];
    CHECK(vfs_getcwd(recovered, sizeof(recovered)) == recovered);
    CHECK(strcmp(recovered, first) == 0);
    cleanup_operations();
    return EXIT_SUCCESS;
}
