/*
 * В stdin даны два натуральных числа.
 * Выведите в stdout их наибольший общий делитель.
 */
#include <iostream>
#include <numeric>

int main() {
    using namespace std;

    int a, b;
    cin >> a >> b;
    cout << gcd(a, b);
}
