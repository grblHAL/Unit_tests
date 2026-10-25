#include "embroidery_host.h"
grbl_t grbl;
uint8_t pattern[4096];
embroidery_t pattern_api;
vfs_file_t *pattern_file;
void pattern_mount(size_t length)
{
    CHECK(length <= sizeof(pattern));
    static embedded_file_t *file;
    static const embedded_file_t *files[2];
    file = malloc(sizeof(*file) + length);
    CHECK(file);
    file->name = "pattern";
    file->size = length;
    file->st_mode = (vfs_st_mode_t){.read_only = On};
    memcpy((void *)file->data, pattern, length);
    files[0] = file;
    CHECK(fs_embedded_mount(files));
    pattern_file = vfs_open("/embedded/pattern", "r");
    CHECK(pattern_file);
}
void dst_header(const char *name)
{
    memset(pattern, ' ', 512);
    char header[256];
    int count =
        snprintf(header, sizeof(header), "LA:%s\rST:4\rCO:2\r+X:121\r-X:20\r+Y:80\r-Y:11\r", name);
    CHECK(count > 0 && count < 200);
    memcpy(pattern, header, count);
    pattern[count] = ASCII_EOF;
}
void dst_open(const uint8_t *stitches, size_t length)
{
    dst_header("Pocket");
    CHECK(512 + length <= sizeof(pattern));
    memcpy(pattern + 512, stitches, length);
    pattern_mount(512 + length);
    CHECK(tajima_open_file(pattern_file, &pattern_api));
    CHECK(vfs_tell(pattern_file) == 512);
}
void pes_open(const uint8_t *stitches, size_t length)
{
    // A PES container points to the PEC label/palette block at byte32.
    memcpy(pattern, "#PES0001", 8);
    pattern[8] = 32;
    memcpy(pattern + 32, "LA:Sample", 9);
    pattern[32 + 20] = 0;
    pattern[32 + 48] = 1;
    pattern[32 + 49] = 5;
    pattern[32 + 50] = 2;
    pattern[32 + 512 + 8] = 120;
    pattern[32 + 512 + 10] = 80;
    CHECK(32 + 512 + 36 + length <= sizeof(pattern));
    memcpy(pattern + 32 + 512 + 36, stitches, length);
    pattern_mount(32 + 512 + 36 + length);
    CHECK(brother_open_file(pattern_file, &pattern_api));
    CHECK(vfs_tell(pattern_file) == 32 + 512 + 36);
}
stitch_t next_stitch(stich_type_t type, float x, float y)
{
    stitch_t stitch = {0};
    CHECK(pattern_api.get_stitch(&stitch, pattern_file));
    CHECK(stitch.type == type && fabsf(stitch.target.x - x) < 0.0001f &&
          fabsf(stitch.target.y - y) < 0.0001f);
    return stitch;
}
void pattern_close(void)
{
    CHECK(pattern_file);
    vfs_close(pattern_file);
    pattern_file = NULL;
}

grbl_hal_t hal;
bool protocol_execute_realtime(void)
{
    CHECK(false);
    return false;
}
bool protocol_exec_rt_system(void)
{
    CHECK(false);
    return false;
}
bool state_door_reopened(void)
{
    CHECK(false);
    return false;
}
bool stream_await_tx_clear(const io_stream_t *stream)
{
    (void)stream;
    CHECK(false);
    return false;
}
