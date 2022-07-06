#ifndef INC_02__STACKVECTOR__STACK_VECTOR_H_
#define INC_02__STACKVECTOR__STACK_VECTOR_H_

#include <array>
#include <stdexcept>

using namespace std;

template<typename T, size_t N>
class StackVector {
 public:
  explicit StackVector(size_t a_size = 0)
      : size_(a_size) {
    if (a_size > N) {
      throw invalid_argument("");
    }
  }

  T& operator[](size_t index) { return data_[index]; }
  const T& operator[](size_t index) const { return data_[index]; }

  T* begin() { return data_.data(); }
  T* end() { return data_.data() + size_; }
  const T* begin() const { return data_.data(); }
  const T* end() const { return data_.data() + size_; }

  [[nodiscard]] size_t Size() const { return size_; }
  [[nodiscard]] size_t Capacity() const { return N; }

  void PushBack(const T& value) {
    if (size_ == N) {
      throw overflow_error("");
    }
    data_[size_] = value;
    ++size_;
  }
  T PopBack() {
    if (size_ == 0) {
      throw underflow_error("");
    }
    --size_;
    return data_[size_];
  }

 private:
  array<T, N> data_;
  size_t      size_;
};

#endif //INC_02__STACKVECTOR__STACK_VECTOR_H_
