#pragma once
#include "hal.h"
#include "fs_ram.h"
#include "vfs.h"
#include "check.h"
#include "support/tracked_malloc_host.h"
#include "support/realloc_failure_host.h"
#include <string.h>
static char ram_program[1024];
static size_t ram_program_length;
static inline void prepare_ram_file_allocation(void)
{
    fs_ram_mount();
    for(unsigned line = 0; line < 64; line++) strcat(ram_program, "G1X1F100\n");
    ram_program_length = strlen(ram_program);
}
static inline void check_new_ram_job_can_be_written_and_read(void)
{
    vfs_file_t *file = vfs_open("/ram/retry", "w");
    CHECK(file != NULL);
    CHECK(vfs_write(ram_program, 1, ram_program_length, file) == ram_program_length);
    vfs_close(file);
    file = vfs_open("/ram/retry", "r");
    CHECK(file != NULL);
    char received[sizeof(ram_program)];
    CHECK(vfs_read(received, 1, sizeof(received), file) == ram_program_length);
    CHECK(memcmp(received, ram_program, ram_program_length) == 0);
    CHECK(vfs_eof(file));
    vfs_close(file);
    CHECK(vfs_open("/ram/retry", "r") == NULL);
}
