#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Person {
 public:
  // Строки не передаются по ссылке намерено, вместо этого используется функция
  // move(). В некоторых ситуациях она позволяет избежать излишнего копирования.
  explicit Person(string name, string type = "Person")
      : type_(move(type)),
        name_(move(name)) {}

  virtual void Walk(const string& destination) const {
    PrintAction("walks to", destination);
  }

  // [[nodiscard]] означает, что НЕЛЬЗЯ вызвать этот метод не использовав
  // возвращаемое функцией значение.
  [[nodiscard]]
  string Name() const { return name_; }
  [[nodiscard]]
  string Type() const { return type_; }

 protected:
  // Все классы выводили почти однотипные фразы, я решил обобщить их, таким
  // образом уменьшив повторения кода.
  void PrintAction(const string& action, const string& detail = "") const {
    cout << type_ << ": " << name_ << " " << action;
    if (!detail.empty()) {
      cout << ": " << detail;
    }
    cout << endl;
  }

  const string type_;
  string name_;
};

class Student : public Person {
 public:
  Student(string name, string favourite_song)
      : Person(move(name), "Student"),
        favourite_song_(move(favourite_song)) {}

  void Learn() const { PrintAction("learns"); }

  void Walk(const string& destination) const override {
    // Студент во время прогулки поет свою любимую песню,
    // по этому пришлось переопределить для него этот метод
    Person::Walk(destination);
    SingSong();
  }

  void SingSong() const { PrintAction("sings a song", favourite_song_); }

 private:
  string favourite_song_;
};

class Teacher : public Person {
 public:
  Teacher(string name, string subject)
      : Person(move(name), "Teacher"),
        subject_(move(subject)) {}

  void Teach() const { PrintAction("teaches", subject_); }

  // Teacher имеет метод Walk(), т.к. наследует его от класса Person

 private:
  string subject_;
};

class Policeman : public Person {
 public:
  explicit Policeman(string name)
      : Person(move(name), "Policeman") {}

  void Check(const Person& p) const {
    PrintAction("checks " + p.Type() + ". " + p.Type() + "'s name is",
                p.Name());
  }

  // Policeman имеет метод Walk(), т.к. наследует его от класса Person

};

void VisitPlaces(const Person& person, const vector<string>& places) {
  for (const auto& p : places) {
    person.Walk(p);
  }
}

int main() {
  Teacher t("Jim", "Math");
  Student s("Ann", "We will rock you");
  Policeman p("Bob");

  VisitPlaces(t, {"Moscow", "London"});
  p.Check(s);
  VisitPlaces(s, {"Moscow", "London"});
}