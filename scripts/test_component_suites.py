import json
from pathlib import Path
import re
import unittest
import tempfile
import xml.etree.ElementTree as ET
from ci_report import build_failure, source_link, test_findings
from resolve_source import resolve_plan

ROOT = Path(__file__).resolve().parent.parent

class ComponentSuitesTests(unittest.TestCase):
    def test_component_plans_lock_candidate_and_core_separately(self):
        suites = json.loads((ROOT / "ci/suites.json").read_text())
        for name in (key for key in suites.keys() - {"core"} if not suites[key].get("source_only")):
            with self.subTest(suite=name):
                calls = []
                def request(repository, endpoint):
                    calls.append((repository, endpoint))
                    return {"sha": ("b" if repository == "grblHAL/core" else "a" if repository == suites[name]["repository"] else "c") * 40}
                plan = resolve_plan(suites, name, ref="candidate", core_ref="compatible-core" if "core" in suites[name]["dependencies"] else "", request=request)
                self.assertEqual(calls, [(suites[name]["repository"], "commits/candidate")] + [(suites[dependency]["repository"], "commits/" + ("compatible-core" if dependency == "core" else suites[dependency]["ref"])) for dependency in suites[name]["dependencies"]])
                self.assertEqual([source["sha"] for source in plan["sources"]], ["a" * 40] + [("b" if suites[dependency]["repository"] == "grblHAL/core" else "c") * 40 for dependency in suites[name]["dependencies"]])
                self.assertEqual(plan["host_bits"], suites[name].get("host_bits", 64))
                self.assertEqual(len({source["path"] for source in plan["sources"]}), 1 + len(suites[name]["dependencies"]))
                self.assertNotEqual(plan["cmake_source"], ".")
                self.assertIsNone(re.search(plan["test_regex"], "boot.normal_startup"))
                self.assertIsNotNone(re.search(plan["test_regex"], name + ".case"))
                self.assertIsNone(re.search(plan["coverage_filter"], "core/gcode.c"))
                self.assertTrue((ROOT / plan["cmake_source"] / "CMakeLists.txt").is_file())
                manifest = ROOT / plan["diagnostics_directory"] / "known_sanitizer_diagnostics.json"
                self.assertIsInstance(json.loads(manifest.read_text()), list)

    def test_driver_error_links_to_driver_revision_not_harness(self):
        for path in ("/checkout/drivers/simulator/src/eeprom.c", "C:\\checkout\\drivers\\simulator\\src\\eeprom.c"):
            with self.subTest(path=path):
                finding = build_failure("build", path + ":42:3: error: incompatible callback")
                self.assertEqual((finding["file"], finding["line"]), ("drivers/simulator/src/eeprom.c", 42))
                lock = {"harness_repository": "owner/tests", "harness_sha": "a" * 40,
                        "sources": [{"path": "drivers/simulator", "repository": "fork/Simulator", "sha": "b" * 40}]}
                link = source_link(finding, lock)
                self.assertIn("fork/Simulator/blob/" + "b" * 40 + "/src/eeprom.c#L42", link)
                self.assertNotIn("owner/tests/blob", link)

    def test_fan_diagnostic_allowance_rejects_missing_and_unrelated_reports(self):
        directory = ROOT / "tests/plugins/fans"
        message = "call to function set_spindle_link through pointer to incorrect function type 'status_code_t (*)(setting_id_t, unsigned short)'"
        diagnostic = "/repo/tests/plugins/fans/spindle_delay.c:8:2: runtime error: " + message
        variants = [(diagnostic, True), (diagnostic.replace(":8:2:", ":9:2:"), False),
                    (diagnostic.replace("set_spindle_link through", "other_function through"), False),
                    (diagnostic.replace("fans/spindle_delay.c", "fans/other.c"), False), ("", False)]
        with tempfile.TemporaryDirectory() as temporary:
            result = Path(temporary) / "results.xml"
            for output, accepted in variants:
                with self.subTest(output=output):
                    tree = ET.Element("testsuite")
                    case = ET.SubElement(tree, "testcase", name="plugin_fans.spindle_delay")
                    properties = ET.SubElement(case, "properties")
                    ET.SubElement(properties, "property", name="cmake_labels", value="known_sanitizer_bug")
                    ET.SubElement(case, "system-out").text = output
                    ET.ElementTree(tree).write(result)
                    findings, counts = test_findings(result, directory)
                    self.assertEqual(counts["known"], int(accepted))
                    self.assertEqual(counts["failed"], int(not accepted))
                    self.assertEqual(bool(findings), not accepted)

    def test_dependency_source_is_not_selectable_as_a_test_suite(self):
        suites = json.loads((ROOT / "ci/suites.json").read_text())
        with self.assertRaisesRegex(ValueError, "no tests registered"):
            resolve_plan(suites, "littlefs", request=lambda *args: self.fail("network requested"))

    def test_dependency_diagnostic_links_to_locked_dependency(self):
        finding = build_failure("build", "/repo/deps/littlefs/lfs.c:42:3: error: incompatible callback")
        self.assertEqual((finding["file"], finding["line"]), ("deps/littlefs/lfs.c", 42))
        link = source_link(finding, {"sources": [{"path": "deps/littlefs", "repository": "littlefs-project/littlefs", "sha": "c" * 40}]})
        self.assertIn("littlefs-project/littlefs/blob/" + "c" * 40 + "/lfs.c#L42", link)

    def test_fixed_psoc_reference_never_uses_current_core(self):
        suites = json.loads((ROOT / "ci/suites.json").read_text())
        calls = []
        def request(repository, endpoint):
            calls.append((repository, endpoint))
            return {"sha": "a" * 40}
        plan = resolve_plan(suites, "driver_psoc5_serial_reference", request=request)
        self.assertEqual(calls, [("grblHAL/PSoC5", "commits/master"),
                                ("grblHAL/core", "commits/070f80cc5c0d095ff63d5980795b5a15c5bb0202")])
        self.assertEqual([source["path"] for source in plan["sources"]],
                         ["drivers/psoc5", "deps/core-20250518"])
        with self.assertRaisesRegex(ValueError, "core-ref"):
            resolve_plan(suites, "driver_psoc5_serial_reference", core_ref="next", request=request)
        with self.assertRaisesRegex(ValueError, "no tests registered"):
            resolve_plan(suites, "psoc5_reference_core", request=request)
