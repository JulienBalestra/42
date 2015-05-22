import unittest
from subprocess import call, check_output
import os
import string

from pymake.pymake import PyMake
from libft_progess import Progress
from utils_config import SetLibftConfig, IterMethods


class TestLibAsserts(unittest.TestCase):
    debug_mod = False
    makefile = PyMake(os.path.split(os.path.dirname(__file__))[0] + "/libft/Makefile")
    lib_ft_progress = Progress("libft")

    @classmethod
    def setUpClass(cls):
        assert cls.lib_ft_progress.full_coverage() is True
        try:
            cls.makefile.make()
            cls.set_config = SetLibftConfig(cls.debug_mod)
            cls.test_methods = iter(IterMethods(cls))
            cls.ascii_printable = string.printable
        except Exception as e:
            cls.makefile.make_fclean()
            raise RuntimeError(e)

    @classmethod
    def tearDownClass(cls):
        if cls.debug_mod is False:
            cls.makefile.make_fclean()
            # print cls.lib_ft_progress
        else:
            raise RuntimeWarning("debug_mod is " + str(cls.debug_mod))

    def setUp(self):
        self.run = self.set_config.next_conf(self.test_methods.next())
        self.assertEqual(1, call(self.run))

    def tearDown(self):
        if self.debug_mod is False:
            os.remove(self.run)

    def test_absint(self):
        for number in [-5, 6, 2 ** 31 - 1, -2 ** 31, -2 ** 31 + 1]:
            self.assertEqual(str(abs(number)), check_output([self.run, str(number)]))

    def test_atoi(self):
        for num in str(range(-11, 11)):
            self.assertEqual(0, call([self.run, num]))
        for char_n_num in [" 11", "\t22", "\n33", "+44", " +55", "\t+66", "+77a7", " -99", "\t-111", "-222c2", "+-333",
                           "-+444", "c1"]:
            self.assertEqual(0, call([self.run, char_n_num]))
            
    def test_bubble_sort(self):
        self.assertEqual("aa,zz,", check_output([self.run, "zz", "aa"]))
        self.assertEqual("aa,zz,", check_output([self.run, "aa", "zz"]))
        self.assertEqual("aa,bb,zz,", check_output([self.run, "aa", "zz", "bb"]))
        self.assertEqual("aa,bb,zz,", check_output([self.run, "zz", "bb", "aa"]))

    def test_bzero(self):
        for args in [("2", "0", "0:0 0:0 "), ("1", "3", "0:0 ")]:
            self.assertEqual(args[2], check_output([self.run, args[0], args[1]]))

    def test_isalpha(self):
        for char in self.ascii_printable:
            self.assertEqual(0, call([self.run, char]))

    def test_isalnum(self):
        for char in self.ascii_printable:
            self.assertEqual(0, call([self.run, char]))

    def test_isascii(self):
        for char in self.ascii_printable:
            self.assertEqual(0, call([self.run, char]))

    def test_isblank(self):
        for char in self.ascii_printable:
            self.assertEqual(0, call([self.run, char]))

    def test_isdigit(self):
        for char in self.ascii_printable:
            self.assertEqual(0, call([self.run, char]))

    def test_isprint(self):
        for char in self.ascii_printable:
            self.assertEqual(0, call([self.run, char]))

    def test_itoa(self):
        for char_int in [0, 1, 10, -5, 111, -22, 1000, 2 ** 31 - 1, -2 ** 31, -2 ** 31 + 1]:
            self.assertEqual(0, call([self.run, str(char_int)]))

    def test_lstiter(self):
        self.assertEqual("12abc", check_output([self.run, "12", "abc"]))

    def test_lstmap(self):
        self.assertEqual("1234:4", check_output([self.run, "12", "abc"]))

    def test_lstadd_end(self):
        self.assertEqual("12:2->abc:3", check_output([self.run, "12", "abc"]))

    def test_lstdel(self):
        self.assertEqual(0, call([self.run, "12", "abc"]))

    def test_lstdelone(self):
        self.assertEqual("12:2->NULL", check_output([self.run, "12", "abc"]))

    def test_lstadd(self):
        self.assertEqual("abc:3->12:2", check_output([self.run, "12", "abc"]))

    def test_lstnew(self):
        self.assertEqual("toto:4", check_output([self.run, "toto"]))

    def test_lstsplit(self):
        for args in [("***salut****!**", "*", "2", "salut:!"),
                     ("test*me", "*", "2", "test:me"), ("   another test   ", " ", "2", "another:test"),
                     ("none", "*", "1", "none"),
                     ("one.test...here....", ".", "3", "one:test:here"), ("****", "*", "0", ""), ("", "*", "0", "")]:
            self.assertEqual(args[3], check_output([self.run, args[0], args[1], args[2]]))

    def test_memalloc(self):
        self.assertEqual(0, call([self.run, "2"]))

    def test_memccpy(self):
        for args in [("2", "0", "1", "2", "16843009:16843009 16843009:16843009 "), ("1", "3", "0", "3", "0:0 ")]:
            self.assertEqual(args[4], check_output([self.run, args[0], args[1], args[2], args[3]]))

    def test_memchr(self):
        for args in [("2", "0", "0"), ("1", "3", "0")]:
            output = check_output([self.run, args[0], args[1], args[2]]).split("==")
            self.assertTrue(output[0] == output[1])

    def test_memcmp(self):
        for args in [("2", "0", "1"), ("1", "3", "0"), ("2", "0", "0")]:
            output = check_output([self.run, args[0], args[1], args[2]]).split("==")
            self.assertTrue(output[0] == output[1])

    def test_memcpy(self):
        for args in [("2", "0", "1", "16843009:16843009 16843009:16843009 "), ("1", "3", "0", "0:0 ")]:
            self.assertEqual(args[3], check_output([self.run, args[0], args[1], args[2]]))

    def test_memdel(self):
        self.assertEqual(0, call([self.run, "2"]))

    def test_memmove(self):
        for args in [("2", "0", "2"), ("5", "9", "2")]:
            output = check_output([self.run, args[0], args[1], args[2]]).split("\n")
            before_move, after_move = output[0].split("!="), output[1].split("==")
            self.assertFalse(before_move[0] == before_move[1]), self.assertTrue(after_move[0] == after_move[1])

    def test_memset(self):
        for args in [("2", "0", "0:0 0:0 "), ("1", "3", "50529027:50529027 ")]:
            self.assertEqual(args[2], check_output([self.run, args[0], args[1]]))
    
    def test_nbrlen(self):
        self.assertEqual("1", check_output([self.run, "0"]))
        self.assertEqual("1", check_output([self.run, "1"]))
        self.assertEqual("2", check_output([self.run, "10"]))
        self.assertEqual("3", check_output([self.run, "101"]))
        self.assertEqual("4", check_output([self.run, "1101"]))

    def test_putchar(self):
        for my_str in ["test", "another test"]:
            self.assertEqual(my_str, check_output([self.run, my_str]))

    def test_putchar_fd(self):
        for my_str in ["test", "another test"]:
            self.assertEqual(my_str, check_output([self.run, my_str]))

    def test_putendl(self):
        for my_str in ["test", "another test"]:
            self.assertEqual(my_str + "\n", check_output([self.run, my_str]))

    def test_putendl_fd(self):
        for my_str in ["test", "another test"]:
            self.assertEqual(my_str + "\n", check_output([self.run, my_str]))

    def test_putnbr(self):
        for num in [0, 1, 10, 11, 22, 111, -1, -10, -11, -2222, 2 ** 31 - 1, -2 ** 31, -2 ** 31 + 1]:
            num = str(num)
            self.assertEqual(num, check_output([self.run, num]))

    def test_putnbr_fd(self):
        for num in [0, 1, 10, 11, 22, 111, -1, -10, -11, -2222, 2 ** 31 - 1, -2 ** 31, -2 ** 31 + 1]:
            num = str(num)
            self.assertEqual(num, check_output([self.run, num]))

    def test_putstr(self):
        for my_str in ["test", "another test"]:
            self.assertEqual(my_str, check_output([self.run, my_str]))

    def test_putstr_fd(self):
        for my_str in ["test", "another test"]:
            self.assertEqual(my_str, check_output([self.run, my_str]))

    def test_strcasestr(self):
        for args in [("1", "a", "(null)"), ("22", "b", "(null)"), ("b", "22", "(null)"),
                     ("aaabcc", "abc", "abcc"), ("0", "", "0"), ("abc", "abc", "abc"), ("ABC", "abc", "ABC"),
                     ("AABCC", 'abc', "ABCC")]:
            self.assertEqual(args[2], check_output([self.run, args[0], args[1]]))

    def test_strcat(self):
        for args in [("1", "a"), ("22", "b"), ("b", "22"), ("", "0"), ("0", "")]:
            try:
                self.assertEqual(0, call([self.run, args[0], args[1]]))
            except AssertionError:
                self.assertEqual(-6, call([self.run, args[0], args[1]]))

    def test_strchr(self):
        for args in [("1", "a", "(null)=(null)"), ("22", "b", "(null)=(null)"), ("b", "c", "(null)=(null)"),
                     ("aaabcc", "b", "bcc=bcc"), ("abc", "c", "c=c"), ("ABC", "A", "ABC=ABC")]:
            self.assertEqual(args[2], check_output([self.run, args[0], args[1]]))

    def test_strclr(self):
        for my_str in ["test", "another test"]:
            self.assertEqual("", check_output([self.run, my_str]))

    def test_strcmp(self):
        for args in [("aaa", "aaa"), ("bb", "bbb"), ("cccc", "ccc"), ("abc", "cba")]:
            self.assertEqual(0, call([self.run, args[0], args[1]]))

    def test_strcpy(self):
        for args in [("1", "a"), ("22", "b"), ("b", "22"), ("", "0"), ("0", "")]:
            try:
                self.assertEqual(0, call([self.run, args[0], args[1]]))
            except AssertionError:
                self.assertEqual(-6, call([self.run, args[0], args[1]]))

    def test_strdel(self):
        self.assertEqual(0, call([self.run, "3", "123"]))

    def test_strdup(self):
        self.assertEqual(0, call([self.run, "", "a", "bb"]))

    def test_strequ(self):
        for args in [("abc", "abc", "1"), ("abc", "aBc", "0"), ("abc", "wxc", "0"),
                     ("123", "abc", "0"), ("ABC", "AB", "0"), ("abcDEF", "abcDEf", "0")]:
            self.assertEqual(0, call([self.run, args[0], args[1], args[2]]))

    def test_striter(self):
        for my_str in ["test", "another test"]:
            self.assertEqual(my_str, check_output([self.run, my_str]))

    def test_striteri(self):
        for my_str in [("0123456789", "00112233445566778899"), ("another test", "0a1n2o3t4h5e6r7 8t9e10s11t")]:
            self.assertEqual(my_str[1], check_output([self.run, my_str[0]]))

    def test_strjoin(self):
        self.assertEqual(0, call([self.run, "123", "abc", "123abc"]))

    def test_strlcat(self):
        for args in [("1", "a", "1", "2=1:a"), ("1", "a", "2", "2=1:a"), ("22", "b", "2", "3=22:b"),
                     ("bb", "aa", "4", "4=bba:"), ("b", "22", "3", "3=b2:"),
                     ("b", "22", "8", "3=b22:2")]:
            self.assertEqual(args[3], check_output([self.run, args[0], args[1], args[2]]))

    def test_strlen(self):
        self.assertEqual("3", check_output([self.run, "123"]))
        self.assertEqual("0", check_output([self.run, ""]))

    def test_strmap(self):
        for my_str in ["Test", "Another Test"]:
            self.assertEqual(my_str.upper(), check_output([self.run, my_str]))

    def test_strmapi(self):
        for my_str in ["Test", "Another Test"]:
            self.assertEqual(my_str.upper(), check_output([self.run, my_str]))

    def test_strncat(self):
        for args in [("1", "a", "0"), ("1", "a", "1"), ("1", "a", "2"), ("22", "b", "1"), ("b", "22", "1"),
                     ("", "0", "1"), ("0", "", "1"), ("ccc", "333", "2"), ("ccc", "333", "8"),
                     ("to be ", "or not to be", "6")]:
            try:
                self.assertEqual(0, call([self.run, args[0], args[1], args[2]]))
            except AssertionError:
                self.assertEqual(-6, call([self.run, args[0], args[1], args[2]]))

    def test_strncmp(self):
        for args in [("aaa", "aaa", "2"), ("bb", "bbb", "3"), ("cccc", "ccc", "0"), ("abc", "cba", "3"),
                     ("abc", "abcde", "3")]:
            self.assertEqual(0, call([self.run, args[0], args[1], args[2]]))

    def test_strncpy(self):
        for args in [("1", "a", "0"), ("1", "a", "1"), ("1", "a", "2"), ("22", "b", "1"), ("b", "22", "1"),
                     ("", "0", "1"), ("0", "", "1"), ("ccc", "333", "2"), ("ccc", "333", "8")]:
            self.assertEqual(0, call([self.run, args[0], args[1], args[2]]))

    def test_strndup(self):
        for args in [("abc", "2", "ab"), ("abcd", "3", "abc"), ("abcd", "1", "a"), ("abcd", "8", "abcd")]:
            self.assertEqual(args[2], check_output([self.run, args[0], args[1]]))

    def test_strnequ(self):
        for args in [("abc", "abc", "3", "1"), ("abc", "aBc", "3", "0"), ("abc", "wxc", "3", "0"),
                     ("123", "abc", "3", "0"), ("ABCD", "ABCZ", "3", "1"), ("ABCD", "ABCZ", "4", "0")]:
            self.assertEqual(0, call([self.run, args[0], args[1], args[2], args[3]]))

    def test_strnew(self):
        self.assertEqual(0, call([self.run, "3", "123"]))

    def test_strnstr(self):
        for args in [("1", "a", "1", "(null)"), ("22", "b", "2", "(null)"),
                     ("b", "22", "1", "(null)"), ("aaabcc", "abc", "5", "abcc"),
                     ("abc", "abc", "3", "abc"), ("ABC", "abc", "3", "(null)")]:
            self.assertEqual(args[3], check_output([self.run, args[0], args[1], args[2]]))

    def test_strrchr(self):
        for args in [("1", "a", "(null)=(null)"), ("22", "b", "(null)=(null)"), ("b", "c", "(null)=(null)"),
                     ("aaabcc", "c", "c=c"), ("abc", "c", "c=c"), ("ABC", "A", "ABC=ABC")]:
            self.assertEqual(args[2], check_output([self.run, args[0], args[1]]))

    def test_strsplit(self):
        for args in [("***salut****!**", "*", "2", "salut:!"),
                     ("test*me", "*", "2", "test:me"), ("   another test   ", " ", "2", "another:test"),
                     ("none", "*", "1", "none"),
                     ("one.test...here....", ".", "3", "one:test:here"), ("****", "*", "0", ""), ("", "*", "0", "")
        ]:
            self.assertEqual(args[3], check_output([self.run, args[0], args[1], args[2]]))

    def test_strstr(self):
        for args in [("1", "a", "(null)=(null)"), ("22", "b", "(null)=(null)"), ("b", "22", "(null)=(null)"),
                     ("aaabcc", "abc", "abcc=abcc"), ("0", "", "0=0"), ("abc", "abc", "abc=abc")]:
            self.assertEqual(args[2], check_output([self.run, args[0], args[1]]))

    def test_strsub(self):
        self.assertEqual(0, call([self.run, "0123456789", "2", "5", "23456"]))

    def test_strtrim(self):
        for args in [("\t\t\n\t\t   ", ""), ("zz", "zz"), ("\t1234\n", "1234"), (" 123 ", "123"), ("123", "123"),
                     ("123\n", "123"),
                     (" \t 123", "123"),
                     ("12 3", "12 3"), (" 1 2 3 ", "1 2 3"), ("\t\n  \tAAA \t BBB\t\n  \t", "AAA \t BBB")
        ]:
            self.assertEqual(0, call([self.run, args[0], args[1]]))

    def test_tolower(self):
        for char in self.ascii_printable:
            self.assertEqual(0, call([self.run, char]))

    def test_toupper(self):
        for char in self.ascii_printable:
            self.assertEqual(0, call([self.run, char]))


class TestMouliTest(unittest.TestCase):
    output_42 = os.path.split(os.path.dirname(__file__))[0] + "/tests_logs/libft_log"
    logs_moulitest = list()
    moulitest_dir = os.path.split(os.path.dirname(__file__))[0] + "/moulitest/"

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
            ["make", "-C", TestMouliTest.moulitest_dir, "libft_bonus"])
        output = output.split("[36;1m-------STARTING ALL UNIT TESTS-------\x1b[0m ]\n")[1]
        output = output.split("\n[ \x1b[36;1m----------END OF UNIT TESTS----------\x1b[0m ]")[0]
        with open(output_file, 'w') as log_file:
            log_file.write(output)
        return output.split("\n")

    def test_00_part1_ft_bzero(self):
        self.assertEqual(98, len(self.method))

    def test_00_part1_ft_atoi(self):
        self.assertEqual(446, len(self.method))

    def test_00_part1_ft_isalnum(self):
        self.assertEqual(290, len(self.method))

    def test_00_part1_ft_isalpha(self):
        self.assertEqual(290, len(self.method))

    def test_00_part1_ft_isascii(self):
        self.assertEqual(290, len(self.method))

    def test_00_part1_ft_isdigit(self):
        self.assertEqual(290, len(self.method))

    def test_00_part1_ft_isprint(self):
        self.assertEqual(290, len(self.method))

    def test_00_part1_ft_memccpy(self):
        self.assertEqual(86, len(self.method))

    def test_00_part1_ft_memchr(self):
        self.assertEqual(74, len(self.method))

    def test_00_part1_ft_memcmp(self):
        self.assertEqual(134, len(self.method))

    def test_00_part1_ft_memcpy(self):
        self.assertEqual(74, len(self.method))

    def test_00_part1_ft_memmove(self):
        self.assertEqual(86, len(self.method))

    def test_00_part1_ft_memset(self):
        self.assertEqual(98, len(self.method))

    def test_00_part1_ft_strcat(self):
        self.assertEqual(74, len(self.method))

    def test_00_part1_ft_strchr(self):
        self.assertEqual(110, len(self.method))

    def test_00_part1_ft_strcmp(self):
        self.assertEqual(122, len(self.method))

    def test_00_part1_ft_strcpy(self):
        self.assertEqual(86, len(self.method))

    def test_00_part1_ft_strdup(self):
        self.assertEqual(98, len(self.method))

    def test_00_part1_ft_strlcat(self):
        self.assertEqual(146, len(self.method))

    def test_00_part1_ft_strlen(self):
        self.assertEqual(110, len(self.method))

    def test_00_part1_ft_strncat(self):
        self.assertEqual(86, len(self.method))

    def test_00_part1_ft_strncmp(self):
        self.assertEqual(122, len(self.method))

    def test_00_part1_ft_strncpy(self):
        self.assertEqual(86, len(self.method))

    def test_00_part1_ft_strnstr(self):
        self.assertEqual(110, len(self.method))

    def test_00_part1_ft_strrchr(self):
        self.assertEqual(110, len(self.method))

    def test_00_part1_ft_strstr(self):
        self.assertEqual(170, len(self.method))

    def test_00_part1_ft_tolower(self):
        self.assertEqual(290, len(self.method))

    def test_00_part1_ft_toupper(self):
        self.assertEqual(290, len(self.method))

    def test_01_part2_ft_itoa(self):
        self.assertEqual(110, len(self.method))

    def test_01_part2_ft_memalloc(self):
        self.assertEqual(86, len(self.method))

    def test_01_part2_ft_memdel(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_putchar(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_putchar_fd(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_putendl(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_putendl_fd(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_putnbr(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_putnbr_fd(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_putstr(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_putstr_fd(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_strclr(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_strdel(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_strequ(self):
        self.assertEqual(98, len(self.method))

    def test_01_part2_ft_striter(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_striteri(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_strjoin(self):
        self.assertEqual(86, len(self.method))

    def test_01_part2_ft_strmap(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_strmapi(self):
        self.assertEqual(74, len(self.method))

    def test_01_part2_ft_strnequ(self):
        self.assertEqual(110, len(self.method))

    def test_01_part2_ft_strnew(self):
        self.assertEqual(98, len(self.method))

    def test_01_part2_ft_strsplit(self):
        self.assertEqual(134, len(self.method))

    def test_01_part2_ft_strsub(self):
        self.assertEqual(98, len(self.method))

    def test_01_part2_ft_strtrim(self):
        self.assertEqual(110, len(self.method))

    def test_02_bonus_ft_lstadd(self):
        self.assertEqual(74, len(self.method))

    def test_02_bonus_ft_lstdel(self):
        self.assertEqual(74, len(self.method))

    def test_02_bonus_ft_lstdelone(self):
        self.assertEqual(74, len(self.method))

    def test_02_bonus_ft_lstiter(self):
        self.assertEqual(74, len(self.method))

    def test_02_bonus_ft_lstmap(self):
        self.assertEqual(74, len(self.method))

    def test_02_bonus_ft_lstnew(self):
        self.assertEqual(74, len(self.method))


if __name__ == "__main__":
    unittest.main()