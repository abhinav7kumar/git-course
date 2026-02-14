#include <iostream>
using namespace std;

int main() {
    int secret = 7, guess;

    while (true) {
        cout << "Guess the number: ";
        cin >> guess;

        if (guess == secret) {
            cout << "Correct!";
            break;
        } else {
            cout << "Try again\n";
        }
    }
    return 0;
}
