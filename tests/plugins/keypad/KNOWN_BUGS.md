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
are not physical I2C/UART, full parser/motion, MPG-sharing or macro checks.
The independent LED-display cases below use their own driver boundary. The coordinate-system formatting helper is a host boundary; no coordinate
cycle result is claimed.

UART keypad_init returns allocation success even when opening its stream fails.
The failed-transport case verifies no settings registration; intended
bool semantics need a maintainer contract before calling this a defect.

## I2C LED display module

Seven cases compile original display/i2c_leds.c with DISPLAY_ENABLE17 and the
default PCA9654E provider. The fixture captures original two-byte register writes,
blocking startup config/inversion, nonblocking complete-state updates, prior
state/spindle/coolant/report callbacks, bus/probe failure and write recovery.
A successful driver write is not physical LED evidence. Spindle selection is the
public provider callback boundary, not the CORE registry/controller. The stock
keypad.c fixtures and four correct signed-char regressions are unchanged.

The protocol display/i2c_interface.c, alternate non-PCA LED provider, repeated
selection of an already-wrapped spindle, real bus timing and target build remain
unvalidated. No settings, SDK header or source alias bypass is introduced.

## Macro key is also lost with signed char - 2026-10-25

`plugin_keypad.macro_keypress_signed` retains the same correct key-start assertion
as its passing unsigned-char peer. First unlabelled execution failed at the public
keypress preview accepting CMD_MACRO_0 (0xB0). Original macros.c keypress_preview
receives char and compares it to positive MACRO_KEY0 in a switch, so signed char
cannot match. The macro never starts. This separate original module shares the
keypad.c portability cause above; no target-wide failure is claimed.

Only this exact signed-char case is WILL_FAIL/known_bug. No sanitizer allowance
or source patch is added. Keep the assertion and remove the property when both
char profiles accept the same ordinary macro key. Nine other macro cases use an
explicit unsigned-char profile and original EEPROM/CRC plus registered string
settings, M810/preview, error and reset hooks. Controller parsing/synchronization
and keypad callback table are host boundaries; actual keypad transport is tested
separately in the stock cases. ID0/private macro entry and oversized strings are
not invoked. Aux-bound macros, all N_MACROS/length configurations, signed-key
repair, full boot/parser and physical inputs remain unfinished.

## Auxiliary macro input coverage - batch39

Five cases compile original MACROS_ENABLE3 with two driver-advertised input pins
and MACROS_ENABLE1 with no inputs. Normal pin-to-macro mapping uses explicit
MACRO_1_AUXIN0/MACRO_2_AUXIN1 board configuration symbols, real CORE ioports/
crossbar claims and captured IRQ registration. High edges do not start macros;
foreground execution rechecks idle state. Registered integer setters bind feed
hold/cycle-start/reset actions and their realtime byte callbacks execute during
active states. Failed IRQ registration warns while M810 remains usable. Original
EEPROM/settings execute; actual interrupt/controller timing remains outside scope.

The action setter's uint_fast16_t signature matches setting_set_int_ptr. Its
getter returns uint_fast16_t whereas CORE setting_get_int_ptr returns uint32_t;
this getter contract is unvalidated and no cast/alias is used to conceal it.
No private fields, invalid macro IDs or oversized strings are injected.

## Protocol-display polling alignment - source review only, 2026-10-25

Original display/i2c_interface.c passes native syntax-only compilation with
DISPLAY_ENABLE9/KEYPAD_ENABLE0. Header-only layout inspection on current Clang/
Windows reports offsetof(machine_status_packet_t,msg)=45, alignof(overrides_t)=2
and offsetof(overrides_t,spindle_rpm)=4. send_status_info's overrides message casts
that byte buffer to overrides_t* and assigns spindle_rpm at byte49, which is not
2-byte aligned. Initial complete_setup enables this report path. Protocol polling
was not executed; no runtime diagnostic or expected failure is claimed. Evidence
and a small layout-only inspection source are in build-evidence/display39-*.

Do not use packing flags, typedef/header aliases, private rt_report changes or a
replacement serializer to bypass this source issue. Resolve the implementation/
ABI contract before protocol polling tests. This is current native host evidence,
not a verified fault on every target. Connection/status/alarm/WCO packet behavior
and full protocol display integration remain unfinished.
