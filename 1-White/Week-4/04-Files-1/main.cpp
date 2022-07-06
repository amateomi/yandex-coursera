/*
 * Ваша программа должна считать содержимое файла input.txt и напечатать его на
 * экран без изменений. Гарантируется, что содержимое файла input.txt
 * заканчивается переводом строки.
 */
#include <iostream>
#include <fstream>

using namespace std;

void PrintFile(ifstream& file) {
  string line;
  while (getline(file, line)) {
    cout << line << endl;
  }
}

int main() {
  ifstream file("input.txt");
  if (file) {
    PrintFile(file);
  }
}
