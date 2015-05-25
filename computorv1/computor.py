#!/usr/bin/env python
import argparse
import re


def my_sqrt(x):
	try:
		if x >= 0:
			return x ** 0.5
	except TypeError:
		raise TypeError("not an int or float type")
	raise ValueError("math domain error")


def create_reduced_dict(equation):
	reduced = {}
	degree = 0
	for deg in re.findall("X\^([0-9]+)", equation):
		if deg > degree:
			degree = deg
		reduced["X^" + deg] = 0
	return reduced, degree


def get_reduced_form(equation):
	coeff = 1
	reduced, degree = create_reduced_dict(equation)
	equation = equation.replace("- ", "-").split(" ")
	for i, elt in enumerate(equation):
		if elt in reduced:
			reduced[elt] += coeff * float(equation[i - 2])
		elif elt == "=":
			coeff = -1
	return reduced, get_degree(reduced, degree)


def my_regex(equation):
	pattern = "(\s)*([0-9]+.?[0-9]*(\s)*\*(\s)*X\^[0-9]+(\s)*[\+\-](\s)*)*[0-9]+.?[0-9]*(\s)*\*(\s)*X\^[0-9]+(\s)*"
	equal = "(\s)*=(\s)*"
	if re.match(pattern + equal + pattern + "$", equation) is not None:
		return True
	elif re.match(pattern + equal + "0(\s)*$", equation) is not None:
		return True
	elif re.match("(\s)*0" + equal + pattern + "$", equation) is not None:
		return True
	return False


def replace_alternatives(equation):
	equation = equation.replace("**", "^")
	equation = equation.replace("x", "X")
	return equation


def is_coherent(equation):
	equation = replace_alternatives(equation)
	if my_regex(equation) is True:
		return manage_blank(equation)
	return None


def manage_blank(equation):
	for char in [" ", "\t"]:
		equation = equation.replace(char, "")
	for sign in ["+", "-", "*", "="]:
		equation = equation.replace(sign, " %s " % sign)
	return equation


def check_args(stdin):
	equation = is_coherent(stdin)
	if equation is not None:
		return equation
	raise ArithmeticError("The equation is not coherent, should be like 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0")


def convert_float(number):
	if number - int(number) == 0:
		return str(int(number))
	return str(number)


def string_reduced_form(reduced, degree):
	equation = []
	for i in range(int(degree) + 1):
		if affect_coeff("X^" + str(i), reduced) != 0:
			equation.append(convert_float(reduced["X^" + str(i)]))
			equation.append("*")
			equation.append("X^" + str(i))
			equation.append("+")
	if equation:
		equation.pop(-1)
		equation.append("=")
		equation.append("0")
		return "Reduced form: " + " ".join(equation).replace("+ -", "- ")
	return "No reduced form"


def get_degree(reduced, degree):
	for i in range(int(degree), -1, -1):
		if reduced["X^" + str(i)] != 0:
			return str(i)
	return str(0)


def solve_one(reduced):
	a = affect_coeff("X^1", reduced)
	b = affect_coeff("X^0", reduced)
	return convert_float(-b / a)


def process_equation(reduced, degree):
	if degree == '0':
		if reduced["X^0"] == 0:
			print "All possibilities are True"
		else:
			print "There is no solutions"
	elif degree == '1':
		print "The solution is:"
		print solve_one(reduced)
	elif degree == '2':
		res = solve_two(reduced)
		if res[0] > 0:
			print "Discriminant is strictly positive, the two solutions are:"
			print res[1]
			print res[2]
		elif res[0] == 0:
			print "Discriminant is null, the solution is:"
			print res[1]
		else:
			print "Discriminant is strictly negative, the two solutions are:"
			print res[1]
			print res[2]
	else:
		print "The polynomial degree is strictly greater than 2, I can't solve."


def affect_coeff(key, reduced):
	try:
		coeff = reduced[key]
	except KeyError:
		coeff = 0
	return coeff


def solve_negative_discr(a, b, discr):
	real = - b / (2 * a)
	im = my_sqrt(- discr) / (2 * a)
	x1 = convert_float(real) + " + i" + convert_float(im)
	x2 = convert_float(real) + " - i" + convert_float(im)
	return discr, x1, x2


def solve_positive_discr(a, b, discr):
	x1 = convert_float((-b + my_sqrt(discr)) / (2 * a))
	x2 = convert_float((-b - my_sqrt(discr)) / (2 * a))
	return discr, x1, x2


def solve_two(reduced):
	a = affect_coeff('X^2', reduced)
	b = affect_coeff('X^1', reduced)
	c = affect_coeff('X^0', reduced)
	discr = b * b - 4 * a * c
	if discr > 0:
		return solve_positive_discr(a, b, discr)
	elif discr == 0:
		return discr, convert_float(-b / (2 * a))
	else:
		return solve_negative_discr(a, b, discr)


def computor(equation, main=False):
	if main is False:
		equation = check_args(equation)
	reduced, degree = get_reduced_form(equation)
	print string_reduced_form(reduced, degree)
	print "Polynomial degree: " + degree
	process_equation(reduced, degree)


if __name__ == "__main__":
	args = argparse.ArgumentParser()
	args.add_argument("equation", type=check_args, help="Should be like 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0")
	computor(args.parse_args().equation, main=True)
