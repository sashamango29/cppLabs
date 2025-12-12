#include "heap.h"

template <typename T>
void MaxHeap<T>::siftUp(Node* node) {
    while (node->parent && node->value > node->parent->value) {
        std::swap(node->value, node->parent->value);
        node = node->parent;
    }
}

template <typename T>
void MaxHeap<T>::siftDown(Node* node) {
    while (node) {
        Node* largest = node;
        if (node->left && node->left->value > largest->value)
            largest = node->left.get();
        if (node->right && node->right->value > largest->value)
            largest = node->right.get();
        if (largest == node) break;
        std::swap(node->value, largest->value);
        node = largest;
    }
}

template <typename T>
MaxHeap<T>::MaxHeap(MaxHeap&& other) noexcept
    : root(std::move(other.root)), size_(other.size_) {
    other.size_ = 0;
}

template <typename T>
MaxHeap<T>& MaxHeap<T>::operator=(MaxHeap&& other) noexcept {
    if (this != &other) {
        root = std::move(other.root);
        size_ = other.size_;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
void MaxHeap<T>::insert(T value) {
    auto newNode = std::make_unique<Node>(std::move(value));

    if (!root) {
        root = std::move(newNode);
        ++size_;
        return;
    }

    Node* current = root.get();
    while (true) {
        if (!current->left) {
            current->left = std::move(newNode);
            current->left->parent = current;
            siftUp(current->left.get());
            break;
        } else if (!current->right) {
            current->right = std::move(newNode);
            current->right->parent = current;
            siftUp(current->right.get());
            break;
        } else {
            current = current->left.get();
        }
    }

    ++size_;
}

template <typename T>
typename MaxHeap<T>::Node* MaxHeap<T>::getLastNode() const {
    if (!root) return nullptr;

    Node* last = root.get();
    int count = 1;

    while (count < size_) {
        if (last->left && count + 1 <= size_) {
            last = last->left.get();
        } else if (last->right && count + 2 <= size_) {
            last = last->right.get();
        } else {
            break;
        }
        ++count;
    }

    return last;
}

template <typename T>
T MaxHeap<T>::extractMax() {
    if (!root) throw std::runtime_error("Heap is empty");

    T maxValue = std::move(root->value);
    Node* last = getLastNode();

    if (last == root.get()) {
        root.reset();
        size_ = 0;
        return maxValue;
    }

    root->value = std::move(last->value);

    if (last->parent->right && last->parent->right.get() == last)
        last->parent->right.reset();
    else if (last->parent->left && last->parent->left.get() == last)
        last->parent->left.reset();

    --size_;
    siftDown(root.get());
    return maxValue;
}

template <typename T>
void MaxHeap<T>::print() const {
    if (!root) {
        std::cout << "(empty)\n";
        return;
    }

    print(root.get());
    std::cout << "\n";
}

template <typename T>
void MaxHeap<T>::print(Node* node) const {
    if (!node) return;
    std::cout << node->value << " ";
    print(node->left.get());
    print(node->right.get());
}
