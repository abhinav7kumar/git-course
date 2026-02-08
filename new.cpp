#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<string> tasks;
    int choice;
    string task;

    do {
        cout << "\n--- To-Do List ---\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter task: ";
                getline(cin, task);
                tasks.push_back(task);
                cout << "Task added.\n";
                break;

            case 2:
                if (tasks.empty()) {
                    cout << "No tasks available.\n";
                } else {
                    cout << "Your Tasks:\n";
                    for (int i = 0; i < tasks.size(); i++) {
                        cout << i + 1 << ". " << tasks[i] << endl;
                    }
                }
                break;

            case 3:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}
