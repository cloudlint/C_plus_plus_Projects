#include <iostream>
using namespace std;

int main() {
    double num1, num2, result;
    char operation;
    char choice;

    cout << "Simple Calculator\n";

    do {
        cout << "Enter first number: ";
        while (!(cin >> num1)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        cout << "Enter an operation (+, -, *, /): ";
        cin >> operation;

        cout << "Enter second number: ";
        while (!(cin >> num2)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        bool error = false;

        switch (operation) {
            case '+':
                result = num1 + num2;
                break;

            case '-':
                result = num1 - num2;
                break;

            case '*':
                result = num1 * num2;
                break;

            case '/':
                if (num2 == 0) {
                    cout << "Error: Division by zero is not allowed.\n";
                    error = true;
                } else {
                    result = num1 / num2;
                }
                break;

            default:
                cout << "Error: Invalid operation.\n";
                error = true;
                break;
        }

        if (!error) {
            cout << num1 << " " << operation << " " << num2 << " = " << result << "\n";
        }

        cout << "Do you want to perform another calculation? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "Thank you for using the calculator. Goodbye!\n";
    return 0;
}
