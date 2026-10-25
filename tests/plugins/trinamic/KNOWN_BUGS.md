# Known defects and scope

One correct TMC2240 UART transport-routing regression is retained below. Original
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

Three-axis non-I2C builds compile TMC2209 UART plus TMC2130/TMC2240/TMC5160 SPI and TMC2660 SPI20
register-callback configurations. TMC2240 UART, I2C bridges, SG-stream/developer
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

Batch40 adds six TMC2240 SPI and six TMC2660 SPI20 cases,53 total registered.
TMC2660 uses a separate native20-bit datagram fixture and a valid idle response;
its lack of StealthChop is verified through public command capability queries.
SPI microsteps check the emitted register field, not just shadow configuration.
Offline2660 setup has five outer startup cycles, each attempting25 retries on
three motors:375 requested ten-ms delays plus five100ms startup delays. A first
single-cycle fixture expectation was corrected from source and the affected case
rerun; no defect/allowance is added. These virtual request counts do not establish
a500ms wall-clock timeout. Existing non2660 timing expectations remain strict.

## TMC2240 UART startup writes COOLCONF over SPI - 2026-10-25

`plugin_trinamic.2240_uart_transport` builds original library/plugin with their
native TRINAMIC_UART_ENABLE1/TMC_UART1 configuration. The UART provider checks
request CRC and provides normal reply CRC/IFCNT; a separate SPI recorder counts
unexpected calls without applying those writes to the UART device. First normal
startup execution reached three enabled motors and failed the correct assertion
`tmc_unexpected_spi == 0`. Only this named case is WILL_FAIL/known_bug, no sanitizer
allowance or production fix. Other TMC2240 UART scenarios are not registered or
claimed as validated.

Source cause: plugin trinamic_driver_config invokes the HAL coolconf callback;
original tmc2240hal.c317 calls tmc_spi_write unconditionally, while surrounding
helpers use the selected tmc2240_write wrapper. A maintainer repair should route
COOLCONF through the selected transport, then remove this property and extend
normal UART scenarios. The SPI recorder is an explicit driver boundary, not an
SPI-to-UART alias or an implementation of the missing transfer.

The original TMC2209 UART model also gains a CRC-noise/recovery case: bad reply
checksums prevent startup; restoring valid replies and public driver reset/status
recovery enables current commands again. Actual library CRC checking/IFCNT and
EEPROM execute.55 cases now registered,54 clean +1 correct assertion regression
in the complete local sanitizer/strict component check. Physical UART and full
board/controller correctness remain unverified.
