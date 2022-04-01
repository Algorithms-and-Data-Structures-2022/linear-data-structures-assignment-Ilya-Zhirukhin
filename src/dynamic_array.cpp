#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    capacity_ = capacity;
    data_ = new int[capacity]{0};
    /*

    for(int i = 0; i < capacity; i++){
      data_[i] = 0;
    }
    */


    // Write your code here ...
  }

  DynamicArray::~DynamicArray() {
    // Write your code here ...
    size_ = 0;
    capacity_ = 0;
    delete[] data_;
    data_ = nullptr;



  }

  void DynamicArray::Add(int value) {

    if(size_ == capacity_){
      Resize(capacity_ + kCapacityGrowthCoefficient);
      data_[size_] = value;
      size_++;
      return;
    }
    data_[size_] = value;
    size_ ++;

    // Write your code here ...
  }

  bool DynamicArray::Insert(int index, int value) {
    // Write your code here ...
    if(index >= 0 && index <= size_) {
        if (size_ < capacity_){
          for (int i = size_; i > index  ; i--) {
            data_[i] = data_[i - 1];
          }
          data_[index] = value;
          size_++;
          return true;
        }
        else if (size_ == capacity_) {
          Resize(capacity_ + kCapacityGrowthCoefficient);
          for (int i = size_; i > index; i--) {
            data_[i] = data_[i - 1];
          }
          data_[index] = value;
          size_++;
          return true;
        }

    }
    return false;

  }

  bool DynamicArray::Set(int index, int new_value) {
    // Write your code here ...
    if(index >= 0 && index < size_){
      data_[index] = new_value;
      return true;
    }

    return false;
  }

  std::optional<int> DynamicArray::Remove(int index) {
    if(index >= 0 && index < size_) {
      int* newarr = new int[size_ - 1];
      for (int i = 0; i < index; i++) {
        newarr[i] = data_[i];
      }
      for (int i = index + 1; i < size_; i++) {
        newarr[i-1] = data_[i];
      }
      int a = data_[index];
      delete[] data_;
      data_ = newarr;
      size_ = size_ - 1;
      return a;
    }

    return std::nullopt;
  }
  void DynamicArray::Clear() {
    int* newarr = new int[0];
    delete[] data_;
    data_ = newarr;
    size_ = 0;
    // Write your code here ...
  }

  std::optional<int> DynamicArray::Get(int index) const {
    // Write your code here ...
    if (index >= 0 && index < size_){
      return data_[index];
    }
    return std::nullopt;
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    // Write your code here ...
    for(int i = 0; i < size_ ;i++){
      if(data_[i] == value) {
        return i;
      }
    }
    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    for(int i = 0; i < size_ ;i++){
      if(data_[i] == value) {
        return true;
      }
    }
    return false;
  }

  bool DynamicArray::IsEmpty() const {
    return size_ == 0;
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
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
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment