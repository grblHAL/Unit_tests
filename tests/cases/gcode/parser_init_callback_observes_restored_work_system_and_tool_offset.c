#include "support/named_parameter_host.h"
static unsigned init_calls, wco_calls;
static void work_offset_changed(void) { wco_calls++; }
static void initialized(parser_state_t *parser)
{
    CHECK(parser == &gc_state);
    CHECK(parser->modal.g5x_offset.id == CoordinateSystem_G55);
    CHECK(parser->modal.tool_offset_mode == ToolLengthOffset_EnableDynamic);
    NEAR(parser->modal.tool_length_offset[Z_AXIS], 4);
    CHECK(wco_calls == 1);
    init_calls++;
}
int main(void)
{
    engine_parser_prepare();
    CHECK(named_parameter_block("G55G43.1Z4") == Status_OK);
    grbl.on_parser_init = initialized;
    grbl.on_wco_changed = work_offset_changed;
    sys.cold_start = false;
    gc_init(true);
    CHECK(init_calls == 1 && wco_calls == 1);
    return EXIT_SUCCESS;
}
