//Use 'std::optional' to safely return a value that may not exist from a search function.

#include <iostream>
#include <vector>
#include <optional>

std::optional<int> find_value(const std::vector<int>& v, int target) {
    for (int x : v) {
        if (x == target)
            return x;          // value exists
    }
    return std::nullopt;       // value does NOT exist
}

//Using it safely

int main() {
    std::vector<int> data = {1, 3, 5, 7, 9};

    auto result = find_value(data, 13);

    if (result.has_value()) {
        std::cout << "Found: " << result.value() << "\n";
    } else {
        std::cout << "Not found\n";
    }

    // cleaner style:
    if (auto r = find_value(data, 10)) {
        std::cout << "Found: " << *r << "\n";
    } else {
        std::cout << "Not found\n";
    }
}


//std::optional<T> --> A container that may or may not hold a value of type T.
//std::nullopt --> Empty optional-- there is no value to return.
//auto --> type interference --> here-- std::vector<int> result
//.has_value() --> boolean that checks if the optional contain a value.
//value() --> give me the contained value. 
