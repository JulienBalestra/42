import unittest
from subprocess import call, check_output
import os
from glob import glob

from utils_config import IterMethods
from pymake.pymake import PyMake


class TestGetNextLineMore(unittest.TestCase):
    debug_mod = False
    base_path = os.path.split(os.path.dirname(__file__))[0]
    context_path, binary_path = base_path + "/get_next_line/", base_path + "/tests/gnl_main/gnl"
    makefile = PyMake(context_path + "libft/Makefile")
    gcc_f, lib_ft_includes = ["gcc", "-Wall", "-Wextra", "-Werror"], ["-I", context_path + "libft/includes"]

    @classmethod
    def setUpClass(cls):
        try:
            if os.path.isfile(cls.binary_path):
                os.remove(cls.binary_path)
            cls.makefile.make()
            cls.config = iter(IterMethods(cls))
        except Exception as e:
            cls.makefile.make_fclean()
            raise RuntimeError(e)

    @classmethod
    def tearDownClass(cls):
        if cls.debug_mod is False:
            [os.remove(obj) for obj in glob("*.o")], os.remove(cls.binary_path), cls.makefile.make_fclean()
        else:
            raise RuntimeWarning("debug_mod is " + str(cls.debug_mod))

    def compilation(self, run=False):
        if run is True:
            self.assertEqual(0, call(self.gcc_f + self.lib_ft_includes + ["-c", self.context_path + "get_next_line.c"]))
            self.assertEqual(0, call(
                self.gcc_f + self.lib_ft_includes + ["-I", self.context_path, "-c", "gnl_main/gnl_main.c"]))
            self.assertEqual(0, call(
                self.gcc_f + glob("*.o") + ["-o", self.binary_path, "-L", self.context_path + "libft/", "-lft"]))
        return os.path.isfile(self.binary_path)

    def setUp(self):
        if self.compilation() is False:
            self.compilation(run=True)
        self.method = "_" + self.config.next()

    def test00(self):
        self.assertEqual("1:12345678,0", check_output([self.binary_path, self.binary_path + self.method]))

    def test01(self):
        self.assertEqual("1:1234567890,0", check_output([self.binary_path, self.binary_path + self.method]))

    def test02(self):
        self.assertEqual("1:12,0", check_output([self.binary_path, self.binary_path + self.method]))

    def test03(self):
        self.assertEqual("1:123456,1:abcdef,0", check_output([self.binary_path, self.binary_path + self.method]))

    def test04(self):
        self.assertEqual("1:1234567890,1:abcdefghij,0",
                         check_output([self.binary_path, self.binary_path + self.method]))

    def test05(self):
        self.assertEqual("1:12,1:34,1:56,1:78,1:90,0", check_output([self.binary_path, self.binary_path + self.method]))

    def test06(self):
        self.assertEqual("1:123,1:,1:4,1:,1:5,1:,1:6,0",
                         check_output([self.binary_path, self.binary_path + self.method]))

    def test07(self):
        self.assertEqual("1:,1:,1:,1:,0", check_output([self.binary_path, self.binary_path + self.method]))

    def test08(self):
        self.assertEqual(
            "1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:," +
            "1:1,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,1:,0",
            check_output([self.binary_path, self.binary_path + self.method]))

    def test09(self):
        self.assertEqual("1:12345678,1:,1:,1:,1:,1:,1:,1:,1:abc,0",
                         check_output([self.binary_path, self.binary_path + self.method]))

    def test10(self):
        self.assertEqual("1:1234567,1:abcdef,0", check_output([self.binary_path, self.binary_path + self.method]))

    def test11(self):
        self.assertEqual("1:1,1:2,1:3,1:4,1:5,1:6,1:7,1:8,1:9,0",
                         check_output([self.binary_path, self.binary_path + self.method]))

    def test12(self):
        self.assertEqual("1:12,1:3,1:45,1:6789,0", check_output([self.binary_path, self.binary_path + self.method]))

    def test13(self):
        self.assertEqual("1:abc,1:,0", check_output([self.binary_path, self.binary_path + self.method]))


class TestGetNextLineMain(unittest.TestCase):
    output_42 = os.path.split(os.path.dirname(__file__))[0] + "/tests_logs/gnl_log"
    moulitest_dir = os.path.split(os.path.dirname(__file__))[0] + "/moulitest/"
    logs_moulitest = list()

    @classmethod
    def setUpClass(cls):
        cls.config = iter(IterMethods(cls))
        cls.logs_moulitest = cls.build_moulitest(cls.output_42)
        cls.logs_moulitest.sort()

    @classmethod
    def tearDownClass(cls):
        if len(cls.logs_moulitest) > 0:
            for line in cls.logs_moulitest:
                print line
                raise AssertionError
        TestGetNextLineMore.makefile.make_fclean()

    def get_current_log_line(self, method):
        for i, line in enumerate(self.logs_moulitest):
            if method in line:
                if "[Ok !]" in line:
                    self.logs_moulitest.pop(i)
                return line

    def setUp(self):
        self.method = self.get_current_log_line(self.config.next()[5:])

    @staticmethod
    def build_moulitest(output_file):
        output = check_output(
            ["make", "-C", TestGetNextLineMain.moulitest_dir, "gnl"])
        output = output.split("[36;1m-------STARTING ALL UNIT TESTS-------\x1b[0m ]\n")[1]
        output = output.split("\n[ \x1b[36;1m----------END OF UNIT TESTS----------\x1b[0m ]")[0]
        with open(output_file, 'w') as log_file:
            log_file.write(output)
        return output.split("\n")

    def test_17_test_line_of_16_without_nl(self):
        self.assertEqual(74, len(self.method))

    def test_07_test_two_lines_of_08(self):
        self.assertEqual(74, len(self.method))

    def test_04_test_return_values(self):
        self.assertEqual(74, len(self.method))

    def test_41_hard_test_large_file(self):
        self.assertEqual(74, len(self.method))

    def test_15_test_line_without_nl(self):
        self.assertEqual(74, len(self.method))

    def test_02_test_eof_with_close(self):
        self.assertEqual(74, len(self.method))

    def test_03_test_medium_string(self):
        self.assertEqual(74, len(self.method))

    def test_11_test_few_lines_of_16(self):
        self.assertEqual(74, len(self.method))

    def test_10_test_two_lines_of_16(self):
        self.assertEqual(74, len(self.method))

    def test_40_hard_test_medium_string(self):
        self.assertEqual(74, len(self.method))

    def test_16_test_line_of_8_without_nl(self):
        self.assertEqual(74, len(self.method))

    def test_05_test_error_handling(self):
        self.assertEqual(74, len(self.method))

    def test_06_test_line_of_08(self):
        self.assertEqual(74, len(self.method))

    def test_01_test_simple(self):
        self.assertEqual(74, len(self.method))

    def test_13_test_two_lines_of_4(self):
        self.assertEqual(74, len(self.method))

    def test_09_test_line_of_16(self):
        self.assertEqual(74, len(self.method))

    def test_08_test_few_lines_of_08(self):
        self.assertEqual(74, len(self.method))

    def test_14_test_few_lines_of_4(self):
        self.assertEqual(74, len(self.method))

    def test_12_test_line_of_4(self):
        self.assertEqual(74, len(self.method))

    def test_42_hard_test_one_big_fat_line(self):
        self.assertEqual(74, len(self.method))

    def test_30_bonus_multiple_fd(self):
        self.assertEqual(74, len(self.method))


if __name__ == "__main__":
    unittest.main()