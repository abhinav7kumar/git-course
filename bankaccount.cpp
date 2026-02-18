#include <iostream>
using namespace std;

int main() {
    float balance = 5000, withdraw;

    cout << "Enter amount to withdraw: ";
    cin >> withdraw;

    if (withdraw <= balance) {
        balance -= withdraw;
        cout << "Withdrawal successful.\n";
    } else {
        cout << "Insufficient balance.\n";
    }

    cout << "Current balance: " << balance << endl;
    return 0;
}