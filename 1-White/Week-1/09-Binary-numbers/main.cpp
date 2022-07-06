/*
 * На вход дано целое положительное число N. Выведите его в двоичной системе
 * счисления без ведущих нулей.
 */
#include <iostream>
#include <deque>

int main() {
    using namespace std;
    
    unsigned n;
    cin >> n;

    deque<unsigned> bin;
    do {
        bin.push_front(n % 2);
        n /= 2;
    } while (n >= 1);

    for (auto i : bin) {
        cout << i;
    }
}
