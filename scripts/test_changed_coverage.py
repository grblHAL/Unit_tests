import json
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch
from changed_coverage import added_lines, assess, coverage_lines

class ChangedCoverageTests(unittest.TestCase):
    def test_diff_tracks_new_line_numbers_not_deleted_lines(self):
        result=added_lines("+++ b/code.c\n@@ -8,1 +8,2 @@\n-old\n+first\n+second\n")
        self.assertEqual(result,{'code.c':{8,9}})

    def test_variants_merge_hits_before_reporting_gap(self):
        with tempfile.TemporaryDirectory() as d:
            p=Path(d)/'coverage.xml';p.write_text('<coverage><class filename="core/code.c"><lines><line number="8" hits="0"/></lines></class><class filename="core/code.c"><lines><line number="8" hits="1"/></lines></class></coverage>')
            self.assertEqual(coverage_lines(p)['core/code.c'][8],1)

    def test_no_baseline_is_explicit_not_missing_tests_claim(self):
        result=assess({},Path('absent.xml'))
        self.assertEqual(result[0]['kind'],'coverage_unavailable')
        self.assertIn('No source baseline',result[0]['message'])

    def test_real_git_diff_ignores_old_gaps_and_comments(self):
        with tempfile.TemporaryDirectory() as d:
            root=Path(d);core=root/'core';core.mkdir()
            def git(*args):
                return subprocess.check_output(['git','-C',str(core),*args],text=True).strip()
            git('init');git('config','user.name','Test');git('config','user.email','test@example.invalid')
            (core/'code.c').write_text('int old = 0;\n')
            git('add','.');git('commit','-m','Baseline');base=git('rev-parse','HEAD')
            (core/'code.c').write_text('int old = 0;\n/* comment */\nint added = 1;\n')
            (core/'new.c').write_text('int new_file = 2;\n')
            git('add','.');git('commit','-m','Candidate');sha=git('rev-parse','HEAD')
            coverage=root/'coverage.xml';coverage.write_text('<coverage><class filename="core/code.c"><lines><line number="1" hits="0"/><line number="3" hits="0"/></lines></class></coverage>')
            lock=dict(path='core',sha=sha,coverage_filter=r'core/.*\.c$',comparison=dict(repository='owner/core',sha=base))
            import os
            before=os.getcwd();os.chdir(root)
            try: result=assess(lock,coverage)
            finally: os.chdir(before)
            uncovered=next(f for f in result if f['kind']=='uncovered')
            self.assertEqual(uncovered['uncovered_lines'],[3])
            self.assertTrue(any(f['kind']=='unmeasured' for f in result))

if __name__=='__main__':
    unittest.main()
