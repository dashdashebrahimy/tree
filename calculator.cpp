#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    else if (op == '*' || op == '/') return 2;
    else if (op == '^') return 3;
}
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
bool isUnaryMinus(const string &expression, int index) {
    if (expression[index] == '-') {
        if (index == 0) return true;
        char previousChar = expression[index - 1];
        return previousChar == '(' || isOperator(previousChar);
    }
    return false;
}
queue<string> infixToPostfix(const string &expression) {
    stack<char> opStack;
    queue<string> postfixQueue;
    for (int i = 0; i < expression.size(); i++) {
        char c = expression[i];
        if (isdigit(c)) {
            string number = "";
            number += c;
            while (i + 1 < expression.size() && isdigit(expression[i + 1])) {
                number += expression[++i];
            }
            postfixQueue.push(number);
        }
        else if (c == '(') {
            opStack.push(c);
        }
        else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfixQueue.push(string(1, opStack.top()));
                opStack.pop();
            }
            opStack.pop();
        }
        else if (isOperator(c)) {
            if (isUnaryMinus(expression, i)) {
                postfixQueue.push("0");
            }
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(c)) {
                postfixQueue.push(string(1, opStack.top()));
                opStack.pop();
            }
            opStack.push(c);
        }
    }
    while (!opStack.empty()) {
        postfixQueue.push(string(1, opStack.top()));
        opStack.pop();
    }

    return postfixQueue;
}
double evaluatePostfix(queue<string> postfixQueue) {
    stack<double> valueStack;

    while (!postfixQueue.empty()) {
        string temp = postfixQueue.front();
        postfixQueue.pop();
        if (isdigit(temp[0])) {
            valueStack.push(stod(temp));
        }
        else if (isOperator(temp[0])) {
            double b = valueStack.top(); valueStack.pop();
            double a = valueStack.top(); valueStack.pop();

            switch (temp[0]) {
                case '+': valueStack.push(a + b); break;
                case '-': valueStack.push(a - b); break;
                case '*': valueStack.push(a * b); break;
                case '/': valueStack.push(a / b); break;
                case '^': valueStack.push(pow(a, b)); break;
            }
        }
    }

    return valueStack.top();
}

int main() {
    string expression;
    getline(cin, expression);
    queue<string> postfix = infixToPostfix(expression);
    double result = evaluatePostfix(postfix);
    cout << result << endl;
}
