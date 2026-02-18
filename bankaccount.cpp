#include <iostream>
using namespace std;

int main() {
    float balance = 5000;
    int choice;
    float amount;

    do {
        cout << "\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter amount: ";
            cin >> amount;
            balance += amount;
        }
        else if (choice == 2) {
            cout << "Enter amount: ";
            cin >> amount;
            if (amount <= balance)
                balance -= amount;
            else
                cout << "Insufficient balance\n";
        }
        else if (choice == 3) {
            cout << "Balance: " << balance << endl;
        }

    } while (choice != 4);

    return 0;
}