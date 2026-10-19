#pragma once
#include "support/boot_host.h"
#include "support/debug_serial_host.h"
static void install_boot_debug_uart(void)
{
    hal.stream.instance = 1; // Console UART1 and the independent debug UART0.
    register_debug_serial_driver();
}
static inline void run_boot_debug_uart(bool reject)
{
    debug_reject_claim = reject;
    boot_during_init = install_boot_debug_uart;
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(debug_claim_calls == 1 && debug_baud == 115200);
    CHECK(strstr(engine_output, "[GC:") != NULL);
    CHECK(hal.stream.instance == 1 && hal.stream.write != hal.debug.write);
    if(reject) {
        CHECK(debug_output[0] == '\0' && hal.debug.write == NULL);
        CHECK(strstr(engine_output, "Failed to initialize debug stream!") != NULL);
    } else {
        CHECK(debug_property.flags.claimed && debug_description_calls == 1);
        CHECK(strstr(debug_output, "UART debug active:") != NULL);
        debug_writeln("board ready");
        CHECK(strstr(debug_output, "board ready" ASCII_EOL) != NULL);
        CHECK(strstr(engine_output, "board ready") == NULL);
    }
}
