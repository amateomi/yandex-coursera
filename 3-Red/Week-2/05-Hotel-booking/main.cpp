/*
 * Условие
 * Разработайте систему бронирования отелей, позволяющую бронировать номера
 * клиентами и контролировать спрос владельцами отелей.
 * Пусть система работает с некоторым набором событий, происходящий в некоторые
 * моменты времени time.
 * Пусть подобные моменты времени time в системе измеряются в секундах,
 * отсчитываемых от некоторого начального момента времени time = 0. Более того,
 * пусть указанная система отсчета времени является общей и единой для всех
 * определяемых далее в условии задачи событий.
 * Наконец, пусть time — время последнего события бронирования BOOK
 * (см. ниже) в системе бронирования отелей относительно всех имеющихся в
 * системе отелей.
 * Тогда Ваша программа должна обрабатывать следующие события:
 * - BOOK time hotel_name client_id room_count — забронировать клиентом
 *   client_id room_count номеров в отеле hotel_name в момент времени time.
 * - CLIENTS hotel_name — вывести количество различных клиентов, бронировавших
 *   номера в отеле hotel_name за последние сутки относительно последнего
 *   события бронирования в системе: time − 86400 < time ⩽ time,
 *   где 86400 — количество секунд в сутках. Обратите внимание, бронирование с
 *   временной меткой time − 86400 учитываться не должно.
 * - ROOMS hotel_name — вывести количество номеров, забронированных в отеле
 *   hotel_name за последние сутки относительно последнего события бронирования
 *   в системе. Работа команды определяется образом, аналогичным определению
 *   работы команды CLIENTS.
 *
 * Формат входных данных
 * В первой строке вводится количество запросов Q — натуральное число, не
 * превосходящее 10^5. В следующих Q строках в соответствии с описанным выше
 * форматом вводятся запросы. Гарантируется, что:
 * - time — целое число в диапазоне от −10^18 до 10^18 и не убывает от события к
 *   событию.
 * - hotel_name — строка из латинских букв и цифр, имеющая длину не более 12
 *   символов.
 * - client_id — натуральное число, не превосходящее 10^9.
 * - room_count — целое положительное число, не превосходящее 1000.
 *
 * Формат выходных данных
 * Для каждого запроса CLIENTS и ROOMS выведите единственное целое число — ответ
 * на запрос. Если указанный в запросе отель пока не имеет ни одного
 * бронирования, выведите 0.
 *
 * Ограничения
 * 1 секунда на выполнение всех запросов. Все описанные в условии гарантии
 * действительно справедливы для всех тестов, на которых будет запускаться ваша
 * программа. Проверять корректность тестов не нужно.
 */
#include <cinttypes>

#include <numeric>
#include <iostream>
#include <list>
#include <map>
#include <set>

using namespace std;

struct Record {
  Record() = default;
  int64_t     time        = 0;
  std::string name_hotel;
  int32_t     client_id   = 0;
  int32_t     rooms_count = 0;
};

class Hotel {
 public:
  Hotel() : clients_(), rooms_(0) {}

  void BookClient(int32_t client_id, int32_t rooms) {
    rooms_ += rooms;
    clients_[client_id].push_back(rooms);
  }

  bool Remove(int32_t client_id) {
    auto find = clients_.find(client_id);
    if (find == clients_.end()) {
      return false;
    }
    if (!find->second.empty()) {
      rooms_ -= find->second.front();
      find->second.pop_front();
    }
    if (find->second.empty()) {
      clients_.erase(find);
    }
    return true;
  }

  [[nodiscard]] int32_t GetClients() const {
    return static_cast<int32_t>(clients_.size());
  }

  [[nodiscard]] int32_t GetRooms() const {
    return rooms_;
  }

 private:
  std::map<int32_t, std::list<int32_t>> clients_;
  int32_t                               rooms_;
};

class BookingManager {
 public:
  BookingManager() = default;
  void Book(int64_t time, const std::string& hotel_name, int32_t client_id, int32_t room_count) {
    Record r = {time, hotel_name, client_id, room_count};
    records_.push_back(r);
    hotels_[hotel_name].BookClient(client_id, room_count);
    UpdateRecords();
  }

  [[nodiscard]]
  int32_t Clients(const std::string& hotel_name) const {
    auto find = hotels_.find(hotel_name);
    return (find == hotels_.end()) ? 0 : find->second.GetClients();
  }

  int32_t Rooms(const std::string& hotel_name) {
    auto find = hotels_.find(hotel_name);
    return (find == hotels_.end()) ? 0 : find->second.GetRooms();
  }

 private:
  static const int             period_time_ = 86400;
  std::list<Record>            records_;
  std::map<std::string, Hotel> hotels_;

  void UpdateRecords() {
    for (auto record = records_.begin(); record != records_.end();) {
      if (!CheckRecordTime(static_cast<int32_t>(record->time))) {
        auto for_delete = records_.front();
        hotels_[for_delete.name_hotel].Remove(for_delete.client_id);
        record = records_.erase(records_.begin());
      } else {
        break;
      }
    }
  }

  bool CheckRecordTime(int32_t time) {
    auto current_time = static_cast<int32_t>(records_.back().time);
    return ((current_time - period_time_) < time) && (time <= current_time);
  }

};

int main() {
  std::cin.tie(nullptr);
  std::ios::sync_with_stdio(false);

  BookingManager manager;

  int query_count;
  std::cin >> query_count;

  for (uint32_t query_id = 0; query_id < query_count; ++query_id) {
    std::string query_type;
    std::cin >> query_type;
    if (query_type == "BOOK") {
      int64_t     time, client_id, room_count;
      std::string hotel_name;
      std::cin >> time >> hotel_name >> client_id >> room_count;
      manager.Book(time, hotel_name, static_cast<int32_t>(client_id),
                   static_cast<int32_t>(room_count));
    } else if (query_type == "CLIENTS") {
      std::string hotel_name;
      std::cin >> hotel_name;
      std::cout << manager.Clients(hotel_name) << "\n";
    } else if (query_type == "ROOMS") {
      std::string hotel_name;
      std::cin >> hotel_name;
      std::cout << manager.Rooms(hotel_name) << "\n";
    }
  }
}