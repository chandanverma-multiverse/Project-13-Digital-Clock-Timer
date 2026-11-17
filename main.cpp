/**
 * Project 13: Digital Clock, Countdown Timer & Stopwatch (Version 3.0)
 * Project Group ID: 13
 * Team Members:
 *   - Het (Roll No: 21)
 *   - Chandan (Roll No: 20)
 *
 * Version 3.0 Upgrades:
 *   1. Added 12-Hour (AM/PM) & 24-Hour format switching + Live Date display
 *   2. Added visual ASCII Progress Bar in Countdown Timer
 *   3. Added a new Stopwatch module with Lap recording
 */

#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>
#include <limits>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ============================================================================
// Class 1: DigitalClock (Upgraded in v3.0 with 12/24-Hr Toggle & Date)
// ============================================================================
class DigitalClock {
private:
    int hours;
    int minutes;
    int seconds;
    string currentDate;
    bool is24HourFormat;

public:
    DigitalClock() : hours(0), minutes(0), seconds(0), is24HourFormat(true) {}

    void toggleFormat() {
        is24HourFormat = !is24HourFormat;
        cout << "\n[Info] Clock format switched to "
             << (is24HourFormat ? "24-Hour" : "12-Hour (AM/PM)") << ".\n";
    }

    void getCurrentTime() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        hours = ltm->tm_hour;
        minutes = ltm->tm_min;
        seconds = ltm->tm_sec;

        char dateBuf[64];
        strftime(dateBuf, sizeof(dateBuf), "%A, %d %b %Y", ltm);
        currentDate = string(dateBuf);
    }

    void displayTime() const {
        int displayHour = hours;
        string period = "";

        if (!is24HourFormat) {
            period = (hours >= 12) ? " PM" : " AM";
            displayHour = hours % 12;
            if (displayHour == 0) displayHour = 12;
        }

        cout << "============================================\n";
        cout << "            DIGITAL CLOCK (v3.0)            \n";
        cout << "============================================\n";
        cout << "  Date: " << currentDate << "\n\n";
        cout << "               "
             << setfill('0') << setw(2) << displayHour << ":"
             << setfill('0') << setw(2) << minutes << ":"
             << setfill('0') << setw(2) << seconds << period << "\n\n";
        cout << "  Mode: " << (is24HourFormat ? "24-Hour Format" : "12-Hour Format") << "\n";
        cout << "============================================\n";
    }

    void updateTime(int refreshCycles = 10) {
        for (int i = 0; i < refreshCycles; ++i) {
            clearScreen();
            getCurrentTime();
            displayTime();
            cout << "Live updating... (" << (refreshCycles - i) << "s remaining)\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
};

// ============================================================================
// Class 2: CountdownTimer (Upgraded in v3.0 with Visual Progress Bar)
// ============================================================================
class CountdownTimer {
private:
    int totalSeconds;
    int remainingSeconds;
    bool isRunning;

public:
    CountdownTimer() : totalSeconds(0), remainingSeconds(0), isRunning(false) {}

    bool setTimer() {
        int h = 0, m = 0, s = 0;
        cout << "\n--- Set Countdown Timer ---\n";
        cout << "Enter Hours   (>= 0): ";
        if (!(cin >> h)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[Error] Invalid input! Enter numbers only.\n";
            return false;
        }

        cout << "Enter Minutes (>= 0): ";
        if (!(cin >> m)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[Error] Invalid input! Enter numbers only.\n";
            return false;
        }

        cout << "Enter Seconds (>= 0): ";
        if (!(cin >> s)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[Error] Invalid input! Enter numbers only.\n";
            return false;
        }

        if (h < 0 || m < 0 || s < 0) {
            cout << "\n[Error] Duration cannot be negative!\n";
            return false;
        }

        totalSeconds = (h * 3600) + (m * 60) + s;
        remainingSeconds = totalSeconds;

        if (remainingSeconds == 0) {
            cout << "\n[Error] Duration must be greater than 0 seconds!\n";
            return false;
        }

        return true;
    }

    void displayRemainingTime() const {
        int hrs = remainingSeconds / 3600;
        int mins = (remainingSeconds % 3600) / 60;
        int secs = remainingSeconds % 60;

        // Calculate visual progress bar
        int barWidth = 24;
        double progress = (double)(totalSeconds - remainingSeconds) / totalSeconds;
        int filled = (int)(progress * barWidth);

        cout << "============================================\n";
        cout << "           COUNTDOWN TIMER (v3.0)           \n";
        cout << "============================================\n\n";
        cout << "                 "
             << setfill('0') << setw(2) << hrs << ":"
             << setfill('0') << setw(2) << mins << ":"
             << setfill('0') << setw(2) << secs << "\n\n";

        cout << "  [";
        for (int i = 0; i < barWidth; ++i) {
            cout << (i < filled ? '#' : '-');
        }
        cout << "] " << (int)(progress * 100) << "%\n\n";
        cout << "            Countdown running...            \n";
        cout << "============================================\n";
    }

    void updateTimer() {
        if (remainingSeconds > 0) {
            remainingSeconds--;
        }
    }

    void showCompletionMessage() const {
        clearScreen();
        cout << "============================================\n";
        cout << "           COUNTDOWN TIMER (v3.0)           \n";
        cout << "============================================\n\n";
        cout << "                 00:00:00                   \n\n";
        cout << "  [########################] 100%           \n\n";
        cout << "                Time's Up!                  \n";
        cout << "============================================\n\n";
        cout << "\a";
    }

    void startTimer() {
        isRunning = true;
        while (isRunning && remainingSeconds > 0) {
            clearScreen();
            displayRemainingTime();
            this_thread::sleep_for(chrono::seconds(1));
            updateTimer();
        }
        isRunning = false;
        showCompletionMessage();
    }
};

// ============================================================================
// Class 3: Stopwatch (New Module in v3.0)
// ============================================================================
class Stopwatch {
private:
    vector<string> laps;

    string formatElapsed(int totalSecs) const {
        int hrs = totalSecs / 3600;
        int mins = (totalSecs % 3600) / 60;
        int secs = totalSecs % 60;
        char buf[16];
        snprintf(buf, sizeof(buf), "%02d:%02d:%02d", hrs, mins, secs);
        return string(buf);
    }

public:
    void runStopwatch() {
        laps.clear();
        int secondsToTrack = 10;
        int lapInterval = 3;

        cout << "\n--- Stopwatch Setup (v3.0) ---\n";
        cout << "Enter total tracking duration in seconds (e.g., 10): ";
        if (!(cin >> secondsToTrack) || secondsToTrack <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            secondsToTrack = 10;
        }

        cout << "Auto-record Lap every N seconds (e.g., 3, or 0 for none): ";
        if (!(cin >> lapInterval) || lapInterval < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            lapInterval = 0;
        }

        for (int elapsed = 1; elapsed <= secondsToTrack; ++elapsed) {
            this_thread::sleep_for(chrono::seconds(1));
            clearScreen();

            if (lapInterval > 0 && elapsed % lapInterval == 0) {
                laps.push_back("Lap " + to_string(laps.size() + 1) + " -> " + formatElapsed(elapsed));
            }

            cout << "============================================\n";
            cout << "              STOPWATCH (v3.0)              \n";
            cout << "============================================\n\n";
            cout << "            Elapsed: " << formatElapsed(elapsed) << "\n\n";

            if (!laps.empty()) {
                cout << "  Recorded Laps:\n";
                for (const string& lap : laps) {
                    cout << "   * " << lap << "\n";
                }
                cout << "\n";
            }
            cout << "============================================\n";
        }
        cout << "Stopwatch finished!\n";
    }
};

// ============================================================================
// Class 4: DigitalClockTimerApp (Main Controller)
// ============================================================================
class DigitalClockTimerApp {
private:
    DigitalClock clock;
    CountdownTimer timer;
    Stopwatch stopwatch;

public:
    void showMenu() const {
        cout << "\n============================================\n";
        cout << "   DIGITAL CLOCK & COUNTDOWN TIMER (v3.0)   \n";
        cout << "   Group ID: 13 | Het (21) & Chandan (20)   \n";
        cout << "============================================\n";
        cout << "  1. Digital Clock (Live Time & Date)\n";
        cout << "  2. Toggle Clock Format (12-Hr / 24-Hr)\n";
        cout << "  3. Countdown Timer (with Progress Bar)\n";
        cout << "  4. Stopwatch (with Lap Split Recorder)\n";
        cout << "  5. Exit\n";
        cout << "============================================\n";
        cout << "Select an option (1-5): ";
    }

    void runClock() {
        int duration = 10;
        cout << "\nEnter seconds to view live Digital Clock (e.g., 10): ";
        if (!(cin >> duration) || duration <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            duration = 10;
        }
        clock.updateTime(duration);
    }

    void runCountdown() {
        if (timer.setTimer()) {
            timer.startTimer();
            cout << "Press Enter to return to the main menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    void run() {
        int choice = 0;
        while (true) {
            showMenu();
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n[Error] Invalid input! Enter a number from 1 to 5.\n";
                continue;
            }

            switch (choice) {
                case 1:
                    runClock();
                    break;
                case 2:
                    clock.toggleFormat();
                    break;
                case 3:
                    runCountdown();
                    break;
                case 4:
                    stopwatch.runStopwatch();
                    break;
                case 5:
                    cout << "\nExiting application (v3.0). Thank you!\n";
                    return;
                default:
                    cout << "\n[Error] Invalid choice! Please select 1 to 5.\n";
                    break;
            }
        }
    }
};

int main() {
    DigitalClockTimerApp app;
    app.run();
    return 0;
}
