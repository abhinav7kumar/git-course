#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

bool isPerfectSquare(int n) {
    if (n < 0) return false;
    int root = sqrt(n);
    return root * root == n;
}

bool isPerfectCube(int n) {
    if (n == 0) return true;
    if (n < 0) n = -n;
    int root = round(cbrt(n));
    return root * root * root == n;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

bool isArithmeticProgression(int x, int y, int z) {
    int arr[3] = {x, y, z};
    sort(arr, arr + 3);
    return (arr[1] - arr[0]) == (arr[2] - arr[1]);
}

bool areConsecutive(int x, int y, int z) {
    int arr[3] = {x, y, z};
    sort(arr, arr + 3);
    return arr[1] == arr[0] + 1 && arr[2] == arr[1] + 1;
}

bool isPythagoreanTriple(int x, int y, int z) {
    int arr[3] = {x, y, z};
    sort(arr, arr + 3);
    return arr[0] > 0 && arr[0] * arr[0] + arr[1] * arr[1] == arr[2] * arr[2];
}

bool canFormTriangle(int x, int y, int z) {
    int arr[3] = {x, y, z};
    sort(arr, arr + 3);
    return arr[0] > 0 && arr[0] + arr[1] > arr[2];
}

int main() {
    int a, b, c;

    cout << "Enter three numbers: ";
    cin >> a >> b >> c;

    // Find largest number
    int largest;
    if (a >= b && a >= c) {
        largest = a;
    } else if (b >= a && b >= c) {
        largest = b;
    } else {
        largest = c;
    }

    // Find smallest number
    int smallest;
    if (a <= b && a <= c) {
        smallest = a;
    } else if (b <= a && b <= c) {
        smallest = b;
    } else {
        smallest = c;
    }

    // Calculate sum and average
    int sum = a + b + c;
    double average = sum / 3.0;
    int product = a * b * c;

    // Calculate range
    int range = largest - smallest;

    // Find middle value (median)
    int middle;
    if ((a >= b && a <= c) || (a >= c && a <= b)) {
        middle = a;
    } else if ((b >= a && b <= c) || (b >= c && b <= a)) {
        middle = b;
    } else {
        middle = c;
    }

    // Count even and odd numbers
    int evenCount = (a % 2 == 0) + (b % 2 == 0) + (c % 2 == 0);
    int oddCount = 3 - evenCount;

    // Check arrangement order
    bool isAscending = (a <= b && b <= c);
    bool isDescending = (a >= b && b >= c);

    // Check for duplicates
    bool hasDuplicates = (a == b) || (b == c) || (a == c);

    // Check number signs
    int negativeCount = (a < 0) + (b < 0) + (c < 0);
    int positiveCount = (a > 0) + (b > 0) + (c > 0);
    bool isArithmetic = isArithmeticProgression(a, b, c);
    bool trianglePossible = canFormTriangle(a, b, c);
    bool consecutive = areConsecutive(a, b, c);
    bool pythagoreanTriple = isPythagoreanTriple(a, b, c);

    // Display results 
    cout << "\n===== ANALYSIS =====" << endl;
    cout << "Numbers: " << a << ", " << b << ", " << c << endl;
    cout << "Largest number: " << largest << endl;
    cout << "Smallest number: " << smallest << endl;
    cout << "Middle value: " << middle << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;
    cout << "Product: " << product << endl;
    cout << "Range: " << range << endl;
    cout << "Even numbers: " << evenCount << " | Odd numbers: " << oddCount << endl;
    cout << "Order: " << (isAscending ? "ASCENDING" : isDescending ? "DESCENDING" : "RANDOM") << endl;
    cout << "Arithmetic progression: " << (isArithmetic ? "YES" : "NO") << endl;
    cout << "Consecutive numbers: " << (consecutive ? "YES" : "NO") << endl;
    cout << "Pythagorean triple: " << (pythagoreanTriple ? "YES" : "NO") << endl;
    cout << "Triangle possible: " << (trianglePossible ? "YES" : "NO") << endl;
    cout << "Duplicates: " << (hasDuplicates ? "YES" : "NO") << endl;
    cout << "Positive: " << positiveCount << " | Negative: " << negativeCount << endl;
    cout << "\n===== PRIME CHECK =====" << endl;
    cout << a << " is " << (isPrime(a) ? "PRIME" : "NOT PRIME") << endl;
    cout << b << " is " << (isPrime(b) ? "PRIME" : "NOT PRIME") << endl;
    cout << c << " is " << (isPrime(c) ? "PRIME" : "NOT PRIME") << endl;
    
    int primeCount = isPrime(a) + isPrime(b) + isPrime(c);
    cout << "\nTotal PRIME numbers: " << primeCount << " out of 3" << endl;
    
    cout << "\n===== PERFECT SQUARE CHECK =====" << endl;
    cout << a << " is " << (isPerfectSquare(a) ? "PERFECT SQUARE" : "NOT A PERFECT SQUARE") << endl;
    cout << b << " is " << (isPerfectSquare(b) ? "PERFECT SQUARE" : "NOT A PERFECT SQUARE") << endl;
    cout << c << " is " << (isPerfectSquare(c) ? "PERFECT SQUARE" : "NOT A PERFECT SQUARE") << endl;
    cout << "\n===== PERFECT CUBE CHECK ====="  << endl;
    cout << a << " is " << (isPerfectCube(a) ? "PERFECT CUBE" : "NOT A PERFECT CUBE") << endl;
    cout << b << " is " << (isPerfectCube(b) ? "PERFECT CUBE" : "NOT A PERFECT CUBE") << endl;
    cout << c << " is " << (isPerfectCube(c) ? "PERFECT CUBE" : "NOT A PERFECT CUBE") << endl;

    cout << "\n===== GCD & LCM ====="  << endl;
    int gcdAll = gcd(a, gcd(b, c));
    int lcmAll = lcm(a, lcm(b, c));
    cout << "GCD of " << a << ", " << b << ", " << c << " = " << gcdAll << endl;
    cout << "LCM of " << a << ", " << b << ", " << c << " = " << lcmAll << endl;
    return 0;
}
