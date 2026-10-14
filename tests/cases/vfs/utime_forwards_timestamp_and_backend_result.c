#include "support/vfs_operations_host.h"

int main(void)
{
    prepare_operations((vfs_st_mode_t){0}); operation_result = -8;
    struct tm time = {.tm_year = 126, .tm_mon = 9, .tm_mday = 14, .tm_hour = 12, .tm_min = 34, .tm_sec = 56};
    CHECK(vfs_utime("/store/file", &time) == -8);
    CHECK(strcmp(operation_path, "/file") == 0);
    CHECK(captured_time.tm_year == 126 && captured_time.tm_mon == 9 && captured_time.tm_mday == 14);
    CHECK(captured_time.tm_hour == 12 && captured_time.tm_min == 34 && captured_time.tm_sec == 56);
    cleanup_operations();
    return EXIT_SUCCESS;
}
