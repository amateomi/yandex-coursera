/*
 * Разработать макрос UNIQ_ID, который будет формировать идентификатор,
 * уникальный в пределах данного cpp-файла.
 */
#include <string>
#include <vector>
using namespace std;

#define SECOND_HELPER(line) id_##line
#define FIRST_HELPER(line) SECOND_HELPER(line)
#define UNIQ_ID FIRST_HELPER(__LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}
