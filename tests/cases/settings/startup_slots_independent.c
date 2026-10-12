#include "support/engine_host.h"
#include "nvs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_prepare();
    stored_line_t first = "G21", second = "G90", result;
    settings_write_startup_line(0, first);
    settings_write_startup_line(1, second);
    CHECK(settings_read_startup_line(0, result));
    CHECK(strcmp(result, first) == 0);
    CHECK(settings_read_startup_line(1, result));
    CHECK(strcmp(result, second) == 0);
    return EXIT_SUCCESS;
}
