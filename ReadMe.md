# Unit tests for the grblHAL core

[![Core tests](https://github.com/grblHAL/Unit_tests/actions/workflows/tests.yml/badge.svg?branch=master)](https://github.com/grblHAL/Unit_tests/actions/workflows/tests.yml)
[![Core line coverage: 98.05%](https://img.shields.io/badge/core_lines-98.05%25-brightgreen)](https://github.com/petervanderwalt/Unit_tests/actions/runs/39859126742)
[![Core branch coverage: 88.53%](https://img.shields.io/badge/core_branches-88.53%25-green)](https://github.com/petervanderwalt/Unit_tests/actions/runs/39859126742)

Coverage badges show a verified successful report, not a live measurement of
every source revision. Click either percentage for its run and coverage artifact.
They cover the core across the tested configurations; they do not include board
drivers or plugins. When updating the badges, use the line and branch totals in
`coverage.xml` from a fully successful run, and update both run links together.

Host tests compile actual source from an ordinary `core` checkout. No CNC
controller is needed. Each new behavior lives in `tests/cases/<module>/<case>.c`
and appears individually in CTest and GitHub Actions. Shared mocks live in
`tests/support/`; unexpected mock calls fail explicitly.

## Known issues

[Known coverage gaps](tests/KNOWN_BUGS.md#known-coverage-gaps) explicitly tracks
unimplemented and unreachable regions, their source evidence and what would make
them testable. They remain uncovered in the measured totals; placeholder failures
do not count as code coverage.

[Pending core features](tests/TODO.md) contains the detailed implementation and
contract questions.

[Known core defects](tests/KNOWN_BUGS.md) lists each confirmed defect and the date
it was marked known, with suggested core fixes and validation/exception-removal
guidance. Suggestions are proposals until tested against the selected core revision.
Their labelled regressions reproduce the defect; they are not counted as ordinary
passes in the Actions summary. A fixed core forces review of each exception.
Recovering sanitizer errors are also checked: the narrow
[known diagnostic manifest](tests/known_sanitizer_diagnostics.json) links to the
defect and removal instructions. Affected assertion passes are shown separately;
unrecognized sanitizer diagnostics fail the reporting step.
Fatal ASan regressions may use a named `known_crash` wrapper with exact test,
source line, top frame and fault matching. For GCC NULL calls that omit the CORE
frame, the inventory instead requires PC zero and the exact captured harness
caller chain. They appear as known reproductions;
assertions after the crash did not run. The wrapper retains full process output
in `build/known-crash-<test>.log`. Fixes, changed/additional faults and runner
errors fail and require exception review. Non-sanitizer builds retain direct tests.

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
git clone https://github.com/grblHAL/Unit_tests.git
cd Unit_tests
python scripts/resolve_source.py
python scripts/prepare_sources.py
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug --parallel
ctest --test-dir build -C Debug --output-on-failure
```

Checks remain active in Release builds; they do not depend on C `assert()`.
The existing `src/driver.c` firmware entry point is not part of the host tests.

## Source selection and upstream CI

There are no tracked submodules. [ci/suites.json](ci/suites.json) is a small JSON
registry of suites, source repositories/default branches, dependency suites,
CMake configuration, test selection and coverage filters. The core default is
`grblHAL/core` at `master`. Nothing requires updating commit hashes in this repo.
Current-source runs can reveal new build incompatibilities as well as assertion
failures; an older suite does not promise a green result against new code.
Each run resolves branches to exact SHAs once, records them in `source-lock.json`,
and uses that same lock in all jobs. Test-harness source is also locked once.
A rerun against moving master can select newer code; use an archived SHA for an
exact reproduction. The historical coverage snapshots describe their recorded
core revision, not today's upstream master.

In Actions > Core tests > Run workflow, select the test-suite branch and inputs.
The repository field accepts `terjeio/grblHAL_core` or
`https://github.com/terjeio/grblHAL_core` (a trailing `/` or `.git` is accepted).
Put a branch, tag or commit SHA in the separate ref field:

Manual runs show the selected source in the Actions list immediately, for example
`Core tests: terjeio/grblHAL_core @ master` or
`Core tests: grblHAL/core @ PR #1037`. A supplied SHA appears in place of the
branch. The title shows the requested source; the source-lock artifact records
the exact resolved commit. Repository URLs are displayed as entered.

| Candidate | source_repository | source_ref | source_pr |
|---|---|---|---|
| Current upstream core | blank | blank | blank |
| Upstream branch/tag/commit | blank | branch, tag or SHA | blank |
| Upstream PR, including fork PR | blank | blank | PR number |
| Fork branch | `owner/core` | branch or SHA | blank |

PR selection tests the head commit, not a synthetic merge. Source summaries and
artifacts identify the repository, source SHA and harness SHA. Manual dispatch
requires the workflow on the default branch and write access to this test repo.

```sh
gh workflow run tests.yml --repo grblHAL/Unit_tests --ref master -f source_pr=123
gh workflow run tests.yml --repo grblHAL/Unit_tests --ref master -f source_repository=yourname/core -f source_ref=my-fix
```

### Read a failed run

Open the **CI diagnosis** job summary first. It groups matching GCC, Clang and
coverage findings and shows the first useful compiler error or test diagnostic,
source links, affected jobs and a focused CTest reproduction command. Numeric
expected/actual values are shown when the test emits them; otherwise the report
shows its failing expression. New tests should print the triggering input and
measured versus expected values when an assertion alone is ambiguous. Full command
logs and JSON findings are in the `report-<suite>-<job>` artifacts; individual
JUnit results and coverage HTML remain available in the existing artifacts.

Unexpected assertion/sanitizer failures are suspected regressions until their
contract and fixture are checked. A changed known regression links to its cleanup
instructions: it may be a fixed regression, but a different crash is not a fix.
Setup/build failures are reported even when tests never execute. Missing reports
and failed jobs cannot produce a successful diagnosis.

After a successful configure, independent build targets and all registered tests
are attempted even if some targets fail to build. Unbuilt tests remain explicit
failures; no registrations or source regions are excluded. Download annotated HTML/XML
from the coverage artifact to investigate remaining gaps. Its HTML title and job
summary mark the data as **partial coverage**: crashed or aborted tests may not
flush their counters or reach later assertions. The run stays failed. Partial
results are not a passing baseline, and changed-code coverage assessment waits
for a successful build and test run. Fix the reported failures before drawing conclusions
about newly added code without tests.

Changed-code coverage is a **warning**, not a required coverage threshold. A source
PR automatically supplies its base repository and SHA. The upstream caller templates
supply the PR base or the previous source commit for pushes. For a branch/SHA run,
provide an explicit baseline:

```sh
gh workflow run tests.yml --repo grblHAL/Unit_tests --ref master \
  -f source_repository=yourname/core -f source_ref=my-fix \
  -f source_base_repository=grblHAL/core -f source_base_ref=master
```

Both revisions are resolved once. Coverage compares the candidate with their Git
merge base and lists added executable C lines with zero hits. Covered feature
variants are combined before checking hits. Changed C files absent from coverage
are listed separately: check CMake inclusion and feature flags before concluding
that tests are missing. This assessment covers the selected suite's coverage
filter; it does not establish test quality, header/configuration coverage or full
coverage of all dependencies. Without a baseline, coverage data, or reachable
history, the report explicitly says changed-code coverage was not assessed.

### Which revision gets tested?

There are two independent selections:

- **Test harness:** this repository's tests, fixtures, workflows and exception
  inventory. The caller selects it with `harness_repository` / `harness_ref`.
- **Source under test:** core or plugin code. The caller passes the push/PR SHA;
  manual runs can select a branch, tag, commit or PR number.

A core PR does not need a commit in this test repository. A fork PR does not
need merging into upstream core. Once the caller is installed, pushing another
commit to that PR starts another upstream run automatically. The caller tests
PR head code; it does not test GitHub's synthetic merge commit. To check a merge
candidate explicitly, provide its published SHA in a manual run.

GitHub's **Re-run jobs** retains the upstream caller event SHA, but source defaults
and branch-based dependencies are resolved again if the source-resolution job
reruns. For exact reproduction, use the saved source SHAs and harness SHA.

### Caller installation for Terje

[ci/callers/core.yml](ci/callers/core.yml) is the complete core caller. After this
branch is published, copy it to `.github/workflows/host-tests.yml` in core.
It calls [reusable-tests.yml](.github/workflows/reusable-tests.yml) on pushes,
PRs and manual runs, passing the PR head repository/SHA for fork PRs and the
pushed commit otherwise. GCC, Clang and coverage run as jobs of the upstream
workflow, so results appear on the upstream PR itself. No dispatch token,
webhook or write-back status bot is needed.

The caller explicitly identifies the test harness because a reusable workflow
inherits the caller's GitHub context: a bare checkout would fetch core instead
of this repository. Keep its `uses` ref and `harness_ref` on the same reviewed
release tag or SHA; the supplied branch ref is for rollout testing. SHA pinning
the **test harness** is optional and separate from automatically testing each
new **source** commit. Publish a reviewed harness version before configuring
required PR checks. Enable Actions/reusable-workflow access in the upstream repo;
GitHub may require approval for first-time fork contributors. Use `pull_request`,
not `pull_request_target`, and do not pass inherited secrets. Candidate source
runs only on hosted runners with read-only contents permission; fetch credentials
are not persisted. These templates target public source repositories.

### Install and verify the core caller

1. Review/publish this CI branch in the chosen public test-harness repository.
   For the initial rollout, the supplied caller uses
   `grblHAL/Unit_tests` at `master`.
2. Copy [ci/callers/core.yml](ci/callers/core.yml) into the core repository as
   `.github/workflows/host-tests.yml`. If hosting the harness elsewhere, update
   both `jobs.core.uses` and `harness_repository`; keep `uses` and `harness_ref`
   on the same harness version. No Personal Access Token is needed.
3. Commit the caller on a core branch and open a PR. Check its Actions run:
   the `source` job should record the PR head repository and commit, followed by
   GCC, Clang and coverage jobs. Compare the recorded SHA with the PR's latest
   commit, including a fork PR.
4. Push another commit to that PR and verify a new run tests its new SHA. Merge
   the caller so later core pushes and PRs receive the same checks.
5. Once the complete suite is passing for supported core and the chosen harness
   version, configure required checks using their actual names from the upstream
   run. Keep them optional while resolving existing compatibility/known-defect
   cleanup failures. Updates to the harness's tests can be deployed independently
   by advancing its branch/tag or updating the caller's reviewed harness version.

The workflow runs in the **core repository's Actions context**, consuming that
repository's runner allocation. Artifacts and logs live on that upstream run.
It does not create a separate run in this test repository or post a bot comment.

### Reusable workflow inputs

| Input | Purpose | Default |
|---|---|---|
| `harness_repository` | Repository containing these tests/workflows | Required |
| `harness_ref` | Harness branch, tag or commit | Required |
| `suite` | Key in the harness's source registry | `core` |
| `source_repository` | Candidate source repository, including a fork | Registry repository |
| `source_ref` | Candidate branch, tag or commit | Registry branch |
| `source_pr` | PR number in `source_repository`; cannot combine with `source_ref` | Empty |
| `core_ref` | Core dependency branch/tag/SHA for a plugin suite | Core registry branch |
| `run_label` | Unique artifact suffix for this invocation | `core` |

Manual **Core tests** exposes candidate repository/ref/PR inputs and optional
comparison-base repository/ref inputs. The upstream caller/reusable workflow
supports the full set. A different candidate
repository needs an explicit ref or PR number. Unknown suites and ambiguous
PR/ref combinations fail before building. Caller inputs are passed as data,
not evaluated as shell commands. Core-only calls should leave `core_ref` empty.

### Plugin and driver tests

Actions has separate manual **Plugin tests** and **Driver tests** workflows.
Choose an implementation suite, optional candidate repository/ref/PR, and
optional `core_ref`. Each run records both source revisions, runs GCC/Clang with
sanitizers, measures that implementation's code, and publishes its own test
results, known defects, diagnostics and coverage artifacts. **Core tests** remains
separate. New dispatch workflows become available after installation on the
repository's default branch.

| Workflow | Suite | Initial tested behavior |
|---|---|---|
| Plugin tests | `plugins_misc` | M220 feed override, M150 RGB, M280 servo |
| Plugin tests | `plugin_eeprom` | I2C EEPROM/FRAM page/block storage |
| Plugin tests | `plugin_fans` | Fan commands, shutdown, spindle links and reports |
| Driver tests | `driver_simulator` | Simulator EEPROM storage |
| Plugin tests | `plugin_openpnp` | Digital/analog I/O, ADC scaling, position reports and synchronization |
| Plugin tests | `plugin_odometer` | Pulse distance, elapsed/spindle time, EEPROM restart and reset backup |
| Plugin tests | `plugin_encoder` | Registered encoder ownership, override commands and persisted settings |
| Plugin tests | `plugin_spindle_vfd` | GS20/MODVFD commands, feedback, exceptions and EEPROM restart |
| Plugin tests | `plugin_sdcard_stream` | File input, stream ownership, error/reset recovery and external macro repeats |
| Driver tests | `driver_simulator_vfs` | File/directory workflows; current CORE compile incompatibility recorded |
| Plugin tests | `plugin_keypad` | I2C/UART jog commands, cancellation, overrides and NVS restart |
| Plugin tests | `plugin_networking` | Interface events/enumeration, status reports and service/MAC helpers with real lwIP headers |
| Plugin tests | `plugin_laser_ppi` | Registered laser PPI spacing, mode changes, shutdown and hardware delegation |
| Plugin tests | `plugin_laser_cluster` | LightBurn cluster expansion, acknowledgement suppression and stream/reset hooks |
| Plugin tests | `plugin_trinamic` | TMC2209 UART/settings/restart, dynamic current, warning polling and homing callbacks |
| Plugin tests | `plugin_plasma` | Materials/imports, EEPROM-backed mode boot, arc retry/loss and up/down height control |
| Plugin tests | `plugin_bluetooth` | HC-05 AT configuration, stream switching, settings and EEPROM restart |
| Plugin tests | `plugin_embroidery_readers` | DST/PES metadata and stitch decoding through real VFS reads |
| Driver tests | `driver_rp2040_flash` | Flash-copy behavior with simulated SDK/IRQ calls |
| Driver tests | `driver_esp32_nvs` | Partition storage, failures and realtime-handler restoration with simulated SDK calls |
| Driver tests | `driver_stm32f4_flash` | Flash read/write, erase retry and failure handling with simulated HAL calls |
| Driver tests | `driver_stm32f7_flash` | Flash read/write and halfword failure regression with simulated HAL calls |
| Driver tests | `driver_lpc176x_flash` | IAP storage, failures and IRQ restoration in a mapped host flash region |
| Driver tests | `driver_stm32h7_flash` | H743/H723 flash-word writes, tail padding and bank selection |
| Driver tests | `driver_stm32f1_flash` | Page erase/retry and halfword storage failure handling |
| Driver tests | `driver_stm32f3_flash` | Flash-size register geometry, page storage and halfword failure regression |
| Plugin tests | `plugin_auxp` | Digital output change reports and reset/chaining |
| Plugin tests | `plugin_interlock` | Forward/inverse spindle interlock requests and settings |
| Plugin tests | `plugin_pneumaseal` | Air-seal state, spindle and delayed-off lifecycle |
| Plugin tests | `plugin_thermistor` | ADC reports, calibration and thermal alarm requests |
| Plugin tests | `plugin_virtual_inputs` | Real CORE probe registration, virtual contacts, commands and reset |
| Plugin tests | `plugin_homingaccel` | Per-axis homing override requests, restoration, units and persistence |
| Plugin tests | `plugin_rgb_sienci` | Legacy/advanced RGB state, override, animation and tool-change callbacks |
| Plugin tests | `plugin_flexgpio` | I2C expander registration, packets, input edges and configuration |
| Plugin tests | `plugin_atci` | Keepout checks, jog clipping, rack sensors and M960 regression |
| Plugin tests | `plugin_mpg_transport` | Framed/plain stream data, acknowledgement, retry and reset behavior |
| Plugin tests | `plugin_webui` | Argument helpers and embedded assets via real CORE VFS; HTTP backends remain |
| Driver tests | `driver_imxrt1062_pwm` | Teensy 4.0/4.1/MicroMod PWM register, routing and ownership workflows |
| Driver tests | `driver_sam3x8e_serial` | Dual UART/USART queues, callbacks, settings and CORE stream suspend |
| Driver tests | `driver_tm4c123_eeprom` | Aligned EEPROM, CRC storage and transfer failures |
| Driver tests | `driver_ti_shared_eeprom` | Standalone TI shared EEPROM candidate and CRC regressions |
| Driver tests | `driver_tm4c123_serial` | Original UART0 queues, realtime dispatch and CORE stream suspend |
| Driver tests | `driver_msp432p_serial` | Primary UART queues and CORE stream lifecycle with real TI/CMSIS headers |

These are initial host tests, not full plugin/driver coverage or board validation.
Trinamic also locks and compiles the actual chip library; its UART device is
simulated. Plasma tests use real CORE I/O/secondary-stepper/spindle/VFS APIs
with simulated pins, time and controller state. Voltage regulation, full CORE
suspension and hardware timing remain separate work.
Bluetooth tests simulate HC-05 replies and STATE inputs while using real CORE
stream/I/O registration; radio and shared-MPG operation remain separate. Embroidery
reader tests compile Tajima/Brother modules; the job coordinator and physical
needle control remain untested. Networking locks upstream lwIP headers separately; its common-interface suite
does not start protocol listeners. Laser tests observe simulated driver pulses
and byte-stream transformations; no physical laser operation is established.
Driver SDK boundaries are simulated; no actual Pico SDK/ESP-IDF/STM32/NXP firmware
build or physical flash/interrupt timing is established. STM32 storage suites use 32-bit host targets. LPC keeps 32-bit physical flash
addresses with native-width RAM pointers. Linux jobs install multilib runtimes
only when the locked suite requests them. LPC's padded-source case does not establish safety
for a normal unpadded CORE allocation. Teensy PWM uses actual SDK register
headers with simulated memory and pin-mux lookup. SAM serial uses actual device/
Arduino headers and CORE streams with simulated clocks/NVIC/IRQ delivery. SDK
revisions are locked separately; these are not Arduino/ARM firmware builds. Keypad tests explicitly compare
signed/unsigned char builds; the observed extended-key defect is compiler-specific.
See [component progress](tests/COMPONENT_PROGRESS.md) and the
[repository backlog](tests/COMPONENT_INVENTORY.csv) for remaining work. Each suite
has its own `KNOWN_BUGS.md`; keep correct regression assertions when removing
expected-failure handling for an upstream fix.

The [plugins](https://github.com/grblHAL/plugins) and
[drivers](https://github.com/grblHAL/drivers) overviews are catalogues. Register
actual implementation repositories in `ci/suites.json`. Add a standalone CMake
project under `tests/plugins/<name>` or `tests/drivers/<name>` before adding its
suite to a workflow's choices. Unknown suites and zero selected tests fail.

For a local run in a fresh checkout:

```sh
python scripts/resolve_source.py --suite plugin_eeprom --core-ref CORE_SHA
python scripts/prepare_sources.py
python scripts/configure_suite.py --mode sanitizers --compiler clang
python scripts/build_suite.py
python scripts/run_suite.py test
python scripts/run_suite.py summary
```

Replace `CORE_SHA` with a real core commit, or omit `core_ref` to select the
configured default. Use a fresh checkout when switching locked sources: source
preparation preserves existing directories rather than overwriting them.
Host callbacks validate original component behavior against CORE interfaces;
complete board builds and electrical/timing behavior need separate SDK/hardware
checks. [ci/callers/plugin.yml.example](ci/callers/plugin.yml.example) remains
an upstream caller template; each invocation needs a unique `run_label`.

Simulator VFS currently fails to compile against CORE `b01f481` because its
`vfs_path_t` dependency was removed. Its separate reference run uses the
Simulator gitlink CORE `4ec1ae44b857a70d2f9298344feac4b43ed0eb6b`: select that
exact `core_ref` in a fresh checkout to reproduce it. There is no automatic
fallback. A passing reference run does not establish current-CORE compatibility.

The EEPROM suite also locks the actual littlefs dependency and tests a complete
format/write/unmount/remount/read workflow without touching the settings region.
Odometer, encoder and VFD suites also lock the actual EEPROM backend for
persistent storage. SD streaming uses real CORE VFS/stream modules with a
read-only host filesystem; it does not establish FATFS/SD hardware or littlefs
adapter compatibility. The latter currently fails its CORE API compile check.
Dependency-only registry entries use `source_only: true`: they are fetched at an
exact resolved revision and cannot be selected as test suites.

### Source registry fields and a future plugin example

The registry contains metadata, not source code or submodule commit hashes:

| Field | Meaning |
|---|---|
| `repository`, `ref` | Public source repository and default branch/tag |
| `path` | Ignored checkout directory inside this workspace |
| `dependencies` | Registered source entries to fetch, such as `core` or `littlefs` |
| `source_only` | `true` for a dependency checkout that has no selectable test suite |
| `cmake_source`, `cmake_options` | CMake project directory and configure arguments |
| `test_regex` | CTest names included in this suite; selecting zero tests fails |
| `coverage_filter` | gcovr file filter for this suite's measured code |
| `diagnostics_directory` | Directory with the suite's diagnostic exception inventory |

Example entry **after adding a real plugin host project and tests**:

```json
"example_plugin": {
  "repository": "OWNER/ACTUAL_PLUGIN_REPOSITORY",
  "ref": "master",
  "path": "plugins/example_plugin",
  "dependencies": ["core"],
  "cmake_source": "tests/plugins/example_plugin",
  "cmake_options": [],
  "test_regex": "^example_plugin[.]",
  "coverage_filter": "plugins/example_plugin/.*\\.c$",
  "diagnostics_directory": "tests/plugins/example_plugin"
}
```

These are placeholders, not an existing plugin suite. Its CMake project must
build the original plugin source against the fetched core and arrange host mocks,
CTest names and sanitizer/coverage instrumentation. `dependencies` fetches source;
it does not automatically link that source or run the dependency's entire suite.
The diagnostics directory must supply the manifest used by `scripts/summary.py`.
Register explicit additional dependencies if a plugin needs other repositories.
The current resolver supports the listed direct dependencies; it does not recurse
through arbitrary dependency graphs.

## Read results and reproduce a run

Expand the upstream **source** job summary to see the harness SHA and every
resolved source SHA. Download artifacts from that same run:

- `source-lock-<run_label>`: immutable source selections and suite configuration.
- `results-<run_label>-gcc` / `results-<run_label>-clang`: source lock, JUnit
  results and `LastTest.log`, with individual test names and failures.
- `coverage-<run_label>`: source lock, HTML/XML coverage and available test logs.

The result summary distinguishes clean passes, passes with known sanitizer
warnings, reproduced known defects, failures and skips.
Failed known regressions include a **see known bugs; it may be a fixed regression**
link to the tested harness revision, plus instructions to confirm the result,
retain the test, remove its precise exception and delete the resolved defect entry.
A different crash/failure must be investigated before declaring a fix. Ordinary
failures include reproduction and source-contract/fixture review guidance; intended
API changes need corresponding test updates rather than weakened assertions.
Coverage gaps include guidance to add behavioral tests or fix missing build/feature
instrumentation. The report does not claim a file is newly added or untested just
because it is missing from coverage; detecting newly uncovered additions requires
an explicit baseline diff, which is not implemented yet. A build failure is a
failed run even if no JUnit report could be produced; inspect the failed build
step first. Coverage percentages describe the selected suite/configurations.
A green core run does not establish plugin or physical-board coverage.

For an exact local reproduction, check out the recorded harness SHA in a fresh
clone, place the downloaded `source-lock.json` at its root, then:

```sh
python scripts/prepare_sources.py
python scripts/configure_suite.py --mode sanitizers --compiler clang
cmake --build build --parallel 2
python scripts/run_suite.py test
python scripts/run_suite.py summary
```

On Windows, use GNU-compatible Clang on PATH with Ninja installed and set the
CMake generator before configuring, for example in PowerShell:

```powershell
$env:CMAKE_GENERATOR = "Ninja"
```

The source-fetch helper refuses dirty or mismatched existing checkouts; use the
fresh clone for this reproduction. Downloaded locks are run records, not tracked
pins. They include build settings, so inspect them before using a lock from
outside a trusted run. A source or harness commit must remain reachable from
its repository for a future fresh fetch.

## Retest a core fix locally

The ignored `core` directory can be a fresh ordinary clone, an existing local
checkout or a worktree. It is not staged in this test repository. You can test
uncommitted fixes without publishing them. Hosted CI needs a reachable commit,
but pushing to your fork is enough; no upstream merge is required.

For a fresh checkout, resolve and fetch:

```sh
python scripts/resolve_source.py --repository yourname/core --ref my-fix
python scripts/prepare_sources.py
```

The fetch helper refuses to overwrite dirty checkouts or silently change existing
revisions. For an existing checkout, preserve local changes and switch explicitly:

```sh
git -C core status --short
git -C core fetch origin my-fix
git -C core checkout --detach FETCH_HEAD
git -C core rev-parse HEAD
```

Use a fresh build directory when switching revisions. Save the tested SHA with
your results, then follow the regression cleanup steps below.

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
  Remove all objects for the resolved issue, keeping valid JSON (an empty
  manifest is `[]`). Also remove that test's `known_sanitizer_bug` label block
  from [tests/known_bugs.cmake](tests/known_bugs.cmake). The label applies only
  to sanitizer builds: if its expected diagnostic disappears, reporting fails
  with cleanup guidance. An unrelated diagnostic or assertion still fails.
  Keep the correct output assertions; the summary must then report a clean pass.
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
git diff
```

Stage the documentation, exception and registration files you actually changed
as well. Commit the test and exception cleanup, then push and verify
both GCC and Clang sanitizer jobs and the coverage job in GitHub Actions. If the
new core introduces an additional defect, add a separate correctly expected
regression and dated known-bug entry; do not silently waive it.

## GitHub Actions

`.github/workflows/tests.yml` currently runs by manual dispatch only while
upstream core trails the candidate fixes. In **Actions > Core tests > Run workflow**,
set `source_repository=terjeio/grblHAL_core` and choose the branch or SHA to test.
Reusable workflows and upstream caller templates remain available for source PRs.
Restore the `push` and `pull_request` triggers once the fixes reach upstream core.
GCC and Clang run the tests with address/undefined-behavior sanitizers. A separate
GCC job publishes HTML and XML coverage as an Actions artifact. Coverage describes
the instrumented modules in this configuration. The summary lists every core C source file and emitted header bodies, including gaps. No separately managed
credential or external reporting service is required.

## Measure coverage locally

Use a separate coverage build without sanitizers. Install the same reporter as CI:
`python -m pip install gcovr==8.4`.

```sh
cmake -S . -B build-coverage -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DENABLE_COVERAGE=ON
cmake --build build-coverage --parallel
ctest --test-dir build-coverage --output-on-failure
gcovr --merge-mode-functions=separate --root . --filter 'core/.*\.[ch]$' --html-details coverage.html --xml coverage.xml --print-summary build-coverage
python scripts/summary.py coverage coverage.xml
```

For GNU-compatible Clang, select `clang` (or its full Windows path) when configuring
and add `--gcov-executable "C:/path/to/llvm-mingw/bin/llvm-cov.exe gcov"` to gcovr.
Core coverage includes executable C source and header bodies emitted by the
selected configurations. This does not inventory optional code that no configured
build emits. Changed-code warnings include added executable header lines and
identify changed files absent from the report without assuming they lack tests.
Older C-source-only percentages use a different denominator.

For authoritative totals, use the hosted Linux coverage job. LLVM on Windows can
omit profile files at long build paths even when tests pass. If measuring locally,
verify that executed test objects produce `.gcda` files before trusting totals.

Open `coverage.html` to inspect uncovered lines and branches. For a fresh measurement,
use a new build directory so old execution counts cannot carry over.

The host variants currently exercise the default configuration, legacy protocol
compatibility level 1, disabled NGC parameters/expressions (including boot and reset), NGC expressions with default and extended (`NGC_MAX_PARAM_LENGTH=80`) named-parameter/macro labels, non-modal lathe U/V/W commands with NGC expressions, cutter-compensation parsing and plugin interfaces, G187 acceleration profiles, jerk acceleration with and without G187 profiles, coordinate rotation with NGC expressions, default Mach3-style and alternate Fanuc-style G51 scaling (`MACH3_SCALING=0`), spindle synchronization with simulated encoder feedback (including normal boot and streamed G95 programs),
CoreXY, polar, wall-plotter, delta and five-axis RTCP kinematics, backlash
compensation, four-axis asymmetric ganging with and without auto-squaring,
seven-axis XYZABCU, the eight-axis maximum, six-axis UVW remapping, and three registered spindles
with two active spindle slots, a four-slot persistent tool table with and without NGC expressions, fixed X/Y/Z tool-offset axes (`TOOL_LENGTH_OFFSET_AXIS`), optional spindle PWM linearization, and enabled PID logging. All variants run in one
CTest suite; coverage merges their executed source lines. Compatibility levels
1, 2 and 10 have runtime reporting tests. Levels 2 and 10 also exercise normal
boot/reset, coordinate availability and legacy settings; their coordinate-report
compile checks remain. The `separate` function
merge mode retains functions compiled at different locations under feature guards. Other feature combinations
still need tests. A green suite or a covered module does not establish full coverage;
use the source-by-source coverage table to choose the next behavior to test.
The table inventories both `.c` and `.h` files; uninstrumented headers may
contain declarations only.

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
Avoid tests that merely reproduce the implementation. Core changes belong in
their own repository; this repository commits tests and source-selection metadata.

PID tests currently specify existing sample-rate behavior. Deadband and
`p_max_error` are not asserted as supported features; the implementation does not
apply them. Zero sample rate needs an upstream-defined contract before testing
an expected result.
