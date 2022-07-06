#ifndef INC_03__RECTANGLE__RECTANGLE_H_
#define INC_03__RECTANGLE__RECTANGLE_H_

class Rectangle {
 public:
  Rectangle(int width, int height);

  [[nodiscard]]
  int GetArea() const;

  [[nodiscard]]
  int GetPerimeter() const;

  [[nodiscard]]
  int GetWidth() const;
  [[nodiscard]]
  int GetHeight() const;

 private:
  int width_, height_;
};

#endif //INC_03__RECTANGLE__RECTANGLE_H_
