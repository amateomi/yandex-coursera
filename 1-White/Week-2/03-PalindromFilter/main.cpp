/*
 * Напишите функцию, которая
 * - называется PalindromFilter,
 * - возвращает vector<string>,
 * - принимает vector<string> words и int minLength и возвращает
 *   все строки из вектора words, которые являются палиндромами и
 *   имеют длину не меньше minLength.
 *
 * Входной вектор содержит не более 100 строк, длина каждой строки не больше 100 символов.
 */
#include <iostream>
#include <vector>

using namespace std;

bool IsPalindrom(string s) {
    for (int i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - 1 - i]) {
            return false;
        }
    }
    return true;
}

vector<string> PalindromFilter(const vector<string> &words, int minLength) {
    vector<string> filtered;
    for (const auto& word: words) {
        if (word.size() >= minLength && IsPalindrom(word)) {
            filtered.push_back(word);
        }
    }
    return filtered;
}

int main() {
    auto res = PalindromFilter({"abacaba", "aba"}, 5);
    for (const auto& i : res) {
        cout << i << endl;
    }
}
