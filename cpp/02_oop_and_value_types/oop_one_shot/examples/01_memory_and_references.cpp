#include <array>
#include <iostream>
#include <memory>
#include <vector>

void swap_by_reference(int& left, int& right) noexcept
{
    const int temporary{left};
    left = right;
    right = temporary;
}

int main()
{
    std::array<int, 5> fixed_values{10, 20, 30, 40, 50};
    std::vector<int> growing_values{2, 4, 6};
    growing_values.push_back(8);

    auto owned_value = std::make_unique<int>(99);

    int first{10};
    int second{20};
    swap_by_reference(first, second);

    std::cout << "fixed_values[2] = " << fixed_values.at(2) << '\n';
    std::cout << "growing_values size = " << growing_values.size() << '\n';
    std::cout << "dynamically stored value = " << *owned_value << '\n';
    std::cout << "after swap: first = " << first
              << ", second = " << second << '\n';
}
