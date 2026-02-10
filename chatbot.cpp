#include <iostream>
#include <string>
using namespace std;

int main() {
    string input;

    cout << "Chatbot started (type 'bye' to exit)\n";

    while (true) {
        cout << "You: ";
        getline(cin, input);

        if (input.find("hello") != string::npos)
            cout << "Bot: Hello! How can I help you?\n";
        else if (input.find("help") != string::npos)
            cout << "Bot: I can answer basic questions.\n";
        else if (input.find("bye") != string::npos) {
            cout << "Bot: Goodbye!\n";
            break;
        } else
            cout << "Bot: I am still learning.\n";
    }
    return 0;
}
            cout << "Enter task number to delete: ";
            cin >> index;

            if (index > 0 && index <= tasks.size()) {
                tasks.erase(tasks.begin() + index - 1);
                cout << "Task deleted successfully.\n";
            } else {
                cout << "Invalid task number.\n";
            }
       