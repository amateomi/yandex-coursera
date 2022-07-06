#ifndef INC_03__SIMPLEVECTOR__SIMPLE_VECTOR_H_
#define INC_03__SIMPLEVECTOR__SIMPLE_VECTOR_H_

#include <cstdlib>

template<typename T>
class SimpleVector {
 public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size) : size_{size}, capacity_{size} {
    data_ = new T[capacity_];
  }
  ~SimpleVector() { delete[] data_; }

  T& operator[](size_t index) { return data_[index]; }

  T* begin() { return data_; }
  T* end() { return data_ + size_; }

  [[nodiscard]] size_t Size() const { return size_; }
  [[nodiscard]] size_t Capacity() const { return capacity_; }

  void PushBack(const T& value) {
    if (data_ == nullptr) {
      capacity_ = 1;
      data_     = new T[capacity_];

    } else if (size_ == capacity_) {
      capacity_ *= 2;
      T* new_data_segment = new T[capacity_];

      for (size_t i = 0; i < size_; ++i) {
        new_data_segment[i] = data_[i];
      }

      delete[] data_;
      data_ = new_data_segment;
    }
    data_[size_] = value;
    ++size_;
  }

 private:
  T* data_ = nullptr;
  size_t size_     = 0;
  size_t capacity_ = 0;
};

#endif //INC_03__SIMPLEVECTOR__SIMPLE_VECTOR_H_
