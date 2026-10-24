# Known defects and scope

No runtime defect is classified for these TMC2209 plugin scenarios. Original
motor source9229617c1d8a3cc7a71fd584896500a779978b02, CORE
b01f481072edecac33d5e40c25869359a5b3fa1f and actual Trinamic library
9b304175318d93818c8967faadc89dd101b17e92 are unchanged. The library is pinned
to the inspected RP2040 driver's gitlink; it is not an automatic compatibility
fallback or a claim about all later library versions.

The original plugin and real TMC2209 chip/HAL/CRC code run against a simulated
UART register device, including request/reply CRC and IFCNT increments. Motor
iteration, board setup, limit IRQ callbacks and parser/settings boundaries are
simulated public interfaces. Parser axis words use named bitfields and the real
consume/restore protocol; this is not a full CORE G-code execution test. Initial
fixture errors used raw bit indexes and omitted restoration, causing NaN values;
those were corrected before classification. No NaN diagnostic is waived.

Settings use the real EEPROM plugin/CRC-backed provider and two-process restart.
Cases cover initialization, address override, runtime current/mode commands,
current/microstep settings and rejection, transport/setup/storage failure,
recovery, fault IRQ and callback chaining. Current assertions inspect configured
milliamps/register behavior, not measured electrical current. The UART failure
provider returns an invalid non-null reply as expected by the library boundary;
actual inspected RP2040/ESP32 UART transports return static reply buffers and
mark address0xFF on timeout. No unproven null reply contract is force-entered.

Only the three-axis TMC2209 non-I2C configuration is compiled; other chips,
bridges, debug/report modes and physical timing remain. Additional runtime cases
enable polling and dynamic current: hold/block/idle current transitions, quiet
polls, repeated/recovered over-temperature warnings, moving hold requests and
homing sensitivity/IRQ callbacks execute through public tasks and HAL hooks.
Homing rate/IRQ callbacks are tested; actual homing motion/stall detection is not.
Original warnings remain visible under -Wno-error while host fixtures stay
-Werror. No sanitizer allowances or whole-plugin/library coverage claim.
