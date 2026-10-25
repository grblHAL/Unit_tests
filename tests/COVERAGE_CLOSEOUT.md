# Functional coverage closeout — 2026-10-25

Coverage expansion stopped at the user's request. This is a handoff, not a claim
of 100% coverage or that every remaining branch is impossible to exercise.

## Last measured result

[Hosted run40121790962](https://github.com/petervanderwalt/Unit_tests/actions/runs/40121790962)
measured harness `ed5b142` against CORE
`b01f481072edecac33d5e40c25869359a5b3fa1f`:

| Measure | Covered / total | Coverage | Remaining |
|---|---:|---:|---:|
| Lines | 17,491 / 17,757 | 98.50% | 266 |
| Branch outcomes | 12,836 / 13,852 | 92.67% | 1,016 |

The last measured batch added eight branch outcomes and no lines. The prior
same-source batch also added eight outcomes and no lines. This is the diminishing
return behind stopping. Four later ordinary workflows are locally tested but
outside this measurement: permanent-idle-lock sender reset, queued G92 status,
laser-off hold/resume, and probe-selector status. No coverage gain is attributed
to them without a report.

Source/helper checks, GCC and coverage passed. Clang failed three existing
rigid-tapping regressions at the same CORE bounds fault; exact saved diagnostics
are documented in [KNOWN_BUGS](KNOWN_BUGS.md). The final matrix is not green.
Correct assertions remain, and assertions after a fatal fault remain unvalidated.
CORE was not changed and no source was excluded from the coverage denominator.

Final local delivery gate: **4,508 cases pass ASan/UBSan in152.20s**; strict
classification reports4,482 clean,25 known regressions and one exact known
sanitizer diagnostic, with zero unexpected failures or skips. Saved evidence:
`build-asan/final-closeout-{build,tests,summary}.log` and
`build-asan/final-closeout-results.xml`. No additional hosted run was dispatched
for the closeout; its new head has no hosted matrix verification.

## Unfinished or deferred functionality

- **Wall-plotter homing:** 56 missing lines. The public homing entry warns and
  returns false; unused homing helpers have no implemented supported workflow.
- **Polar homing:** four missing lines. Installed callbacks do not provide a
  completed public homing cycle. All polar/wall homing remains a maintainer TODO.
- **G76 main taper:** four missing lines across G-code and motion control.
  Geometry/behavior remains deferred; parser-only calls cannot validate it.
- **Modbus registry/configuration stubs:** three missing lines in the unfinished
  public implementation. Existing normal RTU/ASCII/TCP transactions remain tested.
- **Disabled settings:** auxiliary open-drain registration and timezone settings
  are commented out. Several associated getters/setters/availability arms have
  no published setting ID. Enable/define these upstream before testing the paths.

## Other limits of the current supported test surface

- **Earlier guards prevent entry.** Parser validation, valid setting/type tables,
  allocation ownership and native dispatch exclude many private default/error
  arms. Calling private functions with invented enums would add a percentage,
  not an actual-use regression.
- **Homing contracts remain open.** Zero locate-feed behavior, standalone internal
  ganged-motor homing, and several delta reference/precondition paths need a
  supported configuration or maintainer decision.
- **Alarm ordering remains unresolved.** Protocol startup's pending-alarm path
  and motion-cancel's pending-alarm path have no demonstrated ordinary producer
  sequence. These are unproven routes, not universally unreachable code.
- **Filesystem/backend contracts.** Read-only embedded/device directory stubs,
  unavailable mount/handle combinations and a non-UART device naming fallback
  lack a supported owner/provider workflow. Native file/reader pairing and
  exclusive RAM-file ownership rule out some other fallback arms.
- **Startup/no-op hooks.** Empty weak board/plugin hooks have no output to assert;
  failed-startup task filtering discards a detailed private diagnostic before it
  can execute. Scheduler fallback mutation would require an unsupported sequence.
- **Platform-specific behavior.** One analog-PWM narrowing path is exercised on
  Windows; Linux's wider fast integer does not take that path at the same value.
- **Known firmware defects/policy TODOs.** Tapping bounds faults, sleep from an
  initial alarm, storage warning/retry policy and other documented regressions
  retain correct tests and narrow exceptions. A green wrapper is not a firmware fix.

The remaining branch inventory is broader than these line gaps: short-circuit
operands, loops, compiled configurations, unreachable defaults and still-unreviewed
outcomes all contribute. It has **not** been proved that all1,016 are uncoverable.

## Exact follow-up references

- [Line inventory](COVERAGE_LINE_INVENTORY.csv): all266 measured missing lines,
  with source location, disposition and evidence. Historical proofs are labelled.
- [Branch inventory](COVERAGE_BRANCH_INVENTORY.csv): all1,016 measured missing
  outcomes, preserving function/source-block/branch identities.
- [Detailed coverage notes](COVERAGE_GAPS.md): source/caller proofs and limits.
- [Maintainer TODOs](TODO.md): unfinished implementation and undecided contracts.
- [Known defects](KNOWN_BUGS.md): correct regressions and exception cleanup rules.

Resume only when there is a concrete supported workflow, an implemented feature,
a clarified contract or an upstream fix. Do not manufacture states, expand tests
with dummy permutations, or repeat audits merely to approach 100%.
