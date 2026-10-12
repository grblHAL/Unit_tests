#include "support/engine_host.h"
#include "ngc_params.h"
#include "check.h"
static unsigned restore_calls;
static modal_groups_t restored_groups;
static void *restored_context;
static void capture_restore(modal_state_action_t action, modal_groups_t commands, void *context)
{
    CHECK(action == ModalState_Restore);
    restore_calls++;
    restored_groups = commands;
    restored_context = context;
}

int main(void)
{
    engine_parser_prepare();
    gc_override_values_t overrides = {.feed_rate = 100, .rapid_rate = 100, .spindle_rpm = {100}};
    CHECK(ngc_modal_state_save(&gc_state.modal, &overrides, 0, false));
    char changed[] = "G20G91G18";
    CHECK(gc_execute_block(changed) == Status_OK);
    grbl.on_modal_state_action = capture_restore;
    CHECK(ngc_modal_state_restore());
    CHECK(restore_calls == 1);
    CHECK(restored_groups.G2 && restored_groups.G3 && restored_groups.G6);
    CHECK(!restored_groups.G8 && !restored_groups.G12 && !restored_groups.M8);
    CHECK(restored_context == ngc_modal_state_get());
    grbl.on_modal_state_action = NULL;
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
