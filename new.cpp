#include <iostream>
#include <vector>
using namespace std;

struct Task {
    string name;
    bool completed = false;
};

void showTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }
    for (int i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i].name
             << (tasks[i].completed ? " [Done]" : " [Pending]") << endl;
    }
}

int main() {
    vector<Task> tasks;
    int choice;

    do {
        cout << "\n1.Add  2.View  3.Complete  4.Delete  5.Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Task t;
            cout << "Task name: ";
            getline(cin, t.name);
            tasks.push_back(t);
        }
        else if (choice == 2) showTasks(tasks);
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
