#include <iostream>
#include <string>
using namespace std;

void respond(string input) {
    if (input.find("hello") != string::npos)
        cout << "Bot: Hello! 😊\n";
    else if (input.find("email") != string::npos)
        cout << "Bot: I can help manage emails.\n";
    else if (input.find("help") != string::npos)
        cout << "Bot: Try asking about email or account.\n";
    else
        cout << "Bot: Could you rephrase that?\n";
}

int main() {
    string input;
    cout << "Chatbot Active (type 'bye' to exit)\n";

    while (true) {
        cout << "You: ";
        getline(cin, input);

        if (input.find("bye") != string::npos) {
            cout << "Bot: Session ended.\n";
            break;
        }
        respond(input);
    }
    return 0;
}
