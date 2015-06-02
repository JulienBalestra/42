from flask import Flask, request, make_response
from os.path import dirname, abspath
import solver

app = Flask(__name__)


def send_html_page(page):
	return open(dirname(abspath(__file__)) + page).read()


def get_form(received):
	try:
		if received['<left>'] and received['<right>']:
			form = received['<left>'] + " = " + received['<right>']
			form = form.replace('"', " ")
			return form
		elif received['<left>']:
			form = received['<left>'] + " = "
			form = form.replace('"', " ")
			return form
		elif received['<right>']:
			form = received['<right>'] + " = "
			form = form.replace('"', " ")
			return form
		else:
			return None
	except Exception as e:
		print e


@app.route('/', methods=['POST', 'GET'])
def root():
	if request.method == 'POST':
		equation = get_form(request.form)
		if equation is not None:
			try:
				solve = solver.Equation(str(equation))
				eq_input = solve.__repr__().split("=")
				content = solve.build_display_message()
				response = send_html_page('/response.html').replace("__response__", "<br>".join(content))
				response = response.replace("__left__", eq_input[0])
				response = response.replace("__right__", eq_input[1])
				return make_response(response)
			except ArithmeticError:
				content = ["\"<strong> %s </strong>\" <br>"
				           "Input is not coherent, should be like the <i>example</i> above" % equation]
				response = send_html_page('/response.html').replace("__response__", "<br>".join(content))
				response = response.replace("__left__", "5 * X^0 + 4 * X^1 - 9.3 * X^2")
				response = response.replace("__right__", "0")
				return make_response(response)

	return make_response(send_html_page('/index.html'))


if __name__ == '__main__':
	app.run(host="127.0.0.1", port=5000)