/*
 * В этой задаче вам надо разработать класс Matrix для представления
 * целочисленной матрицы. Более подробно, класс Matrix должен иметь:
 * - конструктор по умолчанию, который создаёт матрицу с нулём строк и нулём
 *   столбцов
 * - конструктор от двух целочисленных параметров: num_rows и num_cols, —
 *   которые задают количество строк и столбцов матрицы соответственно
 * - метод Reset, принимающий два целочисленных параметра, которые задают новое
 *   количество строк и столбцов матрицы соответственно; метод Reset меняет
 *   размеры матрицы на заданные и обнуляет все её элементы
 * - константный метод At, который принимает номер строки и номер столбца
 *   (именно в этом порядке; нумерация строк и столбцов начинается с нуля) и
 *   возвращает значение в соответствущей ячейке матрицы
 * - не константный метод At с такими же параметрами, но возвращающий ссылку на
 *   значение в соответствущей ячейке матрицы
 * - константные методы GetNumRows и GetNumColumns, которые возвращают
 *   количество строк и столбцов матрицы соответственно
 * Если количество строк или количество столбцов, переданное в конструктор
 * класса Matrix или метод Reset, оказалось отрицательным, то должно быть
 * выброшено стандартное исключение out_of_range.
 * Это же исключение должен бросать метод At, если переданная в него ячейка
 * выходит за границы матрицы.
 * Кроме того, для класса Matrix должны быть определены следующие операторы:
 * - оператор ввода из потока istream; формат ввода простой — сначала задаётся
 *   количество строк и столбцов (именно в этом порядке), а затем все элементы
 *   матрицы: сначала элемент первой строки и первого столбца, затем элемент
 *   первой строки и второго столбца и так далее
 * - оператор вывода в поток ostream; он должен выводить матрицу в том же
 *   формате, в каком её читает оператор ввода, — в первой строке количество
 *   строк и столбцов, во второй — элементы первой строки, в третьей — элементы
 *   второй строки и т.д.
 * - оператор проверки на равенство (==): он должен возвращать true, если
 *   сравниваемые матрицы имеют одинаковый размер и все их соответствующие
 *   элементы равны между собой, в противном случае он должен возвращать false.
 * - оператор сложения: он должен принимать две матрицы и возвращать новую
 *   матрицу, которая является их суммой; если переданные матрицы имеют разные
 *   размеры этот оператор должен выбрасывать стандартное исключение
 *   invalid_argument.
 * Вам дана заготовка решения, а также пример ввода и вывода. Когда вы
 * реализуете класс Matrix, вы можете использовать этот пример, чтобы убедиться,
 * что ваш код работает правильно.
 * Важно! Пример не проверяет выполнение всех требований, приведённых в условии.
 * Примечание
 * Матрицы с нулём строк или нулём столбцов считаются пустыми. Любые две пустые
 * матрицы равны. Сумма двух пустых матриц также является пустой матрицей.
 */
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix
class Matrix {
 public:
  Matrix() = default;
  Matrix(int num_rows, int num_cols) {
    EnsureAndSetRowsAndCols(num_rows, num_cols);
  }

  void Reset(int num_rows, int num_cols) {
    EnsureAndSetRowsAndCols(num_rows, num_cols);
  }

  [[nodiscard]]
  int At(int row, int col) const {
    return data_.at(row).at(col);
  }
  int& At(int row, int col) {
    return data_.at(row).at(col);
  }

  [[nodiscard]]
  int GetNumRows() const {
    return num_rows_;
  }
  [[nodiscard]]
  int GetNumColumns() const {
    return num_cols_;
  }

  [[nodiscard]]
  bool IsEmpty() const {
    return num_rows_ == 0
        || num_cols_ == 0;
  }

 private:
  void EnsureAndSetRowsAndCols(int num_rows, int num_cols) {
    if (num_rows < 0 || num_cols < 0) {
      throw out_of_range("");
    }

    num_rows_ = num_rows;
    num_cols_ = num_cols;

    data_.assign(num_rows_, vector<int>(num_cols_));
  }

  int num_rows_ = 0;
  int num_cols_ = 0;
  vector<vector<int>> data_;
};

istream& operator>>(istream& in, Matrix& matrix) {
  int num_rows = 0, num_cols = 0;
  in >> num_rows >> num_cols;

  matrix = {num_rows, num_cols};

  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_cols; ++j) {
      in >> matrix.At(i, j);
    }
  }
  return in;
}
ostream& operator<<(ostream& out, const Matrix& matrix) {
  const int kNumRows = matrix.GetNumRows();
  const int kNumCols = matrix.GetNumColumns();

  out << kNumRows << ' ' << kNumCols << endl;
  for (int i = 0; i < kNumRows; ++i) {
    for (int j = 0; j < kNumCols; ++j) {
      out << matrix.At(i, j);
      if (j != kNumCols - 1) {
        out << ' ';
      }
    }
    out << endl;
  }
  return out;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
  const bool kIsLhsEmpty = lhs.IsEmpty();
  const bool kIsRhsEmpty = rhs.IsEmpty();

  if (kIsLhsEmpty || kIsRhsEmpty) {
    return kIsLhsEmpty == kIsRhsEmpty;
  }

  const int kLhsRows = lhs.GetNumRows();
  const int kLhsCols = lhs.GetNumColumns();

  const int kRhsRows = rhs.GetNumRows();
  const int kRhsCols = rhs.GetNumColumns();

  auto compare_elements = [lhs, rhs, kLhsRows, kLhsCols]() {
    for (int i = 0; i < kLhsRows; ++i) {
      for (int j = 0; j < kLhsCols; ++j) {
        if (lhs.At(i, j) != rhs.At(i, j)) {
          return false;
        }
      }
    }
    return true;
  };

  if (kLhsRows == kRhsRows && kLhsCols == kRhsCols) {
    return compare_elements();
  }
  return false;
}
Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
  if (lhs.IsEmpty() && rhs.IsEmpty()) {
    return {};
  }

  const int kLhsRows = lhs.GetNumRows();
  const int kLhsCols = lhs.GetNumColumns();

  const int kRhsRows = rhs.GetNumRows();
  const int kRhsCols = rhs.GetNumColumns();

  if (kLhsRows != kRhsRows || kLhsCols != kRhsCols) {
    throw invalid_argument("");
  }

  Matrix sum{kLhsRows, kLhsCols};

  for (int i = 0; i < kLhsRows; ++i) {
    for (int j = 0; j < kLhsCols; ++j) {
      sum.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
    }
  }
  return sum;
}

int main() {
  Matrix one;
  Matrix two;

  cin >> one >> two;
  cout << one + two << endl;
  return 0;
}
