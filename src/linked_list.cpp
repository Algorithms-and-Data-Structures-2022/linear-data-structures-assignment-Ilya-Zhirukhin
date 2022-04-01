#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {


    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    if(front_ == nullptr){
      auto* curr_node = new Node(value);
      front_ = curr_node;
      front_ -> value = value;
      back_ = front_;
      size_++;
      return;
    }
    auto* der = new Node(4);
    for(auto* current = front_; der != nullptr;){
      if(current->next == nullptr){
        auto* new_node = new Node(value);
        current->next = new_node;
        back_ = current->next;
        size_++;
        der = nullptr;
      }
      else {
        current = current->next;
      }
    }

    }

    // Write your code here ...


  bool LinkedList::Insert(int index, int value) {

    // index = 0    => вставка в начало списка
    // index = size => вставка в конец списка

    // проверка на выход за границы позиции вставки
    if (index < 0 || index > size_) {
      return false;
    }

    auto* node = new Node(value);

    if (front_ == nullptr) {
      // пустой список: "начальный" и "конечный" узлы одинаковы
      front_ = node;
      back_ = node;

    } else {
      // вставка в "начало" списка
      if (index == 0) {
        node->next = front_;
        front_ = node;

      } else if (index == size_) {
        // вставка в "конец" списка
        back_->next = node;
        back_ = node;

      } else {
        // вставка "внутрь" списка
        auto* prev_node = FindNode(index - 1);

        node->next = prev_node->next;
        prev_node->next = node;
      }
    }

    size_ += 1;

    return true;
  }


  bool LinkedList::Set(int index, int new_value) {
    if(index >= 0 && index < size_){
      int find = 0;
      Node* cur_dd = front_;
      for(Node* current = front_ ; find != index && current -> next != nullptr ; /* */){
        current = current -> next;
        cur_dd = current;
        find++;
      }
      cur_dd -> value = new_value;
      return true;
      }
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    // проверка на выход за пределы списка
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }

    // удаление из "начала" списка
    if (index == 0) {
      auto* remove_node = front_;
      const int remove_value = remove_node->value;

      // сдвигаем "начало" списка на следующий узел
      front_ = front_->next;

      // высвобождаем выделенную под удаляемый узел память
      delete remove_node;

      // уменьшаем размер списка
      size_ -= 1;

      return remove_value;
    }

    // удаление из любой другой позиции

    auto* prev_node = FindNode(index - 1);

    // находим удаляемый узел и его значение
    auto* removed_node = prev_node->next;
    const int removed_value = removed_node->value;

    // предыдущий узел "указываем" на следующий после удаляемого узла
    prev_node->next = removed_node->next;

    // высвобождаем выделенную под удаляемый узел память
    delete removed_node;

    // уменьшаем размер списка
    size_ -= 1;

    return removed_value;
  }

  void LinkedList::Clear() {
    for(Node* current = front_; current != nullptr;/* */){
      Node* node_to_remove = current;
      current = current->next;
      delete node_to_remove;
    }
    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
    // Write your code here ...
  }

  std::optional<int> LinkedList::Get(int index) const {
    if(index >= 0 && index < size_){
      int find = 0;
      Node* cur_dd = front_;
      for(Node* current = front_ ; find != index && current -> next != nullptr ; /* */){
        current = current -> next;
        cur_dd = current;
        find++;
      }
      return cur_dd -> value;
    }

    return std::nullopt;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    // Write your code here ...

      int find = 0;
      Node* curr = front_;
      for(Node* current = front_ ; current -> value != value && current -> next != nullptr ; /* */) {
        current = current->next;
        curr = current;
        find++;
      }
      if (curr -> value != value){
        return std::nullopt;
      }
      return find;

  }

  bool LinkedList::Contains(int value) const {
    int find = 0;
    Node* curr = front_;
    for(Node* current = front_ ; current -> value != value && current -> next != nullptr ; /* */) {
      current = current->next;
      curr = current;
      find++;
    }
    if (curr -> value != value){
      return false;
    }
    return true;
  }

  bool LinkedList::IsEmpty() const {
    return front_ == nullptr;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if(front_ != nullptr){
      return front_ -> value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    // Write your code here ...
    if(back_ != nullptr){
      return back_ -> value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    if(index >= 0 && index < size_){
      int find = 0;
      Node* cur_dd = front_;
      for(Node* current = front_ ; find != index && current -> next != nullptr ; /* */){
        current = current -> next;
        cur_dd = current;
        find++;
      }
      return cur_dd;

    }

    // Write your code here ...
    return nullptr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment