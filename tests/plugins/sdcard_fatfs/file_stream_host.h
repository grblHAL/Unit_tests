#pragma once
#include "fatfs_host.h"
#include "../sdcard_stream/sd_host.h"
static inline void prepare_fatfs_job(void)
{
    sd_prepare(true);
    const char data[] = "G1X1\nM30\n";
    fatfs_put_file("/JOB.NC", data, sizeof(data) - 1);
}
