#include "queue.h"

Node::Node(int32_t value, Node* previous) : value{value}, next{next} {
}

Queue::Queue() {
    front_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

Queue::~Queue() {
    Clear();
}

void Queue::Push(int32_t value) {
    Node* new_tail = new Node(value, nullptr);
    if (size_ == 0) {
        front_ = new_tail;
        tail_ = new_tail;
    } else {
        tail_->next = new_tail;
        tail_ = new_tail;
    }
    ++size_;
}

void Queue::Pop() {
    if (size_ == 0) {
        return;
    }
    Node* current = front_;
    if (size_ == 1) {
        front_ = nullptr;
        tail_ = nullptr;
    } else {
        front_ = front_->next;
    }
    delete current;
    --size_;
}

int32_t Queue::Front() const {
    if (size_ == 0) {
        return 0;
    }
    return front_->value;
}

int32_t Queue::Size() const {
    return size_;
}

void Queue::Clear() {
    while (size_ > 0) {
        Pop();
    }
}

bool Queue::Empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}