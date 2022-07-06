/*
 * В заготовке решения задачи «Шаблон Synchronized» мы уже слегка коснулись идеи
 * о том, что уменьшение размера критической секции позволяет повысить скорость
 * работы многопоточной программы. В этой задаче мы разовьём её больше.
 *
 * Давайте представим, что у нас есть map, к которому обращаются несколько
 * потоков. Чтобы синхронизировать доступ к нему, мы можем каждое обращение к
 * этому map'у защитить мьютексом (например, завернув наш map в шаблон
 * Synchronized). Теперь давайте представим, что у нас есть
 * Synchronized<map<int, int>>, в котором хранятся все ключи от 1 до 10000.
 * Интуитивно кажется, что когда из одного потока мы обращаемся к ключу 10, а из
 * другого — например, к ключу 6712, то нет смысла защищать эти обращения одним
 * и тем же мьютексом. Это отдельные области памяти, а внутреннюю структуру
 * словаря мы никак не изменяем. При этом, если мы будем обращаться к ключу 6712
 * одновременно из нескольких потоков, то синхронизация, несомненно, понадобится.
 *
 * Отсюда возникает идея — разбить наш словарь на нескольких подсловарей с
 * непересекающимся набором ключей и защитить каждый из них отдельным мьютексом.
 * Тогда при обращении разных потоков к разным ключам они нечасто будут попадать
 * в один и тот же подсловарь, а значит, смогут параллельно его обрабатывать.
 * Эту идею вам предстоит реализовать в этой задаче. Вам надо написать шаблон
 * класса ConcurrentMap вот с таким интерфейсом:
 * - static_assert в начале класса говорит, что в данной задаче предполагается,
 *   что ключами ConcurrentMap'а могут быть только целые числа.
 * - Конструктор класса ConcurrentMap<K, V> принимает количество подсловарей, на
 *   которые надо разбить всё пространство ключей.
 * - operator[] должен вести себя так же, как аналогичный оператор у map — если
 *   ключ key присутствует в словаре, он должен возвращать объект класса Access,
 *   содержащий ссылку на соответствующее ему значение; если же key отсутствует
 *   в словаре, в него надо добавить пару (key, V()) и вернуть объект класса
 *   Access, содержащий ссылку на только что добавленное значение.
 * - Структура Access, должна вести себя так же, как и в шаблоне Synchronized, —
 *   предоставлять ссылку на значение словаря и обеспечивать синхронизацию
 *   доступа к нему.
 * - Метод BuildOrdinaryMap должен сливать вместе части словаря и возвращать
 *   весь словарь целиком. При этом он должен быть потокобезопасным, то есть
 *   корректно работать, когда другие потоки выполняют операции с ConcurrentMap.
 */
#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <future>
#include <map>
#include <vector>
#include <deque>
#include <string>
#include <random>

using namespace std;

template<typename K, typename V>
class ConcurrentMap {
 public:
  static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

  struct Access {
    lock_guard<mutex> guard;
    V& ref_to_value;
  };

  explicit ConcurrentMap(size_t bucket_count)
      : total_buckets_(bucket_count) {
    buckets_.resize(total_buckets_);
  }

  Access operator[](const K& key) {
    size_t index = key % total_buckets_;
    auto& bucket = buckets_[index];
    return {lock_guard(bucket.sub_mutex), bucket.sub_map[key]};
  }

  map<K, V> BuildOrdinaryMap() {
    map<K, V> ordinary_map;
    for (auto& bucket : buckets_) {
      for (const auto&[key, value] : bucket.sub_map) {
        ordinary_map[key] = operator[](key).ref_to_value;
      }
    }
    return ordinary_map;
  }

 private:
  const size_t  total_buckets_;
  struct Bucket {
    map<K, V> sub_map;
    mutex     sub_mutex;
  };
  deque<Bucket> buckets_;
};

void RunConcurrentUpdates(
    ConcurrentMap<int, int>& cm, size_t thread_count, int key_count) {
  auto kernel            = [&cm, key_count](int seed) {
    vector<int> updates(key_count);
    iota(begin(updates), end(updates), -key_count / 2);
    shuffle(begin(updates), end(updates), default_random_engine(seed));

    for (int i = 0; i < 2; ++i) {
      for (auto key : updates) {
        cm[key].ref_to_value++;
      }
    }
  };

  vector<future<void>> futures;
  for (size_t          i = 0; i < thread_count; ++i) {
    futures.push_back(async(kernel, i));
  }
}

void TestConcurrentUpdate() {
  const size_t thread_count = 3;
  const size_t key_count    = 50000;

  ConcurrentMap<int, int> cm(thread_count);
  RunConcurrentUpdates(cm, thread_count, key_count);

  const auto result = cm.BuildOrdinaryMap();
  ASSERT_EQUAL(result.size(), key_count)
  for (auto&[k, v] : result) {
    AssertEqual(v, 6, "Key = " + to_string(k));
  }
}

void TestReadAndWrite() {
  ConcurrentMap<size_t, string> cm(5);

  auto updater = [&cm] {
    for (size_t i = 0; i < 50000; ++i) {
      cm[i].ref_to_value += 'a';
    }
  };
  auto reader  = [&cm] {
    vector<string> result(50000);
    for (size_t    i = 0; i < result.size(); ++i) {
      result[i] = cm[i].ref_to_value;
    }
    return result;
  };

  auto u_1 = async(updater);
  auto r_1 = async(reader);
  auto u_2 = async(updater);
  auto r_2 = async(reader);

  u_1.get();
  u_2.get();

  for (auto f : {&r_1, &r_2}) {
    auto result = f->get();
    ASSERT(all_of(result.begin(), result.end(), [](const string& s) {
      return s.empty() || s == "a" || s == "aa";
    }))
  }
}

void TestSpeedup() {
  {
    ConcurrentMap<int, int> single_lock(1);

    LOG_DURATION("Single lock")
    RunConcurrentUpdates(single_lock, 4, 50000);
  }
  {
    ConcurrentMap<int, int> many_locks(100);

    LOG_DURATION("100 locks")
    RunConcurrentUpdates(many_locks, 4, 50000);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConcurrentUpdate);
  RUN_TEST(tr, TestReadAndWrite);
  RUN_TEST(tr, TestSpeedup);
}

