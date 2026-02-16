#include <iostream>
using namespace std;

int main() {
    cout << "Welcome to the Puzzle Game!" << endl;
    cout << "Guess the correct number to unlock." << endl;
    return 0;
}

int main() {
    int secret = 5;
    cout << "Guess the secret number (1-10)." << endl;
    return 0;
}

int main() {
    int secret = 5;
    int guess;

    cout << "Enter your guess: ";
    cin >> guess;

    return 0;
}

int main() {
    int secret = 5;
    int guess;

    cout << "Enter your guess: ";
    cin >> guess;

    if (guess == secret)
        cout << "Correct! Puzzle unlocked.";
    else
        cout << "Wrong guess.";

    return 0;
}

int main() {
    int secret = 5;
    int guess;

    while (true) {
        cout << "Enter your guess: ";
        cin >> guess;

        if (guess == secret) {
            cout << "Correct! Puzzle unlocked.";
            break;
        } else {
            cout << "Wrong! Try again.\n";
        }
    }
    return 0;
}