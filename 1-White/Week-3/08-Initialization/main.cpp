/*
 * Определите тип Incognizable, для которого следующий код будет корректен:
 * (смотреть функцию main)
 */

struct Incognizable {
  int first_value = 1;
  int second_value = 2;
};

int main() {
  Incognizable a;
  Incognizable b = {};
  Incognizable c = {0};
  Incognizable d = {0, 1};
}
