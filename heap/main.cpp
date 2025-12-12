#include "heap.h"
#include <iostream>

int main() {
    MaxHeap<int> heap;

    heap.insert(10);
    heap.insert(5);
    heap.insert(20);
    heap.insert(15);
    heap.insert(30);

    std::cout << "Heap after insertions: ";
    heap.print();

    std::cout << "Extracting max: " << heap.extractMax() << "\n";

    std::cout << "Heap after extract: ";
    heap.print();

    // move-конструктор
    MaxHeap<int> movedHeap(std::move(heap));
    std::cout << "After move construction (old heap): ";
    heap.print();
    std::cout << "After move construction (new heap): ";
    movedHeap.print();

    // move-присваивание
    MaxHeap<int> another;
    another.insert(1);
    another.insert(2);
    std::cout << "Before move assign (another): ";
    another.print();

    another = std::move(movedHeap);
    std::cout << "After move assign (another): ";
    another.print();

    std::cout << "Old movedHeap now: ";
    movedHeap.print();

    return 0;
}
