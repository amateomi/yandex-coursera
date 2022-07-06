/*
 * Реализуйте класс, поддерживающий набор строк в отсортированном порядке.
 */
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class SortedStrings {
 public:
  void AddString(const string& s) {
    strings_.insert(s);
  }
  vector<string> GetSortedStrings() {
    return {begin(strings_), end(strings_)};
  }
 private:
  multiset<string> strings_;
};

void PrintSortedStrings(SortedStrings& strings) {
  for (const string& s : strings.GetSortedStrings()) {
    cout << s << " ";
  }
  cout << endl;
}

int main() {
  SortedStrings strings;

  strings.AddString("first");
  strings.AddString("third");
  strings.AddString("second");
  PrintSortedStrings(strings);

  strings.AddString("second");
  PrintSortedStrings(strings);
}