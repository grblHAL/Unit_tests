# Known defects and scope

No runtime defect is classified for these tested Trinamic plugin scenarios. Original
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

Three-axis non-I2C builds compile TMC2209 UART plus TMC2130/TMC5160 SPI
register-callback configurations. TMC2240/TMC2660, I2C bridges, SG-stream/developer
variants and physical timing remain. Additional TMC2209 runtime cases
enable polling and dynamic current: hold/block/idle current transitions, quiet
polls, repeated/recovered over-temperature warnings, moving hold requests and
homing sensitivity/IRQ callbacks execute through public tasks and HAL hooks.
Homing rate/IRQ callbacks are tested; actual homing motion/stall detection is not.
Original warnings remain visible under -Wno-error while host fixtures stay
-Werror. No sanitizer allowances or whole-plugin/library coverage claim.

Batch39 adds public M122 all/selected-axis reports, M911 live warning/fault text,
M912 latched prewarn clearing, M913 speed-to-threshold conversion and zero-disable,
and M919 chopper set/query/rejections. Actual original-library registers are
inspected, with no copied report/driver algorithm. The command fixture only
executes after validation succeeds and restores the consumed mask as CORE does.
The three-axis configuration remains unchanged; no physical current, electrical
chopper timing or full parser/motion claim is made.29 TMC2209 cases are registered.

Generated library header forwarders preserve unchanged contents/timestamps.
A fresh configure preserves all14 forwarding-header timestamps and its next
Ninja build does no work; source changes still rebuild normally.

Batch39 adds12 SPI-chip cases (six each for TMC2130/TMC5160), bringing the suite
to41: original chip/HAL/common library modules execute through captured register
datagrams, original EEPROM and plugin settings/M-codes. Cases cover valid
standstill initialization/readback, default sense resistance, current commands/
settings, valid/rejected microsteps, StealthChop toggles and offline-to-online
recovery. Independent UART cases keep their CRC/IFCNT model unchanged. No aliases,
chip algorithm copies or production-source patches are used.

The SPI fixture provides logical register reads/writes at the library transport
callback. It does not implement physical wire framing/endian conversion, CS/
daisy-chain/pipelining/IRQ/DMA timing or the actual board adapter. Status payload
is a valid idle standstill image; returned SPI status-header behavior and dynamic
fault/poll/homing/current variants on these SPI chips remain unvalidated. Library
source coverage is not included in the plugin-only coverage filter.
