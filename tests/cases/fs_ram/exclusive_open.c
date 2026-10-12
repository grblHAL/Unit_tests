#include "hal.h"
#include "fs_ram.h"
#include "support/backend_close.h"
#include "check.h"

int main(void)
{
    fs_ram_mount(); vfs_file_t *writer = vfs_open("/ram/job", "w"); CHECK(writer != NULL);
    CHECK(vfs_open("/ram/job", "w") == NULL); CHECK(vfs_open("/ram/job", "r") == NULL);
    backend_close(writer); vfs_file_t *reader = vfs_open("/ram/job", "r"); CHECK(reader != NULL); backend_close(reader);
    return EXIT_SUCCESS;
}
