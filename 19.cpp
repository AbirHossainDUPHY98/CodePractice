// Use range-based 'for' loops with 'auto' and 'const&' to iterate over containers   efficiently.

#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> library = {
        "The C++ Programming Language",
        "Structure and Interpretation of Computer Programs",
        "Clean Code",
        "The Pragmatic Programmer"
    };

    std::cout << "Library Inventory:" << std::endl;
    // Use a range-based for loop with 'const auto&' to iterate
    for (const auto& book : library) {
        std::cout << "- " << book << std::endl;
    }

    return 0;
}

// Use const auto& when you just want to read (fastest and safest).

// Use auto& when you want to modify the original list.

// Use auto (no &) only when you specifically want a copy to play with without touching the original.
