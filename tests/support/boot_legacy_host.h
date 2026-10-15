#pragma once
#include "support/boot_host.h"
#include <setjmp.h>

static jmp_buf legacy_program_done;
static void (*legacy_read_observer)(void);
static void finish_legacy_input(void)
{
    if(legacy_read_observer) legacy_read_observer();
    /* Legacy protocol has no host CMD_EXIT. Stop the harness after the final
       complete input line, without altering firmware protocol/state. */
    if(boot_program[boot_reads] == '\0') longjmp(legacy_program_done, 1);
}
static inline void run_legacy_boot_program(void)
{
    boot_before_read = finish_legacy_input;
    if(setjmp(legacy_program_done) == 0) {
        grbl_enter();
        CHECK(false);
    }
    CHECK(sys.driver_started);
}
