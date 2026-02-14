// Use raw pointers, smart pointers('unique_ptr','shared_ptr'), and references to    manage a dynamically allocated array-- compare safety and overhead.

// References are a way to access arrays without owning memory.
#include <iostream>
#include <memory>   // unique_ptr, shared_ptr
#include <vector>

void print_array(int* arr, size_t n) {
    for (size_t i = 0; i < n; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}

void print_array_ref(const int (&arr)[5]) { // reference to fixed-size array
    for (int i = 0; i < 5; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}

int main() {
    size_t n = 8;

    // -------------------------
    // Raw pointer
    // -------------------------
    int* raw = new int[n];          // allocate memory
    for (size_t i = 0; i < n; ++i)
        raw[i] = i+1;

    std::cout << "Raw pointer: ";
    print_array(raw, n);

    delete[] raw;                   // must remember to free memory
    // If we forget delete → memory leak
    // Dangling pointer if we use raw after delete

    // -------------------------
    // unique_ptr (smart pointer)
    // -------------------------
    std::unique_ptr<int[]> u_ptr = std::make_unique<int[]>(n); // allocate & manage
    for (size_t i = 0; i < n; ++i)
        u_ptr[i] = (i+1)*10;

    std::cout << "unique_ptr: ";
    print_array(u_ptr.get(), n);    // access raw pointer with get()

    // automatic deletion at scope end
    // Cannot copy unique_ptr (ownership unique)
    // Safe: no leaks, no dangling pointers

    // -------------------------
    // shared_ptr (smart pointer)
    // -------------------------
    std::shared_ptr<int> s_ptr(new int[n], std::default_delete<int[]>()); // custom deleter
    for (size_t i = 0; i < n; ++i)
        s_ptr.get()[i] = (i+1)*100;

    std::cout << "shared_ptr: ";
    print_array(s_ptr.get(), n);

    // reference count handles deletion automatically
    // Safe for shared ownership
    // Overhead: reference counting + atomic operations

    // -------------------------
    // Reference to array (non-owning)
    // -------------------------
    int arr_ref[5] = {1,2,3,4,5};
    std::cout << "Array reference: ";
    print_array_ref(arr_ref);      // reference provides safe access
    // Reference does not own memory → cannot resize or free

    return 0;
}

