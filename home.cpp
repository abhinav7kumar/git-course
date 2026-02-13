#include <iostream>
using namespace std;

int main() {
    // Integer data types
    int age = 25;
    short small_num = 100;
    long large_num = 1000000;
    
    // Floating point data types
    float price = 19.99f;
    double salary = 5000.50;
    
    // Character and Boolean data types
    char grade = 'A';
    bool is_active = true;
    
    // String (requires <string> header for full functionality)
    string name = "John Doe";
    
    // Displaying variables
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Grade: " << grade << endl;
    cout << "Price: $" << price << endl;
    cout << "Salary: $" << salary << endl;
    cout << "Is Active: " << is_active << endl;
    
    return 0;
}
