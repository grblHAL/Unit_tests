#include "support/engine_host.h"
#include "spindle_control.h"
#include "state_machine.h"
#include "gcode.h"
#include "check.h"
#include <string.h>
static status_code_t program(const char *text)
{
    char block[48];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    return gc_execute_block(block);
}
int main(void)
{
    engine_parser_prepare();
    state_set(STATE_IDLE);
    sys.cold_start = false;
    sys.driver_started = true;
    spindle_ptrs_t *active = spindle_get(0);
    CHECK(active && active->type == SpindleType_Null);
    CHECK(program("M3S500") == Status_OK);
    CHECK(active->get_state(active).on && !active->get_state(active).ccw);
    spindle_set_override(active, 150);
    CHECK(active->param->override_pct == 150);
    CHECK(active->get_state(active).on);
    CHECK(program("M4S250") == Status_OK);
    CHECK(active->get_state(active).on && active->get_state(active).ccw);
    CHECK(program("M5") == Status_OK);
    CHECK(!active->get_state(active).on);
    spindle_set_override(active, 100);
    CHECK(active->param->override_pct == 100);
    CHECK(!active->get_state(active).on);
    CHECK(engine_irq_depth == 0 && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
