from flask import Flask, request, render_template
import solver

app = Flask(__name__)


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
                equation = equation + "= 0"
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


@app.route('/', methods=['POST', 'GET'])
def root():
    if request.method == 'POST':
        equation = get_form(request.form)
        if equation is not None:
            top = "You gave the following input :"
            try:
                solve = solver.Equation(str(equation))
                eq_input = solve.__repr__().split("=")
                response = solve.build_display_message()
                return render_template('index.html', top=top, left=eq_input[0], right=eq_input[1], response=response)

            except ArithmeticError:
                equation = equation.split("=")
                response = ["Arithmetic error, try again like the example :", "", "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 0"]
                return render_template('index.html', top=top, left=equation[0], right=equation[1], response=response)

    top, left, right = "Example :", "5 * X^0 + 4 * X^1 - 9.3 * X^2", "0"
    return render_template('index.html', top=top, left=left, right=right)


if __name__ == '__main__':
    app.run(host="127.0.0.1", port=5000, debug=True)