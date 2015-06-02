import unittest
import os
from math import sqrt
from subprocess import check_output, call

import computorv1.solver as solver
import computorv1.web_engine as web_engine


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

	def test_check_n_format_raise(self):
		eq = "5 * X^0="
		with self.assertRaises(ArithmeticError):
			check = solver.Equation(eq)
			self.assertEqual(None, check.input)

		eq = "zzzzzz"
		with self.assertRaises(ArithmeticError):
			check = solver.Equation(eq)
			self.assertEqual(None, check.input)

		eq = "0 = 0"
		with self.assertRaises(ArithmeticError):
			check = solver.Equation(eq)
			self.assertEqual(None, check.input)

		eq = "5 * X^ + "
		with self.assertRaises(ArithmeticError):
			check = solver.Equation(eq)
			self.assertEqual(None, check.input)

		eq = "5 * X^0 = 5 * X^0 toto"
		with self.assertRaises(ArithmeticError):
			check = solver.Equation(eq)
			self.assertEqual(None, check.input)

		eq = "5 * X^0 + toto - 1 * X^1 = 5 * X^0"
		with self.assertRaises(ArithmeticError):
			check = solver.Equation(eq)
			self.assertEqual(None, check.input)

		eq = "5 * X^0.1 - 1 * X^1 = 5 * X^0"
		with self.assertRaises(ArithmeticError):
			check = solver.Equation(eq)
			self.assertEqual(None, check.input)

		eq = ".0 * X^0 + 1 * X^1 = 5 * X^0"
		with self.assertRaises(ArithmeticError):
			check = solver.Equation(eq)
			self.assertEqual(None, check.input)

		eq = "5 + X^0 = 5 * X^0"
		with self.assertRaises(ArithmeticError):
			check = solver.Equation(eq)
			self.assertEqual(None, check.input)

	def test__get_reduced_form(self):
		check = solver.Equation(self.pos_eq)
		self.assertEqual({'X^1': 4.0, 'X^0': 4.0, 'X^2': -9.3}, check._process_reduced_form())

		check = solver.Equation(self.neg_eq)
		self.assertEqual({'X^1': 5.0, 'X^0': 7.0, 'X^2': 3.0}, check._process_reduced_form())

	def test_process_degree(self):
		check = solver.Equation(self.pos_eq)
		self.assertEqual(2, check._process_degree())

		check = solver.Equation(self.neg_eq)
		self.assertEqual(2, check._process_degree())

		check = solver.Equation("5 * X^0 = 5 * X^0")
		self.assertEqual(0, check._process_degree())

		check = solver.Equation("6 * X^0 = 5 * X^0")
		self.assertEqual(0, check._process_degree())

		check = solver.Equation("6 * X^1 = 5 * X^0")
		self.assertEqual(1, check._process_degree())

		check = solver.Equation("5 * X^1 = 5 * X^1")
		self.assertEqual(0, check._process_degree())

		check = solver.Equation("5 * X^2 = 5 * X^2")
		self.assertEqual(0, check._process_degree())

		check = solver.Equation("5 * X^2 + 7 * X^1 = 5 * X^2")
		self.assertEqual(1, check._process_degree())

	def test_solve_two(self):
		check = solver.Equation(self.pos_eq)
		check.solve()
		self.assertEqual(164.8, check.discriminant)
		self.assertEqual((-0.47513146390886934, 0.9052389907905898), check.solution)

		check = solver.Equation(self.neg_eq)
		check.solve()
		self.assertEqual(-59., check.discriminant)
		self.assertEqual(('-0.833333333333 + i1.28019095798',
		                  '-0.833333333333 - i1.28019095798'), check.solution)

	def test_solve_one(self):
		check = solver.Equation("6 * X^1 = 5 * X^0")
		check.solve()
		self.assertIsNone(check.discriminant)
		self.assertEqual((0.8333333333333334,), check.solution)

	def test_solve_zero(self):
		check = solver.Equation("5 * X^0 = 5 * X^0")
		check.solve()
		self.assertIsNone(check.discriminant)
		self.assertEqual((True,), check.solution)

		check = solver.Equation("6 * X^0 = 5 * X^0")
		check.solve()
		self.assertIsNone(check.discriminant)
		self.assertEqual((False,), check.solution)

	def test_solve_three(self):
		check = solver.Equation("6 * X^3 = 5 * X^0")
		check.solve()
		self.assertIsNone(check.discriminant)
		self.assertEqual((False,), check.solution)

	def test_display_solution_d2(self):
		# d2 > 0
		expect = ['Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0',
		          'Polynomial degree: 2',
		          'Discriminant is strictly positive, the two solutions are:',
		          '-0.475131463909',
		          '0.905238990791']
		check = solver.Equation(self.pos_eq)
		message = check.build_display_message()
		self.assertEqual(expect, message)

		expect = ['Reduced form: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0',
		          'Polynomial degree: 2',
		          'Discriminant is strictly negative, the two solutions are:',
		          '-0.833333333333 + i1.28019095798',
		          '-0.833333333333 - i1.28019095798']
		check = solver.Equation(self.neg_eq)
		message = check.build_display_message()
		self.assertEqual(expect, message)

		expect = ['Reduced form: -3 * X^2 = 0',
		          'Polynomial degree: 2',
		          'Discriminant is null, the solution is:',
		          '0']
		check = solver.Equation("       0=0*X^0+0*X^1+3*X^2")
		message = check.build_display_message()
		self.assertEqual(expect, message)

	def test_display_solution_d1(self):
		# Degree 1
		expect = ['Reduced form: -5 * X^0 + 6 * X^1 = 0',
		          'Polynomial degree: 1',
		          'The solution is:',
		          '0.833333333333']
		check = solver.Equation("6*X^1 = 5 * X^0")
		message = check.build_display_message()
		self.assertEqual(expect, message)

		expect = ['Reduced form: 6 * X^1 = 0',
		          'Polynomial degree: 1',
		          'The solution is:', '0']
		check = solver.Equation("6 * X^1 = 0")
		message = check.build_display_message()
		self.assertEqual(expect, message)

		expect = ['No reduced form', 'Polynomial degree: 0', 'Every complex number is solution']
		check = solver.Equation("6 * X^1 = 6 * X^1")
		message = check.build_display_message()
		self.assertEqual(expect, message)

	def test_display_solution_d0(self):
		# Degree 0 All solutions
		expect = ['No reduced form', 'Polynomial degree: 0', 'Every complex number is solution']
		check = solver.Equation("5 * X^0 = 5 * X^0")
		message = check.build_display_message()
		self.assertEqual(expect, message)

		# Degree 0 No solution
		expect = ['Reduced form: 1 * X^0 = 0', 'Polynomial degree: 0', 'There is no solution']
		check = solver.Equation("6 * X^0 = 5 * X^0")
		message = check.build_display_message()
		self.assertEqual(expect, message)

		expect = ['No reduced form', 'Polynomial degree: 0', 'Every complex number is solution']
		check = solver.Equation("5 * X^0 + 4 * X^1 - 9.3 * X^2 = 5 * X^0 + 4 * X^1 - 9.3 * X^2")
		message = check.build_display_message()
		self.assertEqual(expect, message)

	def test_display_solution_d3(self):
		expect = ['Reduced form: -5 * X^0 + 5 * X^3 = 0',
		          'Polynomial degree: 3',
		          "The polynomial degree is strictly greater than 2, I can't solve"]
		check = solver.Equation("5 * X^3 = 5 * X^0")
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

	def test_get_discriminant(self):
		check = solver.Equation(self.pos_eq)
		self.assertIsNone(check.discriminant)
		self.assertEqual(164.8, check.get_discriminant())

		check = solver.Equation(self.neg_eq)
		self.assertIsNone(check.discriminant)
		self.assertEqual(-59.0, check.get_discriminant())

		check = solver.Equation("5 * X^0 = 5 * X^0")
		self.assertIsNone(check.discriminant)
		self.assertIsNone(check.get_discriminant())

		check = solver.Equation("6*X^1 = 5 * X^0")
		self.assertIsNone(check.discriminant)
		self.assertIsNone(check.get_discriminant())

		check = solver.Equation("       0=0*X^0+0*X^1+3*X^2")
		self.assertIsNone(check.discriminant)
		self.assertEqual(0, check.get_discriminant())

	def test_get_degree(self):
		check = solver.Equation(self.pos_eq)
		self.assertIsNone(check.degree)
		self.assertEqual(2, check.get_degree())

		check = solver.Equation(self.neg_eq)
		self.assertIsNone(check.degree)
		self.assertEqual(2, check.get_degree())

		check = solver.Equation("5 * X^0 = 5 * X^0")
		self.assertIsNone(check.degree)
		self.assertEqual(0, check.get_degree())

		check = solver.Equation("6*X^1 = 5 * X^0")
		self.assertIsNone(check.degree)
		self.assertEqual(1, check.get_degree())

		check = solver.Equation("       0=0*X^0+0*X^1+3*X^2")
		self.assertIsNone(check.degree)
		self.assertEqual(2, check.get_degree())

	def test_get_reduced(self):
		check = solver.Equation(self.pos_eq)
		self.assertEqual({}, check.reduced)
		self.assertEqual({'X^1': 4.0, 'X^0': 4.0, 'X^2': -9.3}, check.get_reduced())

		check = solver.Equation(self.neg_eq)
		self.assertEqual({}, check.reduced)
		self.assertEqual({'X^1': 5.0, 'X^0': 7.0, 'X^2': 3.0}, check.get_reduced())

		check = solver.Equation("5 * X^0 = 5 * X^0")
		self.assertEqual({}, check.reduced)
		self.assertEqual({'X^0': 0.0}, check.get_reduced())

		check = solver.Equation("6*X^1 = 5 * X^0")
		self.assertEqual({}, check.reduced)
		self.assertEqual({'X^1': 6.0, 'X^0': -5.0}, check.get_reduced())

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
		self.assertEqual("Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^12 = 0\n"
		                 "Polynomial degree: 12\n"
		                 "The polynomial degree is strictly greater than 2, I can't solve\n", res)

	def test_basic_0(self):
		# Degree 0 All solutions
		equation = "5 * X^0 = 5 * X^0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual("No reduced form\nPolynomial degree: 0\nEvery complex number is solution\n", res)

		# Degree 0 No solution
		equation = "6 * X^0 = 5 * X^0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual("Reduced form: 1 * X^0 = 0\nPolynomial degree: 0\nThere is no solution\n", res)

	def test_basic_1(self):
		# Degree 1
		equation = "6 * X^1 = 5 * X^0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual(
			"Reduced form: -5 * X^0 + 6 * X^1 = 0\nPolynomial degree: 1\nThe solution is:\n0.833333333333\n", res)
		equation = "6 * X^1 = 0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual(
			"Reduced form: 6 * X^1 = 0\nPolynomial degree: 1\nThe solution is:\n0\n", res)

	def test_basic_2(self):
		# Degree 2
		equation = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual(
			"Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0\nPolynomial degree: 2\n"
			"Discriminant is strictly positive, the two solutions are:\n"
			"-0.475131463909\n0.905238990791\n", res)

		equation = "7 * X^0 + 5 * X^1 + 3 * X^2 = 0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual(
			"Reduced form: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0\nPolynomial degree: 2\n"
			"Discriminant is strictly negative, the two solutions are:\n"
			"-0.833333333333 + i1.28019095798\n-0.833333333333 - i1.28019095798\n", res)

		equation = "0 * X^0 + 0 * X^1 + 3 * X^2 = 0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual("Reduced form: 3 * X^2 = 0\nPolynomial degree: 2\nDiscriminant is null, the solution is:\n0\n",
		                 res)

	def test_blanks_s2(self):
		# Degree > 2
		equation = "  5 * X^0 + 4 * X^1 - 9.3 * X^12 = 1 * X^0    "
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual("Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^12 = 0\n"
		                 "Polynomial degree: 12\n"
		                 "The polynomial degree is strictly greater than 2, I can't solve\n", res)

	def test_blanks_0(self):
		# Degree 0 All solutions
		equation = "5*X^0=5*X^0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual("No reduced form\nPolynomial degree: 0\nEvery complex number is solution\n", res)

		# Degree 0 No solution
		equation = "6 * X^0 =5* X^0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual("Reduced form: 1 * X^0 = 0\nPolynomial degree: 0\nThere is no solution\n", res)

	def test_blanks_1(self):
		# Degree 1
		equation = "6*X^1 = 5 * X^0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual(
			"Reduced form: -5 * X^0 + 6 * X^1 = 0\nPolynomial degree: 1\nThe solution is:\n0.833333333333\n", res)
		equation = "6 * X^1 = 0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual(
			"Reduced form: 6 * X^1 = 0\nPolynomial degree: 1\nThe solution is:\n0\n", res)

	def test_blanks_2(self):
		# Degree 2
		equation = "5 *X^0+4*X^1 \t- 9.3 * X^2 =1*X^0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual(
			"Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0\n"
			"Polynomial degree: 2\n"
			"Discriminant is strictly positive, the two solutions are:\n"
			"-0.475131463909\n"
			"0.905238990791\n", res)

		equation = "   7*X^0+5*X^1+ 3 * X^2 = 0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual(
			"Reduced form: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0\n"
			"Polynomial degree: 2\n"
			"Discriminant is strictly negative, the two solutions are:\n"
			"-0.833333333333 + i1.28019095798\n"
			"-0.833333333333 - i1.28019095798\n", res)

		equation = "0*X^0+0*X^1+3*X^2=0       "
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual("Reduced form: 3 * X^2 = 0\n"
		                 "Polynomial degree: 2\n"
		                 "Discriminant is null, the solution is:\n"
		                 "0\n", res)

		equation = "       0=0*X^0+0*X^1+3*X^2"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual(
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
		equation = "1 = 0"
		ret = call(["python", self.context_path + "/solver.py", equation], stderr=self.null)
		self.assertEqual(1, ret)

	def test_errors_5(self):
		equation = "1 + x**2 = 0"
		ret = call(["python", self.context_path + "/solver.py", equation], stderr=self.null)
		self.assertEqual(1, ret)

	def test_replacement_s2(self):
		# Degree 2
		equation = "5 * x^0 + 4 * x^1 - 9.3 * x^2 = 1 * X^0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual(
			"Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0\n"
			"Polynomial degree: 2\n"
			"Discriminant is strictly positive, the two solutions are:\n"
			"-0.475131463909\n"
			"0.905238990791\n", res)

		equation = "7 * X**0 + 5 * X^1 + 3 * X**2 = 0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual(
			"Reduced form: 7 * X^0 + 5 * X^1 + 3 * X^2 = 0\n"
			"Polynomial degree: 2\n"
			"Discriminant is strictly negative, the two solutions are:\n"
			"-0.833333333333 + i1.28019095798\n"
			"-0.833333333333 - i1.28019095798\n", res)

		equation = "0 * x**0 + 0 * x^1 + 3 * X**2 = 0"
		res = check_output(["python", self.context_path + "/solver.py", equation])
		self.assertEqual("Reduced form: 3 * X^2 = 0\n"
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