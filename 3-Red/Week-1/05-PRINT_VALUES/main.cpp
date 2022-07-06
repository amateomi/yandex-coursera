/*
 * Вам дан макрос, который распечатывает два переданных ему значения в
 * переданный поток вывода. В реализации макроса есть недостаток, ограничивающий
 * его применимость в реальных программах. Вам требуется найти и устранить
 * недостаток.
 *
 * #define PRINT_VALUES(out, x, y) out << (x) << endl; out << (y) << endl
 */

#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) ((out) << (x) << endl << (y) << endl)

int main() {
  TestRunner tr;
  tr.RunTest([] {
    ostringstream output;
    PRINT_VALUES(output, 5, "red belt");
    ASSERT_EQUAL(output.str(), "5\nred belt\n");
  }, "PRINT_VALUES usage example");
  return 0;
}
