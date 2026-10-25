#include "support/boot_host.h"
#include "task.h"

static unsigned connection_events;
static probe_state_t physical_probe_state(void)
{
    return (probe_state_t){.probe_id = Probe_Default,
        .connected = !boot_control_signals.probe_disconnected};
}
static void install_physical_probe(settings_t *current)
{
    CHECK(current == &settings);
    hal.driver_cap.probe = true;
    hal.signals_cap.probe_disconnected = true;
    hal.probe.get_state = physical_probe_state;
    CHECK(hal.probe.connected_toggle == NULL);
}
static void exercise_connection_input(void)
{
    if(connection_events) return;
    CHECK(state_get() == STATE_IDLE);
    CHECK(hal.probe.get_state().connected);
    boot_control_signals.probe_disconnected = true;
    hal.control.interrupt_callback((control_signals_t){.probe_disconnected = true});
    engine_execute_tasks(STATE_IDLE);
    CHECK(!hal.probe.get_state().connected);
    connection_events++;
    boot_control_signals.probe_disconnected = false;
    hal.control.interrupt_callback((control_signals_t){.probe_disconnected = true, .deasserted = true});
    engine_execute_tasks(STATE_IDLE);
    CHECK(hal.probe.get_state().connected);
    connection_events++;
    CHECK(hal.probe.connected_toggle == NULL);
    CHECK(sys.alarm == Alarm_None && !sys.abort);
}

int main(void)
{
    boot_during_setup = install_physical_probe;
    boot_before_read = exercise_connection_input;
    boot_program = "G91\n";
    CHECK(grbl_enter() == 0);
    CHECK(connection_events == 2);
    CHECK(gc_state.modal.distance_incremental);
    CHECK(hal.probe.get_state().connected);
    return EXIT_SUCCESS;
}
