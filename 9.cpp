//Write a template function that finds the maximum of two values of any comparable type. 

#include <iostream>
#include <string>

template <typename T>
T my_max(T a, T b) {
    return (a > b) ? a : b;  //Ternary operator in c++  --> condition ? value_if_true : value_if_false
                             //Const T& my_max(const T& a, const T& b) , to avoid unnecessary copying of large T type into the function.Makes read only.
                             //T is a placeholder type- using template, at compile time the compiler will instantiate this function with the real type passed.
}

int main() {
    int x = 10, y = 20;
    double p = 3.14, q = 2.71;
    std::string s1 = "apple", s2 = "banana";

    std::cout << my_max(x, y) << "\n";   
    std::cout << my_max(p, q) << "\n";   
    std::cout << my_max(s1, s2) << "\n";
    std::cout << my_max("kaka","mami") << "\n";
    std::cout << my_max(5.87, 0.98) << "\n";

    return 0;
}

