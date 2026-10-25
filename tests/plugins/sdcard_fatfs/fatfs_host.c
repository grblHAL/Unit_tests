#include "fatfs_host.h"
grbl_hal_t hal;
static uint8_t disk[2880][512];
static FATFS volume;
static fatfs_dev_t device;
static bool ready;
unsigned fatfs_reads, fatfs_writes;
bool fatfs_read_error;
static void word(uint8_t *p, uint16_t value)
{
    p[0] = value & 255;
    p[1] = value >> 8;
}
DSTATUS disk_initialize(BYTE drive)
{
    CHECK(drive == 0);
    ready = true;
    return 0;
}
DSTATUS disk_status(BYTE drive)
{
    CHECK(drive == 0);
    return ready ? 0 : STA_NOINIT;
}
DRESULT disk_read(BYTE drive, BYTE *buffer, LBA_t sector, UINT count)
{
    CHECK(drive == 0 && count && sector < 2880 && count <= 2880 - sector);
    fatfs_reads++;
    if (fatfs_read_error)
        return RES_ERROR;
    memcpy(buffer, disk[sector], count * 512);
    return RES_OK;
}
DRESULT disk_write(BYTE drive, const BYTE *buffer, LBA_t sector, UINT count)
{
    CHECK(drive == 0 && count && sector < 2880 && count <= 2880 - sector);
    fatfs_writes++;
    memcpy(disk[sector], buffer, count * 512);
    return RES_OK;
}
DRESULT disk_ioctl(BYTE drive, BYTE command, void *buffer)
{
    CHECK(drive == 0);
    switch (command)
    {
    case CTRL_SYNC:
        return RES_OK;
    case GET_SECTOR_COUNT:
        *(LBA_t *)buffer = 2880;
        return RES_OK;
    case GET_SECTOR_SIZE:
        *(WORD *)buffer = 512;
        return RES_OK;
    case GET_BLOCK_SIZE:
        *(DWORD *)buffer = 1;
        return RES_OK;
    default:
        CHECK(false);
        return RES_PARERR;
    }
}
DWORD get_fattime(void) { return ((2026 - 1980) << 25) | (10 << 21) | (25 << 16) | (12 << 11); }
bool stream_await_tx_clear(const io_stream_t *stream)
{
    (void)stream;
    CHECK(false);
    return false;
}
void fatfs_prepare(void)
{
    // Standard 1.44MiB FAT12 volume: two9-sector FATs,224 root entries,512-byte sectors.
    uint8_t *boot = disk[0];
    boot[0] = 0xeb;
    boot[1] = 0x3c;
    boot[2] = 0x90;
    memcpy(boot + 3, "MSDOS5.0", 8);
    word(boot + 11, 512);
    boot[13] = 1;
    word(boot + 14, 1);
    boot[16] = 2;
    word(boot + 17, 224);
    word(boot + 19, 2880);
    boot[21] = 0xf0;
    word(boot + 22, 9);
    word(boot + 24, 18);
    word(boot + 26, 2);
    boot[38] = 0x29;
    boot[39] = 0x12;
    memcpy(boot + 43, "TESTDISK   ", 11);
    memcpy(boot + 54, "FAT12   ", 8);
    boot[510] = 0x55;
    boot[511] = 0xaa;
    disk[1][0] = disk[10][0] = 0xf0;
    disk[1][1] = disk[1][2] = disk[10][1] = disk[10][2] = 0xff;
    CHECK(f_mount(&volume, "0:", 1) == FR_OK);
    device.fs = &volume;
    strcpy(device.name, "0:");
    fs_fatfs_mount("/", &device);
}
void fatfs_put_file(const char *name, const void *data, size_t size)
{
    vfs_file_t *file = vfs_open(name, "w");
    CHECK(file);
    CHECK(vfs_write(data, 1, size, file) == size);
    vfs_close(file);
}

bool protocol_execute_realtime(void) { CHECK(false);return false; }
bool protocol_exec_rt_system(void) { CHECK(false);return false; }
bool state_door_reopened(void) { CHECK(false);return false; }
