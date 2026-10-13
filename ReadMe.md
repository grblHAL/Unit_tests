# Unit tests for the grblHAL core

[![Core tests](https://github.com/petervanderwalt/Unit_tests/actions/workflows/tests.yml/badge.svg?branch=master)](https://github.com/petervanderwalt/Unit_tests/actions/workflows/tests.yml)

Host tests compile actual source from the pinned `core` submodule. No CNC
controller is needed. Each new behavior lives in `tests/cases/<module>/<case>.c`
and appears individually in CTest and GitHub Actions. Shared mocks live in
`tests/support/`; unexpected mock calls fail explicitly.

## Known issues

[Pending core features](tests/TODO.md) lists functionality not fully added yet.

[Known core defects](tests/KNOWN_BUGS.md) lists each confirmed defect and the date
it was marked known.
Their labelled regressions reproduce the defect; they are not counted as ordinary
passes in the Actions summary. A fixed core forces review of each exception.
Recovering sanitizer errors are also checked: the narrow
[known diagnostic manifest](tests/known_sanitizer_diagnostics.json) links to the
defect and removal instructions. Affected assertion passes are shown separately;
unrecognized sanitizer diagnostics fail the reporting step.
Feature compile regressions also check configurations where a known upstream
build defect prevents runtime tests.

## Run locally

Install CMake, Python 3 and GCC or GNU-compatible Clang for the full suite.
Visual Studio's MSVC runs only the standalone modules: other core headers use
GNU extensions and are explicitly skipped. A portable llvm-mingw compiler works
on Windows without installing or changing the system toolchain.

For a Windows GNU-compatible Clang/Ninja build:

```powershell
cmake -S . -B build-clang -G Ninja -DCMAKE_C_COMPILER=C:/path/to/llvm-mingw/bin/clang.exe -DCMAKE_BUILD_TYPE=Debug
cmake --build build-clang --parallel
ctest --test-dir build-clang --output-on-failure --output-junit results.xml
python scripts/summary.py tests build-clang/results.xml
```

For sanitizers, add `-DENABLE_SANITIZERS=ON` to configure. On Windows, put the
compiler's `bin` directory on `PATH` so its sanitizer DLL can load.

```sh
git clone --recurse-submodules https://github.com/petervanderwalt/Unit_tests.git
cd Unit_tests
# For an existing checkout:
git submodule update --init --recursive
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug --parallel
ctest --test-dir build -C Debug --output-on-failure
```

Checks remain active in Release builds; they do not depend on C `assert()`.
The existing `src/driver.c` firmware entry point is not part of the host tests.

## Test branches, forks and PRs in Actions

Open Actions > Core tests > Run workflow. Select the test-suite branch and inputs:

| Candidate | source_repository | source_ref | source_pr |
|---|---|---|---|
| Pinned baseline | blank | blank | blank |
| Upstream branch/tag/commit | blank | branch, tag or SHA | blank |
| Upstream PR, including fork PR | blank | blank | PR number |
| Fork branch | `owner/core` | branch or SHA | blank |

PR runs test the head commit, not a synthetic merge. Selection resolves once to
an immutable SHA used by GCC, Clang and coverage. The source job summary and
`source-lock` artifact record the actual repository and SHA. Ordinary pushes and
test-repository PRs use the baseline. The submodule pin is unchanged.

```sh
gh workflow run tests.yml --repo petervanderwalt/Unit_tests --ref initial-batch-part-2 -f source_pr=123
gh workflow run tests.yml --repo petervanderwalt/Unit_tests --ref initial-batch-part-2 -f source_repository=yourname/core -f source_ref=my-fix
```

Replace example numbers/names. Dispatch requires write access to the test repo.
The workflow must exist on the default branch for manual dispatch: merge these
workflow changes there before relying on the new inputs. The selected test branch
supplies tests and exceptions independently of the core candidate. Fixed known
regressions still force cleanup of their documented exceptions; use a test branch
with that cleanup to obtain a clean candidate result.

### Automatic upstream triggers

Upstream pushes/PRs do not automatically trigger this test repository. An upstream
workflow or GitHub App can call the workflow-dispatch API for `tests.yml`, passing
`source_repository` and `source_ref` with the upstream event's exact commit SHA,
or passing `source_pr`. This needs permission to dispatch in the test repository;
an upstream repository's ordinary GITHUB_TOKEN does not grant cross-repository
write access. No upstream workflow, credential or PR status publisher is installed
by this change. Candidate jobs have read-only permissions and do not retain
checkout credentials. A fix only needs publishing to your fork, not upstream.

### Plugin extension strategy

[ci/suites.json](ci/suites.json) registers source repositories, checkout paths and
coverage filters; core is currently the only implemented suite. The Plugins repo
is an overview: register each plugin's actual source repository when its tests
are added, alongside suite-specific host fixtures/build configuration.

Resolve core and plugin revisions independently: plugin PR plus pinned core,
then optionally plugin PR plus candidate core. Extend the source lock to contain
both immutable SHAs and have every job consume that same lock. Add suite-specific
coverage filters/artifact names and scope defect allowances to the relevant suite.
Do not count plugin code as core coverage. Plugin testing is a next phase, not
implemented by registering source metadata alone.

## Update core and retest a fix

The submodule records the reproducible default baseline. Candidate CI runs can
test published branches, forks, commits and PR heads without changing this pin
or merging upstream. Local builds also test uncommitted changes in `core`.
Updating the recorded baseline is a separate decision after reviewing a revision.

### Select the core commit to test

From the root of this test repository, check for local changes before switching
core revisions. Preserve any unfinished core changes first.

```sh
git status --short
git -C core status --short
git -C core fetch origin
git -C core checkout <fixed-core-commit>
git -C core rev-parse HEAD
git diff --submodule=log -- core
```

Replace `<fixed-core-commit>` with the actual published commit hash. Checking out
that hash leaves the submodule at a detached HEAD, which is normal when testing a
specific revision. The parent repository now shows `core` as modified; it records
the new hash only when you stage and commit that submodule change.

### Run the tests before changing exceptions

Use a sanitizer build, including the summary check. For Windows llvm-mingw,
replace the compiler path below with your installation and put its `bin`
directory on `PATH` as described under [Run locally](#run-locally).

```sh
cmake -S . -B build-asan -G Ninja -DCMAKE_C_COMPILER=C:/path/to/llvm-mingw/bin/clang.exe -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON
cmake --build build-asan --parallel
ctest --test-dir build-asan --output-on-failure --output-junit results.xml
python scripts/summary.py tests build-asan/results.xml
```

On Linux, use `-DCMAKE_C_COMPILER=clang` or `gcc` instead. If an existing build
uses another compiler or generator, use a new build directory. Reconfigure after
changing exception registrations so CTest picks up the changes.

A fixed assertion regression may initially appear as a CTest failure because its
`WILL_FAIL` exception expects the executable to fail. Confirm the executable now
passes its correct assertions; do not change those assertions to match the old
bug. For one test, inspect its output with:

```sh
ctest --test-dir build-asan -V -R '^utf8\.ascii$'
```

Replace `utf8.ascii` with the test name listed in the defect entry. Run the full
suite as well: a core update can affect more than the defect being fixed.

### Remove the fixed defect's exceptions

Start with its entry in [tests/KNOWN_BUGS.md](tests/KNOWN_BUGS.md). Each entry
links to the affected tests and says exactly which exception registrations or
scripts need cleanup. Depending on the defect, cleanup is in these places:

- **Wrong result / expected assertion failure:** remove the matching complete
  `if(TEST ...) ... endif()` block from
  [tests/known_bugs.cmake](tests/known_bugs.cmake). This removes `WILL_FAIL` and the
  `known_bug` label, making the test an ordinary passing test.
- **Correct result with an undefined-behavior warning:** delete every JSON object
  with that defect's `issue` identifier from
  [tests/known_sanitizer_diagnostics.json](tests/known_sanitizer_diagnostics.json).
  These exceptions are documented in `KNOWN_BUGS.md`, but the actual warning
  allowance is stored in this JSON file. One defect can have several objects.
  For example, the tool-table getter defect has two objects with
  `"issue": "tool-table-index-getter-callback-signature"`. Keep valid JSON after
  deleting them. The summary must then report those tests as clean passes.
- **Memory defect checked by a diagnostic wrapper:** follow the defect's linked
  instructions to replace its special Python-wrapper registration in
  [CMakeLists.txt](CMakeLists.txt) with a normal executable test. Remove the
  matching exception in `tests/known_bugs.cmake` and any obsolete matcher. The
  executable must pass under sanitizers without relying on the old diagnostic.
- **Feature configuration that previously could not compile:** replace the
  linked diagnostic-matching compile check with a normal successful compile
  check for that configuration. Remove its expected-failure registration and
  obsolete matcher, following the links in the defect entry.

**Keep the regression test** means keep its file in `tests/cases/` and its check
for the correct behavior. For example, `tests/cases/utf8/ascii.c` must continue
checking that `A` encodes as byte `0x41` after the encoding bug is fixed. The test
then guards against a future change reintroducing that bug. Delete the exception
that tolerates the bug, rather than deleting the test that catches it.

After removing the exceptions, reconfigure, rebuild and rerun the full sanitizer
suite and summary using the commands above. All affected tests must be ordinary
clean passes. Also run the coverage build under [Measure coverage locally](#measure-coverage-locally).
Do not weaken expectations or broaden diagnostic allowances to make an update green.

### Remove the known-bug entry and commit

Once the fix passes without its exceptions, delete the entire resolved defect
section from [tests/KNOWN_BUGS.md](tests/KNOWN_BUGS.md). That file lists outstanding
defects only. Put the fix date and core commit in the Git commit message, where
history preserves them. If only part of a multi-test defect is fixed, retain an
entry covering the remaining failures and their exceptions.

Check that remaining documentation links still point to the correct exception
blocks and source lines; deleting blocks can shift line numbers. Refresh any
remaining diagnostic source-line matches if upstream edits moved them, after
confirming the same defect still reproduces.

```sh
git diff --check
git diff --submodule=log
git add core
```

Stage the documentation, exception and registration files you actually changed
as well. Commit the new core pin and its cleanup together, then push and verify
both GCC and Clang sanitizer jobs and the coverage job in GitHub Actions. If the
new core introduces an additional defect, add a separate correctly expected
regression and dated known-bug entry; do not silently waive it.

## GitHub Actions

`.github/workflows/tests.yml` runs on pushes, pull requests and manual dispatch.
GCC and Clang run the tests with address/undefined-behavior sanitizers. A separate
GCC job publishes HTML and XML coverage as an Actions artifact. Coverage describes
the instrumented modules in this configuration. The summary lists every core source file, including gaps. No token or external service is needed.

## Measure coverage locally

Use a separate coverage build without sanitizers. Install the same reporter as CI:
`python -m pip install gcovr==8.4`.

```sh
cmake -S . -B build-coverage -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DENABLE_COVERAGE=ON
cmake --build build-coverage --parallel
ctest --test-dir build-coverage --output-on-failure
gcovr --merge-mode-functions=separate --root . --filter 'core/.*\.c$' --html-details coverage.html --xml coverage.xml --print-summary build-coverage
python scripts/summary.py coverage coverage.xml
```

For GNU-compatible Clang, select `clang` (or its full Windows path) when configuring
and add `--gcov-executable "C:/path/to/llvm-mingw/bin/llvm-cov.exe gcov"` to gcovr.
Open `coverage.html` to inspect uncovered lines and branches. For a fresh measurement,
use a new build directory so old execution counts cannot carry over.

The host variants currently exercise the default configuration, legacy protocol
compatibility level 1, NGC expressions, non-modal lathe U/V/W commands with NGC expressions, cutter-compensation parsing and plugin interfaces, G187 acceleration profiles, jerk acceleration with and without G187 profiles, coordinate rotation with NGC expressions, spindle synchronization with simulated encoder feedback,
CoreXY, polar, wall-plotter, delta and five-axis RTCP kinematics, backlash
compensation, four-axis asymmetric ganging with and without auto-squaring,
the eight-axis maximum, six-axis UVW remapping, and three registered spindles
with two active spindle slots, a four-slot persistent tool table with and without NGC expressions, optional spindle PWM linearization, and enabled PID logging. All variants run in one
CTest suite; coverage merges their executed source lines. Compatibility levels
2 and 10 currently have linked compile regressions in [Known core defects](tests/KNOWN_BUGS.md#legacy-compatibility-reporting-does-not-compile) because the pinned
core cannot compile their coordinate report. The `separate` function
merge mode retains functions compiled at different locations under feature guards. Other feature combinations
still need tests. A green suite or a covered module does not establish full coverage;
use the source-by-source coverage table to choose the next behavior to test.

## Add tests incrementally

1. Add isolated modules and boundary/error cases first (string utilities, parsing
   helpers, expressions). Compile their original `.c` files; do not copy functions.
2. Introduce a small mock HAL for settings/NVS, streams, spindle and coolant.
   Record calls and inject failures, without claiming hardware timing coverage.
3. Test G-code parsing with accepted/rejected commands, modal state and units.
4. Test planner geometry, limits, queued blocks and feed calculations.
5. Add protocol/state-machine sequences: reset, hold/resume, alarms and probing.
6. Add representative axis/feature configurations and hardware integration tests.

Create `tests/cases/<module>/<case>.c`; CMake discovers each case automatically.
Add module dependencies in `add_core_test()` when needed.
Each regression should name the triggering input and check the expected behavior.
Avoid tests that merely reproduce the implementation. Keep commits to the core
submodule deliberate: `git -C core fetch`, check out the desired revision, rerun
tests, then commit the updated submodule pointer here.

PID tests currently specify existing sample-rate behavior. Deadband and
`p_max_error` are not asserted as supported features; the implementation does not
apply them. Zero sample rate needs an upstream-defined contract before testing
an expected result.
