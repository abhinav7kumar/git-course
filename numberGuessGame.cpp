#include <iostream>
using namespace std;

int main() {
    int secret = 7;
    int guess;

    cout << "Guess the number: ";
    cin >> guess;

    if (guess == secret)
        cout << "Correct!";
    else
        cout << "Wrong!";

    return 0;
}
