#include <iostream>
using namespace std;

int main() {
    float balance = 0, deposit;

    cout << "Enter amount to deposit: ";
    cin >> deposit;

    balance += deposit;
    cout << "Updated balance: " << balance << endl;

    return 0;
}