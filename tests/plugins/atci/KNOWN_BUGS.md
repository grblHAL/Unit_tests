# Known regression - 2026-10-24

ATCi source671f145530ec8ec9f5828897477dc0192593b3d8.
command_disable executes the documented M960 P0 using the actual registered
check -> validate -> execute path. Validation clears block.words.p; execution
then tests that cleared flag, so the disable request is replaced by usage text
and keepout remains active. Correct assertion requires an inside target to become
allowed after disabling. Keep it; upstream should retain parameter presence for
execution or inspect the validated value instead of the consumed word flag.
Remove only the exact WILL_FAIL/known_bug label and entry once repaired. No
sanitizer diagnostic allowance.

# Scope and unresolved integration

Eighteen four-axis cases execute original code with real CORE types. Registered
persistent settings, M-code and travel callbacks are used; planner position,
GPIO reads, NVS and delayed polling are explicit host boundaries. BOARD_LONGBOARD32
selects the source's supported guard, but logical AUXINPUT IDs in the host header
do not compile or validate a physical LongBoard pin map/SDK. Scenarios check
keepout intersections, clipping from four sides, boundary tolerance, untouched
other-axis coordinates, rack/macro transitions, reports and persistence. No
private plugin state is forced. Actual parser/planner/controller jobs and motor
safety are not established by these tests.

Original clipping returns immediately after modifying a blocked target, so native
apply_travel_limits is not chained in that path. The first draft's exact prior-
callback count assumed a contract not yet established; it was removed while all
coordinate assertions were retained. Unrestricted-path chaining has its own
control. Confirm full native envelope handling with CORE integration before
classifying the clipped-path contract. Clang's original set-but-unused global
warning stays visible/nonfatal only for this source; fixtures remain strict.
