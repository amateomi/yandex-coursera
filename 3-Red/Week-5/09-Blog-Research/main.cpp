/*
 * Крупная IT-компания Янгл проводит исследование упоминаемости своего бренда в
 * блогах и социальных сетях. Аналитики компании уже выгрузили интересующие их
 * публикации и сформировали набор ключевых слов. Их интересует, сколько раз
 * каждое ключевое слово входит в набор публикаций.
 *
 * Помогите им это сделать — напишите функцию
 * Stats ExploreKeyWords(const set<string>& key_words, istream& input).
 * Её параметры:
 * - key_words — множество ключевых слов
 * - input — входной поток, содержащий исследуемые публикации в блогах и соц.
 *   сетях, одна строка — одна публикация.
 *
 * Функция ExploreKeyWords должна возвращать структуру Stats, в которой
 * хранится, сколько раз каждое слово из key_words суммарно встретилось в потоке
 * input.
 *
 * При подсчёте вхождения ключевых слов в текст нужно учитывать только вхождения
 * в виде отдельных слов. Слова друг от друга отделяются одним или несколькими
 * пробелами. В качестве примера допустим, что key_words = {"yangle", "rocks",
 * "sucks", "all"} и у нас есть публикация из соц. сети Switter: "Goondex really
 * sucks, but yangle rocks ! Use yangle". Слово «yangle» входит в неё 2 раза,
 * «rocks» — один раз, а слова «all» и «sucks» — ни разу. Слово «sucks» не
 * входит ни разу, потому что в данном примере оно является префиксом слова
 * «sucks,» (по условию, слова друг от друга отделяются только пробелами).
 * Несмотря на то, что слово «all» является частью слова «really», его вхождение
 * тоже нельзя засчитывать, так как это не отдельное слово.
 * Чтобы уложиться в Time Limit, подумайте, можно ли эту задачу распараллелить.
 */
#include "test_runner.h"

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <future>

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

      begin = current_page_end;
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

struct Stats {
  map<string, int> word_frequences;

  void operator+=(const Stats& other) {
    for (const auto&[key, value] : other.word_frequences) {
      word_frequences[key] += value;
    }
  }
};

Stats ExploreKeyWordsSingleThread(const set<string>& key_words,
                                  const IteratorRange<vector<string>::iterator>& words) {
  Stats result;
  for (const auto& word : words) {
    if (key_words.find(word) != key_words.end()) {
      ++result.word_frequences[word];
    }
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  vector<string> records;
  string         word;
  while (true) {
    input >> word;
    if (!input) {
      break;
    }
    records.push_back(move(word));
  }

  vector<future<Stats>> futures;

  const auto parts = Paginate(records, 6250);
  for (auto& part : parts) {
    futures.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(part)));
  }

  Stats result;
  for (auto& future : futures) {
    result += future.get();
  }
  return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
  const auto             stats    = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
      {"yangle", 6},
      {"rocks", 2},
      {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected)
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
