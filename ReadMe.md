# Unit tests for the grblHAL core

[![Core tests](https://github.com/petervanderwalt/Unit_tests/actions/workflows/tests.yml/badge.svg?branch=master)](https://github.com/petervanderwalt/Unit_tests/actions/workflows/tests.yml)

Host tests compile actual source from the pinned `core` submodule. No CNC
controller is needed. Each new behavior lives in `tests/cases/<module>/<case>.c`
and appears individually in CTest and GitHub Actions. Shared mocks live in
`tests/support/`; unexpected mock calls fail explicitly.

## Known issues

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
compatibility level 1, NGC expressions,
CoreXY, polar, wall-plotter, delta and five-axis RTCP kinematics, backlash
compensation, four-axis asymmetric ganging with and without auto-squaring,
the eight-axis maximum, six-axis UVW remapping, and three registered spindles
with two active spindle slots, a four-slot persistent tool table, optional spindle PWM linearization, and enabled PID logging. All variants run in one
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
