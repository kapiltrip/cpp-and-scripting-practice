#include "student.hpp"

int main() {
    student s1("Rahul", 8.19);
    student s2(s1);
    s2.name = "Rahul copy";
    std::cout << "Before change\n";
    s1.getInfo();
    s2.getInfo();
    std::cout << "Same CGPA address: " << std::boolalpha
              << (s1.cgpaptr == s2.cgpaptr) << '\n';
    *s2.cgpaptr = 9.2;
    std::cout << "After change\n";
    s1.getInfo(); // Still 8.19: s1 has its own allocation.
    s2.getInfo(); // Now 9.2: only s2's allocation changed.
    return 0;    // Local objects are then destroyed: s2 first, then s1.
}
