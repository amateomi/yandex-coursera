#include "phone_number.h"

#include <sstream>

PhoneNumber::PhoneNumber(const string& international_number) {
  istringstream ss(international_number);

  if (ss.peek() != '+') {
    throw invalid_argument("delimiter failure");
  }
  ss.ignore();

  getline(ss, country_code_, '-');
  getline(ss, city_code_, '-');
  getline(ss, local_number_);

  if (!ss) {
    throw invalid_argument("ss failure");
  }
}

string PhoneNumber::GetCountryCode() const {
  return country_code_;
}

string PhoneNumber::GetCityCode() const {
  return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
  return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
  return '+' + country_code_ + '-' + city_code_ + '-' + local_number_;
}
