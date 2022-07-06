/*
 * Вам даны задача и её решение — верное, но не удовлетворяющее заданным
 * ограничениям на время работы. Переработайте это решение и сдайте в систему.
 *
 * Условие
 * Разработайте систему стимулирования чтения электронных книг. Для простоты
 * будем считать, что книга всего одна, но её одновременно читают много людей.
 * Необходимо следить за прогрессом чтения у всех пользователей и выводить
 * мотивирующие уведомления. А именно, ваша программа должна обрабатывать
 * следующие события:
 * - READ user page — сохранить факт того, что пользователь под номером user
 *   дочитал книгу до страницы page. Если ранее такой пользователь не
 *   встречался, необходимо его добавить. Гарантируется, что в рамках одного
 *   пользователя номера страниц в соответствующих ему событиях возрастают.
 * - CHEER user — сообщить пользователю user, какая доля существующих
 *   пользователей (не считая его самого) прочитала меньшую часть книги, чем он.
 *   Если этот пользователь на данный момент единственный, доля считается равной
 *   1. Если для данного пользователя пока не было ни одного события READ, доля
 *   считается равной 0, а сам пользователь не учитывается при вычислении долей
 *   для других пользователей до тех пор, пока для него не случится событие READ
 *
 * Формат входных данных
 * В первой строке вводится количество запросов Q — натуральное число, не
 * превосходящее 10^6. В следующих Q строках в соответствии с описанным выше
 * форматом вводятся запросы. Гарантируется, что все вводимые числа целые и
 * положительные, при этом номера пользователей не превосходят 10^5, а номера
 * страниц не превосходят 1000.
 *
 * Формат выходных данных
 * Для каждого запроса CHEER user выведите единственное вещественное число от 0
 * до 1 — долю пользователей, прочитавших меньше страниц, чем user. Формат
 * вывода этого числа должен быть в точности таким же, как в опубликованном ниже
 * медленном решении.
 *
 * Ограничения
 * 4 секунды на выполнение всех запросов. Все описанные в условии гарантии
 * действительно справедливы для всех тестов, на которых будет запускаться ваша
 * программа. Проверять корректность тестов не нужно.
 */
#include <numeric>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class ReadingManager {
  struct PersonInfo {
    int person_before;
    int curr_reading;
  };
 public:
  ReadingManager() : page_for_user_(max_user_count_ + 1, 0),
                     users_for_page_(max_page_count_ + 1, {0, 0}),
                     user_count_(0) {}
  void Read(int user_id, int page_count) {
    int curr_page = page_for_user_[user_id];
    if (curr_page != 0) {
      users_for_page_[curr_page].curr_reading -= 1;
      user_count_--;
    }
    users_for_page_[page_count].curr_reading += 1;
    page_for_user_[user_id] = page_count;
    user_count_++;
    UpdateData();
  }

  [[nodiscard]]
  double Cheer(int user_id) const {
    if (page_for_user_[user_id] == 0) {
      return 0;
    }
    if (user_count_ == 1) {
      return 1;
    }
    const int page_count = page_for_user_[user_id];
    int       count      = users_for_page_[page_count].person_before;
    if (count == user_count_) {
      return 0;
    }
    return (count) * 1.0 / static_cast<double>(user_count_ - 1);
  }
 private:
  static const int max_user_count_ = 100'000;
  static const int max_page_count_ = 1'000;

  void UpdateData() {
    int      last_index = 0;
    for (int i          = 1; i < max_page_count_ + 1; ++i) {
      if (users_for_page_[i].curr_reading) {
        users_for_page_[i].person_before = users_for_page_[last_index].curr_reading +
            users_for_page_[last_index].person_before;
        last_index = i;
      }
    }
  }

  std::vector<PersonInfo> users_for_page_;

  std::vector<int> page_for_user_;
  size_t           user_count_;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }
}
