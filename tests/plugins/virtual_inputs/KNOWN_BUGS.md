# Scope and remaining work

Twenty-one cases execute original Virtual Inputs, CORE probe.c and CORE formatting.
Physical pins/IRQ enable and atomic operations are host callbacks. Registered
CORE probe tables select shared/separate toolsetters and a third probe; the
shared driver input callback models a physical OR before CORE samples it. Public
HAL configure, select and IRQ callbacks exercise toward/away states; no private
probe/plugin state is forced. Tests cover inversion, command rejection without
state loss, realtime counters, explicit clear/reset, chaining and idempotent init.
Topology-independent command/lifecycle cases run once, not once per topology.

No known assertion or diagnostic exception. These are probe HAL boundary tests,
not complete G38 parser/planner/stepper jobs or physical IRQ latency checks. The
optional my_plugin_init entry point and relocated realtime command base are not
configured. Missing original legacy HAL callbacks need a separate supported
fixture; real CORE probe registration supplies them in this suite. The command
reset prefix behavior accepts strings starting with R/r; its broader grammar
contract needs review before adding a regression assertion.
