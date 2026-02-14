#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int secret = rand() % 10 + 1;
    int guess, attempts = 0;

    while (true) {
        cout << "Guess (1-10): ";
        cin >> guess;
        attempts++;

        if (guess == secret) {
            cout << "Correct in " << attempts << " attempts!";
            break;
        }
    }
    return 0;
}
