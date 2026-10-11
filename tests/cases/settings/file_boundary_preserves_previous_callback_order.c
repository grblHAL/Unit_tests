#include "support/settings_file_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_file();
    grbl.on_file_demarcate(true);
    grbl.on_file_demarcate(false);
    CHECK(file_callback_calls == 2);
    CHECK(file_callback_start[0]);
    CHECK(!file_callback_start[1]);
    return EXIT_SUCCESS;
}
