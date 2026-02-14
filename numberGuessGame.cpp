#include <iostream>
using namespace std;

int main() {
    int secret = 7, guess, attempts = 0;

    while (true) {
        cout << "Guess the number: ";
        cin >> guess;
        attempts++;

        if (guess == secret) {
            cout << "Correct in " << attempts << " attempts!";
            break;
        }
    }
    return 0;
}
