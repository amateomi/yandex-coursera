/*
 * Вам дан заголовочный файл phone_number.h, содержащий объявление класса
 * PhoneNumber. При этом в комментариях описано поведение, которое ожидается от
 * реализации этого класса.
 */

#include "test_framework.h"
#include "phone_number.h"

void TestPhoneNumber() {
  string invalid;
  // Correct cases
  try {
    vector<string> phone_numbers{"+7-495-111-22-33",
                                 "+7-495-1112233",
                                 "+323-22-460002",
                                 "+1-2-coursera-cpp"};
    for (const auto& number : phone_numbers) {
      invalid = number;
      PhoneNumber phone_number(number);
    }
  } catch (invalid_argument& err) {
    Assert(false, string(err.what()) + " in " + invalid);
  }

  {
    // Incorrect cases
    vector<string> phone_numbers{"1-2-333",
                                 "+7-1233"};
    for (const auto& number : phone_numbers) {
      try {
        PhoneNumber phone_number(number);
        Assert(false, "invalid " + number + " is created");
      } catch (invalid_argument&) {}
    }
  }
}

int main() {
  TestRunner runner;
  runner.RunTest(TestPhoneNumber, "TestPhoneNumber");
}
