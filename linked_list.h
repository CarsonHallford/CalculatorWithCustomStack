#ifndef LINKED_LIST
#define LINKED_LIST
#define NULL 0

#include <iostream>

template <class T>
class Node {
 public:
  T data;
  Node<T> *next;

  Node() {
    data = NULL;
    next = NULL;
  }
};

template <class T>
class Iterator {
 public:
  // Check if the iterator reached the end of the list
  // O(1)
  bool end() {
    if (this->node == NULL || this->node->next == NULL) {
      return true;
    }

    return false;
  }

  // O(n)
  void operator++(int a) {
    for (int i = 0; i < a; i++) {
      this->prev = this->node;
      this->node = this->node->next;
    }
  }

  T operator->() { return this->node->data; }

  Node<T> *prev;
  Node<T> *node;
};

template <class T>
class LinkedList {
 public:
  // O(1)
  void insert(Iterator<T> it, T data) {
    Node<T> *temp = new Node<T>;
    temp->data = data;
    if (this->head->next == NULL) {
      this->head->next = temp;
    } else {
      it.prev->next = temp;
      temp->next = it.node;
      it.node = temp;
    }
  }
  // O(1)
  void push_back(Iterator<T> it, T data) {
    Node<T> *temp = new Node<T>;
    temp->data = data;
    it.node->next = temp;
  }
  // O(1)
  Iterator<T> begin() {
    Iterator<T> obj;
    obj.prev = this->head;

    obj.node = this->head->next;

    return obj;
  }
  // O(n)
  Iterator<T> last() {
    Iterator<T> obj;
    obj = this->begin();
    while (!obj.end()) {
      obj.operator++(1);
    }
    return obj;
  }
  // O(1)
  void erase(Iterator<T> it) {
    Node<T> *newNext = it.node->next;
    it.prev->next = newNext;
    it.node = newNext;
  }

  // O(n)
  void stack_push(T data) {
    if (this->head->next == NULL) {
      this->insert(this->begin(), data);
    } else {
      Iterator<T> obj = this->last();
      this->push_back(obj, data);
    }
  }

  // O(1)
  void stack_pop() {
    Iterator<T> obj = this->last();
    this->erase(obj);
  }

  // O(1)
  T stack_top() {
    if (this->last().node == NULL) {
      T t;
      return t;
    }
    Iterator<T> obj = this->last();
    return obj.node->data;
  }

  // O(n)
  int stack_size() {
    int size = 0;

    if (this == NULL || this->head == NULL || this->head->next == NULL) {
      return size;
    }

    for (Iterator<T> it = this->begin(); !it.end(); it.operator++(1)) {
      size++;
    }
    return size + 1;
  }

  Node<T> *head;
};

#endif  // LINKED_LIST