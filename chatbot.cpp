#include <iostream>
using namespace std;

int main() {
    string input;
    cout << "You: ";
    cin >> input;

    if (input == "hello")
        cout << "Bot: Hello!" << endl;
    else
        cout << "Bot: I don't understand." << endl;

    return 0;
}
