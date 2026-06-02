#include <iostream>

template <typename T>
struct ListNode {
    T data;
    ListNode<T>* next;
    ListNode(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class MyStack {
private:
    ListNode<T>* top;

    void copyFrom(const MyStack& other) {
        if (other.top == nullptr) {
            top = nullptr;
            return;
        }

        top = new ListNode<T>(other.top->data);
        ListNode<T>* current = top;
        ListNode<T>* otherCurrent = other.top->next;

        while (otherCurrent != nullptr) {
            current->next = new ListNode<T>(otherCurrent->data);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
    }

public:
    MyStack() : top(nullptr) {}

    MyStack(const MyStack& other) : top(nullptr) {
        copyFrom(other);
    }

    MyStack& operator=(const MyStack& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    ~MyStack() { 
        clear();
    }

    void push(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);
        newNode->next = top;
        top = newNode;
    }

    bool pop(T& value) {
        if (isEmpty()) {
            return false;
        }
        ListNode<T>* temp = top;
        value = top->data;
        top = top->next;
        delete temp;
        return true;
    }

    bool peek(T& value) const {
        if (isEmpty()) {
            return false;
        }
        value = top->data;
        return true;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void clear() {
        while (top != nullptr) {
            ListNode<T>* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void print() const {
        ListNode<T>* current = top;
        std::cout << "Stack (top to bottom): ";
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};
