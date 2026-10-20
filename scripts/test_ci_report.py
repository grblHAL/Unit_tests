import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from ci_report import build_failure, merge_reports, render, source_link, test_findings

SCRIPTS = Path(__file__).resolve().parent

class DiagnosisTests(unittest.TestCase):
    def test_compiler_reports_first_error_not_cascade(self):
        report = build_failure("build", "/checkout/tests/support/tool.h:25:3: error: incompatible callback\ncollect2: error: ld returned 1 exit status")
        self.assertEqual(report["file"], "tests/support/tool.h")
        self.assertEqual(report["line"], 25)
        self.assertIn("incompatible callback", report["message"])
        self.assertNotIn("collect2", report["message"])

    def test_checkout_name_containing_tests_does_not_corrupt_source_link(self):
        report = build_failure("build", "/home/runner/work/Unit_tests/Unit_tests/tests/support/tool.h:25:3: error: bad callback")
        self.assertEqual(report["file"], "tests/support/tool.h")

    def test_cmake_failure_includes_reason_and_location(self):
        report = build_failure("configure", "CMake Error at CMakeLists.txt:11 (message):\n  Missing source checkout\n\n-- Configuring incomplete")
        self.assertEqual(report["file"], "CMakeLists.txt")
        self.assertEqual(report["line"], 11)
        self.assertIn("Missing source checkout", report["message"])

    def test_timeout_is_not_reported_as_partial_test_output(self):
        with tempfile.TemporaryDirectory() as d:
            p=Path(d); (p/'known_sanitizer_diagnostics.json').write_text('[]')
            (p/'results.xml').write_text('<testsuite><testcase name="module.case"><failure message="Timeout"/><system-out>Startup message</system-out></testcase></testsuite>')
            findings, counts=test_findings(p/'results.xml',p)
            self.assertIn('timed out', findings[0]['message'])
            self.assertEqual(counts['failed'],1)

    def test_resolution_failure_reports_http_error_not_traceback_header(self):
        report = build_failure("resolve", "Traceback (most recent call last):\n  request failed\nurllib.error.HTTPError: HTTP Error 404: Not Found")
        self.assertIn("HTTP Error 404", report["message"])
        self.assertNotIn("Traceback", report["message"])

    def test_same_location_merges_different_compiler_wording(self):
        reports = [dict(job=c, findings=[build_failure("build", "/checkout/core/gcode.c:2794:3: error: " + msg)]) for c,msg in [("gcc","not an array"),("clang","not an array or vector")]]
        merged = merge_reports(reports)
        self.assertEqual(len(merged), 1)
        self.assertEqual(merged[0]["jobs"], ["gcc", "clang"])

    def test_source_link_uses_candidate_not_harness(self):
        lock = dict(harness_repository="owner/tests", harness_sha="a"*40, sources=[dict(path="plugins/example", repository="fork/plugin", sha="b"*40)])
        link = source_link(dict(file="plugins/example/code.c", line=7), lock)
        self.assertIn("fork/plugin/blob/" + "b"*40 + "/code.c#L7", link)

    def test_empty_process_output_keeps_junit_crash_message_for_known_case(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path = root / "results.xml"
            path.write_text('<testsuite><testcase name="vfs.case"><failure message="SEGFAULT"/>'
                            '<properties><property name="cmake_labels" value="known_bug"/></properties>'
                            '<system-out/><system-err>  </system-err></testcase></testsuite>')
            findings, counts = test_findings(path, root)
            self.assertEqual(counts["failed"], 1)
            self.assertEqual(counts["known"], 0)
            self.assertEqual(findings[0]["kind"], "known_changed")
            self.assertEqual(findings[0]["message"], "SEGFAULT")

    def test_known_changed_report_does_not_assert_fix(self):
        text = render([dict(job="gcc", findings=[dict(kind="known_changed", name="module.case", message="Different fault", severity="error")])], {})
        self.assertIn("it may be a fixed regression", text)
        self.assertIn("A different crash is not proof", text)
        self.assertIn("retain the test", text)

    def test_new_failures_are_not_hidden_by_fixed_exception_findings(self):
        changed = [dict(kind="known_changed", name="known." + str(i), message="Expected failure changed", severity="error") for i in range(15)]
        unexpected = [dict(kind="test", name="new." + str(i), message="Correct assertion failed", severity="error") for i in range(9)]
        text = render([dict(job="gcc", findings=changed + unexpected)], {})
        self.assertIn("9 unexpected failures", text)
        self.assertIn("15 changed known-defect exceptions", text)
        self.assertLess(text.index("**new.8**"), text.index("**known.0**"))
        self.assertIn("remove only the fixed exception", text)

    def test_test_output_cannot_inject_markdown(self):
        text = render([dict(job="clang", findings=[dict(kind="test", name="<script>", message="<img onerror=x>", severity="error")])], {})
        self.assertNotIn("<script>", text)
        self.assertIn("&lt;script&gt;", text)

    def test_unknown_recovering_sanitizer_is_failure(self):
        with tempfile.TemporaryDirectory() as d:
            p=Path(d); (p/'known_sanitizer_diagnostics.json').write_text('[]')
            (p/'results.xml').write_text('<testsuite><testcase name="module.case"><system-out>/repo/core/code.c:7:1: runtime error: bad conversion</system-out></testcase></testsuite>')
            findings, counts=test_findings(p/'results.xml',p)
            self.assertEqual(counts['failed'],1)
            self.assertEqual(findings[0]['kind'],'sanitizer')

    def test_stage_preserves_exit_code_and_full_log(self):
        with tempfile.TemporaryDirectory() as d:
            result=subprocess.run([sys.executable,str(SCRIPTS/'report_stage.py'),'--job','gcc','--stage','build','--',sys.executable,'-c',"print('/repo/core/code.c:7:2: error: bad callback'); raise SystemExit(3)"],cwd=d,capture_output=True,text=True)
            self.assertEqual(result.returncode,3)
            report=json.loads((Path(d)/'report-gcc.json').read_text())
            self.assertEqual(report['stages'][0]['exit_code'],3)
            self.assertIn('bad callback',(Path(d)/'logs/gcc-build.log').read_text())
            self.assertEqual(report['findings'][0]['line'],7)

    def test_failed_execution_keeps_partial_coverage_without_passing_job(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "build").mkdir()
            (root / "build/results.xml").write_text('<testsuite><testcase name="core.case"><failure message="SEGFAULT"/></testcase></testsuite>')
            (root / "coverage.xml").write_text('<coverage/>')
            (root / "report-coverage.json").write_text(json.dumps(dict(job="coverage", findings=[], stages=[dict(stage="test", exit_code=1, log="unused.log")])))
            env = os.environ.copy()
            env.pop("GITHUB_STEP_SUMMARY", None)
            env.pop("GITHUB_ACTIONS", None)
            result = subprocess.run([sys.executable, str(SCRIPTS / "ci_report.py"), "--job", "coverage"], cwd=root, env=env, capture_output=True, text=True)
            self.assertNotEqual(result.returncode, 0, result.stderr)
            report = json.loads((root / "report-coverage.json").read_text())
            self.assertEqual(report["counts"]["failed"], 1)
            partial = [item for item in report["findings"] if item["kind"] == "coverage_partial"]
            self.assertEqual(len(partial), 1)
            self.assertEqual(partial[0]["severity"], "warning")
            self.assertIn("execution is incomplete", partial[0]["message"])
            self.assertNotIn("coverage_unavailable", [item["kind"] for item in report["findings"]])

    def test_aggregate_never_passes_missing_compiler_report(self):
        with tempfile.TemporaryDirectory() as d:
            p=Path(d); (p/'reports').mkdir()
            for job in ['source','gcc','coverage']:
                (p/'reports'/('report-'+job+'.json')).write_text(json.dumps(dict(job=job,findings=[])))
            env=os.environ.copy(); env.pop('GITHUB_STEP_SUMMARY',None); env['NEEDS_JSON']=json.dumps({j:dict(result='success') for j in ['source','test','coverage']})
            result=subprocess.run([sys.executable,str(SCRIPTS/'ci_report.py'),'--aggregate'],cwd=d,env=env,capture_output=True,text=True)
            self.assertNotEqual(result.returncode,0)
            self.assertIn('no diagnostic artifact',result.stdout)

if __name__=='__main__':
    unittest.main()
