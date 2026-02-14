#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int secret = rand() % 10 + 1;
    int guess;

    while (true) {
        cout << "Guess (1-10): ";
        cin >> guess;

        if (guess == secret) {
            cout << "Correct!";
            break;
        } else if (guess > secret) {
            cout << "Too high\n";
        } else {
            cout << "Too low\n";
        }
    }
    return 0;
}
