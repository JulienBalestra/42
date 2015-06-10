import unittest
import os
from math import sqrt
from subprocess import check_output, call

import computorv1.solver as solver
import computorv1.web_engine as web_engine


class TestFraction(unittest.TestCase):
    def test_hcf_0(self):
        self.assertEqual(5, solver.my_hcf(5, 25))

    def test_hcf_1(self):
        self.assertEqual(3, solver.my_hcf(15, 33))

    def test_hcf_2(self):
        self.assertEqual(1, solver.my_hcf(7, 11))

    def test_hcf_3(self):
        with self.assertRaises(ZeroDivisionError):
            solver.my_hcf(0, 13)

    def test_hcf_4(self):
        with self.assertRaises(TypeError):
            solver.my_hcf(0.5, 13)

    def test_hcf_5(self):
        self.assertEqual(1, solver.my_hcf(7551515454, 48454684864465))

    def test_hcf_6(self):
        self.assertEqual(3, solver.my_hcf(755151, 4845468))

    def test_process_result_00(self):
        self.assertEqual("5 / 8", solver.process_result(5, 8))

    def test_process_result_01(self):
        self.assertEqual("1 / 2", solver.process_result(4, 8))

    def test_process_result_02(self):
        self.assertEqual("1 / 2", solver.process_result(1, 2))

    def test_process_result_03(self):
        self.assertEqual(2, solver.process_result(2, 1))

    def test_process_result_04(self):
        self.assertEqual(0, solver.process_result(0, 1))

    def test_process_result_05(self):
        self.assertEqual(0.0505, solver.process_result(101, 2000))

    def test_process_result_06(self):
        self.assertEqual(0.9375, solver.process_result(15, 16))

    def test_process_result_07(self):
        self.assertEqual(0.001, solver.process_result(50, 50000))

    def test_process_result_08(self):
        self.assertEqual('1 / 100', solver.process_result(50, 5000))


class TestNaturalForm(unittest.TestCase):
    def test_00_raise(self):
        with self.assertRaises(ArithmeticError):
            eq = "1*X^0+2*X^0+3*X^0+4*X^0+1*X^0+2*X^0+3*X^0+4*X^0"
            solver.Equation._format_natural_form(eq)

    def test_x0_00(self):
        eq = "1 = 0"
        self.assertEqual('1*X^0=0', solver.Equation._format_natural_form(eq))

    def test_x0_01(self):
        eq = "0 = 1"
        self.assertEqual('0=1*X^0', solver.Equation._format_natural_form(eq))

    def test_x0_02(self):
        eq = "0 = 1.5"
        self.assertEqual('0=1.5*X^0', solver.Equation._format_natural_form(eq))

    def test_x0_03(self):
        eq = "1 = 5"
        self.assertEqual('1*X^0=5*X^0', solver.Equation._format_natural_form(eq))

    def test_x0_04(self):
        eq = "5 = 1"
        self.assertEqual('5*X^0=1*X^0', solver.Equation._format_natural_form(eq))

    def test_x0_05(self):
        eq = "2 * X^1 = 0"
        self.assertEqual('2*X^1=0', solver.Equation._format_natural_form(eq))

    def test_x0_06(self):
        eq = "0 = 2 * X^1 "
        self.assertEqual('0=2*X^1', solver.Equation._format_natural_form(eq))

    def test_x0_07(self):
        eq = "0 = 2 * X^1 + 1"
        self.assertEqual('0=2*X^1+1*X^0', solver.Equation._format_natural_form(eq))

    def test_x0_08(self):
        eq = "2 * X^1 + 1=0"
        self.assertEqual('2*X^1+1*X^0=0', solver.Equation._format_natural_form(eq))

    def test_x0_09(self):
        eq = "2 * X^2 + 1=0"
        self.assertEqual('2*X^2+1*X^0=0', solver.Equation._format_natural_form(eq))

    def test_x0_10(self):
        eq = "2 * X^2 + 1 + 2=0"
        self.assertEqual('2*X^2+1*X^0+2*X^0=0', solver.Equation._format_natural_form(eq))

    def test_x0_11(self):
        eq = "1 + 2 + 3 + 4=0"
        self.assertEqual('1*X^0+2*X^0+3*X^0+4*X^0=0', solver.Equation._format_natural_form(eq))

    def test_x0_12(self):
        eq = "0=1 + 2 + 3 + 4"
        self.assertEqual('0=1*X^0+2*X^0+3*X^0+4*X^0', solver.Equation._format_natural_form(eq))

    def test_x0_13(self):
        eq = "1 + 2 + 3 + 4=1 + 2 + 3 + 4"
        self.assertEqual('1*X^0+2*X^0+3*X^0+4*X^0=1*X^0+2*X^0+3*X^0+4*X^0', solver.Equation._format_natural_form(eq))

    def test_x0_14(self):
        eq = "-1 =0"
        self.assertEqual('-1*X^0=0', solver.Equation._format_natural_form(eq))

    def test_x0_15(self):
        eq = "+1 =0"
        self.assertEqual('+1*X^0=0', solver.Equation._format_natural_form(eq))

    def test_x0_16(self):
        eq = "+1 =-0"
        self.assertEqual('+1*X^0=0', solver.Equation._format_natural_form(eq))

    def test_x0_17(self):
        eq = "+1 =+0"
        self.assertEqual('+1*X^0=0', solver.Equation._format_natural_form(eq))

    def test_x0_18(self):
        eq = "+1 - 2 =0"
        self.assertEqual('+1*X^0-2*X^0=0', solver.Equation._format_natural_form(eq))

    def test_x1_00(self):
        eq = "1*X = 0"
        self.assertEqual('1*X^1=0', solver.Equation._format_natural_form(eq))

    def test_x1_01(self):
        eq = "1*X + 1*X = 0"
        self.assertEqual('1*X^1+1*X^1=0', solver.Equation._format_natural_form(eq))

    def test_x1_02(self):
        eq = "1*X - 1*x = 0"
        self.assertEqual('1*X^1-1*X^1=0', solver.Equation._format_natural_form(eq))

    def test_x1_03(self):
        eq = "1*X^0 + 1*X = 0"
        self.assertEqual('1*X^0+1*X^1=0', solver.Equation._format_natural_form(eq))

    def test_x1_04(self):
        eq = "1*X^0 + 1*X - 5 * 1*X^2 = 0"
        self.assertEqual('1*X^0+1*X^1-5*1*X^2=0', solver.Equation._format_natural_form(eq))

    def test_x1_05(self):
        eq = "7 * X^12 + 1*X = 0"
        self.assertEqual('7*X^12+1*X^1=0', solver.Equation._format_natural_form(eq))

    def test_x1_06(self):
        eq = "- 1*X = 0"
        self.assertEqual('-1*X^1=0', solver.Equation._format_natural_form(eq))

    def test_x1_07(self):
        eq = "- 1*X + 1*X -1*X = 0"
        self.assertEqual('-1*X^1+1*X^1-1*X^1=0', solver.Equation._format_natural_form(eq))

    def test_xn_00(self):
        eq = "X^1= 0"
        self.assertEqual('1*X^1=0', solver.Equation._format_natural_form(eq))

    def test_xn_01(self):
        eq = "-X^1= 0"
        self.assertEqual('-1*X^1=0', solver.Equation._format_natural_form(eq))

    def test_xn_02(self):
        eq = "-1*X^1-X^12= 0"
        self.assertEqual('-1*X^1-1*X^12=0', solver.Equation._format_natural_form(eq))

    def test_xn_03(self):
        eq = "X^5= 0"
        self.assertEqual('1*X^5=0', solver.Equation._format_natural_form(eq))

    def test_xn_04(self):
        eq = "X^2 + X^1 + X^0= X^2 + X^1 + X^0"
        self.assertEqual('1*X^2+1*X^1+1*X^0=1*X^2+1*X^1+1*X^0', solver.Equation._format_natural_form(eq))

    def test_xx_00(self):
        eq = "+   00 =    11 * X^0 "
        self.assertEqual('0=11*X^0', solver.Equation._format_natural_form(eq))

    def test_xx_01(self):
        eq = "+   00 = +   101 * X^0 "
        self.assertEqual('0=+101*X^0', solver.Equation._format_natural_form(eq))

    def test_xx_02(self):
        eq = "+   00 = +   101 * X^01 "
        self.assertEqual('0=+101*X^1', solver.Equation._format_natural_form(eq))

    def test_xx_03(self):
        eq = "+   00 = +   101 * X^000010 "
        self.assertEqual('0=+101*X^10', solver.Equation._format_natural_form(eq))

    def test_xx_04(self):
        eq = "+   00 = +   101 * X^000011 "
        self.assertEqual('0=+101*X^11', solver.Equation._format_natural_form(eq))

    def test_xx_05(self):
        eq = "+   00 = +   101 * X^0100011 "
        self.assertEqual('0=+101*X^100011', solver.Equation._format_natural_form(eq))

    def test_xr_00(self):
        eq = "x * 2 = 0"
        self.assertEqual('2*X^1=0', solver.Equation._format_natural_form(eq))

    def test_xr_01(self):
        eq = "5 + x * 2 = 0"
        self.assertEqual('5*X^0+2*X^1=0', solver.Equation._format_natural_form(eq))

    def test_xr_02(self):
        eq = "5*X^2 + x * 2 = 0"
        self.assertEqual('5*X^2+2*X^1=0', solver.Equation._format_natural_form(eq))

    def test_xf_00(self):
        eq = "5X^2 = 0"
        self.assertEqual('5*X^2=0', solver.Equation._format_natural_form(eq))

    def test_xf_01(self):
        eq = "5X^2 + 2x= 0"
        self.assertEqual('5*X^2+2*X^1=0', solver.Equation._format_natural_form(eq))

    def test_xf_02(self):
        eq = "5X^2 + 2x - 7.77x= 0"
        self.assertEqual('5*X^2+2*X^1-7.77*X^1=0', solver.Equation._format_natural_form(eq))

    def test_xf_03(self):
        eq = "5X^2 + 2x - 007.77x= 0"
        self.assertEqual('5*X^2+2*X^1-7.77*X^1=0', solver.Equation._format_natural_form(eq))

    def test_xf_04(self):
        eq = "5X^2 + 2x - 0000000x= 0"
        self.assertEqual('5*X^2+2*X^1-0*X^1=0', solver.Equation._format_natural_form(eq))


class TestSolver(unittest.TestCase):
    context_path = os.path.split(os.path.dirname(__file__))[0] + "/computorv1"
    pos_eq = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
    neg_eq = "7 * X^0 + 5 * X^1 + 3 * X^2 = 0"
    null = open(os.devnull, 'w')

    def test_check_n_format_true(self):
        check = solver.Equation(self.pos_eq)
        self.assertEqual(self.pos_eq, str(check))

        check = solver.Equation(self.neg_eq)
        self.assertEqual(self.neg_eq, str(check))

        eq = "5 * X^0 = 5 * X^0"
        check = solver.Equation(eq)
        self.assertEqual(eq, str(check))

        eq = "5*X^0=5*X^0"
        check = solver.Equation(eq)
        self.assertEqual('5 * X^0 = 5 * X^0', str(check))

        eq = "5    *X^0=5*X^0"
        check = solver.Equation(eq)
        self.assertEqual('5 * X^0 = 5 * X^0', str(check))

        eq = "5    *X^0   =   5*\tX^0"
        check = solver.Equation(eq)
        self.assertEqual('5 * X^0 = 5 * X^0', str(check))

        eq = "5 * X^0=5 * X^0"
        check = solver.Equation(eq)
        self.assertEqual('5 * X^0 = 5 * X^0', str(check))

    def test_check_n_format_true_more(self):
        eq = "10 * X^0= -5 * X^0"
        check = solver.Equation(eq)
        self.assertEqual('10 * X^0 = - 5 * X^0', str(check))

        eq = "10 * X^0= +5 * X^0"
        check = solver.Equation(eq)
        self.assertEqual('10 * X^0 = 5 * X^0', str(check))

        eq = "-10 * X^0= +5 * X^0"
        check = solver.Equation(eq)
        self.assertEqual('- 10 * X^0 = 5 * X^0', str(check))

        eq = "+10 * X^0= +5 * X^0"
        check = solver.Equation(eq)
        self.assertEqual('10 * X^0 = 5 * X^0', str(check))

        eq = "  +   10 * X^0 = -   5 * X^0"
        check = solver.Equation(eq)
        self.assertEqual('10 * X^0 = - 5 * X^0', str(check))

        eq = "  +   10 * X^0 = -   0"
        check = solver.Equation(eq)
        self.assertEqual('10 * X^0 = 0', str(check))

        eq = "  +   10 * X^0 = +   0"
        check = solver.Equation(eq)
        self.assertEqual('10 * X^0 = 0', str(check))

        eq = "-   0 = +   10 * X^0 "
        check = solver.Equation(eq)
        self.assertEqual('0 = 10 * X^0', str(check))

        eq = "+   0 = +   10 * X^0 "
        check = solver.Equation(eq)
        self.assertEqual('0 = 10 * X^0', str(check))

    def test_check_n_format_true_useless_zero(self):
        eq = "+   00 = +   10 * X^0 "
        check = solver.Equation(eq)
        self.assertEqual('0 = 10 * X^0', str(check))

        eq = "10 * X^0= -0000"
        check = solver.Equation(eq)
        self.assertEqual('10 * X^0 = 0', str(check))

        eq = "10 * X^0= +0000"
        check = solver.Equation(eq)
        self.assertEqual('10 * X^0 = 0', str(check))

        eq = "10 * X^0= 0."
        check = solver.Equation(eq)
        self.assertEqual('10 * X^0 = 0', str(check))

        eq = "0. = 10 * X^0"
        check = solver.Equation(eq)
        self.assertEqual('0 = 10 * X^0', str(check))

        eq = "10 * X^0= 0.0"
        check = solver.Equation(eq)
        self.assertEqual('10 * X^0 = 0', str(check))

        eq = "0.0 = 10 * X^0"
        check = solver.Equation(eq)
        self.assertEqual('0 = 10 * X^0', str(check))

        eq = "0. = 10 * X^0"
        check = solver.Equation(eq)
        self.assertEqual('0 = 10 * X^0', str(check))

        eq = "0,0 = 10 * X^0"
        check = solver.Equation(eq)
        self.assertEqual('0 = 10 * X^0', str(check))

        eq = "0, = 10,0 * X^0"
        check = solver.Equation(eq)
        self.assertEqual('0 = 10.0 * X^0', str(check))

    def test_check_n_format_raise(self):
        eq = "5 * X^0="
        with self.assertRaises(ArithmeticError):
            check = solver.Equation(eq)
            self.assertEqual(None, check.f_input)

        eq = "zzzzzz"
        with self.assertRaises(ArithmeticError):
            check = solver.Equation(eq)
            self.assertEqual(None, check.f_input)

        eq = "0 = 0"
        with self.assertRaises(ArithmeticError):
            check = solver.Equation(eq)
            self.assertEqual(None, check.f_input)

        eq = "5 * X^ + "
        with self.assertRaises(ArithmeticError):
            check = solver.Equation(eq)
            self.assertEqual(None, check.f_input)

        eq = "5 * X^0 = 5 * X^0 toto"
        with self.assertRaises(ArithmeticError):
            check = solver.Equation(eq)
            self.assertEqual(None, check.f_input)

        eq = "5 * X^0 + toto - 1 * X^1 = 5 * X^0"
        with self.assertRaises(ArithmeticError):
            check = solver.Equation(eq)
            self.assertEqual(None, check.f_input)

        eq = "5 * X^0.1 - 1 * X^1 = 5 * X^0"
        with self.assertRaises(ArithmeticError):
            check = solver.Equation(eq)
            self.assertEqual(None, check.f_input)

        eq = ".0 * X^0 + 1 * X^1 = 5 * X^0"
        with self.assertRaises(ArithmeticError):
            check = solver.Equation(eq)
            self.assertEqual(None, check.f_input)

        eq = "++5 * X^0 = 0"
        with self.assertRaises(ArithmeticError):
            check = solver.Equation(eq)
            self.assertEqual(None, check.f_input)

        eq = "+- 5 * X^0 = 0"
        with self.assertRaises(ArithmeticError):
            check = solver.Equation(eq)
            self.assertEqual(None, check.f_input)

    def test__get_reduced_form(self):
        check = solver.Equation(self.pos_eq)
        self.assertEqual({'X^1': 4.0, 'X^0': 4.0, 'X^2': -9.3}, check._process_reduced_form())

        check = solver.Equation(self.neg_eq)
        self.assertEqual({'X^1': 5.0, 'X^0': 7.0, 'X^2': 3.0}, check._process_reduced_form())

    def test_process_degree_0(self):
        check = solver.Equation(self.pos_eq)
        self.assertEqual(2, check._process_degree())

    def test_process_degree_01(self):
        check = solver.Equation(self.neg_eq)
        self.assertEqual(2, check._process_degree())

    def test_process_degree_02(self):
        check = solver.Equation("5 * X^0 = 5 * X^0")
        self.assertEqual(0, check._process_degree())

    def test_process_degree_03(self):
        check = solver.Equation("6 * X^0 = 5 * X^0")
        self.assertEqual(0, check._process_degree())

    def test_process_degree_04(self):
        check = solver.Equation("6 * X^1 = 5 * X^0")
        self.assertEqual(1, check._process_degree())

    def test_process_degree_05(self):
        check = solver.Equation("5 * X^1 = 5 * X^1")
        self.assertEqual(0, check._process_degree())

    def test_process_degree_06(self):
        check = solver.Equation("5 * X^2 = 5 * X^2")
        self.assertEqual(0, check._process_degree())

    def test_process_degree_07(self):
        check = solver.Equation("5 * X^2 + 7 * X^1 = 5 * X^2")
        self.assertEqual(1, check._process_degree())

    def test_process_degree_08(self):
        check = solver.Equation("-5 * X^2 + 7 * X^1 = - 5 * X^2")
        self.assertEqual(1, check._process_degree())

    def test_process_degree_09(self):
        check = solver.Equation(" + 5 * X^2 + 7 * X^1 = + 5 * X^2")
        self.assertEqual(1, check._process_degree())

    def test_process_degree_10(self):
        check = solver.Equation(" + 5 * X^2 + 7 * X^1 = 5 * X^2")
        self.assertEqual(1, check._process_degree())

    def test_solve_two_0(self):
        check = solver.Equation(self.pos_eq)
        check.solve()
        self.assertEqual(164.8, check.discriminant)
        self.assertEqual((-0.47513146390886934, 0.9052389907905898), check.solution)

    def test_solve_two_1(self):
        check = solver.Equation(self.neg_eq)
        check.solve()
        self.assertEqual(-59., check.discriminant)
        self.assertEqual(('5 / -6 + i1.28019095798',
                          '5 / -6 - i1.28019095798'), check.solution)

    def test_solve_one(self):
        check = solver.Equation("6 * X^1 = 5 * X^0")
        check.solve()
        self.assertIsNone(check.discriminant)
        self.assertEqual(('5 / 6',), check.solution)

    def test_solve_zero(self):
        check = solver.Equation("5 * X^0 = 5 * X^0")
        check.solve()
        self.assertIsNone(check.discriminant)
        self.assertEqual((True,), check.solution)

    def test_solve_zero_1(self):
        check = solver.Equation("6 * X^0 = 5 * X^0")
        check.solve()
        self.assertIsNone(check.discriminant)
        self.assertEqual((False,), check.solution)

    def test_solve_three(self):
        check = solver.Equation("6 * X^3 = 5 * X^0")
        check.solve()
        self.assertIsNone(check.discriminant)
        self.assertEqual((False,), check.solution)

    def test_display_solution_d20(self):
        # d2 > 0
        expect = ['Original Equation: 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0',
                  'Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0',
                  'Polynomial degree: 2',
                  'Discriminant is strictly positive, the two solutions are:',
                  '-0.475131463909',
                  '0.905238990791']
        check = solver.Equation(self.pos_eq)
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d21(self):
        # d2 > 0
        expect = ["Original Equation: 6 * X^0 + 11 * X^1 + 5 * X^2 = 1 * X^0 + 1 * X^1",
                  'Reduced form: 5 * X^0 + 10 * X^1 + 5 * X^2 = 0',
                  'Polynomial degree: 2',
                  'Discriminant is null, the solution is:',
                  '-1']
        check = solver.Equation("6 * X^0 + 11 * X^1 + 5 * X^2 = 1 * X^0 + 1 * X^1")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d22(self):
        # d2 > 0
        expect = ["Original Equation: 5 * X^0 + 13 * X^1 + 3 * X^2 = 1 *	X^0 + 1 * X^1",
                  "Formatted Equation: 5 * X^0 + 13 * X^1 + 3 * X^2 = 1 * X^0 + 1 * X^1",
                  'Reduced form: 4 * X^0 + 12 * X^1 + 3 * X^2 = 0',
                  'Polynomial degree: 2',
                  'Discriminant is strictly positive, the two solutions are:',
                  '-0.367006838145',
                  "-3.63299316186"]
        check = solver.Equation("5 * X^0 + 13 * X^1 + 3 * X^2 = 1 *	X^0 + 1 * X^1")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d23(self):
        # d2 > 0
        expect = ["Original Equation: 5 * X^0 + 3 * X^1 + 3 * X^2 = 1 * X^0 + 0 * X^1",
                  'Reduced form: 4 * X^0 + 3 * X^1 + 3 * X^2 = 0',
                  'Polynomial degree: 2',
                  'Discriminant is strictly negative, the two solutions are:',
                  '1 / -2 + i1.04083299973',
                  '1 / -2 - i1.04083299973']
        check = solver.Equation("5 * X^0 + 3 * X^1 + 3 * X^2 = 1 * X^0 + 0 * X^1")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d24(self):
        expect = ["Original Equation: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0",
                  "Reduced form: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0",
                  'Polynomial degree: 2',
                  'Discriminant is strictly negative, the two solutions are:',
                  '5 / -6 + i1.28019095798',
                  '5 / -6 - i1.28019095798']
        check = solver.Equation(self.neg_eq)
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d25(self):
        expect = ["Original Equation:        0=0*X^0+0*X^1+3*X^2",
                  "Formatted Equation: 0 = 0 * X^0 + 0 * X^1 + 3 * X^2",
                  'Reduced form: -3 * X^2 = 0',
                  'Polynomial degree: 2',
                  'Discriminant is null, the solution is:',
                  '0']
        check = solver.Equation("       0=0*X^0+0*X^1+3*X^2")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d10(self):
        # Degree 1
        expect = ["Original Equation: 6*X^1 = 5 * X^0", "Formatted Equation: 6 * X^1 = 5 * X^0",
                  'Reduced form: -5 * X^0 + 6 * X^1 = 0',
                  'Polynomial degree: 1',
                  'The solution is:',
                  '5 / 6']
        check = solver.Equation("6*X^1 = 5 * X^0")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d11(self):
        expect = ["Original Equation: 6 * X^1 = 0",
                  'Reduced form: 6 * X^1 = 0',
                  'Polynomial degree: 1',
                  'The solution is:', '0']
        check = solver.Equation("6 * X^1 = 0")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d12(self):
        expect = ["Original Equation: 6 * X^1 = 6 * X^1", 'No reduced form', 'Polynomial degree: 0',
                  'Every complex number is solution']
        check = solver.Equation("6 * X^1 = 6 * X^1")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d13(self):
        expect = ["Original Equation: 6X = 6X",
                  "Formatted Equation: 6 * X^1 = 6 * X^1",
                  'No reduced form', 'Polynomial degree: 0',
                  'Every complex number is solution']
        check = solver.Equation("6X = 6X")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d14(self):
        expect = ["Original Equation: 6 X = 6 X",
                  "Formatted Equation: 6 * X^1 = 6 * X^1",
                  'No reduced form', 'Polynomial degree: 0',
                  'Every complex number is solution']
        check = solver.Equation("6 X = 6 X")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d15(self):
        expect = ["Original Equation: 5 + 4X= 0",
                  "Formatted Equation: 5 * X^0 + 4 * X^1 = 0",
                  'Reduced form: 5 * X^0 + 4 * X^1 = 0',
                  'Polynomial degree: 1',
                  'The solution is:',
                  '-5 / 4']
        check = solver.Equation("5 + 4X= 0")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d00(self):
        # Degree 0 All solutions
        expect = ["Original Equation: 5 * X^0 = 5 * X^0", 'No reduced form', 'Polynomial degree: 0',
                  'Every complex number is solution']
        check = solver.Equation("5 * X^0 = 5 * X^0")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d01(self):
        # Degree 0 No solution
        expect = ["Original Equation: 6 * X^0 = 5 * X^0", 'Reduced form: 1 * X^0 = 0', 'Polynomial degree: 0',
                  'There is no solution']
        check = solver.Equation("6 * X^0 = 5 * X^0")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d02(self):
        expect = ["Original Equation: 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 5 * X^0 + 4 * X^1 - 9.3 * X^2",
                  'No reduced form', 'Polynomial degree: 0',
                  'Every complex number is solution']
        check = solver.Equation("5 * X^0 + 4 * X^1 - 9.3 * X^2 = 5 * X^0 + 4 * X^1 - 9.3 * X^2")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d30(self):
        expect = ["Original Equation: 5 * X^3 = 5 * X^0",
                  'Reduced form: -5 * X^0 + 5 * X^3 = 0',
                  'Polynomial degree: 3',
                  "The polynomial degree is strictly greater than 2, I can't solve"]
        check = solver.Equation("5 * X^3 = 5 * X^0")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution_d31(self):
        expect = ["Original Equation: 5 * X^3 = 5 + X",
                  "Formatted Equation: 5 * X^3 = 5 * X^0 + 1 * X^1",
                  'Reduced form: -5 * X^0 - 1 * X^1 + 5 * X^3 = 0',
                  'Polynomial degree: 3',
                  "The polynomial degree is strictly greater than 2, I can't solve"]
        check = solver.Equation("5 * X^3 = 5 + X")
        message = check.build_display_message()
        self.assertEqual(expect, message)

    def test_display_solution(self):
        check = solver.Equation(self.neg_eq)
        null = os.open("/dev/null", 777)
        check.display_solution(null)

    def test_sqrt(self):
        for i in range(0, 50):
            self.assertEqual(sqrt(i), solver.my_sqrt(i))
            self.assertEqual(sqrt(float(i) / 2), solver.my_sqrt(float(i) / 2))
        with self.assertRaises(ValueError):
            solver.my_sqrt(-5)
        with self.assertRaises(TypeError):
            solver.my_sqrt("5")

    def test_get_discriminant_01(self):
        check = solver.Equation(self.pos_eq)
        self.assertIsNone(check.discriminant)
        self.assertEqual(164.8, check.get_discriminant())

    def test_get_discriminant_02(self):
        check = solver.Equation(self.neg_eq)
        self.assertIsNone(check.discriminant)
        self.assertEqual(-59.0, check.get_discriminant())

    def test_get_discriminant_03(self):
        check = solver.Equation("5 * X^0 = 5 * X^0")
        self.assertIsNone(check.discriminant)
        self.assertIsNone(check.get_discriminant())

    def test_get_discriminant_04(self):
        check = solver.Equation("6*X^1 = 5 * X^0")
        self.assertIsNone(check.discriminant)
        self.assertIsNone(check.get_discriminant())

    def test_get_discriminant_05(self):
        check = solver.Equation("       0=0*X^0+0*X^1+3*X^2")
        self.assertIsNone(check.discriminant)
        self.assertEqual(0, check.get_discriminant())

    def test_get_degree_0(self):
        check = solver.Equation(self.pos_eq)
        self.assertIsNone(check.degree)
        self.assertEqual(2, check.get_degree())

    def test_get_degree_01(self):
        check = solver.Equation(self.neg_eq)
        self.assertIsNone(check.degree)
        self.assertEqual(2, check.get_degree())

    def test_get_degree_02(self):
        check = solver.Equation("5 * X^0 = 5 * X^0")
        self.assertIsNone(check.degree)
        self.assertEqual(0, check.get_degree())

    def test_get_degree_03(self):
        check = solver.Equation("6*X^1 = 5 * X^0")
        self.assertIsNone(check.degree)
        self.assertEqual(1, check.get_degree())

    def test_get_degree_04(self):
        check = solver.Equation("       0=0*X^0+0*X^1+3*X^2")
        self.assertIsNone(check.degree)
        self.assertEqual(2, check.get_degree())

    def test_get_reduced_00(self):
        check = solver.Equation(self.pos_eq)
        self.assertEqual({}, check.reduced)
        self.assertEqual({'X^1': 4.0, 'X^0': 4.0, 'X^2': -9.3}, check.get_reduced())

    def test_get_reduced_01(self):
        check = solver.Equation(self.neg_eq)
        self.assertEqual({}, check.reduced)
        self.assertEqual({'X^1': 5.0, 'X^0': 7.0, 'X^2': 3.0}, check.get_reduced())

    def test_get_reduced_02(self):
        check = solver.Equation("5 * X^0 = 5 * X^0")
        self.assertEqual({}, check.reduced)
        self.assertEqual({'X^0': 0.0}, check.get_reduced())

    def test_get_reduced_03(self):
        check = solver.Equation("6*X^1 = 5 * X^0")
        self.assertEqual({}, check.reduced)
        self.assertEqual({'X^1': 6.0, 'X^0': -5.0}, check.get_reduced())

    def test_get_reduced_04(self):
        check = solver.Equation("       0=0*X^0+0*X^1+3*X^2")
        self.assertEqual({}, check.reduced)
        self.assertEqual({'X^1': 0.0, 'X^0': 0.0, 'X^2': -3.0}, check.get_reduced())


class FunctionalSolver(unittest.TestCase):
    context_path = os.path.split(os.path.dirname(__file__))[0] + "/computorv1"
    null = open(os.devnull, 'w')

    def test_basic_s2(self):
        # Degree > 2
        equation = "5 * X^0 + 4 * X^1 - 9.3 * X^12 = 1 * X^0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual("Original Equation: 5 * X^0 + 4 * X^1 - 9.3 * X^12 = 1 * X^0\n"
                         "Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^12 = 0\n"
                         "Polynomial degree: 12\n"
                         "The polynomial degree is strictly greater than 2, I can't solve\n", res)

    def test_basic_0(self):
        # Degree 0 All solutions
        equation = "5 * X^0 = 5 * X^0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual(
            "Original Equation: 5 * X^0 = 5 * X^0\nNo reduced form\nPolynomial degree: 0\nEvery complex number is solution\n",
            res)

    def test_basic_01(self):
        # Degree 0 No solution
        equation = "6 * X^0 = 5 * X^0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual(
            "Original Equation: 6 * X^0 = 5 * X^0\nReduced form: 1 * X^0 = 0\nPolynomial degree: 0\nThere is no solution\n",
            res)

    def test_basic_1(self):
        # Degree 1
        equation = "6 * X^1 = 5 * X^0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual(
            "Original Equation: 6 * X^1 = 5 * X^0\n"
            "Reduced form: -5 * X^0 + 6 * X^1 = 0\n"
            "Polynomial degree: 1\n"
            "The solution is:\n"
            "5 / 6\n",
            res)

    def test_basic_11(self):
        equation = "6 * X^1 = 0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual(
            "Original Equation: 6 * X^1 = 0\nReduced form: 6 * X^1 = 0\nPolynomial degree: 1\nThe solution is:\n0\n",
            res)

    def test_basic_20(self):
        # Degree 2
        equation = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual("Original Equation: 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\n"
                         "Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0\nPolynomial degree: 2\n"
                         "Discriminant is strictly positive, the two solutions are:\n"
                         "-0.475131463909\n0.905238990791\n", res)

    def test_basic_21(self):
        equation = "7 * X^0 + 5 * X^1 + 3 * X^2 = 0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual("Original Equation: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0\n"
                         "Reduced form: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0\nPolynomial degree: 2\n"
                         "Discriminant is strictly negative, the two solutions are:\n"
                         "5 / -6 + i1.28019095798\n"
                         "5 / -6 - i1.28019095798\n", res)

    def test_basic_22(self):
        equation = "0 * X^0 + 0 * X^1 + 3 * X^2 = 0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual("Original Equation: 0 * X^0 + 0 * X^1 + 3 * X^2 = 0\n"
                         "Reduced form: 3 * X^2 = 0\nPolynomial degree: 2\nDiscriminant is null, the solution is:\n0\n",
                         res)

    def test_blanks_s2(self):
        # Degree > 2
        equation = "  5 * X^0 + 4 * X^1 - 9.3 * X^12 = 1 * X^0    "
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual("Original Equation:   5 * X^0 + 4 * X^1 - 9.3 * X^12 = 1 * X^0    \n"
                         "Formatted Equation: 5 * X^0 + 4 * X^1 - 9.3 * X^12 = 1 * X^0\n"
                         "Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^12 = 0\n"
                         "Polynomial degree: 12\n"
                         "The polynomial degree is strictly greater than 2, I can't solve\n", res)

    def test_blanks_0(self):
        # Degree 0 All solutions
        equation = "5*X^0=5*X^0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual("Original Equation: 5*X^0=5*X^0\n"
                         "Formatted Equation: 5 * X^0 = 5 * X^0\n"
                         "No reduced form\nPolynomial degree: 0\nEvery complex number is solution\n", res)

        # Degree 0 No solution
        equation = "6 * X^0 =5* X^0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual("Original Equation: 6 * X^0 =5* X^0\n"
                         "Formatted Equation: 6 * X^0 = 5 * X^0\n"
                         "Reduced form: 1 * X^0 = 0\nPolynomial degree: 0\nThere is no solution\n", res)

    def test_blanks_1(self):
        # Degree 1
        equation = "6*X^1 = 5 * X^0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual(
            "Original Equation: 6*X^1 = 5 * X^0\n"
            "Formatted Equation: 6 * X^1 = 5 * X^0\n"
            "Reduced form: -5 * X^0 + 6 * X^1 = 0\n"
            "Polynomial degree: 1\n"
            "The solution is:\n"
            "5 / 6\n", res)

    def test_blanks_11(self):
        equation = " 6 * X^1 = 0 "
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual("Original Equation:  6 * X^1 = 0 \n"
                         "Formatted Equation: 6 * X^1 = 0\n"
                         "Reduced form: 6 * X^1 = 0\nPolynomial degree: 1\nThe solution is:\n0\n", res)

    def test_blanks_2(self):
        # Degree 2
        equation = "5 *X^0+4*X^1 \t- 9.3 * X^2 =1*X^0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual(
            "Original Equation: 5 *X^0+4*X^1 \t- 9.3 * X^2 =1*X^0\n"
            "Formatted Equation: 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\n"
            "Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0\n"
            "Polynomial degree: 2\n"
            "Discriminant is strictly positive, the two solutions are:\n"
            "-0.475131463909\n"
            "0.905238990791\n", res)

    def test_blanks_21(self):
        equation = "   7*X^0+5*X^1+ 3 * X^2 = 0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual(
            "Original Equation:    7*X^0+5*X^1+ 3 * X^2 = 0\n"
            "Formatted Equation: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0\n"
            "Reduced form: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0\n"
            "Polynomial degree: 2\n"
            "Discriminant is strictly negative, the two solutions are:\n"
            "5 / -6 + i1.28019095798\n"
            "5 / -6 - i1.28019095798\n", res)

    def test_blanks_22(self):
        equation = "0*X^0+0*X^1+3*X^2=0       "
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual("Original Equation: 0*X^0+0*X^1+3*X^2=0       \n"
                         "Formatted Equation: 0 * X^0 + 0 * X^1 + 3 * X^2 = 0\n"
                         "Reduced form: 3 * X^2 = 0\n"
                         "Polynomial degree: 2\n"
                         "Discriminant is null, the solution is:\n"
                         "0\n", res)

    def test_blanks_23(self):
        equation = "       0=0*X^0+0*X^1+3*X^2"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual("Original Equation:        0=0*X^0+0*X^1+3*X^2\n"
                         "Formatted Equation: 0 = 0 * X^0 + 0 * X^1 + 3 * X^2\n"
                         "Reduced form: -3 * X^2 = 0\n"
                         "Polynomial degree: 2\n"
                         "Discriminant is null, the solution is:\n"
                         "0\n", res)

    def test_errors_0(self):
        equation = "0 = 0"
        ret = call(["python", self.context_path + "/solver.py", equation], stderr=self.null)
        self.assertEqual(1, ret)

    def test_errors_1(self):
        equation = ""
        ret = call(["python", self.context_path + "/solver.py", equation], stderr=self.null)
        self.assertEqual(1, ret)

    def test_errors_2(self):
        equation = "hello"
        ret = call(["python", self.context_path + "/solver.py", equation], stderr=self.null)
        self.assertEqual(1, ret)

    def test_errors_3(self):
        equation = "hello = World"
        ret = call(["python", self.context_path + "/solver.py", equation], stderr=self.null)
        self.assertEqual(1, ret)

    def test_errors_4(self):
        equation = " = 0"
        ret = call(["python", self.context_path + "/solver.py", equation], stderr=self.null)
        self.assertEqual(1, ret)

    def test_errors_5(self):
        equation = "1 + ^ + x**2 = 0"
        ret = call(["python", self.context_path + "/solver.py", equation], stderr=self.null)
        self.assertEqual(1, ret)

    def test_replacement_s20(self):
        # Degree 2
        equation = "5 * x^0 + 4 * x^1 - 9.3 * x^2 = 1 * X^0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual(
            "Original Equation: 5 * x^0 + 4 * x^1 - 9.3 * x^2 = 1 * X^0\n"
            "Formatted Equation: 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\n"
            "Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0\n"
            "Polynomial degree: 2\n"
            "Discriminant is strictly positive, the two solutions are:\n"
            "-0.475131463909\n"
            "0.905238990791\n", res)

    def test_replacement_s21(self):
        equation = "7 * X**0 + 5 * X^1 + 3 * X**2 = 0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual(
            "Original Equation: 7 * X**0 + 5 * X^1 + 3 * X**2 = 0\n"
            "Formatted Equation: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0\n"
            "Reduced form: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0\n"
            "Polynomial degree: 2\n"
            "Discriminant is strictly negative, the two solutions are:\n"
            "5 / -6 + i1.28019095798\n"
            "5 / -6 - i1.28019095798\n", res)

    def test_replacement_s22(self):
        equation = "0 * x**0 + 0 * x^1 + 3 * X**2 = 0"
        res = check_output(["python", self.context_path + "/solver.py", equation])
        self.assertEqual("Original Equation: 0 * x**0 + 0 * x^1 + 3 * X**2 = 0\n"
                         "Formatted Equation: 0 * X^0 + 0 * X^1 + 3 * X^2 = 0\n"
                         "Reduced form: 3 * X^2 = 0\n"
                         "Polynomial degree: 2\nDiscriminant is null, the solution is:\n"
                         "0\n", res)


class TestWebEngine(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.client = web_engine.app.test_client()

    def test_get(self):
        response = self.client.get('/')
        self.assertEqual(200, response.status_code)

    def test_get_error(self):
        response = self.client.get('/no')
        self.assertEqual(404, response.status_code)

    def test_post(self):
        response = self.client.post("http://127.0.0.1")
        self.assertEqual(301, response.status_code)