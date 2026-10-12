#include "hal.h"
#include "fs_ram.h"
#include "vfs.h"
#include "check.h"

int main(void)
{
    fs_ram_mount();
    CHECK(vfs_open("/ram/missing", "r") == NULL);
    return EXIT_SUCCESS;
}
