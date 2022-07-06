/*
 * Дано два целых числа A и B в диапазоне от 0 до 1 000 000 включительно.
 * Напишите программу, которая вычисляет целую часть частного от деления A на B
 *
 * Если B = 0, выведите "Impossible".
 */
#include <iostream>

int main() {
    using namespace std;
    int a, b;
    cin >> a >> b;
    b != 0 ? cout << a / b : cout << "Impossible";
}
