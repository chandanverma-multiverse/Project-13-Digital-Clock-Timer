#include <iostream>
#include <ctime>
#include <unistd.h> 

using namespace std;

int main() {
    int choice;
    cout << "1. Show Current Time\n2. Simple Countdown\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        time_t now = time(0);
        char* dt = ctime(&now);
        cout << "Current System Time: " << dt << endl;
    } 
    else if (choice == 2) {
        int seconds;
        cout << "Enter seconds to countdown: ";
        cin >> seconds;
        while (seconds > 0) {
            cout << seconds << " seconds remaining..." << endl;
            sleep(1);
            seconds--;
        }
        cout << "Time's Up!" << endl;
    } 
    else {
        cout << "Invalid option." << endl;
    }

    return 0;
}
