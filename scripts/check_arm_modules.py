"""Compile original driver/SDK modules for ARM; no link, execution or hardware claim."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess

from prepare_sources import prepare


STM32 = {
    "stm32f1": [("STM32F103xB", "cortex-m3", None)],
    "stm32f3": [("STM32F303xC", "cortex-m4", "fpv4-sp-d16")],
    "stm32f4": [("STM32F407xx", "cortex-m4", "fpv4-sp-d16")],
    "stm32f7": [("STM32F756xx", "cortex-m7", "fpv5-sp-d16")],
    "stm32h7": [("STM32H743xx", "cortex-m7", "fpv5-d16"),
                ("STM32H723xx", "cortex-m7", "fpv5-d16")],
}


def module_plan(family):
    common = ["-std=gnu11", "-mthumb", "-Os", "-g", "-ffunction-sections",
              "-fdata-sections", "-Wall", "-Wextra", "-DOVERRIDE_MY_MACHINE=1",
              "-DUSB_SERIAL_CDC=0", "-DMPG_BUFFER_SIZE=0",
              "-DRX_BUFFER_SIZE=32", "-DTX_BUFFER_SIZE=32"]
    if family == "lpc176x":
        sdk = "src/lpc_chip_175x_6x"
        return [("LPC176x", common + ["-mcpu=cortex-m3", "-D__LPC17XX__", "-DCORE_M3"],
                 ["src", sdk + "/inc"],
                 ["src/serial.c", sdk + "/src/uart_17xx_40xx.c", sdk + "/src/iocon_17xx_40xx.c"])]
    plans = []
    for mcu, cpu, fpu in STM32[family]:
        vendor = family.upper() + "xx"
        sdk = "Drivers/" + vendor + "_HAL_Driver"
        flags = common + ["-mcpu=" + cpu, "-DUSE_HAL_DRIVER", "-D" + mcu]
        if fpu:
            flags += ["-mfpu=" + fpu, "-mfloat-abi=hard"]
        plans.append((mcu, flags, ["Inc", ".", sdk + "/Inc", "Drivers/CMSIS/Include",
                                  "Drivers/CMSIS/Device/ST/" + vendor + "/Include"],
                      ["Src/serial.c", sdk + "/Src/" + family + "xx_hal_uart.c"]))
    return plans


def is_arm_object(data):
    # ELF32, little endian, relocatable, EM_ARM. Objects are never executed.
    return (len(data) >= 52 and data[:6] == b"\x7fELF\x01\x01"
            and int.from_bytes(data[16:18], "little") == 1
            and int.from_bytes(data[18:20], "little") == 40)


def check(root, lock, output, compiler):
    family = lock["path"].removeprefix("drivers/")
    if lock["path"] != "drivers/" + family or family not in {*STM32, "lpc176x"}:
        raise ValueError("No ARM module plan for this source")
    sources = {source["path"]: source for source in lock["sources"]}
    for path in (lock["path"], "core"):
        prepare(sources[path], root)
    output = output.resolve()
    if not output.is_relative_to(root) or output == root:
        raise ValueError("Build output must be inside the workspace")
    include = output / "include/grbl"
    include.mkdir(parents=True, exist_ok=True)
    for header in (root / "core").glob("*.h"):
        (include / header.name).write_text('#include "' + header.as_posix() + '"\n')
    version = subprocess.check_output([compiler, "--version"], text=True).splitlines()[0]
    driver = root / lock["path"]
    records = []
    for mcu, flags, includes, modules in module_plan(family):
        destination = output / mcu
        destination.mkdir(exist_ok=True)
        for relative in modules:
            source = driver / relative
            target = destination / (source.stem + ".o")
            command = [compiler, *flags]
            for directory in [*(driver / item for item in includes), output / "include", root / "core"]:
                command += ["-I", str(directory)]
            command += ["-c", str(source), "-o", str(target)]
            result = subprocess.run(command, capture_output=True, text=True)
            log = destination / (source.stem + ".log")
            log.write_text(result.stdout + result.stderr)
            data = target.read_bytes() if result.returncode == 0 else b""
            passed = result.returncode == 0 and is_arm_object(data)
            record = {"mcu": mcu, "source": source.relative_to(root).as_posix(),
                      "source_sha256": hashlib.sha256(source.read_bytes()).hexdigest(),
                      "command": command, "returncode": result.returncode, "passed": passed,
                      "architecture": "ELF32 ARM relocatable" if passed else None,
                      "object_sha256": hashlib.sha256(data).hexdigest() if passed else None,
                      "warnings": (result.stdout + result.stderr).count("warning:"),
                      "runtime_executed": False, "firmware_linked": False, "hardware_tested": False}
            records.append(record)
            print(mcu, relative, "PASS" if passed else "FAIL", flush=True)
            if not passed:
                print(result.stdout + result.stderr, flush=True)
    (output / "results.json").write_text(json.dumps(
        {"compiler": version, "source_lock": lock, "checks": records}, indent=2) + "\n")
    return 0 if all(record["passed"] for record in records) else 1


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--lock", default="source-lock.json")
    parser.add_argument("--output", default="build-arm-modules")
    parser.add_argument("--compiler", default="arm-none-eabi-gcc")
    args = parser.parse_args()
    return check(Path.cwd().resolve(), json.loads(Path(args.lock).read_text()),
                 Path(args.output), args.compiler)


if __name__ == "__main__":
    raise SystemExit(main())
