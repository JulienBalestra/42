import unittest
import subprocess as subp
import os
import utils_config
import glob
import time
from datetime import datetime

from pymake.pymake import PyMake


class TestLS(unittest.TestCase):
    debug_mod = False
    kernel = subp.check_output(["uname", "-s"]).replace("\n", "")
    context_path = os.path.split(os.path.dirname(__file__))[0] + "/ls-%s/" % kernel
    makefile = PyMake(context_path + "Makefile")
    options = [opt for opt in "1lQRartUfgdG"]
    real_f, fake_f, null_f = glob.glob(context_path + "*"), [str(k) for k in xrange(50)], open(os.devnull, 'w')

    @classmethod
    def setUpClass(cls):
        [os.remove(binary) for binary in glob.glob(cls.context_path + "*.bft")]
        cls.makefile.make_fclean(), cls.makefile.make()
        cls.set_config = utils_config.SetLSConfig(cls.debug_mod)
        cls.test_methods = iter(utils_config.IterMethods(cls))

    @classmethod
    def tearDownClass(cls):
        cls.makefile.make_fclean(), cls.null_f.close()
        if cls.debug_mod is False:
            [os.remove(binary) for binary in glob.glob(cls.context_path + "*.bft")]

    def setUp(self):
        """
        iter to dry tests
        """
        self.run = self.set_config.next_conf(self.test_methods.next())

    def test_build_child_name(self):
        printed = subp.check_output([self.run, "-1a", "ls_mains/resources"]).split("\n")
        printed.sort()
        self.assertEqual(['', '.', '..', 'file_one'], printed)

    def test_build_child_path(self):
        printed = subp.check_output([self.run, "-1a", "ls_mains/resources"]).split("\n")
        printed.sort()
        self.assertEqual(['', 'ls_mains/resources/.', 'ls_mains/resources/..', 'ls_mains/resources/file_one'], printed)

    def test_build_path(self):
        self.assertEqual("parent/child", subp.check_output([self.run, "parent", "child"]))

    def test_display_date(self):
        self.assertEqual("Jan  1 1970 ", subp.check_output([self.run, "0"]))
        self.assertEqual("Sep  1 2014 ", subp.check_output([self.run, "1409529600"]))
        self.assertEqual("Dec 31 23:59 ", subp.check_output([self.run, "1420066740"]))
        self.assertEqual("Dec 31 23:59 ", subp.check_output([self.run, "1420066799"]))
        self.assertEqual("Jan  1 00:00 ", subp.check_output([self.run, "1420066800"]))
        self.assertEqual("Jan  1 00:01 ", subp.check_output([self.run, "1420066860"]))
        ts = time.time()
        today = datetime.fromtimestamp(ts).strftime('%b %d %H:%M ')
        if datetime.fromtimestamp(ts).strftime('%d')[0] == '0':
            today = datetime.fromtimestamp(ts).strftime('%b  %-d %H:%M ')
        self.assertEqual(today, subp.check_output([self.run, str(ts)]))

        today = datetime.fromtimestamp(ts - 15778463).strftime('%b %d %H:%M ')
        if datetime.fromtimestamp(ts - 15778463).strftime('%d')[0] == '0':
            today = datetime.fromtimestamp(ts - 15778463).strftime('%b  %-d %H:%M ')
        self.assertEqual(today, subp.check_output([self.run, str(ts - 15778463)]))

        today = datetime.fromtimestamp(ts - 15778463 - 86400).strftime('%b %d %Y ')
        if datetime.fromtimestamp(ts - 15778463 - 86400).strftime('%d')[0] == '0':
            today = datetime.fromtimestamp(ts - 15778463 - 86400).strftime('%b  %-d %Y ')
        self.assertEqual(today, subp.check_output([self.run, str(ts - 15778463 - 86400)]))

    def test_long_display_00(self):
        real = subp.check_output(["ls", "-la", self.context_path + "/includes"])
        mine = subp.check_output([self.run, "-la", self.context_path + "/includes"])
        self.assertEqual(real, mine)

    def test_long_display_01(self):
        real = subp.check_output(["ls", "-la", self.context_path + "/srcs"])
        mine = subp.check_output([self.run, "-la", self.context_path + "/srcs"])
        self.assertEqual(real, mine)

    def test_long_display_02(self):
        real = subp.check_output(["ls", "-la", self.context_path])
        mine = subp.check_output([self.run, "-la", self.context_path])
        self.assertEqual(real, mine)

    def test_long_display_03(self):
        real = subp.check_output(["ls", "-la", "/usr/"])
        mine = subp.check_output([self.run, "-la", "/usr/"])
        self.assertEqual(real, mine)

    def test_long_display_04(self):
        usr_wild_card = glob.glob("/usr/*")
        real = subp.check_output(["ls", "-la"] + usr_wild_card)
        mine = subp.check_output([self.run, "-la"] + usr_wild_card)
        self.assertEqual(real, mine)

    def test_long_display_05(self):
        real = subp.check_output(["ls", "-la"] + self.real_f)
        mine = subp.check_output([self.run, "-la"] + self.real_f)
        self.assertEqual(real, mine)

    def test_long_display_06(self):
        real = subp.check_output(["ls", "-la", "/dev/"])
        mine = subp.check_output([self.run, "-la", "/dev/"])
        self.assertEqual(real, mine)

    def test_long_display_07(self):
        dev_wild_card = glob.glob("/dev/")
        real = subp.check_output(["ls", "-la"] + dev_wild_card)
        mine = subp.check_output([self.run, "-la"] + dev_wild_card)
        self.assertEqual(real, mine)

    def test_get_args(self):
        for real in self.real_f:
            self.assertEqual(real + "0", subp.check_output([self.run, real]))
            self.assertEqual(str(len(self.options)),
                             subp.check_output([self.run, "-" + "".join(self.options), real]).split("\n")[-1])
            for opt in self.options:
                if opt == 'f':
                    self.assertEqual(real + "3", subp.check_output([self.run, "-" + opt, real]).split("\n")[-1])
                else:
                    try:
                        self.assertEqual(real + "1", subp.check_output([self.run, "-" + opt, real]).split("\n")[-1])
                    except AssertionError:
                        self.assertEqual("1", subp.check_output([self.run, "-" + opt, real]).split("\n")[-1])

        for arg in self.options:
            if arg == 'f':
                self.assertEqual("3", subp.check_output([self.run, '-' + arg] + self.fake_f, stderr=self.null_f), )
            else:
                self.assertEqual("1", subp.check_output([self.run, '-' + arg] + self.fake_f, stderr=self.null_f), )
        self.assertEqual(str(len(self.options)),
                         subp.check_output([self.run, "-" + "".join(self.options)] + self.fake_f,
                                           stderr=self.null_f))
        self.assertEqual("." + str(len(self.options)),
                         subp.check_output([self.run, "--"] + ["-" + k for k in self.options]).split("\n")[-1])
        self.assertEqual(".0", subp.check_output([self.run, "--"]))
        for arg in self.options:
            if arg == 'f':
                self.assertEqual(".3", subp.check_output([self.run, "--", "-" + arg]).split("\n")[-1])
            else:
                self.assertEqual(".1", subp.check_output([self.run, "--", "-" + arg]).split("\n")[-1])

    def test_get_items(self):
        for real in self.real_f:
            self.assertEqual(real, subp.check_output([self.run, real]))

        for fake in self.fake_f:
            self.assertEqual(self.run + ": cannot access %s: No such file or directory\n" % fake,
                             subp.check_output([self.run, fake], stderr=subp.STDOUT))

        self.assertEqual(self.run + ": cannot access -: No such file or directory\n",
                         subp.check_output([self.run, "-"], stderr=subp.STDOUT))
        self.assertEqual(".", subp.check_output([self.run, "--"], stderr=self.null_f))

    def test_get_options(self):
        for opt in self.options:
            if opt == 'f':
                self.assertEqual("3", subp.check_output([self.run, '-' + opt]).split("\n")[-1])
            else:
                self.assertEqual("1", subp.check_output([self.run, '-' + opt]).split("\n")[-1])

        self.assertEqual(str(len(self.options)),
                         subp.check_output([self.run, "-" + "".join(self.options)]).split("\n")[-1])
        self.assertEqual("2", subp.check_output([self.run, "-l", "-a"]).split("\n")[-1])
        self.assertEqual(str(len(self.options)),
                         subp.check_output([self.run] + ["-" + k for k in self.options]).split("\n")[-1])
        
    def test_matrix_00(self):
        real = subp.check_output(["ls", self.context_path + "srcs/"])
        mine = subp.check_output([self.run, self.context_path + "srcs/"]).split("  ")
        mine = "\n".join([k for k in mine if k != "\n"]) + "\n"
        self.assertEqual(real, mine)

    def test_no_options(self):
        self.assertEqual(1, subp.call([self.run, "-l"]))  # just to be sure

        # Test errors : ret code == 0
        error_msg = self.run + ': cannot access  -%s: No such file or directory\n'  # blank before -
        for arg in self.options:
            self.assertEqual(error_msg % arg, subp.check_output([self.run, ' -' + arg], stderr=subp.STDOUT))
        self.assertEqual(2, subp.call([self.run, "-l-"], stderr=self.null_f))
        self.assertEqual(2, subp.call([self.run, "-lza"], stderr=self.null_f))
        self.assertEqual(2, subp.call([self.run, "-".join(["-" + k for k in self.options])],
                                      stderr=self.null_f))  # e.g. -l-a-R ...

    # TODO ->
    # self.assertEqual(0, subp.call([self.run, "--help"]))  # special case
    # self.assertEqual(0, subp.call([self.run, "--l"], stderr=self.devnull))

    def test_one_a(self):
        real, mine = subp.check_output(["ls", "-1a"]), subp.check_output([self.run, "-1a"])
        self.assertEqual(real, mine)

        real = subp.check_output(["ls", "-1a", ".", ".."])
        mine = subp.check_output([self.run, "-1a", ".", ".."])
        self.assertEqual(real, mine)

        real = subp.check_output(["ls", "-1a"] + self.real_f)
        mine = subp.check_output([self.run, "-1a"] + self.real_f)
        self.assertEqual(real, mine)

    def test_recursive_00(self):
        real = subp.check_output(["ls", "-1R", self.context_path])
        mine = subp.check_output([self.run, "-1R", self.context_path])
        self.assertEqual(real, mine)

    def test_recursive_01(self):
        real = subp.check_output(["ls", "-1aR", self.context_path])
        mine = subp.check_output([self.run, "-1aR", self.context_path])
        self.assertEqual(real, mine)

    def test_recursive_02(self):
        real = subp.check_output(["ls", "-1aR"])
        mine = subp.check_output([self.run, "-1aR"])
        self.assertEqual(real, mine)

    def test_recursive_03(self):
        real = subp.check_output(["ls", "-laR"])
        mine = subp.check_output([self.run, "-laR"])
        self.assertEqual(real, mine)

    def test_recursive_04(self):
        real = subp.check_output(["ls", "-lR", self.context_path])
        mine = subp.check_output([self.run, "-lR", self.context_path])
        self.assertEqual(real, mine)

    def test_short_display(self):
        m_one_a = subp.check_output([self.run, "-1a", "."]).split("\n")
        r_one_a = subp.check_output(["ls", "-a1"]).split("\n")
        self.assertEqual(len(r_one_a), len(m_one_a)), self.assertEqual(set(r_one_a), set(m_one_a))  # unsorted

    def test_reverse_00(self):
        real = subp.check_output(["ls", "-1ar"])
        mine = subp.check_output([self.run, "-1ar"])
        self.assertEqual(real, mine)

    def test_reverse_01(self):
        real = subp.check_output(["ls", "-lar"])
        mine = subp.check_output([self.run, "-lar"])
        self.assertEqual(real, mine)

    def test_reverse_02(self):
        real = subp.check_output(["ls", "-ltr", "/"])
        mine = subp.check_output([self.run, "-ltr", "/"])
        self.assertEqual(real, mine)

    def test_reverse_03(self):
        real = subp.check_output(["ls", "-1tr", "/"])
        mine = subp.check_output([self.run, "-1tr", "/"])
        self.assertEqual(real, mine)

    def test_time_00(self):
        real = subp.check_output(["ls", "-1t", "/"])
        mine = subp.check_output([self.run, "-1t", "/"])
        self.assertEqual(real, mine)

    def test_time_01(self):
        real = subp.check_output(["ls", "-lt", "/"])
        mine = subp.check_output([self.run, "-lt", "/"])
        self.assertEqual(real, mine)

    def test_valgrind_errors(self):
        slow = False  # Very Slow at True because of Valgrind
        if slow is False:
            return
        self.assertFalse(utils_config.valgrind_wrapper(self.run, errors=True, args=["-1"]))  # Will get file "."
        self.assertFalse(utils_config.valgrind_wrapper(self.run, errors=True, args=[".", "..", "-1"]))
        self.assertFalse(utils_config.valgrind_wrapper(self.run, errors=True, args=["-l"]))
        self.assertFalse(utils_config.valgrind_wrapper(self.run, errors=True, args=["-1R"]))
        self.assertFalse(utils_config.valgrind_wrapper(self.run, errors=True, args=["-lR"]))

    def test_valgrind_leaks(self):
        slow = False  # Very Slow at True because of Valgrind
        if slow is False:
            return
        self.assertFalse(utils_config.valgrind_wrapper(self.run, leaks=True))  # Will get file "."
        self.assertFalse(utils_config.valgrind_wrapper(self.run, leaks=True, args=[".", ".."]))
        self.assertFalse(utils_config.valgrind_wrapper(self.run, leaks=True, args=["-l"]))
        self.assertFalse(utils_config.valgrind_wrapper(self.run, leaks=True, args=["-a"]))
        self.assertFalse(utils_config.valgrind_wrapper(self.run, leaks=True, args=["-l"]))
        self.assertFalse(utils_config.valgrind_wrapper(self.run, leaks=True, args=["-R"]))
        self.assertFalse(utils_config.valgrind_wrapper(self.run, leaks=True, args=["-lR"]))


if __name__ == "__main__":
    unittest.main()
