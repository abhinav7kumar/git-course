#include <iostream>
#include <vector>
using namespace std;

struct Task {
    string name;
    bool completed;
};

int main() {
    vector<Task> tasks;
    int choice;

    do {
        cout << "\n--- To-Do List ---\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Task t;
            cout << "Enter task: ";
            getline(cin, t.name);
            t.completed = false;
            tasks.push_back(t);
            cout << "Task added successfully.\n";
        }

        else if (choice == 2) {
            if (tasks.empty()) {
                cout << "No tasks available.\n";
            } else {
                cout << "\nYour Tasks:\n";
                for (int i = 0; i < tasks.size(); i++) {
                    cout << i + 1 << ". " << tasks[i].name
                         << " [" << (tasks[i].completed ? "Done" : "Pending") << "]\n";
                }
            }
        }

        else if (choice == 3) {
            int index;
            cout << "Enter task number to mark completed: ";
            cin >> index;

            if (index > 0 && index <= tasks.size()) {
                tasks[index - 1].completed = true;
                cout << "Task marked as completed.\n";
            } else {
                cout << "Invalid task number.\n";
            }
        }

        else if (choice == 4) {
            int index;
            cout << "Enter task number to delete: ";
            cin >> index;

            if (index > 0 && index <= tasks.size()) {
                tasks.erase(tasks.begin() + index - 1);
                cout << "Task deleted.\n";
            } else {
                cout << "Invalid task number.\n";
            }
        }

        else if (choice == 5) {
            cout << "Exiting program.\n";
        }

        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
