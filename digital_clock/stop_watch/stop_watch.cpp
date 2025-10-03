#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <sstream>

using namespace std;
using namespace chrono;

class StopwatchTimer {
private:
    steady_clock::time_point startTime;
    steady_clock::time_point endTime;
    bool running;
    bool paused;
    duration<double> elapsed;
    
public:
    StopwatchTimer() : running(false), paused(false), elapsed(0) {}
    
    void start();
    void pause();
    void resume();
    void stop();
    void reset();
    double getElapsedTime() const;
    string getFormattedTime() const;
    bool isRunning() const { return running; }
    bool isPaused() const { return paused; }
};

void StopwatchTimer::start() {
    if (!running && !paused) {
        startTime = steady_clock::now();
        running = true;
        paused = false;
        elapsed = duration<double>(0);
    } else if (paused) {
        resume();
    }
}

void StopwatchTimer::pause() {
    if (running && !paused) {
        endTime = steady_clock::now();
        elapsed += duration_cast<duration<double>>(endTime - startTime);
        running = false;
        paused = true;
    }
}

void StopwatchTimer::resume() {
    if (paused) {
        startTime = steady_clock::now();
        running = true;
        paused = false;
    }
}

void StopwatchTimer::stop() {
    if (running) {
        endTime = steady_clock::now();
        elapsed += duration_cast<duration<double>>(endTime - startTime);
        running = false;
        paused = false;
    }
}

void StopwatchTimer::reset() {
    running = false;
    paused = false;
    elapsed = duration<double>(0);
}

double StopwatchTimer::getElapsedTime() const {
    if (running) {
        auto current = steady_clock::now();
        return elapsed.count() + duration_cast<duration<double>>(current - startTime).count();
    }
    return elapsed.count();
}

string StopwatchTimer::getFormattedTime() const {
    double totalSeconds = getElapsedTime();
    int hours = static_cast<int>(totalSeconds) / 3600;
    int minutes = (static_cast<int>(totalSeconds) % 3600) / 60;
    int seconds = static_cast<int>(totalSeconds) % 60;
    int milliseconds = static_cast<int>((totalSeconds - static_cast<int>(totalSeconds)) * 1000);
    
    stringstream ss;
    ss << setfill('0') << setw(2) << hours << ":"
       << setw(2) << minutes << ":" 
       << setw(2) << seconds << "."
       << setw(3) << milliseconds;
    
    return ss.str();
}

void demonstrateStopwatch() {
    StopwatchTimer sw;
    char input;

    cout << "Stopwatch Demo - Commands: s-start, p-pause/resume, r-reset, q-quit" << endl;

    while (true) {
        if (sw.isRunning()) {
            // Update display every 100 ms while running
            cout << "\rTime: " << sw.getFormattedTime() << "   " << flush;
            this_thread::sleep_for(milliseconds(100));
            // Note: Input requires pressing enter in this simple approach
        } else {
            // If paused or stopped, wait for user command
            cout << "\nEnter command: ";
            cin >> input;
            switch (input) {
                case 's':
                    sw.start();
                    cout << "Stopwatch started!" << endl;
                    break;
                case 'p':
                    if (sw.isPaused()) {
                        sw.resume();
                        cout << "Stopwatch resumed." << endl;
                    } else if (sw.isRunning()) {
                        sw.pause();
                        cout << "Stopwatch paused at: " << sw.getFormattedTime() << endl;
                    } else {
                        cout << "Stopwatch is not running." << endl;
                    }
                    break;
                case 'r':
                    sw.reset();
                    cout << "Stopwatch reset!" << endl;
                    break;
                case 'q':
                    return;
                default:
                    cout << "Invalid command! Use s, p, r, or q." << endl;
                    break;
            }
        }
    }
}

int main() {
    demonstrateStopwatch();
    return 0;
}
