#include <iostream>
#include <stack>
#include <string>

bool isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        return true;
    }
    return false;
}

bool isDigit(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

int getPriority(char op) {
    if (op == '^') {
        return 3;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else if (op == '+' || op == '-') {
        return 1;
    }
    else {
        return 0;
    }
}

float performOperation(float num1, float num2, char op) {
    if (op == '+') {
        return num1 + num2;
    }
    else if (op == '-') {
        return num1 - num2;
    }
    else if (op == '*') {
        return num1 * num2;
    }
    else if (op == '/') {
        return num1 / num2;
    }
    else if (op == '^') {
        return pow(num1, num2);
    }
    else {
        return 0;
    }
}

float evaluateExpression(std::string expression) {
    std::stack<float> values;
    std::stack<char> operators;
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') {
            continue;
        }
        else if (expression[i] == '(') {
            operators.push(expression[i]);
        }
        else if (isDigit(expression[i])) {
            float value = 0;
            while (i < expression.length() && (isDigit(expression[i]) || expression[i] == '.')) {
                value = (value * 10) + (expression[i] - '0');
                i++;
            }
            i--;
            values.push(value);
        }
        else if (isOperator(expression[i])) {
            while (!operators.empty() && getPriority(operators.top()) >= getPriority(expression[i])) {
                float num2 = values.top();
                values.pop();
                float num1 = values.top();
                values.pop();
                char op = operators.top();
                operators.pop();
                float result = performOperation(num1, num2, op);
                values.push(result);
            }
            operators.push(expression[i]);
        }
        else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                float num2 = values.top();
                values.pop();
                float num1 = values.top();
                values.pop();
                char op = operators.top();
                operators.pop();
                float result = performOperation(num1, num2, op);
                values.push(result);
            }
            operators.pop();
        }
    }
    while (!operators.empty()) {
        float num2 = values.top();
        values.pop();
        float num1 = values.top();
        values.pop();
        char op = operators.top();
        operators.pop();
        float result = performOperation(num1, num2, op);
        values.push(result);
    }
    return values.top();
}

int main() {
    system("chcp 1251");
    system("cls");
    std::string expression;
    std::cout << "Введите выражение: ";
    std::getline(std::cin, expression);
    float result = evaluateExpression(expression);
    std::cout << "Результат: " << result << std::endl;
}