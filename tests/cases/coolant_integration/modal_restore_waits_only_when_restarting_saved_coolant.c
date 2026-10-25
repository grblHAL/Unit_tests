#include "support/coolant_host.h"
#include "ngc_params.h"
static void command(const char *text)
{
    char block[16];
    CHECK(strlen(text) < sizeof(block));
    strcpy(block, text);
    CHECK(gc_execute_block(block) == Status_OK);
}
int main(void)
{
    prepare_coolant();
    hal.coolant_cap.flood = true;
    settings.coolant.on_delay = 100;
    command("M70");
    command("M8");
    CHECK(actual_coolant.flood && engine_ticks == 100);
    unsigned before = coolant_calls;
    command("M72");
    CHECK(actual_coolant.mask == 0 && gc_state.modal.coolant.mask == 0);
    CHECK(coolant_calls == before + 1 && engine_ticks == 100);
    command("M8");
    CHECK(actual_coolant.flood && engine_ticks == 200);
    command("M70");
    command("M9");
    CHECK(actual_coolant.mask == 0 && engine_ticks == 200);
    before = coolant_calls;
    command("M72");
    CHECK(actual_coolant.flood && gc_state.modal.coolant.flood);
    CHECK(coolant_calls == before + 1 && engine_ticks == 300);
    command("M72");
    CHECK(coolant_calls == before + 1 && engine_ticks == 300);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
