from unittest import TestCase, main
import os
import contextlib
import sys
from cStringIO import StringIO
from os.path import isfile

from pymake.pymake import PyMake


@contextlib.contextmanager
def capture():
    out = None
    oldout, olderr = sys.stdout, sys.stderr
    try:
        out = [StringIO(), StringIO()]
        sys.stdout, sys.stderr = out
        yield out
    finally:
        sys.stdout, sys.stderr = oldout, olderr
        out[0] = out[0].getvalue()


class TestPyMake(TestCase):
    @classmethod
    def setUpClass(cls):
        cls.makefile = PyMake((os.path.dirname(__file__)) + "/test_resources/Makefile")

    def test_0_incorrect_path(self):
        try:
            PyMake((os.path.dirname(__file__)) + "/test_resources/no_makefile")
        except Exception as e:
            self.assertEqual(OSError, type(e))

    def test_1_correct_path(self):
        PyMake((os.path.dirname(__file__)) + "/test_resources/Makefile")

    def test_2_read_makefile(self):
        with capture() as std_out_err:
            print self.makefile
        self.assertEqual(191, len(std_out_err[0]))

    def test_3_make(self):
        self.makefile.make()
        self.assertTrue(isfile(os.path.dirname(__file__) + "/test_resources/all"))

    def test_4_make_clean(self):
        self.makefile.make("clean")
        self.assertFalse(isfile(os.path.dirname(__file__) + "/test_resources/all"))

    def test_5_make(self):
        self.makefile.make("all")
        self.assertTrue(isfile(os.path.dirname(__file__) + "/test_resources/all"))
        self.makefile.make_clean()
        self.assertFalse(isfile(os.path.dirname(__file__) + "/test_resources/all"))
        

if __name__ == "__main__":
    main()