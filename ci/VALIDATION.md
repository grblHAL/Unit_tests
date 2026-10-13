# CI design validation

2026-10-13, branch `ci-source-selection` (separate from paused coverage work).

- No gitlink or `.gitmodules` on this branch; source directories are ignored.
- Twenty CI helper tests pass, including fork PR resolution,
  independent plugin/core locking, unknown suites, dirty checkout preservation,
  path escape rejection and immutable fetch arguments. Reporting tests also
  verify custom suite manifests, rejection of unknown sanitizer warnings and
  plugin-only coverage inventories.
- `actionlint` passes both workflows and both caller templates.
- A fresh clone resolved/fetched upstream master at
  `ca26fc98f1b2171251c946ab91d5912b733efa78` without submodules.
- Representative parser and settings CRC tests passed under Windows Clang
  ASan/UBSan from that fresh ordinary checkout, with strict summary passing.
  This is a pipeline smoke check, not evidence that the complete suite passes
  against the newer core. Use the hosted GCC/Clang/coverage results for that.
- First hosted run: https://github.com/petervanderwalt/Unit_tests/actions/runs/38352941636
  Source resolution passed. GCC, Clang and coverage completed with build
  failures. All jobs correctly reached selected-source configuration/build.
- The full local fresh-checkout build reproduces errors in current core's
  `stepper2.h`: undeclared ceilf/sqrtf/fabsf/lroundf when included by secondary
  stepper fixtures. Representative parser/settings smoke tests pass, but the
  complete latest-core suite has not passed. This is a source/header integration
  failure exposed by selecting newer core, not grounds for excluding those tests.
  Core was not patched. Hosted annotations confirm build failures; hosted logs
  should be consulted before asserting every compiler failed for identical causes.
- Caller installation in upstream core/plugins remains Terje's deployment step.
  Plugin caller is a template until actual plugin fixtures/tests are registered.
- Existing historical core regressions may be fixed in current upstream, which
  intentionally produces cleanup failures rather than silently passing them.

README verification identified and corrected an extra positional diagnostics
argument in `run_suite.py`. `summary.py` now accepts explicit diagnostics,
source inventory and suite-name options; existing two-argument invocations
retain core defaults. Reusable jobs run all 20 helper/reporting regressions.
The original hosted run predates this reporting correction; its build failures
remain separate from the corrected summary invocation.

Actionable-reporting checks verify that changed known regressions link to the
recorded harness's known-bug file and give precise cleanup guidance, ordinary
failures give reproduction/contract-review guidance, and missing coverage files
are flagged without claiming they are newly added code. No changed-line coverage
comparison is implemented; that needs an explicit source baseline.

## Merged-PR follow-up: ci-core-compatibility

2026-10-13, based on upstream master `6a5dada` after PR #2 merged.
Failed upstream run 38354097113 logs confirmed `task_execute` linker failures
in standalone limits tests for GCC, Clang and coverage.

The follow-up supplies a fail-on-unexpected-call scheduler mock for isolated
limits cases, adapts the real scheduler wrapper to its old state/new wait API,
installs valid host foreground hooks, connects homing ISR simulation to both
hooks, and provides math declarations for secondary-stepper header consumers.
Modbus tests invoke the new public reset API where available and verify actual
transaction integrity rather than obsolete callback counts/version numbers.
Critical-alarm checks retain actual hard-limit/critical-lock assertions while
supporting callback-context changes. Timer fallback checks verify polling/output.

The finite-move regression now passes with exactly ten pulses/position ten.
Its expected-failure block and resolved bug entry were removed; assertions stay.
Fix verified in core `ca26fc98f1b2171251c946ab91d5912b733efa78` on 2026-10-13.
The unchanged Modbus null-descriptor defect was reconfirmed at line 1291; its
matcher accepts only verified lines 1225/1291 plus the original strict diagnostic.
Exception documentation anchors were rechecked after cleanup.

Full Windows Clang ASan/UBSan and strict summary: 2,242 tests, 2,141 clean passes,
46 passes with known sanitizer diagnostics, 55 known regressions reproduced,
zero unexpected failures, zero skipped. Evidence in local workspace scratch:
`ci-compatibility-verified-tests.log` / `ci-compatibility-verified-summary.log`.
Nine representative compatibility cases also passed on historical core 451a539.
CI helpers: 20 passing; workflow actionlint passes. Core source was not patched.
Hosted compiler/coverage validation for this follow-up is pending publication.

## Terje's October 13 fixes

Branch `ci-terje-fix-validation`, based on merged upstream harness `63323b5`,
was validated against `terjeio/grblHAL_core` revision
`4b128e68bc63f9a3af11a01a7d8fbb5d5ccc98aa`. Core source was not patched.

- Full Windows Clang ASan/UBSan: **2,242 tests; 2,221 clean passes, 21 documented
  known regressions, zero unexpected failures, zero skipped**. Strict summary passes.
- 44 obsolete expected-failure registrations and all four recovering sanitizer
  manifest entries were removed. Five resolved diagnostic wrappers were deleted;
  compile and executable regressions now run normally.
- Tool callbacks support the new persistence flag. Fixtures model validated tool
  copies, cached tool reload, driver startup, foreground synchronized I/O, valid
  check-mode behavior, alarm callbacks and expanded status-report bits.
- Remaining VFS close and embedded seek memory defects were reproduced with
  strict diagnostic matching. Nine existing laser/tool cases expose two newly
  confirmed defects, documented with source and cleanup links in KNOWN_BUGS.md.
- CI helper tests: 24 passing, including rejection of unrelated sanitizer faults.
  Workflow actionlint passes.

Evidence: workspace scratch `terje-tests-verified.log`,
`terje-results-verified.xml`, `terje-summary-verified.log`. Hosted GCC, Clang and
coverage validation is requested against the same exact candidate source.
The default upstream core may not yet contain these fixes; older-source failures
are genuine regressions against the retained correct expectations.
