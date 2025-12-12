#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <iostream>
#include <memory>
#include <utility>

template <typename T>
class MaxHeap {
public:
    MaxHeap() = default;
    MaxHeap(MaxHeap&& other) noexcept;
    MaxHeap& operator=(MaxHeap&& other) noexcept;

    MaxHeap(const MaxHeap&) = delete;
    MaxHeap& operator=(const MaxHeap&) = delete;

    void insert(T value);
    T extractMax();

    [[nodiscard]] bool empty() const { return size_ == 0; }
    [[nodiscard]] size_t size() const { return size_; }

    void print() const;

private:
    struct Node {
        T value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node* parent = nullptr;

        explicit Node(T&& val) : value(std::move(val)) {}
    };

    std::unique_ptr<Node> root;
    size_t size_ = 0;

    void siftUp(Node* node);
    void siftDown(Node* node);
    Node* getLastNode() const;
    void print(Node* node) const;
};

#include "heap.cpp"

#endif // MAX_HEAP_H
