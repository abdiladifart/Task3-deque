#include <iostream>
#include <string>

template<typename T>
class Dec {
private:
    T* data;
    int capacity;
    int frontIndex;
    int backIndex;
    int count;

    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];

        int current = frontIndex;
        for (int i = 0; i < count; ++i) {
            newData[i] = data[current];
            current = (current + 1) % capacity;
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
        frontIndex = 0;
        backIndex = count - 1;
    }

public:
    Dec(int initialCapacity = 8) : capacity(initialCapacity), count(0), frontIndex(0), backIndex(-1) {
        data = new T[capacity];
    }

    ~Dec() {
        delete[] data;
    }

    void push_front(T value) {
        if (count == capacity)
            resize();

        frontIndex = (frontIndex - 1 + capacity) % capacity;
        data[frontIndex] = value;
        count++;
    }

    void push_back(T value) {
        if (count == capacity)
            resize();

        backIndex = (backIndex + 1) % capacity;
        data[backIndex] = value;
        count++;
    }

    void pop_front() {
        if (isEmpty())
            throw std::out_of_range("Deque is empty");

        frontIndex = (frontIndex + 1) % capacity;
        count--;
    }

    void pop_back() {
        if (isEmpty())
            throw std::out_of_range("Deque is empty");

        backIndex = (backIndex - 1 + capacity) % capacity;
        count--;
    }

    T front() {
        if (isEmpty())
            throw std::out_of_range("Deque is empty");

        return data[frontIndex];
    }

    T back() {
        if (isEmpty())
            throw std::out_of_range("Deque is empty");

        return data[backIndex];
    }

    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }
};

int main() {
    // Example with int
    Dec<int> intDeque;
    intDeque.push_back(1);
    intDeque.push_front(2);
    std::cout << "Front: " << intDeque.front() << ", Back: " << intDeque.back() << std::endl;

    // Example with string
    Dec<std::string> stringDeque;
    stringDeque.push_back("Task");
    stringDeque.push_front("Two");
    std::cout << "Front: " << stringDeque.front() << ", Back: " << stringDeque.back() << std::endl;

    return 0;
}
