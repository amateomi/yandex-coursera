/*
 * В стандартном потоке даны три строки, разделённые пробелом. Каждая строка
 * состоит из строчных латинских букв и имеет длину не более 30 символов.
 * Выведите в стандартный вывод лексикографически минимальную из них.
 */
#include <algorithm>
#include <iostream>
#include <array>
#include <string>

int main() {
    using namespace std;
    array<string, 3> strings;
    for (int i = 0; i < 3; ++i) {
        cin >> strings[i];
    }
    cout << *min_element(strings.begin(), strings.end());
    return 0;
}
