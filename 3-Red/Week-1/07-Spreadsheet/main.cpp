/*
 * Вам надо написать шаблонный класс Table для электронной таблицы. Для простоты
 * будем считать, что все ячейки таблицы имеют один и тот же тип данных T.
 * Таблица должна уметь менять свой размер по требованию пользователя. Вновь
 * созданные ячейки должны заполняться значениями по умолчанию типа T.
 *
 * Требования к классу такие:
 * 1. Класс должен называться Table.
 * 2. У класса должен быть шаблонный параметр T — тип элемента в ячейке.
 * 3. У класса должен быть конструктор, получающий на входе два числа типа
 *    size_t — количество строк и столбцов соответственно.
 * 4. У класса должны быть константная и неконстантная версии оператора [],
 *    возвращающего нечто такое, к чему снова можно было бы применить оператор
 *    []. То есть, должны работать конструкции вида cout << table[i][j];и
 *    table[i][j] = value;. Проверять корректность индексов при этом не нужно.
 * 5. У класса должна быть функция Resize, получающая на вход два параметра типа
 *    size_t и меняющая размер таблицы. Старые данные, умещающиеся в новый
 *    размер, должны при этом сохраниться.
 * 6. У класса должна быть константная функция Size, возвращающая pair<size_t,
 *    size_t> — размер таблицы (в том же порядке, в котором эти аргументы
 *    передавались в конструктор). При этом, если у таблицы Table один из
 *    размеров нулевой, то необходимо считать таковым и второй размер таблицы.
 */
#include "test_runner.h"
#include <vector>

using namespace std;

template<typename T>
class Table {
 public:
  Table(size_t rows, size_t columns)
      : rows_(rows), columns_(columns) {

    HandleZeroSize();

    table_.resize(rows_);
    for (vector<T>& row : table_) {
      row.resize(columns_);
    }
  }

  const vector<T>& operator[](size_t i) const { return table_[i]; }
  vector<T>& operator[](size_t i) { return table_[i]; }

  void Resize(size_t rows, size_t columns) {
    rows_ = rows;
    columns_ = columns;

    HandleZeroSize();

    table_.resize(rows);
    for (vector<T>& row : table_) {
      row.resize(columns);
    }
  }

  [[nodiscard]]
  pair<size_t, size_t> Size() const { return {rows_, columns_}; }

 private:
  void HandleZeroSize() {
    if (rows_ == 0 || columns_ == 0) {
      rows_ = 0;
      columns_ = 0;
    }
  }

  size_t rows_, columns_;
  vector<vector<T>> table_;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
}
