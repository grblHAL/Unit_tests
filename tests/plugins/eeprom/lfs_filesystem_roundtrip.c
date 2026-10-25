#include "eeprom_host.h"
#include "littlefs/lfs.h"
int main(void)
{
 prepare_eeprom(); CHECK(i2c_eeprom_init()); hal.nvs.size = 4096; memset(memory, 0x5A, 4096);
 const struct lfs_config *config = eeprom_littlefs_hal();
 CHECK(config && config->block_size == 256 && config->block_count == 48);
 lfs_t fs = {0}; CHECK(lfs_format(&fs, config) == 0); CHECK(lfs_mount(&fs, config) == 0);
 lfs_file_t file = {0}; const char job[] = "G1X10\nM2\n";
 CHECK(lfs_file_open(&fs, &file, "job.ngc", LFS_O_WRONLY | LFS_O_CREAT | LFS_O_TRUNC) == 0);
 CHECK(lfs_file_write(&fs, &file, job, sizeof(job) - 1) == (lfs_ssize_t)(sizeof(job) - 1));
 CHECK(lfs_file_close(&fs, &file) == 0); CHECK(lfs_unmount(&fs) == 0);
 CHECK(lfs_mount(&fs, config) == 0); CHECK(lfs_file_open(&fs, &file, "job.ngc", LFS_O_RDONLY) == 0);
 char restored[sizeof(job)] = {0}; CHECK(lfs_file_read(&fs, &file, restored, sizeof(restored)) == (lfs_ssize_t)(sizeof(job) - 1));
 CHECK(strcmp(restored, job) == 0); CHECK(lfs_file_close(&fs, &file) == 0); CHECK(lfs_unmount(&fs) == 0);
 for(unsigned i = 0; i < 4096; i++) CHECK(memory[i] == 0x5A);
 return 0;
}
