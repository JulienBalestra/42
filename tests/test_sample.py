from unittest import TestCase
from subprocess import call, check_output
import os

import computorv1.sample as computor


class TestComputorV1(TestCase):
	context_path = os.path.split(os.path.dirname(__file__))[0] + "/computorv1"
	model = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
	neg_model = "7 * X^0 + 5 * X^1 + 3 * X^2 = 0"
	null = open(os.devnull, 'w')

	def test_is_coherent(self):
		self.assertTrue(computor.is_coherent(self.model))
		self.assertFalse(computor.is_coherent("1 == 2"))
		self.assertFalse(computor.is_coherent("1 2"))

	def test_get_reduced_form(self):
		expect = ({'X^1': 4.0, 'X^0': 4.0, 'X^2': -9.3}, '2')
		reduced = computor.get_reduced_form(self.model)
		self.assertEqual(expect, reduced)

	def test_check_args(self):
		with self.assertRaises(ArithmeticError):
			computor.check_args("1 == 2")
		with self.assertRaises(ArithmeticError):
			computor.check_args("1 2")
		self.assertEqual(self.model, computor.check_args(self.model))

	def test_arguments(self):
		ret = call(["python", self.context_path + "/sample.py", self.model], stdout=self.null)
		self.assertEqual(0, ret)
		ret = call(["python", self.context_path + "/sample.py", "1 == 2"], stderr=self.null)
		self.assertEqual(1, ret)
		ret = call(["python", self.context_path + "/sample.py", "1 2"], stderr=self.null)
		self.assertEqual(1, ret)

	def test_get_degree(self):
		reduced = {'X^1': 4.0, 'X^0': 4.0, 'X^2': -9.3}
		self.assertEqual("2", computor.get_degree(reduced, 2))
		reduced = {'X^1': 4.0, 'X^0': 4.0, 'X^2': 0}
		self.assertEqual("1", computor.get_degree(reduced, 2))
		reduced = {'X^1': 0, 'X^0': 4.0, 'X^2': 0}
		self.assertEqual("0", computor.get_degree(reduced, 2))
		reduced = {'X^1': 0, 'X^0': 0, 'X^2': 0}
		self.assertEqual("0", computor.get_degree(reduced, 2))

	def test_reduced_dict(self):
		reduced = {'X^1': 0, 'X^0': 0, 'X^2': 0}
		my_reduced, degree = computor.create_reduced_dict(self.model)
		self.assertEqual(reduced, my_reduced)
		self.assertEqual("2", degree)

	def test_string_reduced_form(self):
		reduced = {'X^1': 4.0, 'X^0': 4.0, 'X^2': -9.3}
		string = computor.string_reduced_form(reduced, "2")
		expect = "Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0"
		self.assertEqual(expect, string)
		reduced = {'X^1': 4.0, 'X^0': 4.0, 'X^2': 0}
		string = computor.string_reduced_form(reduced, "2")
		expect = "Reduced form: 4 * X^0 + 4 * X^1 = 0"
		self.assertEqual(expect, string)

	def test_solve_two(self):
		reduced = {'X^1': 4.0, 'X^0': 4.0, 'X^2': -9.3}
		self.assertEqual((164.8, '-0.475131463909', '0.905238990791'), computor.solve_two(reduced))

		reduced = {'X^1': 5.0, 'X^0': 7.0, 'X^2': 3.0}
		self.assertEqual((-59., '-0.833333333333 + i1.28019095798', '-0.833333333333 - i1.28019095798'),
		                 computor.solve_two(reduced))

	def test_regex_false(self):
		s = "zzzzzz"
		self.assertFalse(computor.my_regex(s))
		s = "0 = 0"
		self.assertFalse(computor.my_regex(s))
		s = "5 * X^ + "
		self.assertFalse(computor.my_regex(s))
		s = "5*X^0+"
		self.assertFalse(computor.my_regex(s))
		s = "5 * X^0 = 5 * X^0 toto"
		self.assertFalse(computor.my_regex(s))
		s = "toto 5 * X^0 = 5 * X^0"
		self.assertFalse(computor.my_regex(s))
		s = "toto5 * X^0 = 5 * X^0"
		self.assertFalse(computor.my_regex(s))
		s = "toto5 ++++ = 0"
		self.assertFalse(computor.my_regex(s))
		s = " * X^0 = 5 * X^0"
		self.assertFalse(computor.my_regex(s))
		s = "5 + X^0 = 5 * X^0"
		self.assertFalse(computor.my_regex(s))
		s = "5 + X^0 = 5 * X^0"
		self.assertFalse(computor.my_regex(s))
		s = "5 * X^0 -+ 1 * X^1 = 5 * X^0"
		self.assertFalse(computor.my_regex(s))
		s = "5 * X^0 +- 1 * X^1 = 5 * X^0"
		self.assertFalse(computor.my_regex(s))
		s = "5 * X^0 + toto - 1 * X^1 = 5 * X^0"
		self.assertFalse(computor.my_regex(s))
		s = "5 * X^0.1 - 1 * X^1 = 5 * X^0"
		self.assertFalse(computor.my_regex(s))
		s = ".0 * X^0 + 1 * X^1 = 5 * X^0"
		self.assertFalse(computor.my_regex(s))

	def test_regex_true(self):
		s = "5 * X^0 = 5 * X^0"
		self.assertTrue(computor.my_regex(s))
		s = "5 * X^0 - 1 * X^1 = 5 * X^0"
		self.assertTrue(computor.my_regex(s))
		s = "5 * X^0 - 1 * X^1 = 0"
		self.assertTrue(computor.my_regex(s))
		s = "0 = 5 * X^0 - 1 * X^1"
		self.assertTrue(computor.my_regex(s))
		s = "5.5 * X^0 = 5 * X^0"
		self.assertTrue(computor.my_regex(s))
		s = "0.5 * X^0 = 5 * X^0"
		self.assertTrue(computor.my_regex(s))
		s = "0.0 * X^0 = 5 * X^0"
		self.assertTrue(computor.my_regex(s))
		s = "5 *X^0 = 5 * X^0"
		self.assertTrue(computor.my_regex(s))
		s = "5 *X^0 = 5*X^0"
		self.assertTrue(computor.my_regex(s))
		s = "5*X^0=5*X^0"
		self.assertTrue(computor.my_regex(s))
		s = "5    *X^0=5*X^0"
		self.assertTrue(computor.my_regex(s))
		s = "5    *X^0   =   5*\tX^0"
		self.assertTrue(computor.my_regex(s))
		s = "    5    *X^0   =   5*\tX^0"
		self.assertTrue(computor.my_regex(s))
		s = "    5    *X^0   =   5*\tX^0    "
		self.assertTrue(computor.my_regex(s))
		s = "5 * X^0=5 * X^0"
		self.assertTrue(computor.my_regex(s))

	def test_sqrt(self):
		from math import sqrt

		for i in range(0, 50):
			self.assertEqual(sqrt(i), computor.my_sqrt(i))
			self.assertEqual(sqrt(float(i) / 2), computor.my_sqrt(float(i) / 2))
		with self.assertRaises(ValueError):
			computor.my_sqrt(-5)
		with self.assertRaises(TypeError):
			computor.my_sqrt("5")


class TestComputorFull(TestCase):
	context_path = os.path.split(os.path.dirname(__file__))[0] + "/computorv1"
	null = open(os.devnull, 'w')

	def test_basic_s2(self):
		# Degree > 2
		equation = "5 * X^0 + 4 * X^1 - 9.3 * X^12 = 1 * X^0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual("Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^12 = 0\n"
		                 "Polynomial degree: 12\n"
		                 "The polynomial degree is strictly greater than 2, I can't solve.\n", res)

	def test_basic_0(self):
		# Degree 0 All solutions
		equation = "5 * X^0 = 5 * X^0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual("No reduced form\nPolynomial degree: 0\nAll possibilities are True\n", res)

		# Degree 0 No solution
		equation = "6 * X^0 = 5 * X^0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual("Reduced form: 1 * X^0 = 0\nPolynomial degree: 0\nThere is no solutions\n", res)

	def test_basic_1(self):
		# Degree 1
		equation = "6 * X^1 = 5 * X^0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual(
			"Reduced form: -5 * X^0 + 6 * X^1 = 0\nPolynomial degree: 1\nThe solution is:\n0.833333333333\n", res)
		equation = "6 * X^1 = 0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual(
			"Reduced form: 6 * X^1 = 0\nPolynomial degree: 1\nThe solution is:\n0\n", res)

	def test_basic_2(self):
		# Degree 2
		equation = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual(
			"Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0\nPolynomial degree: 2\n"
			"Discriminant is strictly positive, the two solutions are:\n"
			"-0.475131463909\n0.905238990791\n", res)

		equation = "7 * X^0 + 5 * X^1 + 3 * X^2 = 0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual(
			"Reduced form: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0\nPolynomial degree: 2\n"
			"Discriminant is strictly negative, the two solutions are:\n"
			"-0.833333333333 + i1.28019095798\n-0.833333333333 - i1.28019095798\n", res)

		equation = "0 * X^0 + 0 * X^1 + 3 * X^2 = 0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual("Reduced form: 3 * X^2 = 0\nPolynomial degree: 2\nDiscriminant is null, the solution is:\n0\n",
		                 res)

	def test_blanks_s2(self):
		# Degree > 2
		equation = "  5 * X^0 + 4 * X^1 - 9.3 * X^12 = 1 * X^0    "
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual("Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^12 = 0\n"
		                 "Polynomial degree: 12\n"
		                 "The polynomial degree is strictly greater than 2, I can't solve.\n", res)

	def test_blanks_0(self):
		# Degree 0 All solutions
		equation = "5*X^0=5*X^0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual("No reduced form\nPolynomial degree: 0\nAll possibilities are True\n", res)

		# Degree 0 No solution
		equation = "6 * X^0 =5* X^0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual("Reduced form: 1 * X^0 = 0\nPolynomial degree: 0\nThere is no solutions\n", res)

	def test_blanks_1(self):
		# Degree 1
		equation = "6*X^1 = 5 * X^0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual(
			"Reduced form: -5 * X^0 + 6 * X^1 = 0\nPolynomial degree: 1\nThe solution is:\n0.833333333333\n", res)
		equation = "6 * X^1 = 0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual(
			"Reduced form: 6 * X^1 = 0\nPolynomial degree: 1\nThe solution is:\n0\n", res)

	def test_blanks_2(self):
		# Degree 2
		equation = "5 *X^0+4*X^1 \t- 9.3 * X^2 =1*X^0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual(
			"Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0\nPolynomial degree: 2\n"
			"Discriminant is strictly positive, the two solutions are:\n"
			"-0.475131463909\n0.905238990791\n", res)

		equation = "   7*X^0+5*X^1+ 3 * X^2 = 0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual(
			"Reduced form: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0\nPolynomial degree: 2\n"
			"Discriminant is strictly negative, the two solutions are:\n"
			"-0.833333333333 + i1.28019095798\n-0.833333333333 - i1.28019095798\n", res)

		equation = "0*X^0+0*X^1+3*X^2=0       "
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual("Reduced form: 3 * X^2 = 0\nPolynomial degree: 2\nDiscriminant is null, the solution is:\n0\n",
		                 res)

		equation = "       0=0*X^0+0*X^1+3*X^2"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual(
			"Reduced form: -3 * X^2 = 0\nPolynomial degree: 2\nDiscriminant is null, the solution is:\n0\n",
			res)

	def test_errors_0(self):
		equation = "0 = 0"
		ret = call(["python", self.context_path + "/sample.py", equation], stderr=self.null)
		self.assertEqual(1, ret)

	def test_errors_1(self):
		equation = ""
		ret = call(["python", self.context_path + "/sample.py", equation], stderr=self.null)
		self.assertEqual(1, ret)

	def test_errors_2(self):
		equation = "hello"
		ret = call(["python", self.context_path + "/sample.py", equation], stderr=self.null)
		self.assertEqual(1, ret)

	def test_errors_3(self):
		equation = "hello = World"
		ret = call(["python", self.context_path + "/sample.py", equation], stderr=self.null)
		self.assertEqual(1, ret)

	def test_errors_4(self):
		equation = "1 = 0"
		ret = call(["python", self.context_path + "/sample.py", equation], stderr=self.null)
		self.assertEqual(1, ret)

	def test_errors_5(self):
		equation = "1 + x**2 = 0"
		ret = call(["python", self.context_path + "/sample.py", equation], stderr=self.null)
		self.assertEqual(1, ret)

	def test_replacement_s2(self):
		# Degree 2
		equation = "5 * x^0 + 4 * x^1 - 9.3 * x^2 = 1 * X^0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual(
			"Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0\nPolynomial degree: 2\n"
			"Discriminant is strictly positive, the two solutions are:\n"
			"-0.475131463909\n0.905238990791\n", res)

		equation = "7 * X**0 + 5 * X^1 + 3 * X**2 = 0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual(
			"Reduced form: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0\nPolynomial degree: 2\n"
			"Discriminant is strictly negative, the two solutions are:\n"
			"-0.833333333333 + i1.28019095798\n-0.833333333333 - i1.28019095798\n", res)

		equation = "0 * x**0 + 0 * x^1 + 3 * X**2 = 0"
		res = check_output(["python", self.context_path + "/sample.py", equation])
		self.assertEqual("Reduced form: 3 * X^2 = 0\nPolynomial degree: 2\nDiscriminant is null, the solution is:\n0\n",
		                 res)