#include "support/boot_host.h"
static const char resumed_program[] = "$62=1\nM8\n$G\nM9\n$62=0\n";
static bool receive_scheduled, receive_arrived, expiry_checked, sender_completed;
static unsigned waiting_polls;
static uint16_t receive_free_space(void)
{
    return 128 - (uint16_t)(strlen(boot_program) - boot_reads);
}
static void receive_sender_commands(void *data)
{
    (void)data;
    CHECK(boot_coolant_state.flood && settings.flags.sleep_enable);
    boot_program = resumed_program;
    receive_arrived = true;
}
static void service_sleep_receive(sys_state_t state)
{
    CHECK(state != STATE_SLEEP);
    if(state != STATE_IDLE || boot_reads != strlen(boot_program)) return;
    if(!receive_arrived && settings.flags.sleep_enable && boot_coolant_state.flood) {
        if(!receive_scheduled) {
            CHECK(task_add_delayed(receive_sender_commands, NULL, 100));
            receive_scheduled = true;
        }
        CHECK(++waiting_polls < 8);
        engine_ticks += 50;
    } else if(receive_arrived && !settings.flags.sleep_enable && boot_coolant_state.mask == 0) {
        if(!expiry_checked) {
            engine_ticks += (uint32_t)(SLEEP_DURATION * 60000.0f) + 1;
            expiry_checked = true;
        } else {
            CHECK(!(sys.rt_exec_state & EXEC_SLEEP));
            sender_completed = true;
            CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
            boot_on_realtime = NULL;
        }
    }
}
static void install_sleep_receive(void) { hal.stream.get_rx_buffer_free = receive_free_space; }
int main(void)
{
    boot_idle_lock_time = 255;
    boot_observe_fault_loop = true;
    boot_during_init = install_sleep_receive;
    boot_on_realtime = service_sleep_receive;
    boot_program = "$62=1\nM8\n";
    CHECK(grbl_enter() == 0);
    CHECK(receive_scheduled && receive_arrived && expiry_checked && sender_completed);
    CHECK(boot_coolant_seen_on && boot_coolant_state.mask == 0);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    CHECK(strstr(engine_output, "Sleeping") == NULL && strstr(engine_output, "error:") == NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
