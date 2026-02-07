#include <iostream>
using namespace std;

int main() {
    int num;
    char choice;

    do {
        cout << "Enter a number: ";
        cin >> num;

        if (num % 2 == 0) {
            cout << num << " is Even\n";
        } else {
            cout << num << " is Odd\n";
        }

        cout << "Do you want to check another number? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;

    do{
        cout << "Enter a name: ";
        cin >> name;

        cout << "Do you want to enter another name? (y/n): ";
        cin >> choice;
    }
}
