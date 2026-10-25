# Local Nowforever VFD checkpoint - 2026-10-25

Goal active. Eleven new original-source Nowforever scenarios cover frequency
range discovery, forward/reverse/stop, nonblocking speed limits and duplicate
suppression, RPM feedback/poll caching, reset range refresh, discovery retry,
async exception thresholds/recovery, settings/report hooks and absent/down
providers. Real CORE registration/Modbus and EEPROM-backed settings retained.
Shared transport fixture explicitly models this protocol's11-byte multiple-
register writes and9-byte range reply, with bounded captured packet assertions.

Initial69-case ASan/UBSan run passed68 and failed the new command fixture: it
changed direction while stopping, which resets cached programmed RPM to zero
and suppresses a redundant speed write. Stop scenario now retains selected CCW
while disabling output, checking stop word0 and minimum-frequency clamp100.
Only this test source changed after that run. Focused repair11/11 passes0.46s
with strict classification all clean. The58 existing protocols passed the
initial shared-fixture run; no fresh combined69 green claim. No new known
failure, assertion weakening, production edit or diagnostic allowance.

Pending local VFD additions32 beyond delivered batch32;868 compatible authored.
Last full global gate remains836 plus26 reference cases and87 helper checks.
No new measured coverage, hosted GCC/Linux result, serial timing, full controller
job or physical VFD validation. Huanyang v1 and remaining spindle variants are
still open. Continue substantial authoring before combined delivery gate/push.

---

# Local Huanyang v2 VFD checkpoint - 2026-10-25

Goal active. Ten new Huanyang v2 scenarios execute original protocol code with
real CORE spindle registration/Modbus and EEPROM-backed settings. Discovery
reads maximum RPM; forward/reverse/stop, nonblocking updates and unchanged-speed
suppression check packet words. Feedback uses RPM directly and the shared150ms
poll interval. Driver reset defers discovery and refreshed maximum RPM changes
speed scaling; rejected initial discovery recovers on first start. Reused async
exception threshold/recovery, settings/report hooks, missing transport/storage
and bus-down scenarios execute against this protocol.

The shared transport fixture adds the protocol-specific eight-byte holding
response layout with explicit compile selection. All58 VFD cases pass Windows
Clang ASan/UBSan3.53s and strict classification:58 clean, zero known/unexpected/
skipped. Existing GS20/MODVFD/H100/YL620 cases included after shared fixture change.
No production source changes, sanitizer allowances or new known failures.

Pending local work now21 new VFD cases beyond delivered batch32:857 compatible
authored, not a fresh global gate or coverage result. Batch32 remains last full
compatible836 plus26 separate reference cases and87 helper checks. Actual serial
ACK timing, physical VFD behavior, full controller/parser integration and hosted
GCC/Linux remain unchecked. Accumulate other supported regions before one
combined delivery gate. Full goal remains active.

---

# Local YL620A VFD protocol checkpoint - 2026-10-25

Goal active. Eleven new YL620 cases pass focused Windows Clang ASan/UBSan0.64s
and strict classification, all clean with zero unexpected failures/skips. Original
source uses existing real CORE spindle registration/Modbus and EEPROM-backed
settings. Forward/reverse/stop and frequency words match selected protocol;
nonblocking RPM update and configured RPM/Hz roundtrip execute. Shared150ms
polling wrapper controls feedback/at-speed and preserves cached response between
polls. Reused scenarios execute rejected mode commands, async exception threshold/
reset-after-success, settings/report hooks, absent transport/storage and bus-down
selection/recovery against the actual new protocol implementation.

No new host transport implementation or private spindle/capability modifications.
Existing holding-register framing suffices; all source remains unchanged. Native
serial/VFD clocks, ACK timing, alternate protocol layouts, full parser/controller
jobs and hardware remain unverified. Original source warnings stay visible/nonfatal
only for this VFD file, matching existing VFD harness policy; no runtime sanitizer
allowance or known result added.

VFD48 registered;847 compatible authored, not a new full global gate. Last
delivered batch32 remains836 plus26 separate reference cases and87 helper checks.
Incremental forwarding headers prevent rebuild of unchanged existing VFD objects
when registering new cases. No fresh coverage report/hosted run; accumulate next
supported protocol group before combined validation/push. Full goal stays active.

---

# Latest component checkpoint - 2026-10-25 (batch32)

Goal active. Deliver14 runtime cases:9 H-100 VFD +5 BLTouch provider/report cases,
plus incremental-header fix and unregistered tool-table proposals. One full Windows
Clang ASan/UBSan compatible gate passes42 suites,836 cases =773 clean +63 documented
known, zero unexpected failures/skips. Known results remain59 correct assertion
regressions +4 diagnostic-only cases;3 assertions also carry exact diagnostics,
counted once. No new known result or sanitizer allowance. Fresh separate reference
gates pass PSoC9 (8 clean +1 known) and TI17 (15 clean +2 known), excluded from836.

VFD37 cases all pass in fresh combined gate, superseding initial authoring red
report. H100 discovery/poles/ranges, CW/CCW/stop, limit clamping, feedback, retry,
reset refresh and provider failure use actual CORE spindle/Modbus plus bounded
device replies and EEPROM-backed storage. Feedback observes common150ms wrapper
and established0.01RPM float policy. BLTouch15 cases retain only fractional-D known
assertion; optional providers/report chains now pass. Physical device timing,
other VFD protocols and actual controller jobs remain unverified.

All87 source/report helper tests pass29.863s, including new CMake timestamp/CORE-
path regression. Shared header generation preserves unchanged files, real target
reconfigure/rebuild reports no work. Broader gate and both legacy source layouts
now validate the shared change; no production header/source mutation or ABI alias.

Fresh selected LLVM coverage: misc12 files1272/1373 lines,661/866 branches,123/128
functions; BLTouch130/138 lines,92/110 branches. VFD4 files401/452 lines,121/199
branches,51/57 functions; H100112/131 lines,40/63 branches. VFD denominator expands
with H100; unbuilt files/configurations remain excluded. Strict reports pass misc129
(121 clean +8 known assertions) and VFD37 clean. Counter paths max224/223.

Seven tool-table proposals remain UNRUN and unregistered: current original setter
ABI fails CORE; they are not passing cases, coverage or known labels. Source-only
compatibility evidence is preserved without cast/fallback/source modifications.
Exact main/reference source locks match clean originals. No helper/workflow edits
beyond the new header regression; unchanged actionlint was not rerun.

Fresh fork listing still exposes only reusable/core workflows; Plugin/Driver
manual dispatch awaits default-branch installation. Keep PR29 draft/unmerged;
no hosted GCC/Linux, full target/SDK or physical hardware success claimed.
Continue the full plugin/core/driver goal with remaining modules/integration.

---

# Local H-100 VFD protocol checkpoint - 2026-10-25

Goal active. Added9 H-100 cases using existing real CORE Modbus/spindle registration
and EEPROM-backed settings fixtures. Source discovery reads poles/min/max, locks
reported range and converts2/4-pole frequency units; direction/stop coils, speed
register writes/clamps, feedback/at-speed, failed discovery retry, deferred reset
range refresh and absent transport/storage paths execute. Transport replies are
bounded host register models, not serial hardware/VFD validation.

Shared fixture expansion first gated all37 VFD cases in2.07s:28 existing GS20/
MODVFD +8 new H100 clean, with1 feedback fixture failure. Source wrapper suppresses
queries before150ms, so feedback now uses150/300ms; retry control also advances
to150ms to exercise unready source rather than wrapper suppression. Rechecks found
normal float limit rounding, resolved using existing VFD0.01RPM comparison policy,
well below the modeled frequency step. Final feedback passes0.10s; affected retry
also passes its focused recheck. No production defect/exception/diagnostic allowance
added. No repeated unchanged global gate during authoring. Current whole VFD/full
component gates remain due at combined delivery; initial red report is not green.

Actual CORE spindle registration/control and Modbus routing execute. Device I/O,
NVS, scheduled-reset services and feedback replies are captured boundaries. No
private spindle pointers/capability mutation or production source edits. H100
exception modes/other protocols, firmware scheduling and physical timing remain.

VFD suite37 registered, compatible836 authored (822 delivered +5 local BLTouch
+9 H100); no new whole-suite count claim. Header incremental fix and unrun tooltable
proposals remain local, excluded from passing-case additions. Accumulate related
work then run combined gate/helpers once before push. Full goal remains active.

---

# Local incremental-header build checkpoint - 2026-10-25

Goal active. Fixed component forwarding-header generation: file(CONFIGURE) writes
only when content changes, replacing unconditional file(WRITE). Reconfiguring a
suite no longer touches every forwarded CORE header and rebuilds unchanged cases.
A new Python integration regression first failed on the original timestamp rewrite,
then passed4.07s with the fix. It configures twice for each of two CORE paths with
spaces and switches back, checking stable timestamps and correct include paths.
The dummy header trees test generation only; no firmware source is substituted.

Real existing BLTouch target was built, reconfigured and rebuilt: Ninja reports
'no work to do'; its sanitizer/strict case still passes0.09s. No target semantics,
source lock, production headers or firmware code changed. New helper joins normal
scripts/test_*.py discovery and requires the existing CMake build dependency on PATH.
Only this new helper was executed; unchanged prior86 helpers were not rerun yet.
A broader component gate remains due at the next substantial delivery because
this shared build helper changed. No new full-suite/coverage/hosted claim.

Compatible authored counts remain827, last delivered822 plus26 separate legacy
references. Five BLTouch cases and unrun tooltable proposals remain local from
prior checkpoints; proposals never count. Continue supported module authoring
with incremental builds and retain the full goal.

---

# Local tool-table compatibility checkpoint - 2026-10-25

Goal active. Authored seven tool-table/VFS scenarios, but original tooltable.c
cannot compile with pinned current CORE. Independent unchanged-source Clang23
syntax check confirms tooltable.c452 assigns bool writeTools(tool_data_t *) to
CORE's bool (*)(tool_data_t *, bool persist) callback. This is separate from
fixture caller errors, which were corrected to CORE's actual two-argument API.
No cast, source/header modification or older-CORE fallback conceals rejection.

Scenarios and bounded file backend are preserved UNREGISTERED under
 tests/proposals/misc_tooltable (README records source pins/contracts). They have
not executed and are excluded from counts, coverage and known-result labels.
Random sparse pockets remains an unverified candidate, not a classified defect.
Original source also warns about uint_fast8_t index against300-byte bound; no
oversized/malformed-line runtime is executed. Syntax evidence is ignored under
build-evidence/tooltable-syntax-batch32.{json,log}; original checkouts remain clean.

Removed the tentative default registration completely and reconfigured the
active misc project; ctest -N -R tooltable confirms0 registered cases. Existing
suite configuration is restored. This is compatibility evidence/proposal work,
not new passing unit coverage. BLTouch's five local validated cases remain from
prior checkpoint. Authored compatible total stays827, last delivered gate822
plus26 separately validated legacy references. No full gate/hosted claim.

Next: retain tool-table source/API requirement for upstream resolution, continue
remaining supported I/O/controller workflows and accumulate a substantial batch.
The full goal remains active; this module mismatch does not block other work.

---

# Local BLTouch optional-provider checkpoint - 2026-10-25

Goal active. Five new cases plus all10 prior BLTouch cases pass focused Windows
Clang ASan/UBSan1.04s and strict classification:14 clean +1 unchanged fractional-D
assertion, zero unexpected failures/skips. Original source's no-readback fallback
remembers commanded angle and suppresses repeated stow/deploy writes and delays.
Available/unavailable option reporting chains the previous handler and emits the
correct plugin identity without output changes. Native toolsetter capability
bypasses automatic deployment while retaining manual commands. Missing prior
probe-start/completed hooks still permit deploy/stow through the installed hooks.

Fixture choices represent optional driver providers/capabilities assigned before
plugin initialization, not private plugin state. Actual CORE numeric/delay helpers
remain unchanged and executing; servo readback/output, port claims, reports and
tasks are captured host boundaries. No production edits, new exception/diagnostic
allowance or weakened assertion. Physical servo/relay timing, actual CORE parser/
controller integration and remaining configurations remain open.

BLTouch15, misc129 and827 compatible are authored totals, not a new full global
gate. Latest delivered batch31 remains822 compatible plus26 separate legacy
references. No fresh coverage measurement or hosted/hardware claim; accumulate
related supported workflows before next combined gate/push. Goal stays active.

---

# Latest component checkpoint - 2026-10-25 (batch31)

Goal active. Corrected an M-code dispatch fixture error and added3 BLTouch option/
validation cases. Full Windows Clang ASan/UBSan gate was justified by the shared
contract repair across ATCi/BLTouch/PPI/RGB fixtures:42 compatible suites,822 cases
=759 clean +63 documented known, zero unexpected failures/skips. Known results
remain59 correct assertion regressions +4 diagnostic-only cases;3 assertions also
carry exact diagnostics, counted once. One false ATCi allowance removed; one
correct BLTouch fractional-D assertion added. No sanitizer allowance added.

IMPORTANT CORRECTION: prior ATCi M960 P0 failure was a harness error, not a
confirmed upstream defect. CORE gcode.c2349-2355 records consumed word bits and
4494 restores them before execute. Host helper omitted restoration. Corrected
helper preserves every assertion; all18 ATCi cases now clean and obsolete exact
WILL_FAIL/known_bug entry is removed. Earlier checkpoint claims about that defect
are superseded. PPI/RGB helpers now apply the same consumed-word handoff; their
registered results remain unchanged. No production source/header changes.

BLTouch S/D/H options work with the faithful handoff. Tests cover high-speed and
auto-deploy on/off, H reporting, S/R numeric rejections and valid ignored R values.
Actual D0.5 validation defect remains: D's integer check reads values.s instead
of values.d, accepts fractional D. Invalid command is never executed. Keep one
correct BadNumberFormat assertion under exact known_bug with source/removal guide.
These remain driver/API boundary tests, not actual CORE parser/controller jobs.

Fresh misc selected-source LLVM report:1267/1373 lines92.3%,655/866 branches75.6%,
122/128 functions across12 files. BLTouch125/138 lines (+24 same configuration).
Strict coverage classification passes124 misc cases (116 clean +8 known assertions).
Counter paths max224. Other modules/configurations/hardware remain unverified.
Exact source locks cover unchanged misc2657119/ATCi671f145/PPI26934c6/RGBdf340905
and CORE b01f481. Unchanged86 helper/actionlint checks were not rerun.

Unchanged26 legacy serial references retain separate batch24 validation. Latest
workflow listing remains batch29's reusable/core-only availability; separate
Plugin/Driver dispatch awaits default installation. Keep PR29 draft/unmerged.
No hosted GCC/Linux, physical timing or full controller/SDK success claimed.
Continue remaining modules and integration with the full goal intact.

---

# Latest component checkpoint - 2026-10-25 (batch30)

Goal active. Deliver19 accumulated cases:12 MCP23017 wait/handler and7 BLTouch
cases. One full Windows Clang ASan/UBSan compatible gate passes42 suites,819 cases
=756 clean +63 documented known, zero unexpected failures/skips. Known results
remain59 correct assertion regressions +4 diagnostic-only cases;3 assertions also
carry exact diagnostics, counted once. No new known result or sanitizer allowance.
Unchanged26 legacy serial references retain separate batch24 validation.

MCP waits cover level/edge success, timeout, abort, previously disabled IRQ masks
and registered-handler retention across completion/timeout in mixed/input-only
builds. Existing edge-filter defect limits independent observation of internal
mode restoration through callbacks. BLTouch covers remapped servo claim/startup
stow, no-argument M401/M402 and duplicate commands, probe hooks/select/rejection,
native-probe bypass, deferred reset stow, BLTEST/BLRESET scheduling/cancellation
and claim failure. Actual original CORE nuts_bolts numeric/format/delay helpers
execute; realtime/delay/task/port boundaries remain modeled driver services.

Fresh selected-source LLVM report spans12 misc files:1243/1373 lines90.5%,620/866
branches71.6%,122/128 functions. BLTouch101/138 lines; expanded denominator differs
from prior11-file report. Strict coverage classification passes121 misc cases
(114 clean +7 unchanged known assertions); fresh counter paths max224. Unbuilt
modules, alternate layouts, BLTouch S/D/R/high-speed/no-readback modes and physical
servo timing remain open. No whole-plugin/repository coverage claim.

GitHub-resolved Plugins_misc2657119 and CORE b01f481 locks match clean originals.
No production header/source edits, private state modifications or weakened
assertions. Unchanged86 helper/actionlint checks were not rerun. Latest workflow
availability remains batch29's reusable/core-only listing; Plugin/Driver manual
dispatch needs default-branch installation. Keep PR29 draft/unmerged. No hosted
GCC/Linux, target linking, controller motion or hardware success claimed. Continue
remaining modules and actual CORE/driver integration on the same branch.

---

# Local MCP23017 active-handler wait checkpoint - 2026-10-25

Goal active. Four new mixed/input-only cases pass focused Windows Clang ASan/
UBSan0.27s and strict classification, all clean with zero unexpected failures/
skips. Existing IRQ_Mode_Change registration/user-port11 survives a successful
rise wait and a separate wait timeout: GPINTEN remains enabled, descriptor keeps
its configured mode and a later captured low event reaches the registered handler.
Matching wait event also delivers normally. Public registration and source IRQ/
deferred paths execute; no private callback or mode writes are used.

These establish observable enabled-mask/handler retention, not independent proof
of internal edge-mode restoration: the documented opposite-edge callback defect
limits what subsequent callback delivery alone can distinguish. Keep correct
regression assertions elsewhere and do not weaken their known labels. Actual
CORE scheduling, hardware IRQ timing and transport failures remain untested.

No new exception/diagnostic allowance or production edit. Four authoring cases
are not a new full gate or coverage report. Misc114 cases,812 compatible authored;
latest delivered batch29 remains800 plus26 separate legacy references. Together
with earlier wait cases,12 local cases accumulate toward the next combined batch.
Continue configuration/module and actual controller integration work.

---

# Local MCP23017 blocking-wait checkpoint - 2026-10-25

Goal active. Eight new blocking-wait cases plus prior17 affected input/IRQ cases
pass Windows Clang ASan/UBSan1.72s and strict classification:21 clean +4 unchanged
edge-filter regressions, zero unexpected failures/skips. Original source polls
for high/low levels, returns immediately for already-matching level, times out
without input, and exits after public controller abort during realtime polling.
Both mixed8-bit and input-only16-bit configurations execute these workflows.

Accepted IRQ source callbacks and deferred reads provide matching rise/fall waits;
completion and timeout restore previously unregistered IRQ mask to disabled.
After timeout, immediate input reads still work. Host realtime callback supplies
normal level/IRQ/abort events; delay boundary records finite <=50ms requests and
poll limits prevent accidental hangs. No private plugin state or invalid IDs.
This verifies return values/control flow/register restoration, not actual elapsed
seconds, CORE scheduler behavior, serial reset handling or physical timing.

No production edit, new known result or sanitizer allowance. Config/inversion
callback ABI, active-handler restoration, transfer failure/uninitialized reads
and hardware remain open. Misc110 cases;808 compatible authored, not a fresh
full global gate. Latest delivered batch29 remains800 plus26 separate legacy
references. No new coverage measurement; accumulate next supported workflows
before combined validation/push. Original checkouts remain unchanged.

---

# Latest component checkpoint - 2026-10-25 (batch29)

Goal active. Deliver23 accumulated MCP23017 cases across ENABLE1 mixed8/8,
ENABLE2 output-only16 and ENABLE3 input-only16. One full Windows Clang ASan/UBSan
compatible gate passes42 suites,800 cases =737 clean +63 documented known, zero
unexpected failures/skips. Known results now59 correct assertion regressions +4
diagnostic-only cases;3 assertions also carry exact diagnostics, counted once.
Unchanged26 legacy serial reference cases retain separate batch24 validation.

Output bit/packet ordering, duplicate writes, descriptors/nonzero bank offsets,
startup failures, input samples/enumeration and mixed isolation execute. Polling-
only driver capability rejects IRQ registration/edge waits without transport work.
Accepted IRQ callback queues original deferred reads; valid flags/capture data
route to distinct user ports, empty flags do not dispatch and detach before queued
execution prevents callback delivery. IRQ fixture holds one deferred task at a
time; it does not test bursts, actual CORE scheduling or MCU electrical interrupts.

Four correct known assertions cover rising/falling in mixed/input-only modes.
Matching edge passes; opposite edge still increments callback count because source
clears the flag then calls handler unconditionally. Keep exact WILL_FAIL/known_bug
entries, source/removal guide and correct assertions. No new sanitizer allowance,
unsafe data/ID injection or production edits. Blocking waits/config ABI, transport
failure/local uninitialized reads and hardware remain untested/source-reviewed.

Fresh selected-source LLVM report spans11 misc files:1119/1235 lines90.6%,552/756
branches73.0%,109/114 functions. Expanded denominator differs from prior10-file
report and excludes unbuilt modules/configurations; no whole-plugin claim.
Strict coverage classification passes102 misc cases (95 clean +7 known assertions),
fresh counter paths max224. Exact source details remain in ignored batch29 reports.

GitHub-resolved Plugins_misc2657119 and CORE b01f481 locks match clean originals.
Unchanged86 helper/actionlint checks were not rerun. Fresh fork workflow listing
still exposes only reusable/core entries; Plugin/Driver manual dispatch awaits
default-branch installation. Keep PR29 draft/unmerged; no hosted GCC/Linux,
actual controller/target linking or physical hardware success claimed. Continue.

---

# Local MCP23017 mixed/input checkpoint - 2026-10-25

Goal active. Nine new cases pass Windows Clang ASan/UBSan0.55s and strict
classification, all clean with zero unexpected failures/skips. Original ENABLE1
mixed8-input/8-output and ENABLE3 input-only16 configurations execute documented
IOCON/direction/interrupt-disable setup, mandatory initial read, immediate sampling
of zero/all-high/alternating GPIO patterns through both bank and descriptor APIs,
and A/B descriptor enumeration. Input/output isolation retains independent mixed
bank values. Input endpoints cover every valid bit and reject the unavailable port.

Fixture driver declines IRQ ownership. Source advertises IRQ_Mode_None, rejects
interrupt registration/edge waits without I2C writes or realtime polling, and
preserves normal immediate sampling. This is supported polling-only behavior,
not IRQ delivery coverage. Original IRQ/deferred code compiles but task dispatch,
blocking polls/delays and settings-config calls fail fast if unexpectedly invoked.
Successful reads initialize exactly the requested1/2 bytes; failed receive paths
remain source-only rather than executing uninitialized local read behavior.

No source edits, private state changes, new known result or sanitizer allowance.
Actual CORE aggregation/I2C SDK/electrical registers, IRQ/wait/config and transport
failure behavior remain open. Misc94 cases,792 compatible authored; latest
delivered batch28 remains777 plus26 separate legacy references. Together with
output-only cases,15 local MCP cases accumulate for next combined gate/push.
No new full gate or coverage measurement; continue supported IRQ/controller work.

---

# Local MCP23017 output-bank checkpoint - 2026-10-25

Goal active. Six new MCP23017_ENABLE2 output-only cases pass Windows Clang
ASan/UBSan0.35s and strict classification, all clean with zero unexpected failures/
skips. Original mcp23017.c executes IOCON/direction/initial GPIO writes,16-bit
GPIO A/B packet ordering, each output bit's preservation/clearing, duplicate write
suppression, public descriptors/function/description and native enumeration.
Bus-start/probe failure registers no bank and performs no writes. Nonzero pin_base2
descriptor reads/writes correctly use local id for both port0 and15; no PCA-style
offset failure occurs in these controls. Only valid descriptor IDs are used.

One original output-only unused direction argument receives a source-scoped
compiler warning option; no production source edit or runtime sanitizer allowance.
I2C and ioports registration are bounded public boundary models, not actual CORE
aggregation or MCU SDK/device execution. Mixed8-input/8-output and input-only16
configurations, input IRQ/wait/error recovery, inversion/config ABI and actual
hardware remain open. No new coverage or full-suite gate for this authoring group.

Misc85 registered cases;783 compatible is authored, not newly gated. Latest
delivered batch28 remains777 compatible plus26 separate legacy references.
Keep accumulating supported MCP input/transport and remaining modules before the
next combined validation/push. Original checkouts remain unchanged; goal active.

---

# Latest component checkpoint - 2026-10-25 (batch28)

Goal active. Deliver16 accumulated cases:11 HC595 SPI and5 deferred event-control/
startup cases. One full Windows Clang ASan/UBSan compatible gate passes42 suites,
777 cases =718 clean +59 documented known, zero unexpected failures/skips. Known
results remain55 correct assertion regressions +4 diagnostic-only cases;3 assertions
also carry exact diagnostics, counted once. No new known result or sanitizer
allowance. Unchanged26 legacy serial references retain separate batch24 validation.

HC5951/2/3-chip configurations execute8/16/24 bits, wire byte ordering, duplicate
successful-write suppression, bus selection failure/retry, startup failure and
public descriptors. Event controls execute via bounded FIFO with source-created
indexes0..3; optional stop/single-block/block-delete deferred outputs, unrelated
signal filtering and disabled binding before dispatch pass. No-port/allocation
startup failures preserve original hooks and queue warning; two available ports
bound settings iteration, coolant output mapping and reset. Remaining4-chip
highest-bit shift/config ABI and full CORE scheduler/hardware remain untested.

Fresh LLVM selected-source report spans10 misc files:887/921 lines96.3%,476/607
branches78.4%,92/95 functions. Eventout202/204 lines,111/127 branches; same-config
line increase33 from batch27. HC59585/96 lines,28/44 branches across1/2/3 chips.
Expanded total denominator differs from prior9-file report; unbuilt modules and
other configurations remain excluded. Strict coverage classification passes79
misc cases (76 clean +3 unchanged known assertions), fresh counter paths max224.

GitHub-resolved Plugins_misc2657119 and CORE b01f481 locks match clean originals.
No production source/header edits, private state changes or new diagnostic waiver.
Unchanged86 helper/actionlint checks were not repeated. Port/NVS/scheduler/SPI
boundaries are host models; no physical power-on state, SPI timing or controller
motion claim. Latest workflow availability remains batch26's core/reusable-only
listing; manual Plugin/Driver dispatch awaits default-branch installation.
Keep draft PR29 unmerged. Continue remaining modules and actual integration.

---

# Local HC595 SPI output checkpoint - 2026-10-25

Goal active. Eleven new cases pass focused Windows Clang ASan/UBSan0.71s plus
strict classification, all clean with zero unexpected failures/skips. Original
hc595.c executes one/two/three-chip builds:8/16/24 output bits, single-byte versus
multi-byte big-endian transmission, each bit's preservation and clearing,
suppression of duplicate successful writes and retry after SPI selection failure.
Pin metadata/ports_id, public descriptor/function/description updates, bounds,
failed SPI startup and native enumeration chaining execute. Default4MHz and
explicit1MHz slave settings plus CS pin7 are checked at the driver boundary.

Original source performs no startup shift transfer; tests assert registration/
software state only, not physical power-on outputs. Four-chip highest-bit signed
shift remains source-only and is not deliberately executed. Nonzero descriptor
bank offsets, config/inversion callback ABI, SPI write/deselect failures, optional
CS-port and physical timing remain open. No source edits, private state changes,
new known result or sanitizer allowance. SPI/port registration remain bounded
host models, not actual CORE aggregator or MCU SPI SDK execution.

Misc76 cases,774 compatible authored; latest delivered batch27 remains761 plus26
separate legacy references. This adds11 to the2 local event-control cases for13
accumulated cases. No fresh whole-suite gate, coverage, hosted or hardware claim.
Continue substantial related work before the next combined validation/push.

---

# Local deferred event-control checkpoint - 2026-10-25

Goal active. Two new control workflows plus all7 existing event-output cases pass
Windows Clang ASan/UBSan0.70s and strict classification:9 clean, zero unexpected
failures/skips. Original signal_out executes from a bounded FIFO boundary with
only source-created event indexes0..3; queue admission verifies uintptr_t values
before storing them. Optional-stop-disable, single-block and block-delete flags
update outputs on dispatch, preserve isolation and chain the previous control hook.
Cycle-start alone schedules no event work. Disabling a binding before dispatch
prevents its pending output change. No injected private callback/index or unsafe
pointer dereference, production edit or sanitizer allowance.

The original pointer/integer cast paths now execute only for validated tiny
indices in this host configuration; do not infer arbitrary pointer portability.
The queue remains a simulated scheduler, not actual CORE task execution. Public
controller flags and driver signals are host event inputs, not a real serial/job
or physical-input workflow. Trigger getter callback ABI and other layouts still
need source review. No fresh coverage measurement or full global gate for2 cases.
Misc65 cases,763 compatible authored; delivered batch27 remains761 plus26 separate
legacy references. Keep accumulating supported work before next combined push.

---

# Latest component checkpoint - 2026-10-25 (batch27)

Goal active. Deliver21 accumulated cases:14 probe-relay and7 event-output cases.
One full Windows Clang ASan/UBSan compatible gate passes42 suites,761 cases =702
clean +59 documented known, zero unexpected failures/skips. Known results remain
55 correct assertion regressions +4 diagnostic-only cases;3 assertions also carry
exact diagnostics and are counted once. No new known result or sanitizer allowance.
Unchanged26 legacy serial reference cases retain separate batch24 validation.

Probe-relay selection covers native/relay combinations, exclusive levels/default
selection, delay requests, disabled/failed ports, saved/deferred mapping, reports
and absent prior selector. Event outputs cover spindle/laser/at-speed, coolant,
state/reset, trigger rebind, settings iteration/early-stop/normalization and
saved/deferred mapping. Claimed/missing/disabled ports reject without unintended
output; valid remaining mapping still responds. Original CORE strgetentry executes.

Fresh LLVM selected-source coverage spans9 misc files:769/825 lines93.2%,429/563
branches76.2%,81/85 functions. Eventout169/204 lines,92/127 branches; probe relays
91/94 lines,60/65 branches. Expanded denominator differs from prior7-file report;
these numbers exclude unbuilt modules and alternative layouts. No whole-plugin
coverage claim. Fresh counter paths max224; strict coverage classification passes
63 misc cases (60 clean +3 unchanged known assertions).

Deferred control-signal tasks remain fail-fast boundaries; pointer-width casts
and trigger getter ABI need review before invocation. MinGW's supported CRT
NO_OLDNAMES option avoids its optional strset alias clash; no production header/
source edit, rename or bypass. Port configuration, scheduler, NVS, debounce and
outputs are host models; actual controller/parser/probe motion/hardware remain.

GitHub-resolved Plugins_misc2657119 and CORE b01f481 locks match clean originals.
Unchanged86 source/report helpers and actionlint were not rerun. Batch26 fork
workflow listing exposes only reusable/core workflows; separate Plugin/Driver
manual dispatch awaits default-branch installation. Keep PR29 draft/unmerged;
no hosted/target/hardware success claimed. Continue remaining modules/integration.

---

# Local event-output callback checkpoint - 2026-10-25

Goal active. Four new workflow cases pass focused Windows Clang ASan/UBSan0.33s
and strict classification, all clean with zero unexpected failures/skips. Original
eventout.c restores settings, resolves public port descriptors during startup and
registers native hooks. Spindle/laser enabled outputs stay separate; at-speed has
its own output. Mist/flood masks remain independent; state outputs track hold,
alarm and homing/cycle/jog, with duplicate state notifications suppressing extra
writes while chaining the previous hook. Reset clears non-alarm bound outputs
and preserves alarm indication. Live mist-to-flood-to-ignore rebinding preserves
single hook ownership and original coolant calls; reports chain.

Original CORE strgetentry executes from unchanged strutils.c. MinGW's supported
NO_OLDNAMES option disables its optional CRT strset alias, avoiding a name clash
with CORE's unrelated string API; no macro renaming or header/source bypass.
Signed-comparison warnings in original strutils and pointer/integer-width cast
warnings in original eventout are source-scoped. Deferred control-signal tasks
are unexecuted: task_add_immediate fails fast. No runtime sanitizer suppression
or new known allowance. Unused ftoa link dependency is a fail-fast boundary.

Port registry/configuration, startup scheduling and outputs are captured host
boundaries; native spindle descriptors are host event inputs, not executed CORE
spindle registration/parser/motion. Remaining event settings, control toggles,
other slot counts and real controller/hardware remain open. Misc60 cases;
758 compatible is authored, not a new full global gate. Latest delivered batch26
remains740 compatible plus26 separate references. Accumulate next group before
combined delivery. Original source checkouts remain unchanged.

---

# Local probe-relay selection checkpoint - 2026-10-25

Goal active. Fourteen new cases pass focused Windows Clang ASan/UBSan plus strict
classification:11 cases0.83s +3 added controls0.25s, all clean with zero unexpected
failures/skips. Original probe_relays.c registers settings, restores/persists port
assignments and wraps hal.probe.select. Tests select toolsetter/second/default,
check output exclusivity and50ms debounce requests, retain existing native probe
selection, handle absent previous selector and reject disabled relay selection
without changing the active relay or requesting another delay.

Saved reversed port mapping loads before first hook installation. Live settings
changes/save retain currently claimed mapping, matching reboot-required settings.
Both disabled ports and failed claims leave the prior selector intact. No probe,
both native probes, no AUX ports and failed NVS allocation preserve existing hooks;
reports/setting availability chain correctly. Native-state reader fails fast if
unexpectedly called. No private state, source edits or new known allowances.

Port configuration/claims, NVS, output levels and delays are captured driver/API
boundaries. Actual CORE port aggregation, G65/P5 routing, probe motion, physical
relay settling and target builds remain untested. Repeated settings load after
hook installation needs ownership review: source saves current hal.probe.select
again; these cases do not force recursion. Original production checkout clean.
Misc suite56 registered;754 compatible is authored, not a new full global gate.
Latest delivered batch26 remains740 compatible +26 separate reference cases.
Accumulate next supported module work before combined validation/push; no new
coverage/hosted/hardware claim. Goal remains active.

---

# Latest component checkpoint - 2026-10-25 (batch26)

Goal active. Deliver18 accumulated cases:8 PCA9654E output-bank and10 per-axis
homing pull-off. One full Windows Clang ASan/UBSan compatible gate passes42 suites,
740 cases =681 clean +59 documented known, zero unexpected failures/skips. Known
results now55 correct assertion regressions +4 diagnostic-only cases;3 assertions
also carry exact diagnostics, counted once. The26 legacy serial reference cases
retain separate unchanged batch24 validation, not included in740.

PCA tests cover startup/bus/probe failures, all8 physical output bits, duplicate
successful writes, descriptor boundaries and native enumeration/function/description
chaining. Retain two correct known descriptor bank-offset assertions: ordinary
port0 writes bit0, descriptor0 with pin_base2 reads/writes bit2 instead. No unsafe
shift, invalid ID, private state edit or new sanitizer allowance. Registration is
modeled from CORE's actual pin_base assignment, not full aggregator execution.

Pull-off tests cover three/six-axis registered settings, defaults, save/load,
per-axis limits requests, global inherited/default changes and hook failures/
chaining. Configured Y/Z/A/B/C defaults and persistence execute. Actual settings
dispatch, limits/planner/stepper implementation and physical homing are boundaries.

One fresh selected-source LLVM report across7 instrumented misc files:509/527
lines96.6%,277/371 branches74.7%,54/55 functions. Pull-off74/74 lines,29/31 branches;
PCA86/97 lines,29/42 branches; ADC49/50 and DAC62/63 lines. This excludes unbuilt
misc modules and alternate configurations: not whole-plugin/repository coverage.
Fresh counter paths max224. Next largest source groups include event outputs,
probe relays and MCP23017; PCA inversion ABI and failure/retry contract stay open.

GitHub-resolved Plugins_misc2657119 and CORE b01f481 locks match clean originals.
Unchanged86 reporting/source helpers and actionlint were not repeated. Latest fork
workflow listing still contains only Reusable host tests and Core tests; separate
Plugin/Driver dispatch needs default-branch installation. No hosted/target/hardware
success or merge claimed. Continue remaining modules and controller integration.

---

# Local per-axis homing pull-off checkpoint - 2026-10-25

Goal active. Ten new cases pass focused Windows Clang ASan/UBSan and strict
classification:7 three-axis cases0.42s +3 six-axis cases0.25s, all clean with
zero unexpected failures/skips. Original homing_pulloff.c registers settings,
restores first-boot defaults, updates per-axis limits requests, persists/reloads
all axes and retains hook chains. Global setting changes update matching inherited
distances while preserving custom axes; unchanged global value avoids extra writes.
Explicit restore uses current global default plus configured axis defaults.
Allocation/registration failure leaves existing hooks intact. Reports chain.

Six-axis builds cover Y/Z/A/B/C compile-time defaults and each axis's update/
persistence independently. X12 is the pinned source's own unconditional default,
not a hardware recommendation. Public settings-family decoding, NVS and limits
requests are host boundaries; actual CORE settings dispatcher, limits machinery,
planner/stepper homing and physical pull-off are NOT executed. No production
source edit, new exception or diagnostic allowance; original checkout clean.

Misc suite42 cases;740 compatible is authored, not a fresh full global gate.
Latest delivered batch25 remains722 compatible +26 separate legacy references.
Together with the local PCA group this accumulates18 cases for the next combined
delivery. No new coverage/hosted/hardware claim. Continue remaining module and
controller integration work on the existing branch.

---

# Local PCA9654E output-bank checkpoint - 2026-10-25

Goal active. Eight new cases pass focused Windows Clang ASan/UBSan0.63s and
strict classification:6 clean +2 documented correct descriptor-offset regressions,
zero unexpected failures/skips. Original module executes startup configuration/
inversion/output register order, bus/probe failure, all8 output bits, suppression
of duplicate successful writes, valid descriptor read/write, public boundary
rejection and native enumeration/function/description chaining.

Two modeled preceding outputs assign pin_base2 through ioports_add_digital, per
actual CORE registration contract. Descriptor0 then reads bit2 rather than bit0,
and descriptor write changes bit2 rather than bit0. Retain both correct assertions
under exact WILL_FAIL/known_bug; zero-base controls pass. No production edits,
private pointer/ID changes, unsafe shifts or sanitizer allowance. Actual CORE bank
aggregation is not executed by this boundary fixture. Inversion configuration's
callback ABI and I2C-failure/cache semantics remain source review, not claimed.

Misc suite now32 cases;730 compatible is authored, not a new full global gate.
Latest delivered batch25 remains722 compatible +26 separately validated legacy
serial references. No new coverage measurement or hosted/hardware success.
Accumulate remaining supported module work before another combined gate/push.

---

# Latest component checkpoint - 2026-10-25 (batch25)

Goal active. Deliver23 accumulated cases:12 fan persistence/configuration and11
MCP3221 ADC/MCP4725 DAC cases. One full Windows Clang ASan/UBSan compatible gate
passes42 suites,722 cases =665 clean +57 documented known, zero unexpected
failures/skips. Known results now53 correct assertion regressions +4 diagnostic-
only cases;3 assertions also carry exact diagnostics and are counted once.
The26 legacy serial reference cases retain separate batch24 validation, unchanged.

New analog cases run original registered callbacks with bounded synchronous I2C:
startup/probe failures,12-bit sample/packet boundaries, initial DAC state, bank
metadata/remapping descriptions and native enumeration chaining. DAC failed send
correctly retains cached output but returns true; keep correct false assertion
in exact WILL_FAIL/known_bug with source/removal guide. Recovery write succeeds.
No new sanitizer allowance, production source edit or unsafe receive-failure run.
ADC failed receive leaves local bytes uninitialized by source review; that path
stays unexecuted pending upstream contract/repair. Host registration is captured,
not actual CORE bank aggregation. Physical I2C/device behavior stays unverified.

Fan21 cases now include one/two/three/four configurations, saved port/delay first
load and delayed shutdown cancellation by reset/new command. Existing setter
diagnostic unchanged. Fresh batch25 selected one/two/four coverage before adding
three-fan builds:184/190 lines,102/119 branches,23/24 functions. No new analog or
three-fan coverage measurement. Final descriptor assertions tightened after the
global gate and both affected cases pass0.17s; strict classification clean.

GitHub-resolved source locks match clean unchanged Plugins_misc2657119, fans
c5c3613 and CORE b01f481. Unchanged86 helper/actionlint checks were not rerun.
Draft PR29 remains unmerged; no hosted GCC/Linux or target/hardware success claim.
Continue remaining modules and actual controller integration on this branch.

---

# Local fan configuration checkpoint - 2026-10-25

Goal active. Nine new cases build original fans.c with FANS_ENABLE1/3/4 and pass
focused Windows Clang ASan/UBSan0.68s plus strict classification:9 clean, zero
unexpected failures/skips. Each configuration checks its actual registered port
settings, boolean/bitfield format, M106 physical mapping, fan count/report mask,
stored disabled last port and shutdown/reset across every configured output.
Only valid public fan indexes are used; no private state or production edits.

Host output storage now bounds four pins and respects advertised port counts.
After this shared fixture change, the initial18-case fan gate passed1.23s and
strict classification17 clean +1 unchanged spindle-setter diagnostic. The later
three-fan expansion changes only case registration/report expectations; all9
configuration cases then passed. The original diagnostic source line is untouched.

One fresh local coverage measurement, before adding three-fan configuration,
covers selected one/two/four-fan builds:184/190 lines,102/119 branches,23/24 functions.
Counter paths max237; original fan pin c5c3613 remains clean. Do not describe this
as three-fan measurement or whole-repository coverage. Current fan suite21 cases;
711 compatible cases is authored, not a new completed global gate. Batch24 remains
latest delivered699 compatible +26 separate reference cases. Accumulate further
work before combined delivery; actual settings/parser/scheduler, physical outputs
and hosted execution remain unverified.

---

# Local fan persistence and delayed-shutdown checkpoint - 2026-10-25

Goal active. Three new fan cases pass focused Windows Clang ASan/UBSan0.27s
and strict classification:3 clean, zero unexpected failures/skips. Saved port
remapping/delay survive live-setting changes before the first registered load;
program completion then uses the persisted physical mapping and7500ms delay.
Driver reset cancels pending shutdown, clears both outputs and permits a later
fan cycle. M106 in check mode preserves the timer; real execution cancels it,
and the next program end schedules a fresh shutdown. Original registered plugin
callbacks execute; scheduler/NVS/physical outputs remain bounded host models.

No fixture/production source edit or new known allowance. Existing spindle setter
diagnostic case is untouched. Fan suite now12 registered cases; compatible702 is
an authored total, not a newly completed global gate. Latest delivered batch24
remains699 compatible plus26 separate reference cases. Accumulate more supported
work before the next full combined gate/push. Hardware/hosted checks remain open.

---

# Latest component checkpoint - 2026-10-25 (batch24)

Goal active. Combined pre-push Windows Clang ASan/UBSan gate passes all42
current-compatible suites:699 cases =643 clean +56 documented known results,
zero unexpected failures/skips. Separate full legacy reference gates pass:
PSoC9 =8 clean +1 known; TI shared serial17 =15 clean +2 known. These26 cases
remain outside699 and the older Simulator VFS reference evidence.

Nine accumulated cases add actual070f80 CORE stream connection/suspend/ACK/
backup/restore under explicit char modes and optional TI UART7 public workflows.
Correct signed-char ACK and secondary descriptor instance assertions remain exact
known_bug regressions; PSoC capacity regression remains. No new sanitizer allowance,
production source edit, cast or fallback. UART7 explicitly enables RX before IRQs;
physical startup policy and MCU default char signedness are not inferred.

Fresh selected-source LLVM coverage: PSoC59/59 lines,14/16 branches,13/13 functions;
TI primary plus optional secondary168/173 lines,48/60 branches,23/24 functions.
TI's expanded configuration changes the denominator from primary-only batch23;
these percentages are not a same-configuration gain or whole-repository coverage.
Original candidate/reference CORE/SDK pins remain unchanged. Existing86 helper
and actionlint checks from batch23 were not repeated: no helper/workflow changes.
Physical hardware, target linking, full task/protocol execution and remaining
components stay open. Draft PR29 remains unmerged; no hosted success claimed.

---

# Local TI secondary-UART checkpoint - 2026-10-25

Goal active. Added5 source-supported SERIAL2_MOD/UART7 cases:4 clean +1 correct
metadata regression. Full affected TI legacy reference suite17 cases passes
Windows Clang ASan/UBSan1.28s and strict classification:15 clean +2 known, zero
unexpected failures/skips. Existing current-compatible TM4C12314 cases also pass
0.69s after shared SDK fixture expansion (13 clean +1 unchanged known result).
No new sanitizer allowance, CORE/SDK/driver edits or weakened assertion.

Dual-port bounded SDK model separates UART0/UART7 masks/inputs/handlers and checks
original GPIOA/PC4/PC5/UART clock/pin constants. Tests cover independent RX,
flush/cancel/wrap, full-ring realtime, separate installed handlers/public enqueue,
and secondary mute/re-enable without affecting primary RX. Secondary TX remains
unsupported/fail-fast. Every RX control explicitly enables via disable_rx(false);
serial2Init startup enablement is not force-classified. Returned secondary
io_stream_t reports0 while registered property advertises1; retain correct
instance1 assertion under exact known_bug, with source/removal guide in suite docs.

TI now17 reference cases; PSoC9 pending reference cases remain from prior local
checkpoint. No addition to current-compatible699-case delivered baseline. A short
owned build path avoids the long Windows object path warning; no build deletion
or restart of live work. Original sources/dependency checkouts remain clean.
No new coverage measurement, global gate or hosted result. Keep accumulating
before next combined delivery; full MCU/parent/SDK startup and hardware remain.

---

# Local legacy CORE stream checkpoint - 2026-10-25

Goal active. Four new reference cases pass focused Windows Clang ASan/UBSan and
strict classification:3 clean +1 correct signed-char portability assertion, zero
unexpected failures/skips. TI adds handler lifecycle and actual legacy CORE
registration/open/connect/suspend under explicit signed/unsigned char builds;
PSoC adds unsigned primary connection/suspend/backup/restore. TI3 cases0.22s;
PSoC1 case0.08s. No source copies/edits, private ring writes or diagnostic allowance.

Original070f80 CORE's char callback cannot match CMD_TOOL_ACK0xA3 under signed-char:
0 acknowledgements rather than1. Correct assertion retained in one exact known_bug;
identical unsigned control accepts ACK and restores original queued input. This
establishes a host compiler-character portability difference, not an unspecified
MCU default or physical board failure. Existing PSoC capacity regression remains.
PSoC now9 and TI shared serial12 registered reference cases, separate from all
current-compatible totals. The prior delivered baseline remains batch23.

One small shared hardware-independent boundary file supplies unused report/task
stubs that fail fast; original CORE stream.c executes. Physical UART/FIFO/IRQ,
full protocol/task execution and SDK firmware builds remain untested. Shared
fixture has explicit LEGACY_CORE_STREAM branches only for these new targets.
No new global gate/coverage/hosted claim; accumulate before combined delivery.

---

# Latest component checkpoint - 2026-10-25 (batch23)

Goal active. Deliver two new explicit fixed-CORE legacy reference suites plus
Thermistor normal first boot. One complete Windows Clang ASan/UBSan compatible
gate:42 suites,699 cases =643 clean +56 documented known results, zero unexpected
failures/skips. Existing52 correct assertion regressions +4 diagnostic-only cases
remain;3 assertions also carry exact diagnostics, counted once. Separate reference
gates: PSoC8 =7 clean +1 correct free-capacity regression (0.45s); TI shared serial9
clean (1.46s). These17 reference cases are NOT added to compatible699 or any older
Simulator VFS reference count. No production edits or new sanitizer allowance.

PSoC uses its actual documented070f80 CORE gitlink with declaration-only generated
UART boundaries; no Cypress SDK claim. New shared serial runs original6adcc848
primary UART0 with real Tiva header mirror and old CORE types. It is not archived
TM4C1294 parent shared3e7873 or an MSP432E SDK/parent build. Existing SDK host
fixture reused with explicit API-signature/metadata branches; current TM4C14
cases pass the full compatible gate. Shared reference tests cover initialization,
FIFO/wrap/cancel, full-ring realtime, queued TX/backpressure/recovery, RX disable
preserving TX and public baud/duplicate-claim rejection. Actual legacy CORE stream
execution and suspension remain boundaries. Current-CORE syntax rejection for
both modules recorded without aliases or fallback. SDK/firmware/hardware untested.

Source-only legacy dependency now has shared descriptive key core_20250518_reference;
manifest choices reject core_ref overrides and exclude dependencies from runnable
suites. Regression coverage verifies both plans and avoids parent substitution.
All86 helper checks pass9.465s; actionlint/whitespace pass. New reference choices
remain subject to default-branch workflow installation; no hosted pass claimed.

Fresh local LLVM: PSoC57/59 lines96.6%,14/16 branches87.5%,12/13 functions;
TI serial92/108 lines85.2%,31/42 branches73.8%,10/15 functions, both explicit
reference configurations. Thermistor138/139 lines99.3%,69/74 branches93.2%,12/12
functions adds1 current-compatible exercised line via real missing-NVS first load.
Reference coverage never implies current compatibility or whole repository gain.
Fresh counter paths max216; strict source locks match clean originals. CORE current
b01f481 and reference070f80 stay separate; Tiva SDKc23bf8ba, PSoCc9d72125,
shared6adcc848 and Thermistor4fae94b9 locked exactly in ignored build-evidence.

Keep existing PR29 draft/unmerged. MSP430 SDK/compiler investigation remains
source-only evidence; actual16-bit target runtime, remaining modules and physical/
controller validation remain open. No goal completion claimed.

---

# Local reference-handler/SDK checkpoint - 2026-10-25

Goal active. Added one PSoC legacy-reference realtime handler lifecycle case:
public enqueue and RX callbacks reach the replacement, direct rejected input is
not queued, restoration recovers normal filtering and ordered RX. Focused Windows
Clang ASan/UBSan1/1 passes0.08s with strict classification;8 reference cases now
registered. No new allowance, production edit or compatible-suite count change.
Keep reference results separate from batch22's698 current-compatible baseline.

MSP430 SDK investigation located/downloaded official TI support package1.207,
verified SHA256 and inspected original F5529/iomacros headers. Word registers use
target-width unsigned int and assembler-bound addresses; native host replacement
would not establish the16-bit target ABI. Installed Clang backend inventory has no
MSP430 target. Archive/source metadata and compiler target list are saved ignored
under build-evidence; no toolchain installer executed. Exact provenance/remaining
compiler boundary are in COMPONENT_TODO. MSP430 runtime remains unclaimed.

PSoC reference workflow/plan helper checks remain last85 pass from prior checkpoint;
unchanged scripts/workflows were not rerun. No full compatible gate/coverage/hosted
result; accumulate pending reference/first-boot work before combined delivery.

---

# Local legacy-reference/first-boot checkpoint - 2026-10-25

Goal active. PSoC5 now has an explicit registered Driver-tests reference choice
with fixed documented CORE070f80 dependency in deps/core-20250518. Seven original
serial-source cases pass Windows Clang ASan/UBSan0.50s with strict classification:
6 clean +1 correct free-capacity assertion, zero unexpected failures/skips.
Candidatec9d721259783ca578ee1b0c3f6111839610c26a4 and reference CORE API-match clean
originals; actual driver gitlink confirms the pin. Current CORE b01f481 unchanged
serial syntax check rejects historical callback signatures. No type aliases or
production edits; no automatic legacy fallback. These seven results are separate
from42 current-compatible suites / batch22's698-case delivered baseline.

Reference uses declaration-only generated UART symbols with bounded FIFO/TX/IRQ
host callbacks; no actual Cypress SDK or UDB/firmware claim. Actual legacy CORE
stream execution/suspend, driver.c/NVS and hardware remain untested. Dependency
and forwarding headers are system includes; fixture warnings remain strict.
One correct RX free-capacity assertion retains31 usable bytes versus32 reported;
separate normal capacity/full-ring realtime controls pass. No diagnostic allowance.

Thermistor also adds one ordinary missing-NVS first-boot case, focused1/1 pass0.09s:
normal first load restores/persists disabled defaults once, claims/reads no sensor
and keeps the existing report chain. No repeated-load recursion invoked.
Thermistor now18 registered cases, pending combined delivery/measurement.

Manifest/Driver workflow expose only the reference test suite; fixed CORE is
source-only and not selectable, core_ref overrides reject. Regression tests lock
that distinction and preserve ordinary candidate/current-CORE selection. All85
reporting/source-plan helpers pass9.751s; actionlint and whitespace pass. No new
full compatible gate, coverage or hosted result; accumulate before next delivery.

---

# Latest component checkpoint - 2026-10-25 (batch22)

Goal active. Combined11 new plugin settings/configuration cases: Interlock6,
PneumaSeal3 and Thermistor2. One complete Windows Clang ASan/UBSan gate:42
compatible suites,698 cases =642 clean +56 documented known results, zero
unexpected failures/skips. Known results remain52 correct expected assertions
plus4 diagnostic-only cases;3 assertion cases also carry exact diagnostics and
are counted once. No new allowances, weakened assertions, CORE or plugin edits.
Strict classification ran every suite. Unchanged84 reporting helpers last passed
batch17; unchanged workflows not relinted. Whitespace passes.

Fresh local LLVM selected-source coverage: Interlock185/185 lines100%,72/84
branches85.7%,23/23 functions (+12 lines); PneumaSeal140/141 lines99.3%,43/52
branches82.7%,26/26 functions (+12 lines); Thermistor137/139 lines98.6%,68/74
branches91.9%,12/12 functions (+4 lines). Adds28 exercised lines; fresh counter
paths max215 characters. Full physical safety, whole repositories, controller
shutdown, settings-parser validation and actual scheduler behavior not established.

Interlock covers registered readback/save/load/restore, inverse-slot disable,
direction/polarity, default4/4 and supported1/2 plus2/1 forward/inverse layouts.
PneumaSeal covers registered getters, persisted timeout/mask values, restore and
pending port changes without abandoning/reclaiming the remapped active output.
Thermistor covers port availability/getter/reboot flag, pending disable, restore
of resistance/calibration/alarm defaults and continued monitoring on the existing
claimed port. Repeated Thermistor load-hook ownership and invalid-sample alarm
counting remain unclassified; no recursive failure or arbitrary threshold contract
is forced. Host ports, alarm/reset requests, NVS and timing remain boundaries.

API source locks match clean originals: Interlock5893ea35645c334ec96333ccd0519eac03128ee6;
PneumaSeal3127ab8c15982569d7e89822a9e1095cdce89cbb;
Thermistor4fae94b9b553604f2f41222bbc04fa45669c2bdf;
COREb01f481072edecac33d5e40c25869359a5b3fa1f. Locks/evidence ignored in
build-evidence. Deliver on existing PR29, keep draft/unmerged. Hosted workflow
installation, remaining components and physical/controller checks remain open.

---

# Local PneumaSeal settings checkpoint - 2026-10-25 (next combined batch)

Goal active. Three additional settings lifecycle cases pass focused Windows Clang
ASan/UBSan0.22s and strict classification:3 clean, zero known/failures/skips.
Registered getters verify persisted timeout/mask values and configured port,
with corresponding state/timer/output behavior. Port changes/disable require a
reboot per the public setting flag; reload retains the existing remapped claim
and active output, rather than treating changed configuration as immediate
hardware reassignment. Restore persists default timing/masks and subsequent
state transitions use the restored delays without reclaiming the port.

PneumaSeal now18 registered cases. Shared fixture extracts its existing registered
setting lookup and adds typed getter/port callbacks; no production source changes,
new assertion allowances or diagnostics. Original candidate
3127ab8c15982569d7e89822a9e1095cdce89cbb verified clean. Public CORE io_port_cfg helpers remain
host boundaries, timer expiry is explicit host delivery, full settings parsing
and actual scheduler/controller/air-pressure behavior remain untested. Combine
with pending Interlock6 and further work before next cumulative gate/delivery.
No new coverage measurement or hosted result; batch21 remains delivered baseline.

---

# Local Interlock settings checkpoint - 2026-10-25 (next combined batch)

Goal active. Six additional cases pass focused Windows Clang ASan/UBSan0.44s and
strict classification:6 clean, zero known/failures/skips. Registered getters now
check every default slot through save/load and restore; inverse guards can be
individually disabled while other configured guards still suppress writes;
direction and active-level changes select the correct observed port/polarity.
Two additional source-supported configurations (forward/inverse1/2 and2/1) verify
runtime-generated setting IDs/names/getters and actual forward/inverse decisions.
Existing default4/4 cases remain. No production edits or new known allowances.

Interlock now19 registered cases. Helper additions invoke original registered
getter callbacks with CORE's exact typed signatures. Ports/NVS/spindle output,
reset/alarm requests and task/realtime boundaries remain simulations; these tests
do not establish controller emergency-stop timing, protocol permission to change
settings during motion, physical machine safety, real settings parser behavior or
multi-spindle ownership. Source5893ea35645c334ec96333ccd0519eac03128ee6 verified
clean. No new coverage measurement, cumulative gate or hosted result; batch21
below remains delivered baseline. Accumulate related modules before delivery.

---

# Latest component checkpoint - 2026-10-25 (batch21)

Goal active. Delivered accumulated17 new driver behavior cases: SAM6, TeensyPWM9,
TM4C123UART2. One complete Windows Clang ASan/UBSan gate:42 compatible suites,
687 cases =631 clean +56 documented known results, zero unexpected failures/skips.
Known results remain52 correct expected assertion regressions +4 diagnostic-only;
3 assertion cases also carry exact existing diagnostics, counted once. No new
assertion/sanitizer allowances, weakened assertions, SDK or production edits.
Strict classifier ran every suite. Unchanged84 reporting helpers last passed
batch17; no redundant rerun or relint of unchanged workflows. Whitespace passes.

Fresh local LLVM selected-source results: SAM serial276/278 lines99.3%,100/108
branches92.6%,39/39 functions; adds2 exercised lines and1 function. Teensy PWM
88/88 lines100%,31/37 branches83.8%,6/6 functions; TM4C123 serial112/112 lines100%,
44/48 branches91.7%,14/14 functions. Latter two source-coverage counts unchanged;
new cases verify additional observable workflows, not a percentage gain. Fresh
counter paths max216 characters. These files/configurations are not whole drivers,
board startup, physical timing, SDK linking or target firmware build evidence.

SAM cases cover supported even/odd/none parity changes retaining other mode bits,
independent simultaneous RX/TX on both UARTs, and primary public realtime handler
routing/restoration in UART(-1)/USART1-primary builds. PWM cases cover repeated
configuration/duty updates, independent FlexPWM submodules and QuadTimer channels
across Teensy4.0/4.1/MicroMod. TMUART timeout-RX and simultaneous TX/RX IRQ delivery
use a bounded SDK event fixture; TX completion preserves receive interrupts.
Known primary/secondary disable and full-ring realtime regressions remain intact.
No opaque PWM handle forging, sixth ownership claim or unsafe memory reproduction.

API source locks match clean originals: COREb01f481072edecac33d5e40c25869359a5b3fa1f;
SAM2321092b02cbbdecf2eba2b168a74b085e573418 with Arduino SDK
790ff2c852bf159787a9966bddee4d9f55352d15; Teensyd1f8d1ed904242ee08b0a5583e78f490afd9ae93
with SDK7f107ee0a309f3813ed13f0d8f615497eca2ee49; TM4C12314fdf8de2126316c14d88656f3a19337800ad1c1
with Tiva mirrorc23bf8ba7a82b20421aa04d4df3f77501c5883ea. Locks/evidence ignored in
build-evidence. Keep existing PR29 draft/unmerged. Hosted workflow installation,
full controller integration and remaining components/hardware checks remain.
Fresh fork API lists only Reusable host tests and Core tests; the separate
Plugin/Driver workflows are still unavailable for manual dispatch. No dispatch
retry or merge is performed to install them.

---

# Local Teensy PWM checkpoint - 2026-10-25 (next combined batch)

Goal active. Nine new cases pass focused Windows Clang ASan/UBSan0.49s and strict
classification:9 clean, zero known/failures/skips. Three behavior files execute
under Teensy4.0/4.1/MicroMod: reconfigure already-claimed X/A/B/QuadTimer handles
through period/prescaler/inversion changes, retain exact duty images, preserve
independent FlexPWM submodule/QuadTimer outputs, and independently configure/update
three QuadTimer channels in the same module. All handles come from public claim;
never exceed five claims or forge opaque signals. No shared fixture/source edits,
new known assertions or sanitizer allowances.

PWM suite now36 registered cases. Driverd1f8d1ed904242ee08b0a5583e78f490afd9ae93
and Teensy SDK7f107ee0a309f3813ed13f0d8f615497eca2ee49 verified clean. Together
with pending SAM6 authoring cases, keep accumulating before combined validation
and delivery. Batch20 below remains delivered baseline; no new source coverage or
hosted result. These tests verify register images, not actual clock source/edge
frequency, physical output timing or board startup. Shared FlexPWM A/B channels
within one submodule still need their separate board-level ownership contract.

---

# Local SAM serial checkpoint - 2026-10-25 (next combined batch)

Goal active. Six new SAM3X8E cases pass focused Windows Clang ASan/UBSan0.38s and
strict classification:6 clean, zero known/failures/skips. Three separate behavior
files run with primary UART(-1)/USART1 and secondary USART2: supported8-bit/one-stop
parity transitions even/odd/none update status and preserve all other mode bits;
queued two-port TX with simultaneous RX retains exact independent payloads; primary
public realtime enqueue and actual RX IRQ use the installed handler, then restore
normal filtering without queuing the direct callback's rejected bytes.

SAM suite now41 registered cases. No shared fixture, source, known assertion or
sanitizer allowance changes. Original driver2321092b02cbbdecf2eba2b168a74b085e573418
and Arduino SDK790ff2c852bf159787a9966bddee4d9f55352d15 verified clean. Existing
CORE b01f481 contract retained. This is focused authoring evidence, not a new
cumulative gate, source coverage measurement, hosted or physical UART result.
Batch20 below remains delivered baseline. Keep accumulating before next full gate.

---

# Latest component checkpoint - 2026-10-25 (batch20)

Goal active. Combined16 additional MPG cases:7 callback cases,6 original CORE
stream integration cases and3 passive command cases. Complete Windows Clang
ASan/UBSan gate:42 compatible suites,670 cases =614 clean +56 documented known
results, zero unexpected failures/skips. Known results now52 correct expected
assertion regressions plus4 diagnostic-only cases;3 assertion cases also carry
existing exact diagnostics, counted once. No new sanitizer exception or firmware
source edits. Strict classifier ran for every suite. Unchanged84 reporting helpers
were not rerun (last full batch17); unchanged workflows need no actionlint rerun.
Whitespace passes; API source lock matches clean original MPG/CORE checkouts.

Fresh local LLVM MPG .c438/468 lines93.6%,166/234 branches70.9%,47/48 functions;
wire header25/25 lines and10/10 branches. Adds15 exercised original plugin lines
since batch19. Counter paths max226 characters; strict profiling checks pass.
CORE integration executes original source but its coverage is not included in the
plugin filter: do not infer CORE-wide or controller coverage from these numbers.

Original CORE stream registration/claim ownership, passive filtering, busy refusal,
mode reader selection/restoration, baud table, broadcast ownership and queued
passive status now execute. Nine integrated cases supplement36 capture cases.
Six integration cases explicitly use MPG_BUFFER_SIZE=0; three enable128 bytes for
command buffering. Single/fragmented commands, realtime filtering, CRLF, blank
commands, G-code rejection and handler error/recovery controls pass in both modes.
Host system handler records strings and emits an explicit marker; actual system
commands, parser, CORE task allocator/executor, primary UART and hardware are not
linked/executed. Bounded FIFO task delivery matches reviewed grbllib.c append order.

New correct regression m1_core_command_burst: valid framed `$I`, `$G`, `$$` burst
queues three jobs, each reads the shared overwritten input and delivers `$$`.
Correct ordered-command assertion retained under one exact WILL_FAIL/known_bug;
source cause/proposed repair/removal guide in suite KNOWN_BUGS. No malformed wire,
unsafe memory failure or private test seam. No claim of physical controller fault.
Manual-tool ownership remains unresolved: CORE MPG mode retains primary suspend
and handler setters while replacing read routing. Do not force a test contract.

Pinned candidate503b422d0aa92c4d2b6a190e92ce25344bcc629e and
COREb01f481072edecac33d5e40c25869359a5b3fa1f. Evidence/source lock ignored in
build-evidence. Deliver together to existing PR29, keep draft/unmerged. Hosted
workflow installation, remaining components and physical/target checks remain.

---

# Local MPG CORE-stream checkpoint - 2026-10-24 (next combined batch)

Goal active. Six new integration cases use original CORE stream.c, stream_passthru.c,
vfs.c, strutils.c and nuts_bolts.c with original MPG source in plain/framed builds.
Complete affected MPG suite42/42 passes Windows Clang ASan/UBSan2.30s and strict
classification:42 clean, zero known/failures/skips. Existing36 capture cases remain
unchanged in behavior. Integration builds exclude the capture replacements for
CORE APIs and link the real functions; fixtures stay strict, original CORE warnings
remain visible under source-specific rules. No production edits or new allowance.

Tests exercise real stream property registration/claim ownership, descriptor-copy
registration, passive filtering, busy refusal/active reader selection, restoration
on disable, runtime baud table and output broadcast ownership. Passive status
requests pass through real stream_mpg_check_enable and queued report delivery,
then original transport output/ACK handling. The host report formatter emits an
explicit marker; no controller report-format claim. CORE's normal null stream
provides the console baseline; physical UART callbacks and time/task/protocol
boundaries remain simulations. MPG_BUFFER_SIZE=0 explicitly disables passive
command buffering, which is untested here. No full parser or driver task loop.

CORE b01f481072edecac33d5e40c25869359a5b3fa1f and candidate
503b422d0aa92c4d2b6a190e92ce25344bcc629e verified clean. Tool-ACK remains unresolved:
mode switching retains primary suspend_read/set_enqueue_rt_handler while replacing
input routing. Establish supported primary-driver ownership before asserting MPG
manual-tool behavior; no forced private state or artificial failure registered.
No new whole-repository coverage or hosted result; batch19 remains delivered
baseline. Accumulate the next substantial group before cumulative gate/push.

---

# Local MPG callback checkpoint - 2026-10-24 (next combined batch)

Goal active. Seven additional public callback cases pass focused Windows Clang
ASan/UBSan0.47s and strict classification:7 clean, zero known/failures/skips.
Delay-time polling chains the existing hook and performs ACK/retry/retirement;
plain/framed realtime callback replacement, removal and restoration control actual
incoming bytes and public enqueue semantics; missing consumers drop/count bytes
without filling RX. RX mute leaves the transport decoder running in both modes,
while realtime filtering controls what reaches the captured parser stream.
Public byte writes preserve output order and framed ACK sequencing.

MPG now36 registered cases. No shared fixture, production, sanitizer allowance or
assertion expectation change. Not yet cumulative validation, coverage measurement
or delivery; batch19 below remains the delivered baseline. Keep accumulating.
Actual CORE stream registration/mode switching/tool-ACK remains a distinct next
integration group: source review confirms stream.c owns proxy copies, passive
realtime filtering, mode selection and suspend backup/restore. Existing capture
fixture must not be called proof of those CORE behaviors. Delay/time/stream/task
callbacks remain explicit simulations.

---

# Latest component checkpoint - 2026-10-24 (batch19)

Goal active. Combined23 new public behavior cases: MPG8, FlexGPIO8 and SienciRGB7.
One complete Windows Clang ASan/UBSan gate:42 compatible suites,654 cases =599
clean +55 documented known results, zero unexpected failures/skips. Existing51
correct expected assertion regressions and4 diagnostic-only results remain;3
assertion cases also have exact diagnostics, counted once. No assertion weakening,
new known failures, diagnostic allowance, production edits or CORE changes.
Strict classifier ran for every suite. Unchanged84 reporting helpers were not
rerun (last full pass batch17); unchanged workflows need no new actionlint run.
Whitespace passes. Source locks API-match candidate/CORE SHAs and clean originals.

Fresh local LLVM configured-source coverage:
- MPG original .c423/468 lines90.4%,160/234 branches68.4%,43/48 functions;
  public wire header25/25 lines,10/10 branches. Adds19 exercised lines.
- FlexGPIO269/272 lines98.9%,126/150 branches84.0%,21/21 functions. Adds12 lines.
- Sienci legacy200/200 lines100%,118/125 branches94.4%; advanced345/357 lines96.6%,
  176/186 branches94.6%; all49 functions exercised. Combined545/557 lines97.8%,
  294/311 branches94.5%. Adds12 lines. All three add43 exercised lines; fresh
  counter paths max226 characters. Not whole repositories or controller coverage.

MPG settings changes retain queued output, enforce runtime ACK/attempt/payload
limits, persist/restore defaults, keep transport pending through soft reset, and
separate discarded output from fresh acknowledgements. Both plain/framed modes
run byte-only UART fallback. FlexGPIO covers each input/output value callback in
three-/six-axis builds, configuration-send alarm and read-failure edge recovery.
RGB covers absent optional hooks/driver callbacks, offboard green/off/automatic,
and stopping/resuming E-stop pulses via overrides. In active animation mode,
offboard changes render on the next scheduled frame; the fixture now waits for
that real callback before asserting the unchanged exact requested colors.

Pinned COREb01f481072edecac33d5e40c25869359a5b3fa1f;
MPG503b422d0aa92c4d2b6a190e92ce25344bcc629e;
Flexbc8dab40162b49718179bffe973c4533fc73436f;
RGBdf3409058f8bb9c202f560e562bb2671a0829561.
Evidence/locks are ignored in build-evidence. Keep PR29 draft/unmerged; hosted
workflow installation, controller integration and hardware validation remain.
See COMPONENT_TODO for remaining executable workflows and compatibility gaps.

---

# Local FlexGPIO authoring checkpoint - 2026-10-24 (next combined batch)

Goal active. Eight additional cases (four behaviors in three-/six-axis builds)
pass focused Windows Clang ASan/UBSan0.45s and strict classification:8 clean,
zero known/failures/skips. Saved public descriptors read each input after walking
physical snapshots and each output after nonzero float/zero commands; expected
wire masks include every spindle/coolant/motor-disable/output mapping. Initial
configuration-send failure raises the expander alarm while the input refresh still
runs. A failed input read preserves the last snapshot and emits no false edge;
subsequent successful IRQ refresh delivers exactly the missing change. No source
or shared fixture edits, sanitizer allowances or assertion changes.

FlexGPIO now25 registered cases. MPG29 and these new cases are local authoring
work, pending a substantial combined full gate and delivery; delivered baseline
remains batch18. Existing FlexGPIO callback diagnostics and two correct expected
assertion regressions remain untouched. Actual CORE ioports aggregation/remapping,
no-IRQ mode, target builds and physical timing remain unverified.

---

# Local authoring checkpoint - 2026-10-24 (next combined batch)

Goal active. Eight additional MPG transport cases; complete affected suite29/29
passes Windows Clang ASan/UBSan in1.71s with strict classification:29 clean,
zero known/failures/skips. Shared fixture adds only byte-only UART capability;
plain/framed fallback both validate original output. Registered setting changes
preserve queued/in-flight output and apply a500ms acknowledgement floor;
transport changes stay pending through soft reset and apply after persisted
settings reload; output discard separates sequence numbers so stale ACKs cannot
retire fresh output. Restore returns exact default settings/status and persists;
runtime payload limit preserves ordered chunks and runtime attempt limit bounds
retransmission without restarting the healthy link. No production source edits.

This is affected-suite authoring validation, not a new cumulative gate, coverage
measurement or hosted result; batch18 below remains delivered baseline. Keep
accumulating before full validation/push. Original candidate503b422d0aa92c4d2b6a190e92ce25344bcc629e
and COREb01f481072edecac33d5e40c25869359a5b3fa1f checkouts verified clean.
Legacy driver review confirms original CORE070f80 commit exists locally, but no
legacy runtime suite or SDK compatibility result is claimed. Never silently
substitute legacy CORE. Actual MPG selection/tool-ACK/controller and physical
transport behavior still require integration checks.

---

# Latest component checkpoint - 2026-10-24 (batch18)

Goal remains active. Delivered the accumulated WebUI13 authoring cases together
with15 new MSP432P401R primary UART cases, rather than a standalone small WebUI
checkpoint. Separate Plugin/Driver tests choices lock original candidate/CORE/SDK
sources. No production edits, source guard replacements, concurrent CORE changes
or merges.

One cumulative Windows Clang ASan/UBSan gate:42 compatible suites,631 cases =
576 clean +55 documented known results, zero unexpected failures/skips. Known
results comprise51 correct assertion regressions +4 passed-assertion diagnostic
cases;3 assertion cases also have exact existing diagnostics, counted once. New
MSP regression requires RX mute to preserve pending TX interrupts/output. No new
sanitizer diagnostic allowance. Targeted source-plan helper passes0.027s; actionlint
and whitespace pass. Unchanged reporting helpers were not rerun; last full84 pass
is batch17 below. Strict per-suite classification ran for this complete gate.

Fresh local LLVM selected-file/configuration coverage: MSP primary serial108/108
lines100%,37/41 branches90.2%,16/16 functions. WebUI args38/38 lines100%,41/44
branches93.2%,3/3 functions; embedded provider3/3 lines100%,1/1 function. Adds149
exercised executable lines. Fresh counter paths max228 characters; strict profiling
checks pass. No secondary UART or HTTP backend coverage inferred from percentages.

MSP original driver/board/TI device/CMSIS headers compile. Real CMSIS NVIC functions
execute against host-owned mapped registers; exactly two CPU interrupt intrinsic
macros are rebound after normal original header inclusion to observable host calls.
No source guard or legacy type is replaced. Real CORE stream registration/claim/
close, connection and tool-ACK suspend backup/restore execute. This does not prove
CPU interrupt scheduling, target SDK linking or physical UART timing. Secondary
status-table guard remains source-review-only; never force a memory failure.
WebUI uses actual CORE VFS with three asset configurations and normal argument
helpers; server/login/v2/v3/upload/lwIP/browser/controller work remains untested.

Pinned CORE b01f481072edecac33d5e40c25869359a5b3fa1f;
MSP432P1fa8bc31d8e8669d4d569e768154a0532ec5311e;
TI/CMSIS header distribution energia/msp432-core7c9a3689dc4dc3c9a7d00fa6cb51c4ed5b260afb;
WebUI3712523bc98f0bce343b56e03bdf881cc7fd4aa0.
All API-matched local original checkouts clean. Not a latest official SDK claim.
Source locks/evidence ignored in build-evidence. PR29 stays draft/unmerged. Hosted
default-branch workflow installation and physical target checks remain outstanding.
Remaining legacy driver source-review details and next gaps are in COMPONENT_TODO.

---

# Latest component checkpoint - 2026-10-24 (batch17)

Goal remains active. Added39 cases: ATCi18 and MPG transport21. New separate
Plugin tests choices lock candidate/CORE revisions; ATCi defaults main and MPG
master. No production source or concurrent CORE changes, no merge. Public hooks,
registered settings and source-supported configurations only; no private test seams.

One cumulative Windows Clang ASan/UBSan gate:40 compatible suites,603 cases =
549 clean +54 documented known results, zero unexpected failures/skips. Known
results comprise50 correct assertion regressions +4 passed-assertion diagnostic
cases;3 assertion cases also have exact existing diagnostics, counted once.
New correct ATCi M960 disable assertion reproduces consumed-word execution defect.
MPG21 cases clean. No new sanitizer expectation/allowance. All84 reporting helpers
pass14.056s; actionlint and whitespace pass.

Fresh local LLVM selected-file coverage: ATCi292/305 lines95.7%,156/193 branches
80.8%,20/20 functions. MPG .c404/468 lines86.3%,146/234 branches62.4%,41/48
functions; public .h25/25 lines100%,10/10 branches100%,3/3 functions. MPG combined
429/493 lines87%,156/244 branches63.9%. Adds721 exercised executable lines.
Fresh counter paths max224 characters, strict profiling checks pass. Remaining
source/configuration/integration gaps stay explicit in TODO and per-suite guides.

ATCi uses logical host GPIO/planner/NVS callbacks, not actual LongBoard pin maps
or complete native motion safety. Geometry assertions retain four clipping sides,
other-axis preservation and boundary behavior; initial unsupported exact chained-
callback count removed, unrestricted chaining independently controlled. MPG uses
captured stream registration and active byte consumer, not CORE MPG mode switching,
broadcast ownership or tool-ACK suspend. Valid peer frames/retries only.

Pinned CORE b01f481072edecac33d5e40c25869359a5b3fa1f;
ATCi671f145530ec8ec9f5828897477dc0192593b3d8;
MPG503b422d0aa92c4d2b6a190e92ce25344bcc629e.
API-matched local source/CORE HEADs clean. PicoHAL babac83b030fdc053b66f711e82f92b6fdfcc455
fails current-CORE syntax compilation on removed probe-fixture APIs and changed
probe-completed argument. No source aliases, runtime suite or compatibility
fallback registered. Source locks/evidence ignored in build-evidence. PR29 stays
draft/unmerged; default-branch hosted workflow installation and physical checks
remain outstanding. Existing564-case delivered checkpoint below is preserved.

---

# Latest component checkpoint - 2026-10-24 (batch16)

Goal remains active. Added41 cases: Sienci RGB24 (legacy2 and advanced3 modes),
FlexGPIO17 (three-axis behaviors and six-axis registration). New Plugin tests
choices source-lock candidate/CORE separately. Corrected both component workflow
run names to suite default instead of assuming master; Sienci defaults SLB32_DEV.
No production source changes, concurrent CORE edits or merges.

One cumulative Windows Clang ASan/UBSan gate:38 compatible suites,564 cases =
511 clean +53 documented known results, zero unexpected failures/skips. Known
results comprise49 correct assertion regressions +4 passed-assertion diagnostic
cases;3 assertion cases also have exact diagnostics, counted once. New assertions
retain legacy delayed tool color, FlexGPIO IRQ-disable result and unsupported
pull-mode acceptance. Four new exact test/file/line/function/type expectations
cover original FlexGPIO config callbacks through CORE's GNU transparent-union API;
this records the Clang signature diagnostic separately from functional defects.
No sanitizer disabled; unknown/missing diagnostics fail strict reporting. Actual
mixed assertion/diagnostic summary verified. All84 helpers pass17.106s; actionlint
and whitespace pass after workflow label correction.

Fresh local LLVM selected-file coverage: Sienci rgb.c194/200 lines97%,104/125
branches83.2%,15/15 functions; rgbv2.c339/357 lines95%,163/186 branches87.6%,
34/34 functions. Combined533/557 lines,267/311 branches. FlexGPIO257/272 lines
94.5%,123/150 branches82%,19/21 functions. Adds790 exercised executable lines.
Fresh counter paths max212 characters, strict profiling checks pass. No full
controller/parser/CORE task scheduling/port aggregation or hardware claim.

Pinned CORE b01f481072edecac33d5e40c25869359a5b3fa1f;
Sienci RGB df3409058f8bb9c202f560e562bb2671a0829561;
FlexGPIO bc8dab40162b49718179bffe973c4533fc73436f.
API-matched local source/CORE HEADs clean. Datron RGB672ebd8beeed746b5c668be18b4e4c48b6c14883
fails unchanged-source syntax compilation due private static bit_count versus
CORE declaration; ffsl is additionally undeclared on Windows. No source aliases,
header bypasses or compatibility fallback; no runtime choice registered for it.
Remaining scope in TODO/per-suite guides; evidence and source locks ignored in
build-evidence. PR29 stays draft/unmerged. Hosted workflow installation on default
branch and physical target checks remain outstanding.

---

# Latest component checkpoint - 2026-10-24 (batch15)

Goal remains active. Added35 cases: TM4C123 EEPROM12/UART012 and standalone TI
shared EEPROM11. Three new Driver tests choices source-lock original driver/
shared code, CORE and a declared TivaWare vendor-header mirror. Actual driver.h,
tiva.h and board headers compile unchanged. CORE CRC and full stream support
execute; hardware calls are explicit bounded EEPROM and UART/IRQ simulations.
No production edits, no concurrent CORE checkout changes, no merges.

One cumulative Windows Clang ASan/UBSan gate:36 compatible suites,523 cases =
476 clean +47 documented known results, zero unexpected failures/skips. Known
results now46 correct expected assertion regressions +1 fan-only diagnostic;
two existing SAM assertion cases also retain exact diagnostics, counted once.
Added12 correct assertion regressions: CRC8 read location, shared checksum layout/
read location, ignored hardware/allocation errors in both EEPROM modules, and
full RX ring dropping realtime dispatch. No new sanitizer allowance. All84
reporting helpers pass16.302s; actionlint and whitespace pass.

Fresh local LLVM selected-file coverage: TM4C123 EEPROM49/51 lines96.1%,17/20
branches85%,7/7 functions; shared EEPROM49/51 lines96.1%,17/20 branches85%,7/7
functions; TM4C123 UART0112/112 lines100%,44/48 branches91.7%,14/14 functions.
Adds210 exercised executable lines. Fresh counter paths max227 characters;
strict profiling checks pass. Missing EEPROM direct-transfer branches cannot be
entered by valid alignment: alignend is always1..4. Retained without exclusions.

Pinned CORE b01f481072edecac33d5e40c25869359a5b3fa1f;
TM4C12314fdf8de2126316c14d88656f3a19337800ad1c1;
TI shared6adcc848946fe69075f6ed062afa31f11c5a4c97;
TivaWare mirror c23bf8ba7a82b20421aa04d4df3f77501c5883ea(yuvadm/tiva-c).
API-matched upstream/CORE/SDK HEADs clean. Shared is a standalone candidate;
archived TM4C1294 parent pins a different shared source3e7873 and remains unbuilt.
No latest-official-SDK, full target-link, timing/endurance or physical-board claim.
Evidence/source locks in ignored build-evidence; remaining scope in TODO and
per-suite guides. PR29 remains draft/unmerged; hosted component workflow default-
branch installation remains separate from these local results.

---

# Latest component checkpoint - 2026-10-24 (batch14)

Goal remains active; no production sources or concurrent CORE edits, no merges.
Added34 cases:21 Virtual Inputs and13 Homing Acceleration. Separate Plugin tests
choices resolve candidate and CORE independently into immutable source locks.
Topology-independent Virtual Inputs cases run once; only sensor behavior varies
across shared/separate registration. Original CORE probe.c and formatting execute
with public registration/select/configure/IRQ boundaries and simulated pins.
Homing cases capture public per-axis settings/override requests, including
restoration, failures, persistence and rotary units; real settings.c backup and
planner/stepper homing are not executed by that suite.

One cumulative Windows Clang ASan/UBSan gate:33 compatible suites,488 cases =
453 clean +35 documented known results, zero unexpected failures/skips. Same34
correct expected assertion regressions plus1 fan-only diagnostic; two existing
SAM assertion cases also have exact callback diagnostics, counted once. All34
new cases clean; no new exception/diagnostic allowance. All84 reporting helpers
pass16.345s; actionlint and whitespace pass.

Fresh local LLVM selected-file coverage: Virtual Inputs146/146 lines100%,66/71
branches93.0%,17/17 functions; Homing Acceleration101/101 lines100%,43/44
branches97.7%,14/14 functions. Adds247 exercised executable lines. Fresh counter
paths max226 characters; strict profiling checks pass. These are selected host
configurations, not complete plugin/controller or hardware coverage.

Pinned CORE b01f481072edecac33d5e40c25869359a5b3fa1f;
Virtual Inputs e943e0c5da8a70ac9cfa91234bfa0a35a388c5f6;
Homing Acceleration a06b7cd6095a40478dde5bb1b44323d0e10373c2.
API-matched local source/CORE HEADs clean. Panel09c90184288a09d7357fd994c395911dec38683f
fails unchanged-source syntax checks in CAN and README-required Modbus64 configs:
obsolete one-argument system_execute_line at707 versus CORE two-argument API.
No panel runtime suite/Actions choice or source alias; evidence in build-evidence.
Remaining TI families fetched/read for next batch; details and ownership concerns
in COMPONENT_TODO. PR29 stays draft/unmerged. Hosted component workflows still
need default-branch installation; no Linux/GCC/physical-board success claimed.

---

# Latest component checkpoint - 2026-10-24 (batch13)

Goal remains active. Added50 unchanged-source third-party plugin cases in separate
behavior files: AUXP7, Interlock13, PneumaSeal15 and Thermistor15. Added four
Plugin tests workflow choices with immutable candidate/CORE plans. Default branches
are main, not master. No production source or concurrent CORE edits, no merge.

One cumulative Windows Clang ASan/UBSan gate:31 compatible suites,454 cases =
419 clean +35 documented known results, zero unexpected failures/skips. This is
34 correct expected assertion regressions plus1 fan-only diagnostic; two SAM
assertion cases also retain exact callback diagnostics without double counting.
All50 new cases clean, no new exception/diagnostic allowance. All84 CI/reporting
helpers pass15.879s; actionlint and whitespace checks pass. Clang23's original
Interlock default-const-field initialization warning stays visible/nonfatal only
for that source; fixtures remain strict.

Fresh local LLVM selected-file coverage:
- AUXP45/45 lines100%,24/24 branches100%,5/5 functions.
- Interlock173/185 lines93.5%,67/84 branches79.8%,19/23 functions.
- PneumaSeal128/141 lines90.8%,43/52 branches82.7%,20/26 functions.
- Thermistor133/139 lines95.7%,68/74 branches91.9%,10/12 functions.
These add479 exercised lines across510 selected executable lines. Fresh counter
paths max215 characters; strict profiling checks pass. No full-plugin, complete
settings parser, physical sensor/solenoid or actual emergency-stop timing claim.
Port/settings/NVS/task/alarm boundaries are explicit host simulations; original
CORE formatting is linked where used. No private plugin state is modified.

Pinned CORE remains b01f481072edecac33d5e40c25869359a5b3fa1f.
AUXP ded4a654f9ad17eec449431a51310b44f6da86c9;
Interlock5893ea35645c334ec96333ccd0519eac03128ee6;
PneumaSeal3127ab8c15982569d7e89822a9e1095cdce89cbb;
Thermistor4fae94b9b553604f2f41222bbc04fa45669c2bdf.
All local upstream/CORE HEADs API-matched and clean. Source locks, classification,
coverage and helper evidence are ignored under build-evidence. Remaining settings
getters/parser integration and lifecycle contract questions are in COMPONENT_TODO.
PR29 remains draft/unmerged. Hosted component workflows still require default-
branch installation; no hosted Linux/GCC or hardware result is claimed.

---

# Latest component checkpoint - 2026-10-24 (batch12)

Goal remains active across48 inventoried implementations. Added62 driver cases:
27 Teensy PWM across4.0/4.1/MicroMod and35 SAM3X8E serial across UART/USART1.
Original production sources, actual board/device headers and pinned SDK register
layouts compile unchanged; host memory, clock and IRQ callbacks model hardware
boundaries. No production or concurrent CORE checkout changes, no merges.

One cumulative Windows Clang ASan/UBSan gate covers27 compatible suites:
404 cases =369 clean +34 correct expected assertion regressions +1 fan-only
passed-assertion diagnostic. Two of the34 assertion cases also reproduce exact
SAM callback type diagnostics; they are counted once, with explicit mixed labels.
Zero unexpected failures/skips. All84 reporting helpers pass9.514s; actionlint
and whitespace pass. Two new narrowly scoped SAM diagnostic expectations retain
the actual callback defect; no blanket sanitizer suppression.

SAM regressions cover RX disable writing IER instead of IDR, secondary realtime
routing to the primary handler, and USART1 TX pin peripheral selection. The
secondary callback also has a char versus uint8_t signature mismatch. Correct
assertions and repair/removal guides remain in the suite KNOWN_BUGS.md. Reporting
now distinguishes mixed assertion/diagnostic cases without double counting or
claiming their assertions passed.

Fresh local LLVM selected-file coverage: Teensy pwm.c88/88 lines100%,31/37
branches83.8%,6/6 functions; SAM serial.c274/278 lines98.6%,100/108 branches92.6%,
38/39 functions. Fresh counter paths max210 characters; strict profiling checks
pass. These are selected-file host results, not whole-driver/board coverage.

Pinned CORE b01f481072edecac33d5e40c25869359a5b3fa1f;
iMXRT1062 d1f8d1ed904242ee08b0a5583e78f490afd9ae93;
SAM3X8E2321092b02cbbdecf2eba2b168a74b085e573418;
Teensy SDK7f107ee0a309f3813ed13f0d8f615497eca2ee49;
Arduino SAM SDK790ff2c852bf159787a9966bddee4d9f55352d15.
Source locks and local evidence live in ignored build-evidence. Separate Driver
tests choices added for both suites. PR29 stays draft/unmerged; fork default
branch still registers only Core tests and Reusable host tests. No hosted GCC,
Linux, full ARM SDK or physical-board success is claimed. Remaining public APIs,
other modules and SAMD21 legacy support boundary are in COMPONENT_TODO.md.

---

# Latest component checkpoint - 2026-10-24 (batch11)

All-plugin/driver/CORE goal remains active across48 inventoried implementations.
No production sources or concurrent CORE work changed. Existing PR29 verified
OPEN/draft/unmerged at prior pushed head20fa750. Fork still registers only Core
tests and Reusable host tests; no hosted component success or merge is claimed.

Added37 cases:18 H7 (nine each H743/H723),9 F1 and10 F3. All three have separate
Driver tests choices and immutable host_bits32 source plans. One cumulative
Windows Clang ASan/UBSan gate covers all25 compatible suites:342 cases =314 clean
+27 correct known assertion regressions +1 previously scoped fan diagnostic.
Zero unexpected failures/skips. All83 CI/reporting helpers pass9.325s; actionlint
and whitespace pass. No new sanitizer allowance. New STM32 sources/fixtures stay
-Werror; native LPC fixed-address cast warnings remain visible under one narrow
original-source warning rule, and its fixture remains strict.

H7 compiles original Src/flash.c and original Inc/flash.h in actual source-supported
H743 dual-bank/H723 single-bank configurations. Inspected CMSIS/HAL headers define
8 sectors and32-byte flash words for both; BANK_2 only applies to H743. The host
HAL uses the real32-bit DataAddress third argument. Cases cover bank/sector
selection, aligned and exact-length36-byte source writes with zero-padded tail,
readback/unchanged handling, unlock/erase/first/second word failures and retry.
No invented16-byte write configuration is compiled despite the source comment.

F1 uses the shared halfword fixture with its actual page erase layout and linker
page-count/address symbols. Its unlock status is unchecked; locked erase errors
are returned by the HAL model rather than becoming fixture assertions. Erase
retry/failure, both halfword failures, recovery and copy/read controls pass.
Existing F4/F7 layout/lock checks remain intact and pass the cumulative gate.

F3 keeps FLASH_TARGET calculation unchanged. Dedicated test-process mappings
supply actual F303xC flash base0x08000000 and size register0x1FFFF7CC with2KB pages.
Separate128/256KB cases validate end-minus4KB target selection; full2KB-page,
read/unchanged, unlock/erase/program failure and retry controls execute. One new
correct first-halfword failure assertion reproduces its F7-like overwritten
status defect. Exact WILL_FAIL/known_bug plus dated guidance retain the proper
false result/immediate-stop contract without changing firmware.

Initial cumulative execution caught an intermittent address collision in the old
32-bit LPC fixture. Its original module does not convert RAM pointers to32-bit
integers, so that host restriction was unnecessary. It now uses native64-bit RAM
pointers with unchanged32-bit physical flash addresses and normal ASLR. Mappings
still refuse occupied addresses. All10 affected cases pass three repetitions,
then cumulative strict classification and fresh coverage. Failed evidence is kept
as lpc-batch11-address-collision.xml. Earlier passing suites were retained after
this isolated repair; they were not repeatedly rerun. LPC CORE2048 allocation/
4096-copy compatibility remains unresolved and is not masked by padded tests.

Fresh LOCAL LLVM compiled-file/configuration coverage, strict profiling checks pass:

| Suite / original selected file | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| driver_stm32h7_flash / Src/flash.c | 21/21 (100%) | 12/12 (100%) |
| driver_stm32f1_flash / Src/flash.c | 20/20 (100%) | 10/10 (100%) |
| driver_stm32f3_flash / Src/flash.c | 20/20 (100%) | 6/6 (100%) |
| driver_lpc176x_flash / src/flash.c, native host repair | 14/14 (100%) | 4/4 (100%) |

Maximum counter paths219/220/214/213 in fresh short builds. These are selected
storage-module results including retained regressions, not whole-driver/SDK/board
coverage. No Linux/GCC execution, physical flash/cache/IRQ timing or ARM firmware
build is claimed. Default-branch workflow installation remains unavailable.

GitHub-resolved locks match clean unchanged sources:
H7bfe5d4f6ec271cc9929336244c3b1c8e55d1d040 (dresco/STM32H7xx),
F1c22362352f6abeea94897bb0346ae8042cdf3210,
F39a40877b87b6fffbb475f753f0e12cc6c5126770,
COREb01f481072edecac33d5e40c25869359a5b3fa1f.
LPC source remains ea6e9f78fa349e86fbd58a203760b614f513684a; its updated native
source lock is part of this checkpoint. Ignored build-evidence/*batch11* contains
classification, locks, coverage XML/JSON/HTML and logs. Local short builds:
build-sh7-asan/build-sf1-asan/build-sf3-asan; PATH needs LLVM bin plus its
i686-w64-mingw32/bin for STM32 ASan DLLs. LPC now uses the normal native LLVM bin.

Continue the remaining driver families and untested plugin modules/configurations.
No full-goal completion claim, CORE edits or merges.

---

# Previous batch10 checkpoint - 2026-10-24

All-plugin/driver/CORE goal remains active across48 inventoried implementations.
No production sources or concurrent CORE work changed. Continue PR29, freshly
OPEN/draft/unmerged. Fork still registers only Core tests and Reusable host tests;
component dispatch/32-bit runtime installation awaits default-branch workflow
installation. No hosted component run or merge is claimed.

Added27 driver cases:9 STM32F4 flash,8 STM32F7 flash and10 LPC176x IAP storage.
All three have separate Driver tests choices and immutable source plans with
host_bits32. One cumulative Windows Clang ASan/UBSan gate covers all22 compatible
suites:305 cases =278 clean +26 correct known assertion regressions +1 previously
scoped fan callback diagnostic. Zero unexpected failures/skips. All83 CI/reporting
helpers pass17.915s; actionlint/whitespace checks pass. No new sanitizer allowance.
Existing plugin/CORE source warning policies remain; these new storage sources
and their fixtures compile with -Werror.

STM32 cases compile original flash.c with -m32, a pointer-width assertion and
linker-style region/sector symbols. No original pointer type or source is patched.
Shared HAL fixture models the distinct F4/F7 erase structures, unlock/erase/
halfword program/lock, byte output and failure state. Cases cover read/copy,
unchanged suppression, unlock failure, F4 erase retry, exhausted erase failure,
first/second halfword failure, recovery and selected word-aligned buffer sizes.
CORE nvs_buffer_init253 explicitly requires word alignment. These helper tests
are not complete CORE settings boot/integration or real STM32 HAL execution.

F7 first-halfword write failure is a confirmed source defect: its second call
unconditionally overwrites failure status with success, continuing and returning
true despite missing data. One exact program_first_failure WILL_FAIL/known_bug
retains the correct false assertion, with dated source/removal guidance. F4's
corresponding failure path and F7's second-halfword failure controls pass.

LPC tests compile original src/flash.c and map its fixed0x78000 region inside the
dedicated test process. Windows VirtualAlloc refuses an occupied address; Linux
MAP_FIXED_NOREPLACE is authored but not executed here. Simulated IAP callbacks
validate sector29, preparation/blank-state requirements, writes and IRQ restoration.
Cases cover erased reads,1024/4096 copy/readback, unchanged suppression, failure
at either preparation/erase/copy stage and retry. The2048 configured-size case
supplies4096 source bytes because original code copies4096 except for size1024.
It does not establish safety for normal CORE2048 allocation; unpadded overread is
not reproduced. Earlier IAP errors are overwritten in source; provider state
preserves failed prerequisites so final copy reports failure. Immediate abort,
allocation/copy-size compatibility and full CORE integration remain TODO.

Reusable jobs now install gcc-multilib/libclang-rt-dev only for source-locked32-bit
plans; existing plans default64. Host width is validated before source resolution.
Two new helpers verify default/accepted/rejected widths; component plan checks
also validate width metadata. The target Linux STM32 flags disable PIE to retain
absolute sector-symbol semantics. No Linux/GCC/multilib execution is claimed until
actual hosted runs exist. Source and fixture SDK boundaries remain simulated.

Fresh LOCAL LLVM compiled-file/configuration coverage, strict profiling checks pass:

| Suite / original selected file | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| driver_stm32f4_flash / Src/flash.c | 20/20 (100%) | 12/12 (100%) |
| driver_stm32f7_flash / Src/flash.c | 19/19 (100%) | 8/8 (100%) |
| driver_lpc176x_flash / src/flash.c | 14/14 (100%) | 4/4 (100%) |

Maximum counter paths220/223/213 in fresh short builds. These numbers cover only
three storage modules, including the retained F7 regression; no full-driver,
board, cache/IRQ timing, ARM firmware or real SDK validation is claimed.

GitHub-resolved locks match unchanged clean original sources:
STM32F4a6318ac92f079f49fab91687530f832997396edc,
STM32F785e6e800b16fb1a46bc00b87b7015489b9d3ec93,
LPC176x ea6e9f78fa349e86fbd58a203760b614f513684a,
COREb01f481072edecac33d5e40c25869359a5b3fa1f.
Ignored build-evidence/*batch10* contains immutable source locks, classification,
coverage XML/JSON/HTML and logs. Local short builds are build-sf4-asan,
build-sf7-asan and build-lpc-asan; PATH needs LLVM bin plus its i686-w64-mingw32/bin
for32-bit ASan DLLs. Historical compatibility limits remain unchanged.

Continue remaining driver families and plugin modules/configurations with public
interfaces. Do not narrow the full goal to these storage helpers, modify CORE or
merge PRs. The requested full supported coverage is not complete.

---

# Previous batch9 checkpoint - 2026-10-24

All-plugin/driver/CORE goal remains active across48 inventoried implementations.
No production sources or concurrent CORE work changed. Continue existing PR29,
freshly verified OPEN/draft/unmerged. Fork still registers only Core tests and
Reusable host tests. No hosted component run or merge is claimed.

Added34 registered cases:21 Bluetooth HC-05 and13 embroidery reader cases. Both
suites are now selectable in Plugin tests with their own immutable source plans.
One cumulative Windows Clang ASan/UBSan gate covers all19 compatible suites:
278 cases =252 clean +25 correct known assertion regressions +1 previously scoped
fan callback diagnostic. Zero unexpected failures/skips. All81 reporting/helper
checks pass17.050s; actionlint/whitespace checks pass. No new sanitizer allowance.
Source warnings remain visible under documented rules; fixtures retain -Werror.

Bluetooth compiles original hc_05.c with actual CORE stream registry/selection,
I/O registration and EEPROM/CRC. Simulated UART module replies, ticks and STATE
IRQs exercise all four AT command stages, failure/timeout, custom name, baud and
handler restoration, manual enable/disable, missing dependencies, port settings,
claimed-pin rejection, reports and fresh-process persisted auto-configuration.
Actual CORE selects/restores streams and sends the welcome message; no stream
switch stub is used. No radio/hardware or full protocol execution is claimed.

Two correct regressions reproduce original source defects and retain exact
WILL_FAIL/known_bug labels plus dated source/removal guidance in KNOWN_BUGS.md:
- Factory default selects highest free STATE pin but load rejects it using
  >= port_max, although CORE port_max is the highest valid index. No setup runs.
  Other workflow controls explicitly select the valid lower pin through settings.
- An enabled, boot-high STATE input selects Bluetooth and sends welcome but its
  connection predicate stays false; setup updates only a local variable.

Reserved options from erased storage are masked to the defined enable bit in
fixture getter checks; their broader Format_Bool contract remains a TODO. Shared
MPG mode and IRQ-provider failure notification remain untested, not excluded.

Embroidery compiles original tajima.c/brother.c readers with actual CORE VFS and
embedded backend. Valid DST/PES fixtures cover metadata/counts/dimensions/palette,
small/large signed movement, jump/trim/stop/color/end and format fallback/rewind.
No replacement decoder or private state forcing. Results omit the uncompiled
embroidery.c job coordinator: rendering, planner/needle synchronization, settings,
SD hardware and physical stitch timing remain. Mixed-axis flag precedence and
sequin lifetime need contract review before assertions.

Fresh LOCAL LLVM compiled-file/configuration coverage, strict profiling checks pass:

| Suite | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| plugin_bluetooth / HC-05 serial mode | 122/124 (98.39%) | 56/66 (84.85%) |
| plugin_embroidery_readers / two readers | 168/177 (94.92%) | 96/108 (88.89%) |

Reader detail: Brother62/63 lines and26/28 branches; Tajima106/114 and70/80.
Both fresh short builds have maximum counter path212. No source exclusions or
whole-plugin/catalogue claim. No hosted/GCC/firmware/board validation is claimed.

GitHub-resolved locks match clean unchanged sources:
Bluetooth3fc40665af6d49250f09fec665ec267a988ee148,
embroidery9a112c3c2509563aa5c745d5773aba5a62046d7c,
COREb01f481072edecac33d5e40c25869359a5b3fa1f,
EEPROM0c278db74edc38303b9d86583a7d51a1ec1be51e.
Ignored build-evidence/*batch9* contains source locks, strict classifications,
coverage XML/JSON/HTML and validation logs. Prior source compatibility limits and
known assertions remain unchanged. Full goal is not complete.

Next: remaining supported modules/configurations and additional driver families.
STM32F4 sourcea6318ac92f079f49fab91687530f832997396edc was fetched/read only;
flash.c uses linker-address symbols and a32-bit target address contract. Establish
an appropriate target/linker fixture before runtime assertions; no driver result
or SDK/board build is inferred from this source review.

---

# Previous batch8 checkpoint - 2026-10-24

Goal remains active across48 inventoried implementation repositories. No production
sources or concurrent CORE work changed. Existing PR29 verified OPEN/draft/unmerged.
Fork still registers only Core tests and Reusable host tests: component workflows
await default-branch installation. No merge or hosted component success claimed.

Added20 registered cases:9 Trinamic runtime cases plus7 plasma runtime cases and
4 fresh-process EEPROM setup/cleanup cases. One cumulative Windows Clang ASan/UBSan
gate covers all17 current-compatible suites:244 cases =220 clean +23 correct known
assertion regressions +1 previously scoped fan callback diagnostic. Zero unexpected
failures/skips. Both expanded suites pass23/23. All81 reporting/helper checks pass
9.554s; actionlint and whitespace checks pass. Source warnings remain visible under
documented rules; host fixtures remain -Werror. No new exception/diagnostic waiver.
Formatting reordered two dependent headers; restoring the host include first fixed
those fixture builds. Completed unaffected suite results were retained, not rerun.

Trinamic enables actual status polling and dynamic current in nine targets while
keeping the existing default targets. Registered task/stepper/limit callbacks cover
hold/block/idle current, quiet polls, persistent/recovered over-temperature reports,
moving feed-hold requests and homing seek/locate sensitivity plus IRQ routing.
Disable retains the homing-rate callback but inactive axes prevent register writes;
assert that observable behavior. The source Pending holding-state assignment is
commented out; no private state is forced. Current is configured/register behavior,
not measured electrical current; actual homing motion and stall timing remain.

Plasma saves its registered reboot-required Mode setting through actual EEPROM/CRC
then boots a fresh process into Arc-ok or Up/down mode. Actual CORE spindle registry,
I/O registration and secondary-stepper polling execute with simulated torch/pins,
clock and controller state. Cases cover successful ignition/shutdown, three failed
attempts, third-attempt success, lost-arc hold requests, positive/negative Z output,
velocity lock/recovery and reset. No private init_ok/state handler is assigned.
Mode3 does not claim cutter inputs: fixture setup now initializes physical values
without demanding those unregistered descriptions. Full CORE suspension, primary XY
motion, voltage/PID regulation, pierce/cut-height planner moves, PowerMax, expression
integration and physical timing remain. These are not board/firmware build results.

Fresh LOCAL LLVM compiled-file/configuration coverage, strict profiling checks pass:

| Suite | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| plugin_trinamic / trinamic.c | 446/1001 (44.56%) | 192/652 (29.45%) |
| plugin_plasma / THC + two importers | 457/869 (52.59%) | 222/553 (40.14%) |

Trinamic gained126 covered lines while the denominator expanded885->1001 because
polling/dynamic configurations now compile. Plasma gained194 covered lines with
unchanged denominator: THC361/764; importers remain LinuxCNC51/56 and SheetCam45/49.
Fresh short coverage builds have maximum counter paths223/225. No source exclusions,
whole-plugin/library/catalogue coverage claim or reused old counter graphs.

GitHub-resolved locks match unchanged clean source checkouts:
COREb01f481072edecac33d5e40c25869359a5b3fa1f,
motor9229617c1d8a3cc7a71fd584896500a779978b02,
plasma d2f91b5887db6550ddec0fc0229cd87ec0af1a56,
EEPROM0c278db74edc38303b9d86583a7d51a1ec1be51e,
Trinamic library9b304175318d93818c8967faadc89dd101b17e92 (explicit RP2040 gitlink pin).
Ignored build-evidence/*batch8* contains strict classifications, source locks, logs
and coverage XML/JSON/HTML. Existing source compatibility limits remain recorded.
No hosted/GCC/hardware validation is claimed. Continue remaining supported modules
and configurations; the all-plugin/driver/CORE goal is not complete.

---

# Previous batch7 checkpoint - 2026-10-24

Full all-plugin/driver/CORE goal remains active across48 implementation repos.
No production sources or concurrent CORE work changed. Isolated branch continues
existing PR29, freshly OPEN/draft/unmerged. Fork list still registers only Core
tests and Reusable host tests. No hosted component run or merge is claimed.

Added26 cases:14 Trinamic and12 plasma. One cumulative Windows Clang ASan/UBSan
gate rebuilds/rechecks all seventeen compatible suites against pinned COREb01f481:
224 cases =200 clean +23 correct known assertions +1 previously scoped fan
callback diagnostic. Zero unexpected failures/skips. All81 CI/reporting helpers
pass9.677s; actionlint/whitespace checks pass. Original source warnings remain
visible under documented rules; fixtures stay -Werror. No new sanitizer allowance.

Trinamic executes original plugin plus actual TMC2209 chip/HAL/common library
against a simulated UART register device with CRC-checked packets and real IFCNT
accounting. Cases cover3 registered motors, setup/address callbacks, current and
mode commands, current/microstep settings/rejection, communication/setup/storage
failure, recovery/status reset, fault IRQ, callback chaining and EEPROM-backed
restart in two processes. Current checks concern configured values, not measured
motor current. Host parser/settings boundaries model named axis words and their
consumption/restoration; full CORE parser execution is not claimed. An initial
fixture mistake caused NaN conversions and was corrected to the real public
parser contract before classification; no diagnostic was waived.

Plasma compiles original THC/SheetCam/LinuxCNC modules with actual CORE I/O
registration, secondary stepper, PID, VFS/embedded backend and real EEPROM/CRC.
Cases use its normal initial Off mode and do not fabricate private ready state.
Initialization failures, material validation/add/overwrite/enumeration, comments/
rejection/recovery, registered listing and report hooks pass. Both external file
formats load through actual VFS mount listeners with the read-only host backend
mounted through public APIs. I/O and plasma settings are distinct registrations
and receive separate NVS allocations. Full torch/arc/voltage/up-down motion,
PowerMax, expression integration and hardware timing remain untested. MinGW's
exported isnanf lacks a math.h declaration; the Windows-only host declaration
uses the actual runtime function, without replacement code or production aliases.

Fresh LOCAL LLVM measured compiled-file/configuration coverage:

| Suite | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| plugin_trinamic / trinamic.c | 320/885 (36.16%) | 122/570 (21.40%) |
| plugin_plasma / THC + two importers | 263/869 (30.26%) | 150/553 (27.12%) |

Plasma detail: THC167/764 lines, LinuxCNC51/56, SheetCam45/49. Remaining runtime
code stays in the denominator; no whole-plugin, library or catalogue claim.
All coverage result sets pass strict profiling-error checks; maximum counter
paths222/227. The largest remaining supported runtime regions are recorded in
COMPONENT_TODO.md rather than excluded or entered through private state.

GitHub-resolved locks match clean local sources:
motor9229617c1d8a3cc7a71fd584896500a779978b02,
plasma d2f91b5887db6550ddec0fc0229cd87ec0af1a56,
COREb01f481072edecac33d5e40c25869359a5b3fa1f,
EEPROM0c278db74edc38303b9d86583a7d51a1ec1be51e,
Trinamic-library9b304175318d93818c8967faadc89dd101b17e92. The latter is an
explicit dependency-only pin from the inspected RP2040 gitlink, not an implicit
fallback. Full immutable locks/classification/logs are in ignored build-evidence/
*batch7*, alongside per-suite coverage XML/JSON/HTML. New Plugin tests choices
await default-branch installation. No hosted/GCC/board/physical-device pass claim.

Continue supported plasma/TMC runtime and remaining catalogue/modules/configs.
The full goal is not complete.

---

# Previous batch6 checkpoint - 2026-10-24

Full all-plugin/driver/CORE goal remains active across48 inventoried repositories.
No production sources or concurrent CORE work changed. This isolated branch
continues PR29, freshly OPEN/draft/unmerged. Fork workflow list still exposes
only Core tests and Reusable host tests; no hosted component run is claimed.

Added31 cases:11 common networking,12 laser PPI and8 LightBurn cluster cases.
One cumulative Windows Clang ASan/UBSan gate rebuilds/rechecks all fifteen
current-compatible suites:198 cases =174 clean +23 correct known assertions
+1 previously scoped fan callback diagnostic. Zero unexpected failures/skips.
All81 CI/reporting helpers pass11.915s; actionlint/whitespace checks pass.
Source warnings remain visible under documented rules; fixture warnings stay
strict. No sanitizer allowances added.

Networking uses the original public event/provider/enumeration API and registered
NETIF/report hooks. Cases cover Ethernet/STA/AP notifications, unavailable provider,
enumeration/short-circuit, listening-port/status reports, one hostname, cached
stream selection across file mode, enabled service labels, MAC conversion and
idempotent init/hook chaining. Actual lwIP headers are source-locked with a local
NO_SYS IPv4 architecture/configuration boundary. No actual listeners/packets,
stack runtime, wireless or Ethernet hardware is exercised by this suite.

PPI tests compile actual CORE spindle registration/selection. Driver step/pulse/
PWM/RPM callbacks and gc_laser_ppi_enable are simulated public boundaries. Normal
spacing/width, zero RPM, enabling/disabling, check mode, reset/program-end,
zero configuration, hardware delegation and callback chaining pass. One correct
regression demonstrates ppiUpdatePWM requests pulse_on even when PWM becomes
zero. Driver callback observation does not establish physical emitted energy.

LightBurn tests execute the original decoder with simulated normal/file byte
sources and real CORE numeric helpers. Valid X/Y/negative moves divide distance,
preserve feed/power, restore initial S when required and acknowledge one input
cluster. Paired EOL, fragment reset, source changes and report chaining pass.
Default unscaled16-value configuration only; not full parser/motion or physical
LightBurn integration. Coolant/overdrive/alternate PPI and decoder modes remain.

Fresh LOCAL LLVM measured-file/configuration coverage:

| Suite / file | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| plugin_networking / networking.c | 157/165 (95.15%) | 84/106 (79.25%) |
| plugin_laser_ppi / ppi.c | 144/146 (98.63%) | 83/100 (83.00%) |
| plugin_laser_cluster / lb_clusters.c | 181/209 (86.60%) | 97/141 (68.79%) |

All coverage result sets pass strict profiling-error checks; maximum counter
paths229/198/203. Uncovered code remains in denominators. These are not whole
repository/catalogue percentages. Known defects remain despite line coverage.

GitHub-resolved source locks match clean local checkouts and master defaults:
networking0b665ee0c0be5161d5044bdf2dcdf59ad62509f8,
laser26934c6c9607e0b5ba4a711516a60d4657bf142c,
lwIPd08f4773edd0182b7910fc8f046eed82ffcd67c9,
COREb01f481072edecac33d5e40c25869359a5b3fa1f. Local immutable locks,
classification and sanitizer logs are in ignored build-evidence/*batch6*, with
per-suite coverage XML/JSON/HTML and build logs. lwIP is dependency-only and
cannot be selected as a suite. New choices are in the separate Plugin tests
workflow, awaiting default-branch installation. No hosted/GCC/hardware pass claim.

Plasma d2f91b5 and motor9229617 sources were fetched unchanged and assessed for
real registration/dependency requirements; no test suite or runtime support is
claimed for them yet. RP2040's actual Trinamic-library gitlink was identified.
Continue THC/material/Trinamic workflows and remaining modules/configurations
from COMPONENT_TODO.md. The full goal is not complete.

---

# Previous batch5 checkpoint - 2026-10-24

Goal remains active across all48 implementation repositories. No production
sources or concurrent CORE work changed. The isolated plugin-driver-tests branch
continues existing PR29, freshly confirmed OPEN/draft/unmerged. Fork workflow
listing still contains only Core tests and Reusable host tests; no hosted plugin/
driver success or merge is claimed.

Added43 cases:30 keypad cases and13 driver-storage cases. One cumulative Windows
Clang ASan/UBSan gate rebuilds/rechecks all twelve current-compatible suites:
167 cases =144 clean +22 correct known assertions +1 previously scoped fan
callback diagnostic. Zero unexpected failures/skips. All81 CI/reporting helpers
pass9.743s. Actionlint and whitespace checks pass. Keypad source warnings remain
visible under documented production-source rules; fixtures and both small driver
sources retain -Werror. No sanitizer allowances added.

Keypad cases cover I2C strobe/UART registration, fast/slow/step and diagonal jog
commands, modifiers, preview hooks, released-key suppression before foreground
processing, successful/rejected enqueue cancellation, legacy control, real CORE
override queues, settings/report callbacks, initialization failures and NVS
restart. The NVS provider is opaque CRC-backed RAM, with two-process persisted
bytes and actual CORE CRC; no private serialized plugin structure is copied.
Initial jog string expectations were corrected to CORE ftoa's trailing decimal
point; actual numeric distances/feed assertions remain exact.

Four correct regressions reproduce extended keys lost when char is signed:
I2C/UART extended control and override cases. The identical unsigned-char controls
pass. Compile modes are explicit, not inferred as universal firmware behavior.
UART failed stream opening leaves no settings registration but init returns NVS
allocation success; intended bool semantics remain TODO, not a declared defect.

RP2040 original flash.c executes against a RAM XIP mapping and simulated erase/
program/IRQ calls. Five cases verify erased reads, bytes copied, unchanged-write
avoidance, page rounding with a padded source and readback verification failure.
The host preinclude omits board driver.h setup intentionally; it does not compile
the actual Pico SDK/PIO/pins or prove timing/multicore safety. ESP32 original
main/nvs.c executes through simulated partition APIs. Eight cases verify discovery,
absent/uninitialized storage, bytes, erase/write/read failures, invalidation,
reinitialization and retry. Every erase checks all256 input values through the
original temporary realtime filter; handler restoration is observed on success
and failure. No physical flash/cache/UART timing or full-driver claim.

Fresh LOCAL LLVM coverage, selected compiled files/configurations only:

| Suite / measured file | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| plugin_keypad / keypad.c | 218/230 (94.78%) | 109/144 (75.69%) |
| driver_rp2040_flash / flash.c | 12/12 (100.00%) | 2/2 (100.00%) |
| driver_esp32_nvs / main/nvs.c | 16/16 (100.00%) | 14/14 (100.00%) |

All coverage result sets pass strict profiling-error classification. Maximum
counter paths237/203/199. Initial local keypad aggregation failed because the
two conditional keypad_init definitions occupy different lines. Re-reading the
same counters with --merge-mode-functions=separate, already used by hosted CI,
fixes reporting; no source changes, ignored errors, denominator exclusion or
redundant test run. Rejected attempt/log retained. These are not percentages for
whole drivers/catalogues. Source/configuration gaps remain in the inventory.

GitHub-resolved locks match clean source checkouts and verified master defaults:
keypad c34933091df668d009fe11ed7397a9b78c9bfd79,
RP2040 2f5bc4a06ecea3b1f78c1644623810f9b6416376,
ESP32 0b2d3e1bb7da3b0ae0e03490b71275374eb84c67,
CORE b01f481072edecac33d5e40c25869359a5b3fa1f. Local evidence is in ignored
build-evidence/*batch5* plus per-suite sanitizer/coverage logs/XML/JSON/HTML.
SDK boundary declarations are local test fixtures, not SDK version-lock claims.

The new choices are wired into separate Plugin tests / Driver tests workflows,
available after default-branch installation. No hosted/GCC/hardware pass claim.
Next: remaining catalogue families, VFD/SD/MPG gaps and other driver modules;
keep source incompatibilities and reference-only results visible below. The full
goal is not complete.

---

# Previous batch4 checkpoint - 2026-10-24

Goal remains active across all48 inventoried implementation repositories. No
production sources or concurrent CORE work changed. Isolated plugin-driver-tests
continues the existing OPEN/draft/unmerged PR29. Fresh fork API still registers
only Core tests and Reusable host tests; no hosted component success is claimed.

Added41 cases:28 GS20/MODVFD cases and13 SD streaming cases. One cumulative
Windows Clang ASan/UBSan gate rebuilds/rechecks all nine current-compatible suites:
124 cases =105 clean +18 correct assertion regressions +1 previously scoped fan
callback diagnostic. Zero unexpected failures/skips. A subsequent fixture-only
cancellation assertion verifies EXEC_MOTION_CANCEL before simulating the stop;
its affected connection-change case and strict summary pass0.11s. All81 helpers pass9.626s;
actionlint and whitespace checks pass. Original-source compiler warnings remain
visible under documented production-source rules; fixtures retain -Werror.

VFD tests use original coordinator/protocols, real CORE spindle registration,
selection, at-speed math and Modbus API dispatch. A registered RTU fixture verifies
exact requests and returns replies/rejections/exceptions. Tests cover CW/CCW/stop,
asynchronous speed updates, query throttling, measured RPM, exception thresholds
and success reset, cold-start alarm deferral, settings/report hook chaining,
missing transport/storage, down-bus recovery and custom registers/conversions.
Two-process EEPROM-backed restarts verify saved protocol settings without copying
private serialized layouts. Initial feedback equality was replaced with0.01 RPM
float tolerance; exact Modbus byte assertions remain.

SD tests use original fs_stream.c/macros.c with real CORE VFS, stream, redirect
and embedded read-only filesystem mounted at / via public VFS calls. Job byte
streaming/completion, final newline, status-error recovery, reset, tool-change
ack/suspend/resume, rejected startup, filtered/all listings, progress, realtime
input filtering, connection-change termination and external M98-style macro repeat
are observed. Parameter-local G65, expression ATC and physical SD are not claimed.
Two correct known assertions reproduce extra EOF blank lines in already terminated
job input and dumps. Unterminated job/dump controls pass. No new sanitizer waivers.

The separate original SD littlefs adapter syntax check fails against current CORE
on removed vfs_path_t (fs_littlefs.c58/64), after resolving real CORE/littlefs
headers. No source alias/fallback masks it. Streaming success does not establish
adapter or FATFS/SD hardware compatibility. Simulator reference-only results from
batch3 below remain separate and unchanged.

Fresh LOCAL LLVM coverage (only compiled original files/configurations):

| Suite | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| plugin_spindle_vfd | 288/320 (90.00%) | 81/136 (59.56%) |
| plugin_sdcard_stream | 394/591 (66.67%) | 174/378 (46.03%) |

All coverage cases pass strict result/profile-error checks; max counter paths
226/209. Unused supported paths remain counted. No catalogue-wide percentages.
Coverage includes coordinator plus GS20/MODVFD and stream/macros configurations;
other files/configurations remain in COMPONENT_INVENTORY.csv/COMPONENT_TODO.md.

GitHub-resolved locks match clean source checkouts: spindle
8a3ae47f5a218834da9c742424c3dd22c5629fdb, SD card
d0fe753d622e79a60e54e729ba83f7207276114c, CORE
b01f481072edecac33d5e40c25869359a5b3fa1f, EEPROM backend
0c278db74edc38303b9d86583a7d51a1ec1be51e. Local evidence is retained in ignored
build-evidence/*batch4* plus per-suite coverage HTML/XML/JSON and compile logs.
Both suites are selectable in the separate Plugin tests workflow after default
branch installation; no merge/hosted/hardware/GCC completion claim.

Next: remaining VFD protocols, supported SD adapter/job paths, I2C keypad and
host-testable driver helpers. The full goal is not complete.

---

# Previous batch3 checkpoint - 2026-10-24

Continuing the active all-plugin/driver/CORE goal on isolated plugin-driver-tests.
No production source edits or merges. The separate CORE chat remains untouched.
PR29 is freshly confirmed OPEN/draft/unmerged; its fork still registers only
Core tests and Reusable host tests. No hosted component success is claimed.

83 cases against CORE b01f481072edecac33d5e40c25869359a5b3fa1f pass strict
Windows Clang ASan/UBSan classification:66 clean,16 correct known assertions,
1 previously scoped fan callback diagnostic,0 unexpected failures/skips.
All81 Python helpers pass9.906s; actionlint and whitespace checks pass.
The combined gate rebuilt/rechecked all seven current-compatible suites after
CORE-root selection changes. Fixture files retain strict compiler warnings;
original-source portability warnings remain visible and documented.

New odometer10 cases use real EEPROM/CRC storage and pulse/state/time callbacks:
restart persistence runs in two processes, reset preserves previous readings,
foreground work persists spindle time, and settings callbacks reclaim pulse
observation. Encoder12 cases use real CORE registration/claim/enumeration,
actual EEPROM restart and observed realtime command bytes. Four correct
regressions reproduce rapid command mapping and early enumeration termination.
No encoder sanitizer allowances. Unsupported MPG routes remain TODO.

Simulator VFS is separate from its EEPROM suite. Current CORE compilation fails
on removed vfs_path_t; the failure log is retained, with no alias/fallback.
The driver's own CORE gitlink4ec1ae44b857a70d2f9298344feac4b43ed0eb6b was fetched
unchanged to a separate directory. Its explicit reference build passes strict
classification:9 cases,6 clean/3 known assertions,0 unexpected/skipped/diagnostics.
These confirm nested-directory metadata, stale remount success and buffered
truncate defects. Reference success does not validate current CORE.

New local LLVM coverage, selected original files/configurations only:

| Suite / CORE selection | Lines | Branch outcomes |
|---|---:|---:|
| plugin_odometer / b01f481 | 124/124 (100.00%) | 44/50 (88.00%) |
| plugin_encoder / b01f481 | 186/346 (53.76%) | 77/195 (39.49%) |
| driver_simulator_vfs / reference4ec1ae4 | 125/139 (89.93%) | 54/72 (75.00%) |

Each measured JUnit file passes strict profiling-error classification. Maximum
counter paths217/229/223; no counters lost. Unused/unproven encoder code remains
in the denominator. Earlier five-suite coverage below remains unchanged.
Source locks were independently resolved through GitHub and verified against
clean local source checkouts; odometer a752dc6, encoder b3e31df, EEPROM backend
0c278db, Simulator150e3f9. Immutable full revisions are in ignored build-evidence
*-batch3-source-lock.json alongside sanitizer/coverage logs, XML, JSON and HTML.

Next substantial work: SD-card stream/job ownership and spindle integrations;
resolve valid public encoder MPG contracts without private-state forcing. The
48-repository inventory is partial; this checkpoint does not complete the goal.

---

# Plugin and driver coverage - 2026-10-24

Goal: meaningful functional tests across all plugin/driver catalogue implementations
and CORE. Never edit CORE/plugin/driver production sources or merge PRs. Preserve
other work and use substantial batches. CORE coverage continues in its active chat.

## Previous validated checkpoint

Draft https://github.com/grblHAL/Unit_tests/pull/29 is OPEN/draft, not merged
(fresh API check). Branch plugin-driver-tests tracks origin/plugin-driver-tests;
initial checkpoint200ecaf was already published. Tested implementation:
6bcfb404aacdaf39a1ff69150dd372ff1b134129; a documentation-only checkpoint records these results.
Do not touch the concurrent CORE checkout or merge the PR.

61 Windows Clang ASan/UBSan cases pass strict classification:48 clean,
12 correct expected-failure regressions,1 exact known recovering fan-setting
callback diagnostic; no unexpected failures/skips. Suite times: misc0.81s,
EEPROM1.56s, fans0.88s, Simulator0.38s, OpenPNP0.51s. All81 CI helpers pass9.590s;
actionlint also passes. No production source was edited.

The batch adds OpenPNP, real EEPROM-backed littlefs format/write/unmount/remount/
read with settings-region preservation, upper-bank CRC blocks, persisted fan
ports, delayed program end, callback chaining and RGB/RGBW/servo readback.
Dependency-only littlefs is independently locked and cannot be selected as a
suite. Correct regressions additionally record M42 fractional output ports and
littlefs physical read/program failures reported as success.

One misc coverage attempt lost a counter file at Windows path length263 and is
REJECTED. Both reporters now fail Clang/GCC profiling errors even for known tests;
positive/negative helper controls and the saved real failure prove this. Verified
misc coverage uses the shorter attached-workspace build-plugin-cov directory
(max counter path226), reading this isolated branch's source. All five accepted
coverage JUnit files have zero counter errors and pass strict classification.

Latest LOCAL LLVM measured coverage (instrumented files/configurations only):

| Suite | Covered/total lines | Covered/total branch outcomes |
|---|---:|---:|
| plugins_misc | 238/243 (97.94%) | 178/238 (74.79%) |
| plugin_eeprom | 156/156 (100.00%) | 52/58 (89.66%) |
| plugin_fans | 184/190 (96.84%) | 101/119 (84.87%) |
| plugin_openpnp | 141/148 (95.27%) | 86/113 (76.11%) |
| driver_simulator | 48/54 (88.89%) | 19/26 (73.08%) |

These are not full repository/catalogue coverage: uncompiled files/configurations
remain in the inventory. Same-source/configuration misc gains20 lines/31 outcomes
and fans22 lines/18 outcomes over the initial checkpoint. EEPROM additionally
instruments its littlefs adapter, so its denominator expanded; do not present its
percentage change as a like-for-like gain. Known defects remain despite coverage.

PR29 remains draft: the fork only registered Core tests and Reusable host tests
at the last workflow-list check. New manual workflows require default-branch
installation; no hosted component success or hardware verification is claimed.
Do not repeatedly dispatch/poll unavailable workflows. Continue substantial
independent batches from COMPONENT_TODO.md, starting Simulator VFS and the next
catalogue implementations. Keep the full goal active; this checkpoint is not
completion. Local logs/locks/HTML/XML/JSON remain in ignored build directories.

## Current branch and source locks

`plugin-driver-tests`, isolated from concurrent `coverage-batch-74` authoring,
initially based on 58774aa; moved onto merged upstream for focused delivery. Only this chat's verified edits were moved from the shared
checkout; original source checkouts and all existing work remain preserved.

| Suite | Repository | Local revision |
|---|---|---|
| plugins_misc | grblHAL/Plugins_misc | 265711922037cab6b6e47a9560ef11da3a6e5f83 |
| plugin_eeprom | grblHAL/Plugin_EEPROM | 0c278db74edc38303b9d86583a7d51a1ec1be51e |
| plugin_fans | grblHAL/Plugin_fans | c5c3613c8d311b43427ec32d551a1e62a5a68531 |
| driver_simulator | grblHAL/Simulator | 150e3f935e4b7cab7b90263b6b90b78912d9158d |
| plugin_openpnp | grblHAL/Plugin_OpenPNP | 76dbbc1420dd9773b1008a21f9d97b266f564bc9 |

CORE dependency: b01f481072edecac33d5e40c25869359a5b3fa1f.
littlefs dependency: 6cb4e86540eca0d9ba62500a298385c9d863c8be. Sources are unchanged.
Separate manual-only Plugin tests and Driver tests Actions callers reuse the
compiler/sanitizer/coverage/reporter workflow. Each resolves immutable candidate
and CORE revisions and uses separate artifacts, diagnostics and coverage filters.

## Implemented workflows and confirmed defects

- Misc plugins: M220 override validation/backup/restore; M150 RGB strip routing,
  masks and brightness; M280 servo attachment, PWM configuration, angle and readback.
- EEPROM plugin: single-/two-byte address layouts, 16/32/64/256-byte pages,
  upper bank, CRC roundtrip/corruption, write failure and EEPROM versus FRAM delay.
- Fan plugin: M106/M107, check mode, reset/program end, spindle-linked delayed
  shutdown, realtime reports, toggling and unavailable resources/ports.
- Simulator driver: erased-file creation, persistence, close-before-open,
  block roundtrip and checksum regressions.

Correct assertions retained for confirmed defect groups, documented under
suite-specific KNOWN_BUGS.md with individual expected-failure properties:
Simulator checksum writer/reader; EEPROM failed reads reported as successful;
two-byte-address EEPROM writes checksums after failed payload transfer; fan
spindle-link setter integer type differs from CORE callback contract.
One exact Clang-only fan-setting callback type diagnostic is tracked; all other sanitizer diagnostics fail. Checksum-reader fixture provides spare valid
caller buffer room so it validates rejection without relying on an overread.

These are callback-level unit tests using original source and real CORE headers,
math and CRC helpers. Full parser/firmware integration and board electrical/timing
behavior are additional work, not implied by a host pass.

## Full catalogue backlog and next action

COMPONENT_INVENTORY.csv includes official and third-party plugin repositories,
plus drivers.json and all architecture links from the driver overview. Duplicate
laser features share their implementation repository; per-file/configuration
coverage remains unfinished within each repository. SDKs, examples, senders,
hardware accessories and unrelated WebUI dependencies are not driver entries.

Catalogue snapshots: grblHAL/plugins f642e7f82fcf91077048cea7833dbdff6afde743;
grblHAL/drivers 9f443d40ccb7060b8bdcaece2b67100e5c2dfc25. Reconcile future
catalogue additions before claiming all implementations are accounted for.

## Initial validation checkpoint

43 Windows Clang ASan/UBSan component cases classified strictly: 33 clean,
9 correct expected-failure regressions, 1 exact known recovering fan-setting
function-type diagnostic; zero unexpected failures or skipped cases. Individual
suite wall times: misc0.85s, EEPROM1.74s, fans0.58s, Simulator0.52s.
CI helpers78/78 passed7.271s. YAML parsing and checksum-verified actionlint1.7.7
passed for the new callers/reusable workflow. Live resolver plus preservation
checks verified all four candidate/CORE locks against unchanged local checkouts.
Sandbox temp-directory failures were infrastructure-only; retry with a workspace
temp directory passed. No production source changes were needed.

Local LLVM coverage measurements (same source revisions above):

| Suite | Covered/total measured lines | Covered/total branch outcomes |
|---|---:|---:|
| plugins_misc | 218/243 (89.71%) | 147/238 (61.76%) |
| plugin_eeprom | 134/136 (98.53%) | 46/50 (92.00%) |
| plugin_fans | 162/190 (85.26%) | 83/119 (69.75%) |
| driver_simulator | 48/54 (88.89%) | 19/26 (73.08%) |

These denominators contain instrumented files/configurations only; they do NOT
include uncompiled implementations in these repositories or the full catalogue.
Inventory/report missing-file rows remain essential. Windows LLVM results are
not substituted for hosted Linux GCC/Clang evidence. Local build-evidence and
build-coverage-* directories retain logs, source locks and HTML/XML/JSON reports.

Next: publish one focused initial-support draft PR against current upstream,
then continue the highest-value remaining fan/misc workflows and additional
catalogue implementations. New manual workflows require installation on the
default branch before GitHub exposes dispatch controls; do not merge them
yourself or claim hosted success. No hosted run or full-coverage claim is made.
