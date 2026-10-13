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
