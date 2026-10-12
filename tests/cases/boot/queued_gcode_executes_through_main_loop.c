#include "support/boot_host.h"
#include "check.h"
static unsigned queue_calls;
static void enqueue_units(void)
{
    char command[] = "G20";
    CHECK(protocol_enqueue_gcode(command));
    queue_calls++;
}

int main(void)
{
    boot_program = "";
    boot_before_read = enqueue_units;
    CHECK(grbl_enter() == 0);
    CHECK(queue_calls == 1);
    CHECK(gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
