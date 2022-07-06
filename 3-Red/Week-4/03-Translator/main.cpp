/*
 * Разработайте класс Translator, позволяющий сохранять двуязычные пары слов и
 * затем переводить слова с одного языка на другой с использованием уже
 * добавленных пар.
 *
 * Объект t типа Translator должен допускать следующие действия:
 * - Создание с помощью конструктора по умолчанию. В этом случае база переводов
 *   пуста.
 * - Добавление двуязычной пары: t.Add(source, target). После такого вызова
 *   считается, что слово source на языке 1 соответствует слову target на языке
 *   2. Переданные в метод Add строки могут быть уничтожены раньше объекта t.
 * - Перевод с языка 1 на язык 2: t.TranslateForward(source). Если ранее уже был
 *   вызов t.Add(source_copy, target)для некоторой строки target и строки
 *   source_copy, равной source (или являющейся ей), нужно вернуть target. Если
 *   такого вызова не было, нужно вернуть пустую строку. Если таких вызовов было
 *   несколько, нужно вернуть target для последнего из них.
 * - Перевод с языка 2 на язык 1: t.TranslateBackward(target). Если ранее уже
 *   был вызов t.Add(source, target_copy)для некоторой строки source и строки
 *   target_copy, равной target (или являющейся ей), нужно вернуть source. Если
 *   такого вызова не было, нужно вернуть пустую строку. Если таких вызовов было
 *   несколько, нужно вернуть source для последнего из них.
 *
 * Ограничения
 * Каждая строка должна храниться в экземпляре класса Translator не более одного
 * раза. При нарушении этого ограничения вы получите ошибку «Memory limit
 * exceeded».
 */
#include "test_runner.h"

#include <string>
#include <map>
#include <deque>

using namespace std;

class Translator {
 public:
  void Add(string_view source, string_view target) {
    const string_view source_view = GetClonedView(source);
    const string_view target_view = GetClonedView(target);
    forward_dict_[source_view]  = target_view;
    backward_dict_[target_view] = source_view;
  }
  [[nodiscard]]
  string_view TranslateForward(string_view source) const {
    return Translate(forward_dict_, source);
  }
  [[nodiscard]]
  string_view TranslateBackward(string_view target) const {
    return Translate(backward_dict_, target);
  }

 private:
  string_view GetClonedView(string_view s) {
    for (const auto* map_ptr : {&forward_dict_, &backward_dict_}) {
      const auto it = map_ptr->find(s);
      if (it != map_ptr->end()) {
        return it->first;
      }
    }
    return data_.emplace_back(s);
  }

  static string_view Translate(const map<string_view, string_view>& dict, string_view s) {
    if (const auto it = dict.find(s); it != dict.end()) {
      return it->second;
    } else {
      return {};
    }
  }

  map<string_view, string_view> forward_dict_;
  map<string_view, string_view> backward_dict_;
  deque<string>                 data_;
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window")
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol")
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "")
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}

