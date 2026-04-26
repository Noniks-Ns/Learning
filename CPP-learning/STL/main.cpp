#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <deque>
#include <array>
#include <list>
#include <algorithm>
#include <numeric>

int main() {
    std::array<int, 3> myArray = { 5, 10, 15 };

    std::cout << "front: " << myArray.front() << '\n';
    std::cout << "back: " << myArray.back() << '\n';
    std::cout <<  "second element: " << myArray[1] << '\n';

    try {
        std::cout << "element [10]: " << myArray.at(10) << '\n';
    }
    catch (const std::out_of_range& e) {
        std::cout << "error: " << e.what() << '\n';
    }

    std::cout << "all elements: ";
    for (const int& value : myArray) {
        std::cout << value << '\n';
    }

    auto maxElement = max_element(myArray.begin(), myArray.end());
    std::cout << "biggest element: " << *maxElement << '\n';

    std::array<int, 3> copyArray = myArray;
    std::cout << "array copy: ";
    for (int n : copyArray) {
        std::cout << n << '\n';
    }

    copyArray.fill(0);
    std::cout << "after fill(0): ";
    for (int n : copyArray) {
        std::cout << n << '\n';
    }

    std::cout << "array size: " << myArray.size() << '\n';
    std::cout << "array empty? " << std::boolalpha << myArray.empty() << '\n';

    return 0;
}
