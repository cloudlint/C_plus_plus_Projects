#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>

using namespace std;

class DigitalClock {
private:
    bool is24HourFormat;
    bool showSeconds;
    bool showDate;

public:
    DigitalClock() : is24HourFormat(true), showSeconds(true), showDate(true) {}
    
    void displayClock();
    void displayMenu();
    void toggleTimeFormat();
    void toggleSeconds();
    void toggleDate();
    void clearScreen();
    string getCurrentTime();
    string getCurrentDate();
    void run();
};

void DigitalClock::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

string DigitalClock::getCurrentDate() {
    time_t now = time(0);
    tm *localTime = localtime(&now);
    
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%A, %B %d, %Y", localTime);
    return string(buffer);
}

string DigitalClock::getCurrentTime() {
    time_t now = time(0);
    tm *localTime = localtime(&now);
    
    char buffer[80];
    if (is24HourFormat) {
        if (showSeconds) {
            strftime(buffer, sizeof(buffer), "%H:%M:%S", localTime);
        } else {
            strftime(buffer, sizeof(buffer), "%H:%M", localTime);
        }
    } else {
        if (showSeconds) {
            strftime(buffer, sizeof(buffer), "%I:%M:%S %p", localTime);
        } else {
            strftime(buffer, sizeof(buffer), "%I:%M %p", localTime);
        }
    }
    return string(buffer);
}

void DigitalClock::displayClock() {
    clearScreen();
    
    cout << "==========================================" << endl;
    cout << "             DIGITAL CLOCK" << endl;
    cout << "==========================================" << endl;
    
    if (showDate) {
        cout << "         " << getCurrentDate() << endl;
    }
    
    cout << endl;
    cout << "           ╔═══════════════════╗" << endl;
    cout << "           ║   " << setw(11) << getCurrentTime() << "     ║" << endl;
    cout << "           ╚═══════════════════╝" << endl;
    cout << endl;
    
    cout << "==========================================" << endl;
    cout << "Format: " << (is24HourFormat ? "24-hour" : "12-hour") << " | ";
    cout << "Seconds: " << (showSeconds ? "ON" : "OFF") << " | ";
    cout << "Date: " << (showDate ? "ON" : "OFF") << endl;
    cout << "==========================================" << endl;
    cout << "Controls: 1-Toggle Format, 2-Toggle Seconds," << endl;
    cout << "          3-Toggle Date,   4-Exit" << endl;
    cout << "==========================================" << endl;
}

void DigitalClock::toggleTimeFormat() {
    is24HourFormat = !is24HourFormat;
}

void DigitalClock::toggleSeconds() {
    showSeconds = !showSeconds;
}

void DigitalClock::toggleDate() {
    showDate = !showDate;
}

void DigitalClock::run() {
    char input;
    bool running = true;
    
    cout << "Starting Digital Clock..." << endl;
    cout << "Press any key to show menu options..." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    
    while (running) {
        displayClock();
        
        // Check for user input without blocking
        if (cin.peek() != EOF) {
            cin >> input;
            cin.ignore(); // Clear input buffer
            
            switch (input) {
                case '1':
                    toggleTimeFormat();
                    break;
                case '2':
                    toggleSeconds();
                    break;
                case '3':
                    toggleDate();
                    break;
                case '4':
                    running = false;
                    cout << "Exiting Digital Clock. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid option! Press 1-4." << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    break;
            }
        }
        
        // Update every second
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    DigitalClock clock;
    clock.run();
    return 0;
}