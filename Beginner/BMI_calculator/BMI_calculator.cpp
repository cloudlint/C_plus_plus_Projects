#include <iostream>
#include <iomanip>  // for setprecision
using namespace std;

int main() {
    double height, weight, bmi;

    cout << "BMI Calculator\n\n";

    // Input height in meters
    cout << "Enter your height in meters (e.g., 1.75): ";
    cin >> height;
    while (height <= 0) {
        cout << "Height must be positive. Please enter again: ";
        cin >> height;
    }

    // Input weight in kilograms
    cout << "Enter your weight in kilograms (e.g., 70): ";
    cin >> weight;
    while (weight <= 0) {
        cout << "Weight must be positive. Please enter again: ";
        cin >> weight;
    }

    // Calculate BMI
    bmi = weight / (height * height);

    // Show result with 2 decimal places
    cout << fixed << setprecision(2);
    cout << "\nYour BMI is " << bmi << "\n";

    // BMI interpretation
    if (bmi < 18.5) {
        cout << "You are underweight.\n";
    }
    else if (bmi >= 18.5 && bmi < 24.9) {
        cout << "You have a normal weight.\n";
    }
    else if (bmi >= 24.9 && bmi < 30) {
        cout << "You are overweight.\n";
    }
    else {
        cout << "You are obese.\n";
    }

    return 0;
}
