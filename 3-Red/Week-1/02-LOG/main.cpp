/*
 * Вам дан класс Logger и макрос LOG.
 * Параметры макроса LOG — объект класса Logger и строковое сообщение, которое
 * должно быть передано в метод Log. В зависимости от настроек объекта класса
 * Logger логируемое сообщение должно предваряться именем файла или номером
 * строки. Смотрите юнит-тесты в заготовке решения для более подробного описания
 * поведения.
 * Реализуйте макрос LOG так, чтобы он добавлял в логируемое сообщение имя файла
 * и номер строки в зависимости от настроек объекта logger.
 */
#include "test_runner.h"
#include <sstream>
#include <string>
using namespace std;

class Logger {
 public:
  explicit Logger(ostream& output_stream)
      : os_(output_stream) {}

  void SetLogLine(bool value) { log_line_ = value; }
  void SetLogFile(bool value) { log_file_ = value; }

  [[nodiscard]] bool GetLogLine() const { return log_line_; }
  [[nodiscard]] bool GetLogFile() const { return log_file_; }

  void Log(const string& message) {
    os_ << message << endl;
  }

 private:
  ostream& os_;
  bool log_line_ = false;
  bool log_file_ = false;
};

#define LOG(logger, message) {                \
          ostringstream os;                   \
          if ((logger).GetLogFile()) {        \
            os << __FILE__;                   \
            if((logger).GetLogLine()) {       \
              os << ":" << __LINE__;          \
            }                                 \
            os << " ";                        \
          } else if ((logger).GetLogLine()) { \
            os << "Line " << __LINE__ << " "; \
          }                                   \
          (logger).Log(os.str() + (message)); \
}

void TestLog() {
#line 1 "logger.cpp"

  ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
}
