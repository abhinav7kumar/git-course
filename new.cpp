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
        cout << "\n1. Add Task\n2. View Tasks\n3. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Task t;
            cout << "Enter task: ";
            getline(cin, t.name);
            t.completed = false;
            tasks.push_back(t);
        } 
        else if (choice == 2) {
            for (int i = 0; i < tasks.size(); i++) {
                cout << i + 1 << ". " << tasks[i].name
                     << (tasks[i].completed ? " [Done]" : " [Pending]") << endl;
            }
        }
    } while (choice != 3);

    return 0;
}
