/*
 * Дан вектор токенов. Напишите функцию, разбивающую токены на предложения.
 *
 * Token — шаблонный тип, про который известно лишь то, что он имеет константный
 * метод IsEndSentencePunctuation, возвращающий true, если токен является знаком
 * пунктуации, заканчивающим предложение, и false в противном случае. Объекты
 * этого типа запрещено копировать. При наличии копирования этих объектов вы
 * получите ошибку компиляции.
 *
 * Предложением считается последовательность токенов, заканчивающаяся подряд
 * идущими токенами, являющимися знаками пунктуации конца предложения. Иными
 * словами, любое предложение должно состоять из двух частей:
 * - токены, для которых IsEndSentencePunctuation возвращает false (такие токены
 *   обязаны присутствовать в предложении за исключением, возможно, первого
 *   предложения);
 * - токены, для которых IsEndSentencePunctuation возвращает true (такие токены
 *   обязаны присутствовать в предложении за исключением, возможно, последнего
 *   предложения).
 */
#include "test_runner.h"

#include <vector>

using namespace std;

template<typename Token>
using Sentence = vector<Token>;

template<typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
  vector<Sentence<Token>> result;
  Sentence<Token>         sentence;

  bool is_prev_sentence_end = false;
  bool is_sentence_end      = false;

  for (Token& token : tokens) {
    is_sentence_end = token.IsEndSentencePunctuation();
    if (!is_sentence_end && is_prev_sentence_end) {
      result.push_back(move(sentence));
      sentence.clear();
    }
    sentence.push_back(move(token));
    is_prev_sentence_end = is_sentence_end;
  }
  if (!sentence.empty()) {
    result.push_back(move(sentence));
  }
  return result;
}

struct TestToken {
  string data;
  bool   is_end_sentence_punctuation = false;

  [[nodiscard]] bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

void TestSplitting() {
  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
      vector<Sentence<TestToken>>({
                                      {{"Split"}, {"into"}, {"sentences"}, {"!"}}
                                  })
  )

  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
      vector<Sentence<TestToken>>({
                                      {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
                                  })
  )

  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"},
                                            {"copies"}, {".", true}})),
      vector<Sentence<TestToken>>({
                                      {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
                                      {{"Without"}, {"copies"}, {".", true}},
                                  })
  )
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
}

