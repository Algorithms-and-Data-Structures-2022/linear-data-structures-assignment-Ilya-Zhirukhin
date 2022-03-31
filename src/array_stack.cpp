#include "assignment/array_stack.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  ArrayStack::ArrayStack(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость стека
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    capacity_ = capacity;
    data_ = new int[capacity]{0};

    // Write your code here ...
  }

  ArrayStack::~ArrayStack() {
    // Write your code here ...
  }

  void ArrayStack::Push(int value) {
    if (size_ == capacity_) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
      data_[size_] = value;
      size_++;
      return;
    }
    data_[size_] = value;
    size_++;
  }


  bool ArrayStack::Pop() {
    if (size_ > 0){
      int* newarr = new int[size_ - 1];
      for (int i = 0; i < size_ - 1; i++) {
        newarr[i] = data_[i];
      }

      delete[] data_;
      data_ = newarr;
      size_ = size_ - 1;
      return true;

    }
    // Write your code here ...
    return false;
  }

  void ArrayStack::Clear() {
    int* newarr = new int[0];
    delete[] data_;
    data_ = newarr;
    size_ = 0;
    // Write your code here ...
  }

  std::optional<int> ArrayStack::Peek() const {
    if (size_ > 0){
      return data_[size_- 1];

    }
    // Write your code here ...
    return std::nullopt;
  }

  bool ArrayStack::IsEmpty() const {
    return size_ == 0;
  }

  int ArrayStack::size() const {
    // Write your code here ...
    return size_;
  }

  int ArrayStack::capacity() const {
    // Write your code here ...
    return capacity_;
  }

  bool ArrayStack::Resize(int new_capacity) {
    // Write your code here ...
    if(new_capacity > capacity_){
      int* arr = new int[new_capacity];
      int cap = capacity_;
      std::copy(data_, data_ + capacity_, arr);
      delete[] data_;
      data_ = arr;
      capacity_ = new_capacity;
      if (capacity_ > cap) {
        return true;
      }
      return false;
    }
    return false;
  }


  // ДЛЯ ТЕСТИРОВАНИЯ
  ArrayStack::ArrayStack(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> ArrayStack::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment
