#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int secret = rand() % 10 + 1;
    int guess, attempts = 0;

    while (attempts < 5) {
        cout << "Guess (1-10): ";
        cin >> guess;
        attempts++;

        if (guess == secret) {
            cout << "You win!";
            return 0;
        }
    }

    cout << "Game Over! Number was " << secret;
    return 0;
}
