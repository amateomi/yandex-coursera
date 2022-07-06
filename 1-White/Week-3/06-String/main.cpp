/*
 * Реализуйте класс ReversibleString, хранящий строку и поддерживающий методы
 * Reverse для переворота строки и ToString для получения строки.
 */
#include <algorithm>
#include <iostream>

using namespace std;

class ReversibleString {
 public:
  ReversibleString() = default;

  explicit ReversibleString(const string &string) {
    string_ = string;
  }

  void Reverse() {
    reverse(string_.begin(), string_.end());
  }

  [[nodiscard]]
  string ToString() const {
    return string_;
  }

 private:
  string string_;
};

int main() {
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;

  s.Reverse();
  const ReversibleString &s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;

  ReversibleString empty;
  cout << '"' << empty.ToString() << '"' << endl;
}
