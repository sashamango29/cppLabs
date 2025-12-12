#include <iostream>
#include <stdexcept>
#include <new>

template <typename T>
class Stack {
private:
    T* data;
    std::size_t capacity;
    std::size_t count;

    void resize(std::size_t new_capacity) {
        T* new_data = static_cast<T*>(operator new[](new_capacity * sizeof(T)));
        for (std::size_t i = 0; i < count; ++i) {
            new (new_data + i) T(data[i]);
            data[i].~T();
        }
        operator delete[](data);
        data = new_data;
        capacity = new_capacity;
    }

public:
    Stack(std::size_t cap = 10)
        : data(static_cast<T*>(operator new[](cap * sizeof(T)))), capacity(cap), count(0) {}

    ~Stack() {
        for (std::size_t i = 0; i < count; ++i) {
            data[i].~T();
        }
        operator delete[](data);
    }

    Stack(const Stack& other)
        : data(static_cast<T*>(operator new[](other.capacity * sizeof(T)))), capacity(other.capacity), count(other.count) {
        for (std::size_t i = 0; i < count; ++i) {
            new (data + i) T(other.data[i]);
        }
    }

    void push(const T& value) {
        if (count >= capacity) {
            resize(capacity * 2);
        }
        new (data + count) T(value);
        ++count;
    }

    void pop() {
        if (count == 0) throw std::underflow_error("stack is empty");
        data[count - 1].~T();
        --count;
    }

    T& top() {
        if (count == 0) throw std::out_of_range("stack is empty");
        return data[count - 1];
    }

    bool empty() const { return count == 0; }
    std::size_t size() const { return count; }
};

int main() {
    try {
        Stack<int> st;

        std::cout << "=== normal operations ===\n";
        st.push(10);
        st.push(20);
        st.push(30);

        std::cout << "top element " << st.top() << "\n";

        st.pop();
        std::cout << "after pop top element " << st.top() << "\n";

        std::cout << "\n=== test exceptions ===\n";

        st.pop();
        st.pop();

        std::cout << "stack is now empty\n";

        try {
            st.pop();
        } catch (const std::exception& e) {
            std::cout << "caught exception on pop: " << e.what() << "\n";
        }

        try {
            st.top();
        } catch (const std::exception& e) {
            std::cout << "caught exception on top: " << e.what() << "\n";
        }

        std::cout << "\n=== test copy constructor ===\n";
        st.push(100);
        st.push(200);
        st.push(300);

        std::cout << "original stack top = " << st.top() << "\n";

        Stack<int> st2 = st;

        std::cout << "copy stack top = " << st2.top() << "\n";

        st2.pop();
        std::cout << "after pop in copy, st2 top = " << st2.top() << "\n";

        std::cout << "original stack still top = " << st.top() << "\n";

    } catch (const std::exception& e) {
        std::cerr << "unhandled error: " << e.what() << "\n";
    }

    return 0;
}
