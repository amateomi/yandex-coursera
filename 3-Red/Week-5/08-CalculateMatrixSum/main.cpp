/*
 * В лекциях мы рассмотрели пример, в котором сначала выполнялась генерация
 * квадратной матрицы, а затем находилась сумма элементов в ней. При этом нам
 * удалось ускорить генерацию матрицы за счёт применения многопоточности. В этой
 * задаче вам нужно сделать то же самое для суммирования элементов матрицы.
 *
 * Вам нужно написать функцию
 * int64_t CalculateMatrixSum(const vector<vector<int>>& matrix),
 * которая получает на вход квадратную матрицу и возвращает сумму элементов в
 * ней.
 *
 * Ваша реализация будет тестироваться следующим образом:
 * - на вход вашей функции будут подаваться квадратные матрицы размером до 9000
 *   (в данном случае размер матрицы — это количество строк в ней);
 * - для одной и той же матрицы функция CalculateMatrixSum будет запускаться
 *   несколько раз; среднее время работы одного вызова в нашей тестирующей
 *   системе не должно превышать 15 мс;
 */
#include "test_runner.h"
#include <vector>
#include <future>
#include <numeric>

using namespace std;

template<typename Iterator>
class IteratorRange {
 public:
  IteratorRange(Iterator begin, Iterator end)
      : first_(begin), last_(end), size_(distance(first_, last_)) {
  }

  [[nodiscard]]
  Iterator begin() const {
    return first_;
  }

  [[nodiscard]]
  Iterator end() const {
    return last_;
  }

  [[nodiscard]]
  size_t size() const {
    return size_;
  }

 private:
  Iterator first_, last_;
  size_t   size_;
};

template<typename Iterator>
class Paginator {
 private:
  vector<IteratorRange<Iterator>> pages_;

 public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (size_t left = distance(begin, end); left > 0;) {
      size_t   current_page_size = min(page_size, left);
      Iterator current_page_end  = next(begin, current_page_size);
      pages_.push_back({begin, current_page_end});

      left -= current_page_size;
      begin                      = current_page_end;
    }
  }

  [[nodiscard]]
  auto begin() const {
    return pages_.begin();
  }

  [[nodiscard]]
  auto end() const {
    return pages_.end();
  }

  [[nodiscard]]
  size_t size() const {
    return pages_.size();
  }
};

template<typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}

template<typename ContainerOfVectors>
int64_t CalculateSingleThread(const ContainerOfVectors& matrix) {
  int64_t result = 0;
  for (const auto& row : matrix) {
    for (auto item : row) {
      result += item;
    }
  }
  return result;
}

const size_t kRowForThread = 2000;

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  vector<future<int64_t>> futures;
  for (auto row : Paginate(matrix, kRowForThread)) {
    futures.push_back(async([=] { return CalculateSingleThread(row); }));
  }
  int64_t result = 0;
  for (auto& future : futures) {
    result += future.get();
  }
  return result;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 10, 11, 12},
      {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136)
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}

