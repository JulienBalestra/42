from flask import Flask, request, render_template
from computorv1 import computor

application = Flask(__name__)


def coherent_split(string):
    splited = string.split("=")
    if len(splited) != 2:
        return False
    for item in splited:
        item = item.replace(" ", "")
        if len(item) == 0:
            return False
    return True


def get_form(received):
    try:
        if received['<left>'] and received['<right>']:
            if "=" not in received['<left>'] and "=" not in received['<right>']:
                equation = received['<left>'] + " = " + received['<right>']
            else:
                equation = received['<left>'] + received['<right>']
        elif received['<left>']:
            if "=" in received['<left>'] and coherent_split(received['<left>']) is True:
                equation = received['<left>']
            else:
                equation = received['<left>'].replace("=", "")
                equation += " = 0"
        elif received['<right>']:
            if "=" in received['<right>'] and coherent_split(received['<right>']) is True:
                equation = received['<right>']
            else:
                equation = received['<right>'].replace("=", "")
                equation = "0 = " + equation
        else:
            return None
        return equation.replace('"', " ")

    except Exception as e:
        print e


def split_list(message):
    equation = list()
    solution = list(message)
    for i in range(0, 2):
        equation.append(message[i].split(": "))
        solution.pop(0)
    if "Reduced" in message[2]:
        equation.append(message[2].split(": "))
        solution.pop(0)
    return equation, solution


@application.route('/', methods=['POST', 'GET'])
def root():
    if request.method == 'POST':
        equation = get_form(request.form)
        if equation is not None:
            top = "You gave the following input :"
            try:
                solve = computor.Equation(str(equation))
                eq_input = solve.__repr__().split("=")
                message = solve.build_display_message()
                response = split_list(message)
                return render_template('index.html', top=top, left=eq_input[0], right=eq_input[1],
                                       equation=response[0], solution=response[1])

            except ArithmeticError:
                equation = equation.split("=")
                response = ["Arithmetic error, try again like the example :", "", "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 0"]
                return render_template('index.html', top=top, left=equation[0], right=equation[1], solution=response)

    top, left, right = "Example :", "5 * X^0 + 4 * X^1 - 9.3 * X^2", "0"
    return render_template('index.html', top=top, left=left, right=right)


if __name__ == '__main__':
    application.run(host="0.0.0.0", port=5000)