#include <iostream>
#include <iomanip>
using namespace std;

// Length conversions
void lengthConverter() {
    double value;
    int choice;
    cout << "\nLength Converter:\n";
    cout << "1. Meters to Kilometers\n";
    cout << "2. Kilometers to Meters\n";
    cout << "3. Inches to Centimeters\n";
    cout << "4. Centimeters to Inches\n";
    cout << "Enter your choice: ";
    cin >> choice;

    cout << "Enter value to convert: ";
    cin >> value;

    switch (choice) {
        case 1:
            cout << fixed << setprecision(4) << value << " meters = " << value / 1000 << " kilometers\n";
            break;
        case 2:
            cout << fixed << setprecision(4) << value << " kilometers = " << value * 1000 << " meters\n";
            break;
        case 3:
            cout << fixed << setprecision(4) << value << " inches = " << value * 2.54 << " centimeters\n";
            break;
        case 4:
            cout << fixed << setprecision(4) << value << " centimeters = " << value / 2.54 << " inches\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
    }
}

// Weight conversions
void weightConverter() {
    double value;
    int choice;
    cout << "\nWeight Converter:\n";
    cout << "1. Kilograms to Grams\n";
    cout << "2. Grams to Kilograms\n";
    cout << "3. Pounds to Kilograms\n";
    cout << "4. Kilograms to Pounds\n";
    cout << "Enter your choice: ";
    cin >> choice;

    cout << "Enter value to convert: ";
    cin >> value;

    switch (choice) {
        case 1:
            cout << fixed << setprecision(4) << value << " kilograms = " << value * 1000 << " grams\n";
            break;
        case 2:
            cout << fixed << setprecision(4) << value << " grams = " << value / 1000 << " kilograms\n";
            break;
        case 3:
            cout << fixed << setprecision(4) << value << " pounds = " << value * 0.453592 << " kilograms\n";
            break;
        case 4:
            cout << fixed << setprecision(4) << value << " kilograms = " << value / 0.453592 << " pounds\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
    }
}

// Temperature conversions
void temperatureConverter() {
    double value;
    int choice;
    cout << "\nTemperature Converter:\n";
    cout << "1. Celsius to Fahrenheit\n";
    cout << "2. Fahrenheit to Celsius\n";
    cout << "3. Celsius to Kelvin\n";
    cout << "4. Kelvin to Celsius\n";
    cout << "Enter your choice: ";
    cin >> choice;

    cout << "Enter temperature value: ";
    cin >> value;

    switch (choice) {
        case 1:
            cout << fixed << setprecision(2) << value << " Celsius = " << (value * 9/5) + 32 << " Fahrenheit\n";
            break;
        case 2:
            cout << fixed << setprecision(2) << value << " Fahrenheit = " << (value - 32) * 5/9 << " Celsius\n";
            break;
        case 3:
            cout << fixed << setprecision(2) << value << " Celsius = " << value + 273.15 << " Kelvin\n";
            break;
        case 4:
            cout << fixed << setprecision(2) << value << " Kelvin = " << value - 273.15 << " Celsius\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
    }
}

int main() {
    int mainChoice;
    do {
        cout << "\nUnit Converter Menu:\n";
        cout << "1. Length conversion\n";
        cout << "2. Weight conversion\n";
        cout << "3. Temperature conversion\n";
        cout << "4. Exit\n";
        cout << "Choose a conversion category: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                lengthConverter();
                break;
            case 2:
                weightConverter();
                break;
            case 3:
                temperatureConverter();
                break;
            case 4:
                cout << "Exiting Unit Converter. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please select 1-4.\n";
                break;
        }
    } while (mainChoice != 4);

    return 0;
}
