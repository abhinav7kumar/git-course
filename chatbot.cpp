#include <iostream>
using namespace std;

int main() {
    string input;

    cout << "Type 'bye' to exit\n";

    while (true) {
        cout << "You: ";
        cin >> input;

        if (input == "hello")
            cout << "Bot: Hi there!" << endl;
        else if (input == "bye") {
            cout << "Bot: Goodbye!" << endl;
            break;
        } else
            cout << "Bot: Sorry, I don't understand." << endl;
    }
    return 0;
}
