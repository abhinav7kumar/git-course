#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;

int main() {
    srand((unsigned int) time(nullptr));
    cout << "Welcome to the Number Lock Puzzle!" << endl;
    cout << "You can choose difficulty and use one hint during the game." << endl;

    int choice;
    int maxAttempts;
    int maxNumber;

    cout << "Select difficulty: 1) Easy (1-10, 8 attempts) 2) Medium (1-20, 6 attempts) 3) Hard (1-50, 4 attempts)\n";
    cout << "Enter 1, 2, or 3: ";
    cin >> choice;

    if (choice == 1) { maxNumber = 10; maxAttempts = 8; }
    else if (choice == 2) { maxNumber = 20; maxAttempts = 6; }
    else { maxNumber = 50; maxAttempts = 4; }

    int secret = rand() % maxNumber + 1;
    int attemptsLeft = maxAttempts;
    bool usedHint = false;

    cout << "Guess the secret number in range 1 to " << maxNumber << ".\n";
    cout << "Tip: enter 0 to unlock one bonus hint (odd/even)." << endl;

    while (attemptsLeft > 0) {
        int guess;
        cout << "Attempts left: " << attemptsLeft << ". Enter your guess: ";
        cin >> guess;

        if (guess == 0) {
            if (!usedHint) {
                usedHint = true;
                cout << "Hint: The secret number is " << (secret % 2 == 0 ? "even" : "odd") << "." << endl;
                continue;
            } else {
                cout << "Hint already used. No extra hints available." << endl;
                continue;
            }
        }

        if (guess == secret) {
            cout << "Correct! Puzzle unlocked." << endl;
            return 0;
        }

        attemptsLeft--;

        if (guess < secret)
            cout << "Too low!" << endl;
        else
            cout << "Too high!" << endl;

        if (attemptsLeft > 0) {
            cout << "Try again.\n";
        }
    }

    cout << "Game over. You failed to unlock the puzzle." << endl;
    cout << "Secret number was " << secret << "." << endl;

    cout << "Lock cooldown engaged for 5 seconds..." << endl;
    this_thread::sleep_for(chrono::seconds(5));
    cout << "You can retry after cooldown." << endl;
    return 0;
}