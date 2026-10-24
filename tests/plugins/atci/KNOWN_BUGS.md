# M-code dispatch contract correction - 2026-10-25

No confirmed command-disable defect remains in this fixture. CORE gcode.c2349-
2355 records consumed user words and4494 restores them before execution. The old
host helper passed cleared validation flags straight to execute, creating a false
M960 P0 failure. The helper now models consumed-word restoration; original
assertions and production code remain unchanged. Remove the obsolete exact
WILL_FAIL/known_bug entry. This is a harness repair, not an upstream source fix.

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
