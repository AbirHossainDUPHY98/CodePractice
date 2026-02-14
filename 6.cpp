/*Demonstrate move semantics by implementing a simple 'Vector' class that avoids unnecessary copies*/

//Vector implementation must- 1)Own a heap buffer. 2)Implement the Rule of Five. 
// 3)Transfer ownership in move constructor/move assignment instead of copying.
// Move semantics(C++ mechanism) -- Transfering ownership of resources instead of copying them.
// Previously -- Allocate new memory, copy every element, slow, expensive, unnecessary if the earlier owner was supposed to be temporary. 
// With MS- don't copy data, steal the pointer, invalidate the source, transfer ownership. 
// Implemented with -- T(T&& other); move constructor and T& operator = (T&& other); move assignment.
// Rule of 5(Ownership behaviour) -- 1) Destructor, 2) Copy constructor, 3)Copy assignment, 4)Move constructor, 5)Move assignment.
// These must be applied when -- the class owns- (raw memory, file handles, sockets, OS resources, GPU buffers, mutexes, manages lifetimes manually. 
// Not needed for RAII types.(std:: vector, string, unique_ptr, shared_ptr, array, map) -- Modern c++
// Partial uses are allowed. Like Transfer-only ownership: Move only, Immutable shared data: Copy only
// Prevents 'dangling pointer -- Points to memory already freed'.
// Memory Leak: Memory that is allocated but no longer reachable by any pointer. Simply an unreachable memory. 

#include <iostream>

class Vector{
  double* data; 
  size_t size;
  public:
    //Constructor  
    Vector(size_t s) : size(s) {
      data = new double[size];
      std::cout << "Memory allocated at: "<< data << std::endl;
    }
    //Destructor
    ~Vector() {
      if (data != nullptr) {
        delete[] data;
        std::cout << "Memory at " << data << " freed." << std::endl;
      } 
      else {
        std::cout << "Destructor called, but no memory to free (already moved)." << std::endl;
      }
    }

    //Copy constructor
    Vector(const Vector& other) noexcept:size(other.size)
      {
        data = new double[size];
        for (size_t i=0; i<size; i++)
          data[i] = other.data[i];
        std::cout << "Copy constructor called, memory allocated at " << data <<"\n";
      }
    //Copy assignment
    Vector& operator=(const Vector& other) noexcept
      {
        if (this != &other){
          delete[] data;
          size = other.size;
          data = new double[size];
          for (size_t i = 0; i<size; i++)
            data[i] = other.data[i];
        }
        std::cout<< "Copy assignment called\n";
        return *this;
      }

    //Move constructor
    Vector(Vector&& other) noexcept: data(other.data), size(other.size)
      {
        other.data = nullptr;
        other.size = 0;
        std::cout<< "Move constructor called\n";
      }

    //Move assignment
    Vector& operator=(Vector&& other) noexcept
      {
        if (this != &other)
          {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
          }
        std::cout<<"Move assignment called\n";
        return *this;
      }

    size_t getsize() const {return size;}
};

int main() {
    std::cout << "\n=== Creating Vector a ===\n";
    Vector a(5);  // Constructor

    std::cout << "\n=== Copying a to b ===\n";
    Vector b = a; // Copy constructor

    std::cout << "\n=== Assigning a to c ===\n";
    Vector c(2);  
    c = a;        // Copy assignment

    std::cout << "\n=== Moving a to d ===\n";
    Vector d = std::move(a);  // Move constructor

    std::cout << "\n=== Moving c to e ===\n";
    Vector e(3);
    e = std::move(c);         // Move assignment

    std::cout << "\n=== End of main, destructors called ===\n";
}

