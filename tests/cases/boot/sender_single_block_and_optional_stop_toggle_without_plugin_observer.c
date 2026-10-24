#include "support/boot_host.h"

static bool initialized, changed_seen, restored_seen;
static bool initial_single_block, initial_optional_stop;
static bool deleted_seen;
static const char deleted_block[] = "$S\n$O\n$G\n$S\n$O\n$G\n$B\n/G91\n$G\n";
static const char first_options[] = "$S\n$O\n$G\n";
static void observe_sender_options(void)
{
    CHECK(grbl.on_control_signals_changed == NULL);
    CHECK(!hal.signals_cap.single_block && !hal.signals_cap.stop_disable);
    if(!initialized) {
        initial_single_block = sys.flags.single_block;
        initial_optional_stop = sys.flags.optional_stop_disable;
        initialized = true;
    }
    if(boot_reads == strlen(first_options)) {
        CHECK(sys.flags.single_block != initial_single_block);
        CHECK(sys.flags.optional_stop_disable != initial_optional_stop);
        changed_seen = true;
    } else if(boot_reads == strlen(first_options) * 2) {
        CHECK(sys.flags.single_block == initial_single_block);
        CHECK(sys.flags.optional_stop_disable == initial_optional_stop);
        restored_seen = true;
    }
    if(boot_reads == strlen(deleted_block)) {
        CHECK(sys.flags.block_delete_enabled);
        CHECK(!gc_state.modal.distance_incremental);
        deleted_seen = true;
    }
}

int main(void)
{
    boot_before_read = observe_sender_options;
    boot_program = "$S\n$O\n$G\n$S\n$O\n$G\n$B\n/G91\n$G\n$B\n/G91\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(initialized && changed_seen && restored_seen && deleted_seen);
    CHECK(!sys.flags.block_delete_enabled && gc_state.modal.distance_incremental);
    CHECK(state_get() == STATE_IDLE && sys.alarm == Alarm_None);
    CHECK(strstr(engine_output, "error:") == NULL);
    const char *first = strstr(engine_output, "[GC:");
    CHECK(first != NULL && strstr(first + 4, "[GC:") != NULL);
    return EXIT_SUCCESS;
}
