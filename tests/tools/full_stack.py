import unittest
from time import time
from sys import stdout
import os

import test_gnl
import test_libft


class TestIncrementBuff(unittest.TestCase):
    mylog = os.path.split(os.path.dirname(__file__))[0] + "/tests_logs/mylog"
    max_buffer_size = 500
    old_buffer = None

    @classmethod
    def setUpClass(cls):
        cls.lib, cls.gnl = suite(test_libft.TestLibAsserts), suite(test_gnl.TestGetNextLineMore)
        cls.old_buffer = test_gnl.read_include(only_buff_size=True)
    
    @classmethod
    def tearDownClass(cls):
        assert 5 == test_gnl.read_include(only_buff_size=True)

    def counting_tests(self):
        return self.gnl.countTestCases() * (self.max_buffer_size - 1)

    @staticmethod
    def read_results(mylog):
        with open(mylog, 'r') as fd:
            return fd.read()

    @staticmethod
    def parse_results(results):
        if "failures" in results:
            raise AssertionError

    def test_buffer(self, pprint=False):
        start = time()
        with open(self.mylog, 'w') as fd:
            runner = unittest.TextTestRunner(stream=fd, verbosity=1)
            for i in range(1, self.max_buffer_size, 20):
                if pprint is True:
                    stdout.write("\r%s%%" % (((i + 1) * 100) / self.max_buffer_size)), stdout.flush()
                assert test_gnl.read_include(only_buff_size=True) != i
                test_gnl.change_buff_size(i)
                runner.run(self.gnl)
                fd.write("BS %s\n%s\n" % (str(i), "-" * 70))
                assert test_gnl.read_include(only_buff_size=True) == i
            test_gnl.change_buff_size(str(self.old_buffer))
            assert test_gnl.read_include(only_buff_size=True) == self.old_buffer
            ending = "Ran %s tests in %ss !!" % (str(self.counting_tests()), str(round(time() - start, 3)))
            fd.write(ending)

    def test_results(self):
        self.parse_results(self.read_results(self.mylog))


class TestGetNextLineMore(test_gnl.TestGetNextLineMore):
    pass


def suite(test_case_class):
    test_suite = unittest.TestSuite()
    test_suite.addTests(unittest.makeSuite(test_case_class))
    return test_suite




if __name__ == "__main__":
    unittest.main()
