#ifndef INC_03__ASSIGNMENT_FOR_SIMPLEVECTOR__SIMPLE_VECTOR_H_
#define INC_03__ASSIGNMENT_FOR_SIMPLEVECTOR__SIMPLE_VECTOR_H_

#include <algorithm>
#include <cstdlib>

using namespace std;

template<typename T>
class SimpleVector {
 public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size)
      : data_{new T[size]},
        size_{size},
        capacity_{size} {}
  SimpleVector(const SimpleVector& other)
      : data_{new T[other.capacity_]},
        size_{other.size_},
        capacity_{other.capacity_} {
    copy_n(other.begin(), other.size_, begin());
  }
  ~SimpleVector() { delete[] data_; }

  void operator=(const SimpleVector<T>& other) {
    if (other.size_ <= capacity_) {
      copy_n(other.begin(), other.size_, begin());
      size_ = other.size_;
    } else {
      delete[] data_;
      data_ = new T[other.size_];

      copy_n(other.begin(), other.size_, begin());
      size_     = other.size_;
      capacity_ = other.capacity_;
    }
  }

  T& operator[](size_t index) { return data_[index]; }

  T* begin() { return data_; }
  T* end() { return data_ + size_; }

  const T* begin() const { return data_; }
  const T* end() const { return data_ + size_; }

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

#endif //INC_03__ASSIGNMENT_FOR_SIMPLEVECTOR__SIMPLE_VECTOR_H_
