/*
 * Рассмотрим упрощённый текстовый редактор, поддерживающий следующий набор команд:
 * - Перемещение курсора влево (Left) и вправо (Right) на одну позицию.
 * - Ввод символа в текущую позицию курсора (Insert).
 * - Копирование фрагмента текста, начинающегося в текущей позиции курсора, в
 *   буфер обмена (Copy).
 * - Вырезание фрагмента текста аналогично копированию с последующим удалением
 *   скопированных символов из текста (Cut).
 * - Вставка содержимого буфера обмена в текущую позицию курсора (Paste).
 *
 * Реализация класса Editor должна обрабатывать 10^6 запросов не более чем за 1
 * секунду. При этом гарантируется, что:
 * - длина текста никогда не превышает 10^6 символов;
 * - методы Copy() и Cut() суммарно копируют/вырезают не более 10^6 символов;
 * - метод GetText() вызывается один раз в каждом из тестов.
 */
#include "test_runner.h"

#include <string>
#include <list>

using namespace std;

class Editor {
 public:
  Editor() : cursor_(text_.end()) {}

  void Left() {
    if (cursor_ != text_.begin() &&
        *prev(cursor_)) {
      --cursor_;
    }
  }
  void Right() {
    if (cursor_ != text_.end() &&
        *next(cursor_)) {
      ++cursor_;
    }
  }

  void Insert(char token) {
    text_.insert(cursor_, token);
  }

  void Cut(size_t tokens = 1) {
    auto cut_end = UpdateBuffer(tokens);
    text_.erase(cursor_, cut_end);
    cursor_ = cut_end;
  }
  void Copy(size_t tokens = 1) {
    UpdateBuffer(tokens);
  }

  void Paste() {
    if (!buffer_.empty()) {
      text_.insert(cursor_, buffer_.begin(), buffer_.end());
    }
  }

  [[nodiscard]]
  string GetText() const {
    return {text_.begin(), text_.end()};
  }

 private:
  using Text = list<char>;

  Text::const_iterator UpdateBuffer(size_t tokens) {
    auto text_part_end = cursor_;

    while (text_part_end != text_.end() && tokens != 0) {
      ++text_part_end;
      --tokens;
    }
    buffer_.assign(cursor_, text_part_end);
    return text_part_end;
  }

  Text                 text_;
  Text::const_iterator cursor_;
  Text                 buffer_;
};

void TypeText(Editor& editor, const string& text) {
  for (char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len       = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for (size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for (size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello")
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint")
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for (char    c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse")
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "")

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "")
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example")
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
}