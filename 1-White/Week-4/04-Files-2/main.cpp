/*
 * Снова считайте все содержимое файла input.txt, но на этот раз выведите его в
 * файл output.txt. Точно так же гарантируется, что содержимое файла input.txt
 * заканчивается переводом строки.
 */
#include <iostream>
#include <fstream>

using namespace std;

void CopyFile(ostream& destination, istream& source) {
  string line;
  while (getline(source, line)) {
    destination << line << endl;
  }
}

int main() {
  ifstream source("input.txt");
  ofstream destination("output.txt");
  if (source && destination) {
    CopyFile(destination, source);
  }
}
