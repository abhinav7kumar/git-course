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
        cout << "\n1. Add\n2. View\n3. Complete\n4. Delete\n5. Exit\nChoice: ";
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
        else if (choice == 3) {
            int n;
            cin >> n;
            if (n > 0 && n <= tasks.size())
                tasks[n - 1].completed = true;
        }
        else if (choice == 4) {
            int n;
            cin >> n;
            if (n > 0 && n <= tasks.size())
                tasks.erase(tasks.begin() + n - 1);
        }
    } while (choice != 5);

    return 0;
}
