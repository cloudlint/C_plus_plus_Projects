#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

class AdvancedDigitalClock {
private:
    struct TimeZone {
        string name;
        string location;
        double offset; // fractional hours offset from UTC
    };
    
    bool is24HourFormat;
    bool showSeconds;
    bool showDate;
    bool showMultipleTimeZones;
    vector<TimeZone> timeZones;
    int currentMainTimeZone;
    
public:
    AdvancedDigitalClock();
    void displayClock();
    void displayMenu();
    void toggleTimeFormat();
    void toggleSeconds();
    void toggleDate();
    void toggleMultipleTimeZones();
    void changeMainTimeZone();
    void addCustomTimeZone();
    void clearScreen();
    string getFormattedTime(double timeZoneOffset = 0);
    string getFormattedDate(double timeZoneOffset = 0);
    void showWorldClocks();
    void run();
};

AdvancedDigitalClock::AdvancedDigitalClock() : 
    is24HourFormat(true), 
    showSeconds(true), 
    showDate(true),
    showMultipleTimeZones(false),
    currentMainTimeZone(0) {
    
    // Initialize common time zones with fractional offset support
    timeZones = {
        {"UTC", "London", 0},
        {"EST", "New York", -5},
        {"PST", "Los Angeles", -8},
        {"CET", "Paris", +1},
        {"JST", "Tokyo", +9},
        {"IST", "Mumbai", +5.5},
        {"AEST", "Sydney", +10}
    };
}

void AdvancedDigitalClock::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

string AdvancedDigitalClock::getFormattedDate(double timeZoneOffset) {
    auto now = chrono::system_clock::now();
    auto adjustedTime = now + chrono::minutes(static_cast<int>(timeZoneOffset * 60));
    time_t adjustedTime_t = chrono::system_clock::to_time_t(adjustedTime);
    tm* adjustedTm = gmtime(&adjustedTime_t);
    
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%A, %B %d, %Y", adjustedTm);
    return string(buffer);
}

string AdvancedDigitalClock::getFormattedTime(double timeZoneOffset) {
    auto now = chrono::system_clock::now();
    auto adjustedTime = now + chrono::minutes(static_cast<int>(timeZoneOffset * 60));
    time_t adjustedTime_t = chrono::system_clock::to_time_t(adjustedTime);
    tm* adjustedTm = gmtime(&adjustedTime_t);
    
    char buffer[80];
    if (is24HourFormat) {
        if (showSeconds) {
            strftime(buffer, sizeof(buffer), "%H:%M:%S", adjustedTm);
        } else {
            strftime(buffer, sizeof(buffer), "%H:%M", adjustedTm);
        }
    } else {
        if (showSeconds) {
            strftime(buffer, sizeof(buffer), "%I:%M:%S %p", adjustedTm);
        } else {
            strftime(buffer, sizeof(buffer), "%I:%M %p", adjustedTm);
        }
    }
    return string(buffer);
}

void AdvancedDigitalClock::showWorldClocks() {
    cout << "┌────────────────────────────────────────┐" << endl;
    cout << "│             WORLD CLOCKS               │" << endl;
    cout << "├────────────────────────────────────────┤" << endl;
    
    for (size_t i = 0; i < timeZones.size(); ++i) {
        string timeStr = getFormattedTime(timeZones[i].offset);
        string marker = (i == currentMainTimeZone) ? "  *" : "";
        cout << "│ " << setw(4) << left << timeZones[i].name 
             << " " << setw(15) << left << timeZones[i].location 
             << " " << setw(11) << right << timeStr 
             << marker << setw(10 - marker.length()) << " │" << endl;
    }
    cout << "└────────────────────────────────────────┘" << endl;
}

void AdvancedDigitalClock::displayClock() {
    clearScreen();
    
    // Header
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║               ADVANCED DIGITAL CLOCK             ║" << endl;
    cout << "╠══════════════════════════════════════════════════╣" << endl;
    
    // Main time display
    if (showDate) {
        cout << "║      " << setw(40) << left 
             << getFormattedDate(timeZones[currentMainTimeZone].offset) << " ║" << endl;
    }
    
    cout << "║                                                  ║" << endl;
    cout << "║              ┌─────────────────┐                ║" << endl;
    cout << "║              │    " << setw(11) 
         << getFormattedTime(timeZones[currentMainTimeZone].offset) << "    │                ║" << endl;
    cout << "║              └─────────────────┘                ║" << endl;
    cout << "║                                                  ║" << endl;
    cout << "║  Location: " << setw(30) << left 
         << timeZones[currentMainTimeZone].location + " (" + timeZones[currentMainTimeZone].name + ")"
         << "     ║" << endl;
    cout << "║                                                  ║" << endl;
    
    // World clocks if enabled
    if (showMultipleTimeZones) {
        showWorldClocks();
    }
    
    // Footer with controls
    cout << "╠══════════════════════════════════════════════════╣" << endl;
    cout << "║ Controls: 1-Format 2-Seconds 3-Date 4-World       ║" << endl;
    cout << "║          5-Change TZ 6-Add TZ 7-Exit              ║" << endl;
    cout << "║                                                  ║" << endl;
    cout << "║ Status: " 
         << "Format:" << setw(9) << (is24HourFormat ? "24-hour" : "12-hour") 
         << " Seconds:" << setw(4) << (showSeconds ? "ON" : "OFF")
         << " Date:" << setw(4) << (showDate ? "ON" : "OFF") << " ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
}

void AdvancedDigitalClock::toggleTimeFormat() {
    is24HourFormat = !is24HourFormat;
}

void AdvancedDigitalClock::toggleSeconds() {
    showSeconds = !showSeconds;
}

void AdvancedDigitalClock::toggleDate() {
    showDate = !showDate;
}

void AdvancedDigitalClock::toggleMultipleTimeZones() {
    showMultipleTimeZones = !showMultipleTimeZones;
}

void AdvancedDigitalClock::changeMainTimeZone() {
    cout << "\nAvailable Time Zones:" << endl;
    for (size_t i = 0; i < timeZones.size(); ++i) {
        cout << i + 1 << ". " << timeZones[i].name << " - " << timeZones[i].location << endl;
    }
    cout << "Select time zone (1-" << timeZones.size() << "): ";
    
    int choice;
    cin >> choice;
    if (choice >= 1 && choice <= static_cast<int>(timeZones.size())) {
        currentMainTimeZone = choice - 1;
        cout << "Main time zone changed to " << timeZones[currentMainTimeZone].location << endl;
    } else {
        cout << "Invalid selection!" << endl;
    }
    this_thread::sleep_for(chrono::seconds(2));
}

void AdvancedDigitalClock::addCustomTimeZone() {
    string name, location;
    double offset;
    
    cout << "\nAdd Custom Time Zone" << endl;
    cout << "Enter time zone abbreviation (e.g., IST): ";
    cin >> name;
    cout << "Enter location (e.g., Berlin): ";
    cin.ignore();
    getline(cin, location);
    cout << "Enter UTC offset (e.g., +2, -5, +5.5): ";
    cin >> offset;
    
    timeZones.push_back({name, location, offset});
    cout << "Time zone added successfully!" << endl;
    this_thread::sleep_for(chrono::seconds(2));
}

void AdvancedDigitalClock::run() {
    bool running = true;
    
    cout << "Starting Advanced Digital Clock..." << endl;
    cout << "Loading time zones..." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    
    while (running) {
        displayClock();

        cout << "Enter option (1-7): ";
        char input;
        cin >> input;
        cin.ignore(); // Clear newline from input buffer
        
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
                toggleMultipleTimeZones();
                break;
            case '5':
                changeMainTimeZone();
                break;
            case '6':
                addCustomTimeZone();
                break;
            case '7':
                running = false;
                cout << "Exiting Advanced Digital Clock. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option! Press 1-7." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                break;
        }
    }
}

int main() {
    AdvancedDigitalClock clock;
    clock.run();
    return 0;
}
