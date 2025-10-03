#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <iomanip>

using namespace std;

class AdvancedCalculator {
private:
    double memory;
    vector<string> history;
    
public:
    AdvancedCalculator() : memory(0) {}
    
    void displayMenu();
    void performOperation();
    void showHistory();
    void clearHistory();
    void memoryFunctions();
    void run();
    
    // Basic operations
    double add(double a, double b) { return a + b; }
    double subtract(double a, double b) { return a - b; }
    double multiply(double a, double b) { return a * b; }
    double divide(double a, double b) { 
        if (b == 0) throw runtime_error("Division by zero");
        return a / b; 
    }
    double power(double base, double exponent) { return pow(base, exponent); }
    int factorial(int n) {
        if (n < 0) throw runtime_error("Factorial of negative number");
        if (n == 0 || n == 1) return 1;
        return n * factorial(n - 1);
    }
    
    // Additional operations
    double squareRoot(double n) {
        if (n < 0) throw runtime_error("Square root of negative number");
        return sqrt(n);
    }
    
    double logarithm(double n) {
        if (n <= 0) throw runtime_error("Logarithm of non-positive number");
        return log(n);
    }
    
    double sine(double angle) { return sin(angle * M_PI / 180.0); }
    double cosine(double angle) { return cos(angle * M_PI / 180.0); }
    double tangent(double angle) { return tan(angle * M_PI / 180.0); }
};

void AdvancedCalculator::displayMenu() {
    cout << "==========================================" << endl;
    cout << "        ADVANCED C++ CALCULATOR" << endl;
    cout << "==========================================" << endl;
    cout << "1.  Addition (+)" << endl;
    cout << "2.  Subtraction (-)" << endl;
    cout << "3.  Multiplication (*)" << endl;
    cout << "4.  Division (/)" << endl;
    cout << "5.  Power (x^y)" << endl;
    cout << "6.  Factorial (n!)" << endl;
    cout << "7.  Square Root (√)" << endl;
    cout << "8.  Logarithm (ln)" << endl;
    cout << "9.  Trigonometric Functions" << endl;
    cout << "10. Memory Functions" << endl;
    cout << "11. Show History" << endl;
    cout << "12. Clear History" << endl;
    cout << "13. Exit" << endl;
    cout << "==========================================" << endl;
}

void AdvancedCalculator::performOperation() {
    int choice;
    double num1, num2, result;
    int num;
    
    cout << "Select operation (1-9): ";
    cin >> choice;
    
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!\n";
        return;
    }
    
    try {
        switch (choice) {
            case 1:
                cout << "Enter two numbers: ";
                cin >> num1 >> num2;
                result = add(num1, num2);
                cout << "Result: " << num1 << " + " << num2 << " = " << result << endl;
                history.push_back(to_string(num1) + " + " + to_string(num2) + " = " + to_string(result));
                break;
                
            case 2:
                cout << "Enter two numbers: ";
                cin >> num1 >> num2;
                result = subtract(num1, num2);
                cout << "Result: " << num1 << " - " << num2 << " = " << result << endl;
                history.push_back(to_string(num1) + " - " + to_string(num2) + " = " + to_string(result));
                break;
                
            case 3:
                cout << "Enter two numbers: ";
                cin >> num1 >> num2;
                result = multiply(num1, num2);
                cout << "Result: " << num1 << " * " << num2 << " = " << result << endl;
                history.push_back(to_string(num1) + " * " + to_string(num2) + " = " + to_string(result));
                break;
                
            case 4:
                cout << "Enter two numbers: ";
                cin >> num1 >> num2;
                result = divide(num1, num2);
                cout << "Result: " << num1 << " / " << num2 << " = " << result << endl;
                history.push_back(to_string(num1) + " / " + to_string(num2) + " = " + to_string(result));
                break;
                
            case 5:
                cout << "Enter base and exponent: ";
                cin >> num1 >> num2;
                result = power(num1, num2);
                cout << "Result: " << num1 << " ^ " << num2 << " = " << result << endl;
                history.push_back(to_string(num1) + " ^ " + to_string(num2) + " = " + to_string(result));
                break;
                
            case 6:
                cout << "Enter a non-negative integer: ";
                cin >> num;
                result = factorial(num);
                cout << "Result: " << num << "! = " << result << endl;
                history.push_back(to_string(num) + "! = " + to_string(result));
                break;
                
            case 7:
                cout << "Enter a number: ";
                cin >> num1;
                result = squareRoot(num1);
                cout << "Result: √" << num1 << " = " << result << endl;
                history.push_back("√" + to_string(num1) + " = " + to_string(result));
                break;
                
            case 8:
                cout << "Enter a positive number: ";
                cin >> num1;
                result = logarithm(num1);
                cout << "Result: ln(" << num1 << ") = " << result << endl;
                history.push_back("ln(" + to_string(num1) + ") = " + to_string(result));
                break;
                
            case 9:
                int trigChoice;
                double angle;
                cout << "1. Sine\n2. Cosine\n3. Tangent\nSelect: ";
                cin >> trigChoice;
                cout << "Enter angle in degrees: ";
                cin >> angle;
                
                if (trigChoice == 1) {
                    result = sine(angle);
                    cout << "sin(" << angle << "°) = " << result << endl;
                    history.push_back("sin(" + to_string(angle) + "°) = " + to_string(result));
                } else if (trigChoice == 2) {
                    result = cosine(angle);
                    cout << "cos(" << angle << "°) = " << result << endl;
                    history.push_back("cos(" + to_string(angle) + "°) = " + to_string(result));
                } else if (trigChoice == 3) {
                    result = tangent(angle);
                    cout << "tan(" << angle << "°) = " << result << endl;
                    history.push_back("tan(" + to_string(angle) + "°) = " + to_string(result));
                } else {
                    cout << "Invalid choice!\n";
                }
                break;
                
            default:
                cout << "Invalid operation!\n";
                break;
        }
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void AdvancedCalculator::memoryFunctions() {
    int choice;
    double value;
    
    cout << "\n=== Memory Functions ===" << endl;
    cout << "1. Store in Memory (MC)" << endl;
    cout << "2. Recall from Memory (MR)" << endl;
    cout << "3. Add to Memory (M+)" << endl;
    cout << "4. Subtract from Memory (M-)" << endl;
    cout << "5. Clear Memory" << endl;
    cout << "Select: ";
    cin >> choice;
    
    switch (choice) {
        case 1:
            cout << "Enter value to store: ";
            cin >> value;
            memory = value;
            cout << "Value " << value << " stored in memory." << endl;
            break;
        case 2:
            cout << "Memory value: " << memory << endl;
            break;
        case 3:
            cout << "Enter value to add: ";
            cin >> value;
            memory += value;
            cout << "Added " << value << " to memory. New value: " << memory << endl;
            break;
        case 4:
            cout << "Enter value to subtract: ";
            cin >> value;
            memory -= value;
            cout << "Subtracted " << value << " from memory. New value: " << memory << endl;
            break;
        case 5:
            memory = 0;
            cout << "Memory cleared." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
}

void AdvancedCalculator::showHistory() {
    if (history.empty()) {
        cout << "No calculations in history.\n";
        return;
    }
    
    cout << "\n=== Calculation History ===" << endl;
    for (size_t i = 0; i < history.size(); ++i) {
        cout << i + 1 << ". " << history[i] << endl;
    }
}

void AdvancedCalculator::clearHistory() {
    history.clear();
    cout << "History cleared.\n";
}

void AdvancedCalculator::run() {
    int choice;
    
    do {
        displayMenu();
        cout << "Enter your choice (1-13): ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1-13.\n\n";
            continue;
        }
        
        switch (choice) {
            case 1: case 2: case 3: case 4: case 5: 
            case 6: case 7: case 8: case 9:
                performOperation();
                break;
            case 10:
                memoryFunctions();
                break;
            case 11:
                showHistory();
                break;
            case 12:
                clearHistory();
                break;
            case 13:
                cout << "Thank you for using the Advanced Calculator. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please select between 1-13.\n";
                break;
        }
        
        if (choice != 13) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls || clear");
        }
        
    } while (choice != 13);
}

int main() {
    AdvancedCalculator calc;
    calc.run();
    return 0;
}