/*
 * Студента попросили написать класс Learner, помогающий изучать иностранный
 * язык. В публичном интерфейсе класса должны быть две функции:
 *
 * int Learn(const vector<string>& words);
 * vector<string> KnownWords();
 *
 * Функция Learn должна получать порцию слов, "запоминать" их и возвращать
 * количество различных новых слов. Функция KnownWords должна возвращать
 * отсортированный по алфавиту список всех выученных слов. В списке не должно
 * быть повторов.
 *
 * Студент написал следующее решение этой задачи, однако оно почему-то работает
 * очень медленно. Вам надо его ускорить.
 *
 * Вам дан файл learner.cpp с медленным решением задачи. Не меняя публичный
 * интерфейс класса Learner, найдите в нём узкие места, исправьте их и сдайте
 * переделанный класс в тестирующую систему.
 */
#include <algorithm>
#include <string>
#include <set>

using namespace std;

class Learner {
 public:
  int Learn(const vector<string>& words) {
    size_t old_dict_size = dict.size();
    for (const auto& word : words) {
      dict.insert(word);
    }
    return static_cast<int>(dict.size() - old_dict_size);
  }

  vector<string> KnownWords() {
    return {dict.begin(), dict.end()};
  }

 private:
  set<string> dict;
};

