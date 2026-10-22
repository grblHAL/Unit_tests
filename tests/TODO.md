# Pending core features and maintainer follow-ups

Pending implementation and design questions are separate from confirmed defects.
The deferred-defect section links to KNOWN_BUGS.md; their existing regressions
retain explicit expected-failure labels until fixed.

## Storage write-failure policy

**Maintainer disposition:** 2026-10-14, low priority; policy/design follow-up.

Terje notes that failures of flash-emulated EEPROM may be permanent, and a
simulator failure may instead involve a write-protected backing file. The driver
reports the operation's failure and identifies the storage type. A driver may
retry internally, but the **core decides the response to a reported failure**.
Neither a failed write nor this TODO implies that the user needs a new board.

Decide how the core reports failure, retains unsaved data and permits recovery,
accounting for physical EEPROM, flash emulation and simulator storage. Retry
count, timing and any alarm are undecided; five attempts is not an agreed rule.
Existing coordinate/global/build-info/driver retry controls provide comparisons,
not a universal retry policy for every storage backend.

The observations below are retained as reproductions and review options, rather
than urgent confirmed-bug entries. Existing expected-failure tests remain visible
until the maintainer chooses and implements the contract. Their `known_bug`
CTest label tracks the current exception; it does not assign priority. Revisit
pending-state and retry assertions against that chosen contract before cleanup.

### Review the new EEPROM warning counter

**Recorded:** 2026-10-15, Terje `feebef26222111f11c7a3b3b0156d023aa786937`.
The new EEPROM failure branch increments `retries` twice per failed sync
(`retries++` followed by `if(++retries == 5)`). Starting at zero, the counter
visits even values, so it does not reach the warning threshold of five before
integer wraparound. This is source-review evidence, pending a focused public
storage workflow reproduction and the maintainer's warning/retry policy.
Do not turn an assumed five-attempt policy into a registered failing test.

### Version-only pending state after a failed write

**Observation recorded:** 2026-10-14, Terje `50055a283328c3f9726bbc8f22d20a801190c66e`.

Write the settings version byte through buffered `hal.nvs.memcpy_to_nvs()`, then
reject its first physical write. The version flag correctly remains true, but
[the aggregate dirty calculation at nvs_buffer.c:379](https://github.com/terjeio/grblHAL_core/blob/50055a283328c3f9726bbc8f22d20a801190c66e/nvs_buffer.c#L379)
omits `settings_dirty.version` and makes `is_dirty` false when no other record is
pending. Later syncs return immediately without retrying the version byte.

**Regression:** [failed version sync](cases/nvs_buffer/failed_version_only_write_remains_pending_for_retry.c).
**Passing control:** [successful version sync](cases/nvs_buffer/version_only_successful_sync_clears_pending_write.c).
Both exercise the public buffer-write API without manually changing dirty flags.

**Earlier implementation option (not applied; subject to the chosen policy):** Include the pending version
flag in the aggregate dirty expression. Preserve per-record success/failure flags.

**After implementing the agreed contract:** remove the version retry block in
[known_bugs.cmake](known_bugs.cmake), retain correct assertions and the control,
run storage/version cases and full sanitizers, then delete this TODO observation.
No sanitizer allowance applies.

## Plain G71 and G72 lathe roughing

**Recorded:** 2026-10-12

**Status:** TODO - roughing geometry is pending; core parser dispatch is tested.

Terje's core `e65020a8389b19d3c03277e02f34219e25800e6a` now dispatches plain
G71/G72 to the roughing plugin interface with the correct motion code and
arguments. Tests capture that interface; they do not implement roughing geometry:

- [G71](cases/lathe_ngc/g71_passes_default_roughing_arguments_to_plugin.c)
- [G72](cases/lathe_ngc/g72_passes_default_roughing_arguments_to_plugin.c)

The existing G70 and fractional G71.1/G71.2/G72.1/G72.2 tests likewise exercise
parser/plugin interfaces using a capture handler.
The default [mc_lathe_cycle handler](https://github.com/grblHAL/core/blob/451a539c6ed0f00499b8b48258f9aa7971fac384/motion_control.c#L806-L810)
also remains a placeholder.

When roughing geometry is implemented, add execution and endpoint tests against
that implementation, retain the parser/interface tests, and delete this TODO entry.

## Possible improvement: asymmetric ganging resolution validation

**Recorded:** 2026-10-13; reviewed with the user as an improvement, not a failure.

Writing an out-of-range secondary motor resolution through setting 103 currently
returns OK, then resets the value to the primary motor resolution and prints a
warning. The registered kinematics validator instead returns
`Status_SettingValueOutOfRange` without changing the previous secondary value.
The public lookup normalizes the axis setting ID and selects the generic axis
handler before the custom secondary-motor handler.

**Suggestion:** consider routing setting 103 to the registered kinematics validator
before the generic axis handler, so invalid writes return a clear error and preserve
the previous value. Keep the current warning/reset behavior until the maintainer
chooses that contract. The tests exercise the public valid write and the registered
validator independently; no expected-failure exception applies.

See [registered validator](cases/asymmetric_ganging/registered_resolution_validator_rejects_large_difference_without_mutating_motor.c)
and [public valid write](cases/asymmetric_ganging/resolution_setting_accepts_and_reports_small_motor_difference.c).

## Lathe diameter-mode conventions for reported offsets

**Maintainer review:** 2026-10-14; design question, not a newly confirmed failure.

Terje requested checking whether coordinate-style output in diameter mode should
apply special handling to tool offsets and other reported quantities. Define the
expected convention for each record before changing assertions. The dimensionless
G51 factor regressions already pass on Terje `50055a2`; their old exceptions and
known-bug entry were removed after direct verification. Do not reinstate that
fixed entry or treat the broader offset question as a confirmed defect.

Retain [inch-display factors](cases/report/scaling_parameter_report_keeps_dimensionless_factors_in_inches.c)
and [lathe factor reporting](cases/lathe_ngc/scaling_parameter_report_does_not_double_diameter_mode_factor.c).
Add offset-specific tests when the maintainer confirms the intended units/diameter
convention, and preserve existing coordinate and unit controls.

## G70–G72 execution and reporting contract

**Maintainer clarification:** 2026-10-14; design still undecided.

G70–G72 may not be motion modal states that should appear in reports. Their
implementation will trap motion commands emitted by the Q-word subprogram and
build a new subprogram for execution. Terje is considering a RAM file executed
through the parser, rather than direct `mc_line()` calls, because cutter
compensation is essential. Neither execution strategy is finalized.

Retain parser/plugin-dispatch tests. Do not add assertions that require G70–G72
to remain reported motion modes. The existing G70 modal-report and G70–G72 named
motion-parameter cases need review when the reporting contract is confirmed;
their current encoded values describe the present implementation, not a decision
about future cycle reporting. Add generated-subprogram execution, cutter-comp
and actual-motion reporting tests once the implementation and contract land.

## Removed SCARA source

Terje's `683589bd10bb1082825bfc7e9bcee6db102b9530` removes
`kinematics/scara.c`. The earlier source-integration and compile observations
on `39a69a2` are historical, so there is no current SCARA module to add to
the executable coverage inventory. Reassess support and tests if SCARA returns.

Path blending is separately marked experimental and unconditionally disabled
in `config.h`; do not change that definition solely to increase coverage.

## DO/WHILE CONTINUE contract

**Observation recorded:** 2026-10-14, Terje `39a69a2`; the user requested leaving this for Terje to comment on.

CONTINUE in a DO/WHILE loop currently rewinds directly to the body at
[ngc_flowctrl.c:611-612](https://github.com/terjeio/grblHAL_core/blob/39a69a22c72283ab186133b25fb89b8f5be35767/ngc_flowctrl.c#L611).
A finite counter loop with CONTINUE before its trailing WHILE never evaluates
that condition and repeats until the host read bound. Ordinary DO/WHILE and
CONTINUE with a later explicit BREAK have passing streamed-parser controls.

LinuxCNC O-code CONTINUE evaluates the loop condition. Confirm whether that
contract is intended here or whether restarting the body is a deliberate
difference. A bounded, no-motion [candidate regression](proposals/do_continue_rechecks_trailing_condition_and_skips_remaining_body.c)
is retained for review, outside the registered case set until intent is settled;
there is no expected-failure exception or source exclusion for this proposal.
Its correct resolution requires either implementing the chosen loop semantics
or documenting the deliberate difference, then reviewing the candidate assertion.

## Disabled auxiliary-output open-drain and timezone registrations

**Coverage inventory:** 2026-10-15, Terje `683589b`.

The auxiliary open-drain setter/getter exists, but its public setting registration
is commented out at [ioports.c:1449](https://github.com/terjeio/grblHAL_core/blob/683589bd10bb1082825bfc7e9bcee6db102b9530/ioports.c#L1449).
The ordinary public setting-disabled regression remains. The timezone setting
registration is likewise commented out at [settings.c:2503](https://github.com/terjeio/grblHAL_core/blob/683589bd10bb1082825bfc7e9bcee6db102b9530/settings.c#L2503).
These observations are not new core defects. Confirm supported exposure before
adding executable setting-update cases. Do not call the private setters or
modify production registrations merely to fill uncovered lines. If enabled
upstream, add public configuration, readback, persistence and driver-effect tests.

## Partial manual reference for ganged motors

**Contract question recorded:** 2026-10-15, Terje `683589b`; leave for maintainer review.

With persisted manual-homing mode, no homing phases and force-set-origin enabled,
real startup restoring XYZ/A motor counters {160, -240, 320, -240}, then `$HY`,
sets Y to zero but retains the secondary A counter at -240. X/Z are retained,
Y is marked referenced and no driver pulses occur. Both asymmetric ganging and
auto-square reproduce this result. Normal full startup homing and single-X
controls pass.

Should partial manual referencing of logical Y also zero its ganged secondary
counter, or should these configurations require referencing all axes? The
[kinematics position hook, lines 200-205](https://github.com/terjeio/grblHAL_core/blob/683589bd10bb1082825bfc7e9bcee6db102b9530/kinematics/asymmetric_ganging.c#L200-L205)
updates the secondary counter only when force-set-origin is disabled. The manual
homing path forwards the requested Y mask without the secondary bit. Confirm
supported use and intended semantics before calling this a defect.

The [candidate test](proposals/manual_ganged_y_reference_resets_both_motor_coordinates.c)
is unregistered pending that decision. Its fixture expects N_AXIS=4 and a ganging
or auto-square boot variant. No exception, source exclusion or production patch
was added. The ordinary startup homing tests remain registered.

## RTCP activation and measurement sequence

**Contract question recorded:** 2026-10-15, Terje `683589b`.

With default nonzero A/C center offsets and zero motor counters, public M851
changes the current RTCP coordinates to approximately (-113.660, -158.700,
186.540), while the parser's cached XYZ remains (0, 0, 0). A no-motion
[candidate frame check](proposals/rtcp_activation_updates_parser_frame_before_following_commands.c)
observes this after the sender acknowledgements, before another command or
motor pulse. It is unregistered, with no expected-failure allowance.

The [normal measured-frame control](cases/boot_rtcp/streamed_calibrated_default_geometry_keeps_incremental_move_local.c)
passes: M852 then M851 followed by a small incremental cut produces the intended
20/40/10 motor counters using those same default centers. Zero-centered and
fixed-angle streamed RTCP controls also pass.

Is M852 mandatory before enabling RTCP with nonzero center offsets? If so,
confirm/document that sequence and consider guidance for omitted measurement.
If direct activation is supported, should the parser coordinate cache be
resynchronized when the frame changes? The [M-code handler at lines 420-436](https://github.com/terjeio/grblHAL_core/blob/683589bd10bb1082825bfc7e9bcee6db102b9530/kinematics/rtcp_ac.c#L420-L436)
resynchronizes on M850 but not M851. This remains a workflow/contract question,
not a confirmed core defect. No production patch or source exclusion was added.

## Analog expansion pin-base bookkeeping

**Possible improvement / usage review:** 2026-10-15, Terje `683589b`.

Two external analog banks with two inputs and outputs each register and route
ADC/DAC calls correctly. A host inspection after public registration reports
bank 0 input/output pin bases 0/0, bank 1 bases 0/2. Digital expansion banks
advance both direction-specific bases consistently. In [ioports.c:1080-1087](https://github.com/terjeio/grblHAL_core/blob/683589bd10bb1082825bfc7e9bcee6db102b9530/ioports.c#L1080-L1087),
the input branch writes `out.pin_base` rather than `in.pin_base`.

Confirm whether supported analog expansion drivers use this input metadata
before classifying a user-visible defect. If the intended contract matches the
digital registration, assign the computed input base to `in.pin_base`, keeping
output and input counts independent, and add driver-facing metadata tests with
unequal bank sizes. Current routing/claim/IRQ tests pass; no known-failure label,
production change or source exclusion was added for this observation.

## Coverage inventory: inline/header implementations

**Rechecked:** 2026-10-22. The current core coverage_filter and README gcovr
example already include both .c and .h files. Archived PARTIAL run39373002337
(c9941ca/CORE7a6a432) measures six headers, including rgb.h and stepper2.h.
The previous .c-only scope note was stale.

The detailed summary now inventories C sources and headers together, so measured
header line/branch gaps are visible and its file count uses the same file types.
Uninstrumented headers may contain only declarations; their absence is not proof
of missing executable tests. No coverage filters, XML metrics or runtime cases
were changed by this reporting repair. The archived report remains PARTIAL.

Full-supported coverage still requires reviewing executable inline bodies and
conditional code that are not emitted in the tested configurations. Retain them
in the source inventory; never equate a green suite or a covered file with full
CORE line/branch coverage.

## Hide pullup-disable settings for protected board inputs

**Maintainer follow-up:** 2026-10-15. Terje confirmed that the core control-input
configuration test should expect PullMode_Down. Actual electrical behavior may
be None depending on the processor; board input protection belongs to the driver/
hardware contract. Terje plans to remove the disable-pullup option for boards
with input protection. Do not require physical pull-down behavior from host tests.
Review setting availability tests when the board capability/API is implemented.


## Updating an active G66.1 registration

**Contract question:** 2026-10-15, Terje `feebef2`. After successful G66.1P100X12
in the normal macro parser fixture, G66.1X24 returns status 21 (modal group
violation), with no second macro callback. Repeating P100 is also rejected.
The callback returns Status_OK and local scope returns to zero; ordinary first
registration/cancellation and callback-error cleanup pass. The parser contains a
same-call-level argument-reuse branch, but its intended public command sequence
needs confirmation. Should callers cancel with G67 and register afresh, or can
active arguments be updated? The candidate is unregistered in
[tests/proposals](proposals/g66_1_repeated_registration_updates_arguments_and_cancels_cleanly.c).
No known-failure exception or confirmed defect is added for this question.


## RGB strip clear device-index convention

**Contract question:** 2026-10-15, Terje `feebef2`. rgb.h's rgb_clear helper
calls the output callback for indices zero through num_devices inclusive, while
num_devices is described as the number available. Confirm the supported driver
convention (including whether zero has a broadcast meaning) before asserting
strip-clear bounds. These helpers are explicitly not used by core execution.
Packing, channel masks and intensity conversions have ordinary passing tests;
no artificial short buffer, confirmed defect or expected-failure test is added
for this index question.


## Native rigid tapping execution

**Pending implementation:** 2026-10-15, Terje `feebef2`. The default weak
mc_rigid_tapping implementation in motion_control.c returns
Status_GcodeUnsupportedCommand and is explicitly marked TBC. Keep parser/
extension dispatch distinct from native tapping execution. When a real
implementation is supplied, add execution endpoints and spindle-reversal tests
through valid driver/encoder setup. Do not implement substitute tapping geometry
in a test fixture or classify the absent feature as a new confirmed defect.


## Windows LLVM profile paths and header-inclusive CI reporting

**Verified collection limitation:** 2026-10-15. The local Clang header-inclusive
report at batch 12 checkpoint 5172863 says 17,319/18,815 lines and 10,254/12,856
branches, but is incomplete: passing RGB cases have gcno files and no gcda
profiles. The byte-mask case's original gcda path is 262 characters. Running the
same executable with GCOV_PREFIX pointing to a short workspace folder and
GCOV_PREFIX_STRIP=99 produces its 212-byte gcda profile. Core source is unchanged.
Evidence: ../batch-12-header-coverage.xml/logs and the short-path proof under
C:/Users/User/Documents/Codex/p12/rgb-mask. This is a host profiler/path issue,
not nine untested RGB helpers or new core faults. Earlier local header totals
may have the same limitation and must not be treated as authoritative.

Header filters are already inclusive; the reporting-only inventory correction
is separate from the runtime test batch. It does not repair Windows profile-path
collection. Use hosted Linux results for authoritative totals and keep failed-run
measurements explicitly PARTIAL. Never suppress gcovr errors or exclude real code
to claim full CORE coverage.


## Compatibility-level coordinate availability documentation

**Documentation clarification:** 2026-10-15, Terje `feebef2`. config.h describes
level 10 as disabling G59.1-G59.3, but gcode.h's coordinate enum explicitly makes
them available only when COMPATIBILITY_LEVEL <= 1. Runtime level-2/10 tests use
six standard work systems; level 2 retains HOME reporting, while level 10 omits
that extension. Align the configuration description with intended availability.
No missing-feature failure or exception is registered for this documentation
question.

## Wall-plotter homing coverage requires an implemented public workflow

**Review date:** 2026-10-15, Terje core feebef26222111f11c7a3b3b0156d023aa786937.

The hosted report still lists the wall-plotter target/reference homing helpers
as uncovered. Although initialization installs the kinematics limit callbacks,
its public home_machine handler explicitly reports "Homing is not implemented!"
and returns false. The existing unsupported_homing_reports_warning case verifies
that response. Do not directly invoke the private helpers or bypass that handler
solely to cover their lines. Revisit normal sender-driven homing tests when the
maintainer implements the wall-plotter homing workflow and defines its reference
contract. This is a pending feature/coverage limitation, not a new confirmed bug;
no source exclusion or expected-failure exception is added.

## Confirm whether NO_SAFETY_DOOR_SUPPORT remains supported

**Review date:** 2026-10-15, Terje core feebef26222111f11c7a3b3b0156d023aa786937.

A proposed runtime host variant defining NO_SAFETY_DOOR_SUPPORT=1 cannot compile:
settings.c:1152-1173 removes set_parking_enable and set_restore_overrides, but the
setting table still references them at lines 2425 and 2444. The first two Clang
errors identify those undeclared names; the later incomplete-array sizeof error
is consequential. driver_opts.h:530 still checks this symbol against enabled
safety-door hardware, and grbllib.c:324 clears the door capability for it.

Confirm whether the option is an intended current configuration or obsolete.
If supported, align setting-table guards with the setter definitions (review
parking/restore semantics rather than guessing), then register and run the four
candidate startup/settings tests in proposals/boot_no_safety_door and
proposals/no_safety_door with consistent host/test compile definitions. Current
proposals are unregistered; no production patch, broad compiler allowance or
expected-failure exception is introduced. Local compiler evidence is in the
parent workspace batch15-no-door-build.log. Reproduce with:

```sh
cc -std=gnu11 -fsyntax-only -DNO_SAFETY_DOOR_SUPPORT=1 -Icore core/settings.c
```

## Probe protection startup workflow is currently disabled

**Review date:** 2026-10-15, Terje feebef26222111f11c7a3b3b0156d023aa786937.
settings.c:3885-3893 uses an inactive #if 0 capability branch and unconditionally
clears settings.probe.enable_protection. Thus normal boot cannot currently reach
protocol.c's enabled-protection startup alarm via a saved setting. Do not force
it back on after settings_init simply to cover that branch. Two candidate enabled
startup cases remain unregistered in proposals/boot_probe_protection, pending
maintainer activation/support confirmation. Registered controls verify that boot
clears the unavailable stored flag and leaves ordinary parser commands usable;
these do not claim protection is operational or prove physical interlock behavior.
No production patch, source exclusion or new known-failure exception is added.


**Runtime clarification, 2026-10-19:** full normal boot with a registered
watchable probe accepts `$65=32` and arms its guard after startup. Clearing the
saved protection flag during settings initialization does not prevent this
runtime workflow. The ordinary idle probe IRQ cases remain registered; see
[cold boot then runtime enable](cases/boot/initialized_probe_options_allow_runtime_protection_enable.c).
Do not withdraw those cases based solely on the startup flag clearing above.

## Failed-startup detailed driver diagnostic policy

**Review date:** 2026-10-15, Terje feebef26222111f11c7a3b3b0156d023aa786937.
This is a maintainer question, not a registered defect or expected failure.
[grbllib.c:413](https://github.com/terjeio/grblHAL_core/blob/feebef26222111f11c7a3b3b0156d023aa786937/grbllib.c#L413)
queues report_driver_error, which formats the incompatible-driver detail at
[lines 140-150](https://github.com/terjeio/grblHAL_core/blob/feebef26222111f11c7a3b3b0156d023aa786937/grbllib.c#L140-L150).
Failed-startup filtering at
[lines 837-860](https://github.com/terjeio/grblHAL_core/blob/feebef26222111f11c7a3b3b0156d023aa786937/grbllib.c#L837-L860)
retains only report_warning tasks, so this differently named diagnostic task is
discarded along with ordinary plugin work. Confirm whether that detail should
also survive, or whether the generic self-test message is the intended output.
Do not call the private formatter directly simply to cover its lines.

The registered [USB failure test](cases/boot/usb_connection_reports_failed_selftest_then_retained_startup_warnings.c)
checks the existing public connection workflow: matching DTR emits the delayed
generic failure message and retained warnings in order; unrelated startup tasks
stay suppressed. No change to the startup policy or core source was made.


## Planner exhaustion during controller startup

**Recorded:** 2026-10-16, core `4ec1ae44b857a70d2f9298344feac4b43ed0eb6b`.
The new public planner tests verify reduced usable capacity and a successful
retry after an allocation failure. A normal boot test verifies fallback warning
output and a successful sender query. Complete startup exhaustion is a separate
policy/defensive-handling question, not a registered failure.
[plan_reset](https://github.com/terjeio/grblHAL_core/blob/4ec1ae44b857a70d2f9298344feac4b43ed0eb6b/planner.c#L225-L247)
returns false if it cannot allocate even its minimum attempted buffer;
[grbllib.c:489](https://github.com/terjeio/grblHAL_core/blob/4ec1ae44b857a70d2f9298344feac4b43ed0eb6b/grbllib.c#L489)
does not check that return. Confirm how startup should report this condition and
restrict operation. No boot-exhaustion regression/alarm expectation has been
registered, and no controller crash or physical outcome is claimed here.

## Possible improvement: simultaneous override-change notifications

**Recorded:** 2026-10-16, core `4ec1ae44b857a70d2f9298344feac4b43ed0eb6b`.
Individual feed and rapid changes notify the matching observer exactly once;
repeated unchanged requests do not. The new ordinary control tests verify those
contracts and their resulting nominal rates.
In [planner.c:753-765](https://github.com/terjeio/grblHAL_core/blob/4ec1ae44b857a70d2f9298344feac4b43ed0eb6b/planner.c#L753-L765),
the logical OR short-circuits assignment of rapidrate_changed when feed changes.
Both percentages are still stored/applied, but the rapid-specific callback is
then omitted. Confirm whether a combined update should notify both groups or
whether one callback is intended to prompt an observer to refresh all values.
This is source-review evidence and an undecided observer policy, not a confirmed
motion defect. Do not register a two-callback expected failure before review.
If both events are desired, compute the two change booleans independently before
testing their OR, then add a combined-update regression.


## Confirm modal-save scope for CSS surface speed and RPM cap

**Recorded:** 2026-10-17, core `ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216`.
Normal runtime G96/G97 and G7/G8 snapshot restoration now has registered-spindle
controls. Before asserting a stronger contract, confirm whether M70/M72 must
also preserve G96's surface-speed S value and D RPM cap after another G96 changes
them. This is an undecided scope question, not a registered expected failure.
Source review: [snapshot save](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/ngc_params.c#L1044-L1063)
copies gc_modal_t, whose spindle CSS field is a pointer into the active spindle
parameters. [CSS updates](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/gcode.c#L2510-L2534)
update that shared parameter storage. Reproduce two different G96 S/D commands
around M70/M72 and check subsequent planned RPM at a known tool radius after
Terje confirms the intended saved-state scope. Do not infer a physical failure
or register a new exception from pointer ownership alone.


## Review embedded asset size accounting after allocation failure

2026-10-18, Terje ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216. Low-priority
source-review note, not a registered failure or a claimed production incident.
The new public allocation-failure tests confirm an appended list can be retried
without losing existing assets. fs_embedded_mount() increments fs_size before
allocating the appended-list node; review whether a failed registration and retry
should roll back that diagnostic size accounting. No runtime size regression is
asserted yet. Decide whether this rare exhausted-heap reporting detail warrants
work before adding an assertion; retain the ordinary directory/retry controls.
Source: [registration](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/fs_embedded.c#L241-L267).


## Clarify reachability of the MPG zero-report-flag callback arm

2026-10-19, Terje ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216. Source-only coverage
note, no registered failure. report_add_realtime(Report_ClearAll) clears the
active stream flags and returns before firing on_rt_reports_added. The MPG
observer has a zero-flags arm, which this supported publisher does not reach.
Do not directly invoke a private handler just to color that branch. Ask whether
clear is intentionally per active stream, or whether an external publisher uses
that callback contract. Keep the gap visible until clarified; no change to
independent primary/pendant pending-report semantics is proposed.
Sources: [publisher](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/report.c#L3006-L3042),
[MPG observer](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/stream.c#L608-L617).


## Confirm coordinate-rotation pivot for translated work offsets

**Recorded:** 2026-10-19, Terje core `ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216`.
Undecided coordinate convention, not a confirmed defect or registered failure.
Public parser/actual stepper reproduction: `G10L2P2R90`, `G10L2P2X3Y4`,
`G55G0X0Y0`, then `G3X1Y1J1F100`. At 80 steps/mm, final machine/driver
positions are (-400,320) steps = (-5,4) mm, with 400/320 motor pulses.
The core adds the G55 offset to the work target before rotating, so the work
origin itself rotates around the machine origin. A convention that rotates
about the translated work origin would instead end at (2,5) mm = (160,400)
steps. Confirm the intended pivot before changing either implementation or
expectations. This also affects the initial linear move, so it is not claimed
as an arc-only error. Zero-translation XY/ZX/YZ and inch arc controls pass.

Candidate: `tests/proposals/translated_rotated_center_arc_keeps_work_origin_separate_from_center_delta.c`
(unregistered; no WILL_FAIL or sanitizer allowance). Evidence:
`../batch62-translation-proposal.log`. Source: [offset before rotation](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/gcode.c#L3258-L3263),
[relative arc-centre rotation](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/gcode.c#L3794-L3796).


## Hold snapshot null-pointer guard is not reached by valid slot iteration

**Reviewed:** 2026-10-19, Terje `ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216`.
The new primary-only two-slot hold/resume tests exercise a disabled secondary
slot through settings/startup, including the `spindle->hal == NULL` snapshot
branch. The separate `gc_spindle_get(...) == NULL` fallback remains uncovered:
initiate_hold iterates valid nonnegative slot indices, and gc_spindle_get returns
the address of the corresponding modal slot for all such indices in both the
single- and multi-spindle builds. Do not corrupt a slot pointer or call a private
handler to cover this defensive fallback. Keep it visible in raw coverage;
revisit if the getter contract changes. This is a reachability note, not a bug
or a request to remove a defensive check.
Sources: [slot getter](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/gcode.c#L886-L893),
[hold snapshot](https://github.com/terjeio/grblHAL_core/blob/ad57c788e15fb4e5d8ef9c20ed50755ffa3d9216/state_machine.c#L134-L158).

## Remaining coverage: unexposed settings and parser branches

**Reviewed 2026-10-19, Terje 16c7dff3aa9614322cfc2b47a2109cc9196ccca4.**

- `ioports.c`: the `Settings_IoPort_OD_Enable` setting registration is commented
  out. Existing ordinary tests verify that setting writes are disabled. Do not
  invoke its private setter to cover its dormant configuration/getter cases.
- `gcode.c`: M48/M49 branches for `spindle_id == -1` are not reached by normal
  override blocks: `is_single_spindle_block()` does not address a spindle for
  those commands, and the remaining dollar word is rejected. M51 explicitly
  requires one spindle. Keep default/per-spindle workflow tests; do not forge
  parser state to execute the dormant all-spindle loops.

These are reachability observations, not confirmed firmware defects or requests
for new features. Keep them in the reported denominator; revisit if the public
interfaces expose these paths. Prefer remaining supported workflows first.

## Named macro with a different SUB header: clarify supported structure

**Observed 2026-10-19, Terje 16c7dff3aa9614322cfc2b47a2109cc9196ccca4.**
Calling `fixture.macro` whose body starts with an assignment followed by
`O<other>SUB` did not complete within the 15-second test timeout. Other ordinary
named-macro syntax-error/unwind tests pass. The candidate expected a syntax
error, caller scope restoration and suppression of the caller tail; the supported
meaning of a differently named SUB within a named macro still needs review.
The candidate is unregistered in
[proposals](proposals/named_macro_mismatched_sub_header_unwinds_scope_and_suppresses_caller_tail.c).
Evidence: local batch69-recovery-results.xml / batch69-recovery-tests.log.
Do not classify it as a confirmed core defect or add an expected-failure allowance
without checking the macro-file contract and identifying the exact stalled path.

## G76 X-word main taper: confirm implementation scope

**Source review 2026-10-19, Terje 16c7dff3aa9614322cfc2b47a2109cc9196ccca4.**
`gcode.c` computes `thread.main_taper_height` and a pitch correction when G76 has
an X word. `motion_control.c` rescales that height, but no generated threading
move consumes the value. Existing entry/exit tapers, straight and reverse-Z
threads have ordinary encoder-driven motion tests. Before adding a main-taper
geometry assertion, confirm whether the X-word feature is intended to be complete.
This is an implementation-scope question, not a registered defect or exception.
Do not add a test that merely executes the calculation and blesses straight
motion as a correctly tapered thread to improve a coverage percentage.

## Settings coverage: obsolete private dispatch cases

**Reviewed 2026-10-19, Terje 16c7dff3aa9614322cfc2b47a2109cc9196ccca4.**
`Setting_HomingDirMask` and `Setting_SteppersEnergize` register `get_axis_mask`,
so their older cases inside private `get_int` are not reachable through the
registered settings API. Their public setting/query behavior already has tests.
Likewise the safety-door delay settings have no availability callback, automatic
and MPG report intervals register no availability callback, and the timezone
setting registration is commented out. Those corresponding cases inside private
`is_setting_available` cannot be reached through these current registrations.
Do not replace registry entries or invoke static handlers to cover these obsolete
paths. Leave them visible in coverage; revisit if core registrations change.

## Bare G38 command: confirm whether modal-only selection is intentional

**Observed 2026-10-19, Terje 16c7dff3aa9614322cfc2b47a2109cc9196ccca4.**
Public parser input `G38.2F100` returns `Status_OK`, rather than the
`Status_GcodeNoAxisWords` suggested by the probe-validation comment/check.
The overall motion validation is gated by `AxisCommand_MotionMode`, so an
axis-free block can instead select the modal probing mode without entering
that check. Confirm whether this is intentionally supported before requiring
an error or registering a positive modal-only contract test.
The unchanged rejection assertion is unregistered in
[proposals](proposals/probe_command_without_axis_words_rejects_without_arming_and_next_probe_works.c).
Evidence: batch69-controller-options-results.xml and
batch69-probe-command-diagnostic.log (actual0, expected26). No expected-failure
allowance, source change or coverage exclusion was added. The ordinary
same-position-target rejection followed by a successful contact probe passes.

## Additional unreachable coverage guards: help dispatch and MPG pullup

**Reviewed 2026-10-19, Terje 16c7dff3aa9614322cfc2b47a2109cc9196ccca4.**
`system_execute_line()` handles every HELP-prefixed command before command-table
lookup, so the static HELP table handler `output_help()` is redundant in the
ordinary dispatcher. Its public behavior is already tested via `$HELP`.
In `ioports_configure()`, the `Input_MPGSelect` comparison is inside a condition
requiring `xbar->function < Input_Probe`, although the MPG enum is greater than
Input_Probe. That particular branch is unreachable. Existing loaded MPG-select
configuration tests verify observable pullup/debounce behavior, which currently
comes from the initial configuration value. Do not invent different enum values
or invoke private dispatchers to execute these lines. These are source-audit
notes, not new expected failures or coverage exclusions.

## G66 after arcs: confirm intended supported motion types

**Observed 2026-10-19, Terje 16c7dff3aa9614322cfc2b47a2109cc9196ccca4.**
An armed G66 callback fires after G0/G1 but not after G2/G3. Source contains the
scope-aware trigger only in the linear and rapid cases. Four real-stepper arc
candidates (CW, CCW, helix and full circle) returnedOK and reached the callback
count assertion with zero calls; a nested-arc scope candidate also assumes arc
trigger support. All five are unregistered in proposals pending confirmation.
Do not label an intentional/incomplete motion-type limitation as a confirmed
regression. Evidence: batch69-startup-macros-results.xml and
batch69-macro-diagnostic.log (stored P100/L1, zero callback calls).
The linear nested-G65 scope case uses explicit L1 so it tests scope independently
of the separately registered G65 default-repeat/required-P defect.


## Unreachable G10 missing-P/L guard (2026-10-19)

On core16c7dff, the missing-P/L check is inside values.l > 0. An ordinary parsed nonzero L already sets words.l, making !(words.p || words.l) false. Bare G10 instead selects L0/reload and correctly returns unsupported when no reload handler exists. Keep this gap visible; do not force private parser state to exercise it.

## G53 with active Fanuc scaling - contract review (2026-10-19)

The incoming test assumed G53 bypasses G51 scaling. Current parser scales axis
values before machine-coordinate override; G51X0Y0P2 then G53G0X10Y10 targets
X20 Y20. Confirm intended interaction with Terje before classifying a defect.
Unregistered proposal: tests/proposals/g53_scaling_machine_coordinates.c.
Registered control cancels scaling with G50 before the G53 move.


## Secondary PWM inversion guard reachability

**Reviewed:** 2026-10-20, clean Terje `7a6a432eaf78e028b81ff3a5f9804e14519f5f01`.

Driver registration trims unsupported PWM inversion from the secondary spindle's
public bitfield metadata. An ordinary setting write requesting that bit therefore
returns `Status_SettingValueOutOfRange` before `set_spindle_invert()` can reach
its older `Status_SettingDisabled` fallback. The supported rejection and subsequent
enable/direction inversion are covered by
[the public-setting case](cases/multi_spindle/secondary_pwm_rejects_signal_inversion_not_supported_by_driver.c).
Do not call the private setter or replace registered metadata to color that guard
in coverage. This is a reachability note, not a firmware bug or an exclusion.


## Redundant YZ cutter-compensation plane guard

**Reviewed:** 2026-10-20, clean Terje7a6a432. The common validation in
`gcode.c:2720-2721` rejects YZ cutter compensation with
`Status_CutterCompConflict` before the later same-condition
`Status_GcodeIllegalPlane` check at2853-2854. The public rejection and corrected
XY retry are tested in
[the activation case](cases/cutter_comp/enabling_compensation_in_yz_plane_rejects_before_plugin_and_allows_xy_retry.c).
Do not bypass the earlier guard to color the later one in coverage. This is a
reachability observation, not a new defect or a coverage exclusion.


## Plasma material handling is a plugin integration contract

**Maintainer context supplied by the user:** 2026-10-22. Terje is developing
controller-local SD-card material handling in the plasma plugin and ioSender.
The plugin handles M190 and LinuxCNC-style material comments; feed can reference
`F#<_hal[plasmac.cut-feed-rate]>`. The material comment itself is separate from
that named parameter expression.

Keep standalone CORE tests on published parameter-provider and comment-hook
contracts. Do not invent material persistence, selection, required fields or
sender behavior without the plasma plugin and its supported configuration.
The current parser-flag refactor and source build failures are recorded against
an exact revision in KNOWN_BUGS; they do not establish a settled material API.
Revisit integration coverage when the implementation and plugin fixture are available.


## Closing serial demarcation after an alarm-rejected block

**Observed:** 2026-10-22, Terje `fab8d1c248990f53f13a444018fbb3ee353061dd`.
The existing full-boot alarm-locked settings-upload case sends `%`, a valid
$11 setting, rejected G91, then `%`. The closing marker no longer reaches the
observer: compatibility-level-zero last_error gating follows the demarcation
alarm bypass. Confirm whether closing demarcation must release a settings batch
after an intervening error, or whether the sender must explicitly clear the error.
Keep the existing regression and its callback/motion assertions pending that
contract review. A named WILL_FAIL now records the observed failure per the
requested nonblocking policy; it does not establish the intended contract, and
there is no sanitizer allowance.
Evidence: build-asan/batch72-current-core-available.xml,
boot.alarm_locked_settings_upload_demarcates_batch_and_keeps_motion_blocked.


## Expression dispatcher gaps that require invalid private enums

**Reviewed:** 2026-10-22, clean Terje fab8d1c. The old partial map marks
ngc_expr.c115-116,189-190,292-293 and337-341 as missing. These are private
binary/unary/precedence defaults: read_operation/read_unary reject unknown text
before dispatching a valid enum. Do not inject enum values into private helpers.
The execute_unary EXISTS no-op at250-252 is bypassed by read_unary's dedicated
EXISTS evaluation path. Existing public EXISTS and unknown-operator controls,
including a malformed second operator with queued motion, remain registered.
Keep these defensive/unemitted paths in raw reporting; revisit if public dispatch
changes. This is reachability evidence, not a request to remove source lines.


## Settings dispatch cases not wired by public metadata

**Reviewed:** 2026-10-22, clean Terje fab8d1c. The saved partial map lists
settings.c2181-2187 and2198-2204 in is_setting_available. DoorSpindleOnDelay,
DoorCoolantOnDelay and AutoReportInterval registrations pass NULL for
is_available, so ordinary queries do not call those switch cases. TimeZoneOffset
registration is commented out. The get_int SteppersEnergize case at1789-1791
is also unused: the registered setting routes reads to get_axis_mask instead.

Do not call private setters/getters with unrelated IDs or replace metadata just
to enter these cases. Keep them in the raw source denominator and revisit if
registrations change. Existing public motor-hold write/read/persistence tests
remain; malformed integer rejection now also verifies driver and stored-state
preservation followed by a successful retry. Description allocation recovery
is tested through the ordinary registered plugin query.


## Fault-axis inline fallback is guarded at the CORE caller

**Reviewed:** 2026-10-22, clean Terje fab8d1c; archived header branch detail is
unchanged except for new analog declarations in crossbar.h. The remaining
false-range conditions in xbar_fault_pin_to_axis require a non-motor-fault
function. Its only CORE caller, config_fault_pins in ioports.c1495-1497,
first requires xbar_is_motor_fault_in(function). Existing primary/secondary
XYZ identity tests exercise both valid fault ranges.

No current supported CORE workflow reaches the unmatched fallback. Do not route
an unrelated signal through a private configuration path merely to fill these
branches. Retain the raw denominator; revisit if callers or supported pin ranges
change. RGB-clear index semantics remain the separate deferred contract above.


## Default VFS metadata after 68eba79

The rewritten default backend only implements root stat for `/`; it no longer
synthesizes mounted-child metadata or preserves a failed stat output buffer.
Existing root/missing-path regressions now exercise public vfs_stat and check
success metadata or ENOTDIR, without imposing failure-buffer contents. Retired
the old direct-default-backend child-stat test: its callback-free child was
never a usable provider for public stat, which requires fstat. Do not call a
missing child callback just to cover the removed fallback. No CORE edits.

Hidden embedded mount navigation is a separate maintainer contract question:
68eba79 allows chdir while all embedded entries are hidden. Existing directory
listing assertions pass; two old rejection assertions remain named expected
failures pending confirmation whether hidden means invisible or inaccessible.


## Delayed-task fallback after atomic selection (68eba79)

Passing hosted coverage job39779207602 measures grbllib.c590-594 as uncovered.
The new task_get_due selects and returns tasks.delayed while leaving IRQs
masked; task_execute has no intervening callback before comparing that result
with tasks.delayed. Under the supported single-core ISR model the old fallback
search cannot be reached. Existing pending-IRQ insertion/cancellation controls
pass. Do not force a private queue change or violate the IRQ-mask contract to
hit this defensive search. Retain these lines in raw coverage, and revisit if
selection or supported concurrency changes.

## Remaining large extension gaps at exact68eba79 report

Coverage job39779207602 at harness97bb6aa measures17,185/17,684 executable
lines (97.18%) and11,928/13,754 branches (86.72%);499 lines remain. This is a
successful coverage job, while full compiler matrix readiness is separate.
The highest remaining regions still include unfinished wall-plotter homing,
unregistered I/O open-drain settings, unexposed settings metadata and the weak
unsupported rigid-tapping extension/macro path. Prior dispositions remain in
this TODO. Do not register inaccessible settings, forge private state or replace
an unimplemented motion extension solely to improve the number. Raw counts
retain all measured regions. Reuse the exact new gaps inventory under
build-asan/hosted39779207602/gaps.json for the next substantial batch, checking
already-written local follow-ups before authoring.


## RTU callback re-entry contract

**Source review:** 2026-10-22, clean68eba79. Blocking receive callbacks run after
poll releases spin_lock, and modbus_send_rtu explicitly rejects nested blocking
requests while is_blocking is set. Async receive/timeout/CRC callbacks instead
run while the poll spin_lock is held; a synchronous re-entry into modbus_send
would reach its while(spin_lock) before queuing. Confirm whether async callbacks
must defer sends to a foreground task, or direct nonblocking chaining is meant
to be supported. No watchdog/timeout placeholder or speculative assertion is
registered, and no confirmed bug is claimed without that callback contract.
Existing ordinary transaction, timeout/retry and deferred-send behavior remains
covered. Source evidence: modbus_rtu.c async callbacks around181/212/226 and
send's spin-lock wait around268. Revisit using the actual registered RTU stream
fixture and a bounded process if direct callback re-entry is supported.


## Settings-list N/A fallback cannot be reached by a valid plugin descriptor

**Reviewed:** 2026-10-22, clean68eba79. report.c450-452 prints N/A only when
setting->value is NULL. Public settings_register validates every descriptor's
value before linking its owner (settings.c2765). A null-storage plugin therefore
cannot reach that listing fallback. The new executable registration case proves
whole-owner rejection (neither setting is discoverable), corrected registration
and ordered reporting of both valid values. Do not mutate already registered
metadata or bypass settings_register to claim that fallback covered. Raw source
coverage retains the lines; no global-table reachability claim is made here.
Further registration branch coverage can extend the same scenario for missing
persistence/getter callbacks and invalid group/description metadata, rather than
adding duplicate aliases for each boolean guard.

## Legacy version repair and checksum repair are separate startup paths

**Resolved source distinction:** 2026-10-22, clean68eba79. The existing legacy
unrecognized-version tests exercise nvs_buffer_init's early repair when byte0
does not match SETTINGS_VERSION. That restores the record before settings_init
reads it, so it cannot cover the later settings.c3783 recovery report call.
This is not evidence of a gcov attribution error.

New boot_compat_2/boot_compat_10 checksum cases instead store a valid changed
calibration and valid version marker, verify the good record, corrupt one CRC
byte and verify checksum rejection. The normal boot then restores defaults,
reports the read failure and setting values, and persists a valid repaired
record. Shared fixture reuses the existing version-repair assertions; both old
and new fault types pass grouped sanitizers/strict. No private settings call or
alternate implementation is used. The next hosted report must establish the
measured line gain; current source review alone is not a percentage claim.


## Tool-table absence guards implied by earlier parsing

**Verified source review:** 2026-10-22, clean68eba79. The G43/G43.2 word parser
requires grbl.tool_table.n_tools before selecting Enable/ApplyAdditional
(gcode.c1678/1680). The later n_tools==0 rejection arms at2959/2971 therefore
cannot be reached with supported stable table metadata. The passing no-table
scenario tests the actual early rejection branches and preserves a dynamic
offset plus queued80step cut; it does not cover those later defensive lines.
Do not change table capacity from a callback mid-block or forge the private
modal block merely to reach them. Keep raw coverage and revisit if parsing or
the table-lifetime contract changes.

## Verified residual guards: VFS lookup/rename and virtual-parameter root

2026-10-22, CORE68eba7906ba60d66c8b55c4adc90cd5e85b5a828, compared with
source-locked hosted39801089848. These four lines remain in raw coverage.

- get_mount (vfs.c265-289) returns cwdmount for relative paths, and an existing
  mount or &root for absolute paths. Public unmount selects root/null filesystem;
  no public API removes root. Thus null-mount arms vfs_chdir474 and
  vfs_get_drive774 cannot run for valid path pointers.
- vfs_rename403 only permits backend success for equal source/destination mounts.
  Its later second-mount notification410 requires different mounts, contradicting
  that guard. Existing cross-mount rejection and same-mount notification tests
  exercise the meaningful contract.
- ngc_params.c169-171 initializes the virtual list with built-in _value and
  _value_returned nodes. No public API clears it; registration appends nodes.
  The empty-list assignment942 is unreachable. Existing multi-provider tests
  exercise append and lookup.

Do not force private state or create fake WILL_FAIL placeholders. Revisit these
source-proven guards if upstream lookup, rename or parameter lifecycle changes.
