#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    boot_program = "G20\r\n$G\r\n";
    CHECK(grbl_enter() == 0);
    CHECK(gc_state.modal.units_imperial);
    unsigned replies = 0;
    const char *cursor = engine_output;
    while((cursor = strstr(cursor, "ok" ASCII_EOL))) { replies++; cursor += 2; }
    CHECK(replies == 2);
    return EXIT_SUCCESS;
}
