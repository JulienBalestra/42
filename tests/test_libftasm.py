import subprocess
import unittest
import os
from pymake.pymake import PyMake


class TestLS(unittest.TestCase):
	context_path = os.path.split(os.path.dirname(__file__))[0] + "/libftASM/"
	makefile = PyMake(context_path + "Makefile")
	dev_null = open(os.devnull, 'w')

	@classmethod
	def setUpClass(cls):
		cls.makefile.make_fclean(), cls.makefile.make(), cls.makefile.make(string_arg="test")
		cls.test = cls.context_path + "test"

	@classmethod
	def tearDownClass(cls):
		cls.makefile.make_fclean()

	def test_libftasm(self):
		self.assertEqual(0, subprocess.call(self.test, stdout=self.dev_null))


if __name__ == "__main__":
	unittest.main()