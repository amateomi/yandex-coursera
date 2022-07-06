/*
 * Вам дана функция main, которая считывает из стандартного ввода команды по
 * работе с набором геометрических фигур.
 *
 * Есть два вида команд:
 * - ADD — добавить фигуру в набор;
 * - PRINT — для каждой фигуры в наборе распечатать название, периметр и площадь.
 *
 * Программа поддерживает три вида фигур: прямоугольник, треугольник и круг.
 * Их добавление описывается так:
 * - ADD RECT width height —  добавить прямоугольник с размерами width и height
 *   (например, ADD RECT 2 3).
 * - ADD TRIANGLE a b c —  добавить треугольник со сторонами a, b и c (например,
 *   ADD TRIANGLE 3 4 5).
 * - ADD CIRCLE r —  добавить круг радиуса r (например, ADD CIRCLE 5).
 *
 * Не меняя функцию main, реализуйте недостающие функции и классы:
 * - базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area;
 * - классы Triangle, Rect и Circle, которые являются наследниками класса Figure
 *   и переопределяют его виртуальные методы;
 * - функцию CreateFigure, которая в зависимости от содержимого входного потока
 *   создаёт shared_ptr<Rect>, shared_ptr<Triangle> или shared_ptr<Circle>.
 *
 * Гарантируется, что размеры всех фигур — это натуральные числа не больше
 * 1000. В качестве значения PI используйте 3,14.
 */
#include <cmath>

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

using namespace std;

class Figure {
 public:
  virtual string Name() = 0;
  [[nodiscard]] double Perimeter() const { return perimeter_; }
  [[nodiscard]] double Area() const { return area_; }

 protected:
  double perimeter_{};
  double area_{};
};

class Triangle : public Figure {
 public:
  Triangle(int a, int b, int c) {
    perimeter_ = a + b + c;
    double p = perimeter_ / 2;
    area_ = sqrt(p * (p - a) * (p - b) * (p - c));
  }
  string Name() override { return "TRIANGLE"; }
};

class Rect : public Figure {
 public:
  Rect(int w, int h) {
    perimeter_ = (w + h) * 2;
    area_ = w * h;
  }
  string Name() override { return "RECT"; }
};

constexpr double Pi = 3.14;

class Circle : public Figure {
 public:
  explicit Circle(int r) {
    perimeter_ = 2 * Pi * r;
    area_ = Pi * r * r;
  }
  string Name() override { return "CIRCLE"; }
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
  string figure_type;
  is >> figure_type;
  if (figure_type == "TRIANGLE") {
    int a, b, c;
    is >> a >> b >> c;
    return make_shared<Triangle>(a, b, c);
  } else if (figure_type == "RECT") {
    int w, h;
    is >> w >> h;
    return make_shared<Rect>(w, h);
  } else if (figure_type == "CIRCLE") {
    int r;
    is >> r;
    return make_shared<Circle>(r);
  }
  throw runtime_error("Invalid figure type");
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line);) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
}
