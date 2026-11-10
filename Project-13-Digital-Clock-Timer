main.cpp
/**
 * Project 13: Digital Clock & Countdown Timer (Version 2.0)
 * Project Group ID: 13
 * Team Members:
 *   - Het (Roll No: 21)
 *   - Chandan (Roll No: 20)
 */

#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>
#include <limits>
#include <cstdlib>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

class DigitalClock {
private:
    int hours;
    int minutes;
    int seconds;

public:
    DigitalClock() : hours(0), minutes(0), seconds(0) {}

    void getCurrentTime() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        hours = ltm->tm_hour;
        minutes = ltm->tm_min;
        seconds = ltm->tm_sec;
    }

    void displayTime() const {
        cout << "====================================\n";
        cout << "           DIGITAL CLOCK            \n";
        cout << "====================================\n\n";
        cout << "              "
             << setfill('0') << setw(2) << hours << ":"
             << setfill('0') << setw(2) << minutes << ":"
             << setfill('0') << setw(2) << seconds << "\n\n";
        cout << "====================================\n";
    }

    void updateTime(int refreshCycles = 10) {
        for (int i = 0; i < refreshCycles; ++i) {
            clearScreen();
            getCurrentTime();
            displayTime();
            cout << "Refreshing live... (" << (refreshCycles - i) << "s remaining before returning to menu)\n";
            cout << "(Press Ctrl+C anytime to force quit)\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
};

class CountdownTimer {
private:
    int remainingSeconds;
    bool isRunning;

public:
    CountdownTimer() : remainingSeconds(0), isRunning(false) {}

    bool setTimer() {
        int h = 0, m = 0, s = 0;
        cout << "\n--- Set Countdown Timer ---\n";
        cout << "Enter Hours   (>= 0): ";
        if (!(cin >> h)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[Error] Invalid input! Please enter numeric values only.\n";
            return false;
        }

        cout << "Enter Minutes (>= 0): ";
        if (!(cin >> m)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[Error] Invalid input! Please enter numeric values only.\n";
            return false;
        }

        cout << "Enter Seconds (>= 0): ";
        if (!(cin >> s)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[Error] Invalid input! Please enter numeric values only.\n";
            return false;
        }

        if (h < 0 || m < 0 || s < 0) {
            cout << "\n[Error] Countdown duration cannot be negative!\n";
            return false;
        }

        remainingSeconds = (h * 3600) + (m * 60) + s;

        if (remainingSeconds == 0) {
            cout << "\n[Error] Duration cannot be 0 seconds! Please enter a valid duration.\n";
            return false;
        }

        return true;
    }

    void displayRemainingTime() const {
        int hrs = remainingSeconds / 3600;
        int mins = (remainingSeconds % 3600) / 60;
        int secs = remainingSeconds % 60;

        cout << "====================================\n";
        cout << "          COUNTDOWN TIMER           \n";
        cout << "====================================\n\n";
        cout << "              "
             << setfill('0') << setw(2) << hrs << ":"
             << setfill('0') << setw(2) << mins << ":"
             << setfill('0') << setw(2) << secs << "\n\n";
        cout << "         Countdown running...       \n";
        cout << "====================================\n";
    }

    void updateTimer() {
        if (remainingSeconds > 0) {
            remainingSeconds--;
        }
    }

    void showCompletionMessage() const {
        clearScreen();
        cout << "====================================\n";
        cout << "          COUNTDOWN TIMER           \n";
        cout << "====================================\n\n";
        cout << "              00:00:00              \n\n";
        cout << "             Time's Up!             \n";
        cout << "====================================\n\n";
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

class DigitalClockTimerApp {
private:
    DigitalClock clock;
    CountdownTimer timer;

public:
    void showMenu() const {
        cout << "\n============================================\n";
        cout << "   DIGITAL CLOCK & COUNTDOWN TIMER (v2.0)   \n";
        cout << "   Group ID: 13 | Het (21) & Chandan (20)   \n";
        cout << "============================================\n";
        cout << "  1. Digital Clock\n";
        cout << "  2. Countdown Timer\n";
        cout << "  3. Exit\n";
        cout << "============================================\n";
        cout << "Select an option (1-3): ";
    }

    void runClock() {
        int duration = 10;
        cout << "\nEnter how many seconds to view the live Digital Clock (e.g., 10): ";
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

    void exitApplication() const {
        cout << "\nExiting application. Thank you!\n";
    }

    void run() {
        int choice = 0;
        while (true) {
            showMenu();
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n[Error] Invalid input! Please enter a number between 1 and 3.\n";
                continue;
            }

            switch (choice) {
                case 1:
                    runClock();
                    break;
                case 2:
                    runCountdown();
                    break;
                case 3:
                    exitApplication();
                    return;
                default:
                    cout << "\n[Error] Invalid menu choice! Please select 1, 2, or 3.\n";
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
