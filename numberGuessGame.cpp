#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int secret = rand() % 10 + 1;
    int guess;
    int attempts = 0;
    const int maxAttempts = 5;

    cout << "Number Guessing Game (1-10)\n";

    while (attempts < maxAttempts) {
        cout << "Attempt " << attempts + 1 << ": ";
        cin >> guess;
        attempts++;

        if (guess == secret) {
            cout << " You guessed it right!\n";
            return 0;
        } else if (guess > secret) {
            cout << "Too high!\n";
        } else {
            cout << "Too low!\n";
        }
    }

    cout << "Game Over! The number was " << secret;
    return 0;
}
