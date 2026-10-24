# Known defects and test scope

Original keypad source c34933091df668d009fe11ed7397a9b78c9bfd79 with CORE
b01f481072edecac33d5e40c25869359a5b3fa1f. No production code changes.

## Extended bytes are lost when char is signed

keypad_get_keycode() and the processing local keycode use char. Incoming bytes
0x80 and above become negative on signed-char builds, missing positive CMD_*
switch cases. Both I2C and UART signed-char extended_control and
extended_overrides retain correct expected command assertions as individually
named WILL_FAIL/known_bug tests. Identical unsigned-char controls pass. No
sanitizer diagnostic is waived. This establishes C signedness portability, not
failure on every board/compiler. Proposed repair: use an unsigned keycode type
end to end. Remove the four properties and this entry after both profiles pass.

The suite selects -fsigned-char explicitly for ordinary cases and -funsigned-char
for the paired controls. Both are supported host compiler modes; it does not
pretend to execute the target firmware. Production warnings remain visible under
the established -Wno-error rule, while fixtures keep -Werror.

## Scope and unresolved initialization return

I2C start/probe/strobe and UART registration are simulated public driver
boundaries. Real CORE override queues and CRC/math helpers are compiled. NVS is
an opaque CRC-backed RAM provider; restart uses two processes and persisted
provider bytes without copying the plugin's private serialized structure. These
are not physical I2C/UART, full parser/motion, MPG-sharing, macros or LED/display
checks. The coordinate-system formatting helper is a host boundary; no coordinate
cycle result is claimed.

UART keypad_init returns allocation success even when opening its stream fails.
The failed-transport case verifies no settings registration; intended
bool semantics need a maintainer contract before calling this a defect.
