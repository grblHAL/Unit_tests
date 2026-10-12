#include "hal.h"
#include "fs_ram.h"
#include "support/backend_close.h"
#include "check.h"

int main(void)
{
    fs_ram_mount(); vfs_file_t *file = vfs_open("/ram/job", "w"); CHECK(file != NULL);
    uint8_t input[4096], output[4096]; for(unsigned i = 0; i < sizeof(input); i++) input[i] = (uint8_t)i;
    CHECK(vfs_write(input, 1, sizeof(input), file) == sizeof(input)); backend_close(file);
    file = vfs_open("/ram/job", "r"); CHECK(file != NULL);
    CHECK(vfs_read(output, 1, sizeof(output), file) == sizeof(output)); CHECK(memcmp(input, output, sizeof(input)) == 0); backend_close(file);
    return EXIT_SUCCESS;
}
