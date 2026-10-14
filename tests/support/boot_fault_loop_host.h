#pragma once
#include "support/boot_host.h"
#include "task.h"
static unsigned fault_task_calls, fault_observer_calls, fault_expected_setup_calls;
static void forbidden_startup_task(void *data) { (void)data; fault_task_calls++; }
static void register_fault_startup_tasks(void)
{
    CHECK(task_run_on_startup(forbidden_startup_task, NULL));
    CHECK(task_add_delayed(forbidden_startup_task, NULL, 1));
    CHECK(task_add_systick(forbidden_startup_task, NULL));
}
static void observe_startup_fault(sys_state_t state)
{
    CHECK(++fault_observer_calls <= 10);
    engine_ticks += 1000;
    CHECK(!sys.driver_started && sys.alarm == Alarm_SelftestFailed);
    CHECK(state == STATE_ALARM);
    CHECK(fault_task_calls == 0);
    if(fault_observer_calls == 3) {
        CHECK(boot_setup_calls == fault_expected_setup_calls && boot_release_calls == 0);
        CHECK(strstr(engine_output, "GrblHAL 1.1f") != NULL);
        CHECK(plan_get_current_block() == NULL);
        /* Startup failure intentionally does not return. Finish the host observer
           after three scheduler turns, rather than altering that core behavior. */
        exit(EXIT_SUCCESS);
    }
}
static inline void observe_fault_startup(unsigned setup_calls)
{
    fault_expected_setup_calls = setup_calls;
    boot_program = "";
    boot_observe_fault_loop = true;
    boot_during_init = register_fault_startup_tasks;
    boot_on_realtime = observe_startup_fault;
    (void)grbl_enter();
    CHECK(false);
}
