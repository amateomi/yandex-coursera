/*
 * Определите до конца тела классов, соблюдая следующие требования:
 * - Класс Dog должен являться наследником класса Animal.
 * - Конструктор класса Dog должен принимать параметр типа string и
 *   инициализировать им поле Name в классе Animal.
 */
#include <iostream>

using namespace std;

class Animal {
 public:
  explicit Animal(string name)
      : Name(move(name)) {}

  const string Name;
};

class Dog : public Animal {
 public:
  explicit Dog(const string& name)
      : Animal(name) {}

  void Bark() {
    cout << Name << " barks: woof!" << endl;
  }
};
