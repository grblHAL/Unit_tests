#include "support/engine_host.h"
#include "nvs.h"
#include <string.h>
#include "check.h"

int main(void)
{
    engine_prepare();
    stored_line_t source = "G21G90", result;
    settings_write_startup_line(0, source);
    CHECK(settings_read_startup_line(0, result));
    CHECK(strcmp(result, source) == 0);
    return EXIT_SUCCESS;
}
