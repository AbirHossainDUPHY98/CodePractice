// Write a thread-safe circular buffer using 'std::mutex' and 'std::condition_vari   able'.
/*
A circular buffer that:
Holds a fixed number of elements (capacity)
Supports:
push() → add an element (blocks if full)
pop() → remove an element (blocks if empty)
Thread-safe for multiple producers and consumers.
*/

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

template <typename T>
class CircularBuffer {
private:
    std::vector<T> buffer;
    size_t head = 0;  // next position to write
    size_t tail = 0;  // next position to read
    size_t count = 0; // current number of elements
    size_t capacity;

    std::mutex mtx;
    std::condition_variable not_full;
    std::condition_variable not_empty;

public:
    CircularBuffer(size_t size) : buffer(size), capacity(size) {}

    // Add an element (blocks if full)
    void push(const T& item) {
        std::unique_lock<std::mutex> lock(mtx);
        not_full.wait(lock, [this]() { return count < capacity; }); // wait if full

        buffer[head] = item;
        head = (head + 1) % capacity;
        ++count;

        lock.unlock();
        not_empty.notify_one(); // signal a waiting consumer
    }

    // Remove an element (blocks if empty)
    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        not_empty.wait(lock, [this]() { return count > 0; }); // wait if empty

        T item = buffer[tail];
        tail = (tail + 1) % capacity;
        --count;

        lock.unlock();
        not_full.notify_one(); // signal a waiting producer
        return item;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx);
        return count == 0;
    }

    bool full() {
        std::lock_guard<std::mutex> lock(mtx);
        return count == capacity;
    }
};

void producer(CircularBuffer<int>& cb, int start, int n) {
    for (int i = start; i < start + n; ++i) {
        cb.push(i);
        std::cout << "Produced: " << i << std::endl;
    }
}

void consumer(CircularBuffer<int>& cb, int n) {
    for (int i = 0; i < n; ++i) {
        int item = cb.pop();
        std::cout << "Consumed: " << item << std::endl;
    }
}

int main() {
    CircularBuffer<int> cb(5); // buffer capacity 5

    std::thread p1(producer, std::ref(cb), 0, 10);
    std::thread c1(consumer, std::ref(cb), 5);
    std::thread c2(consumer, std::ref(cb), 5);

    p1.join();
    c1.join();
    c2.join();

    return 0;
}

// Don't understand anything about this problem. Got to go deep.
