// Constructor overloading provides different ways to initialize a student.
#include <iostream>
#include <string>

class student {
public:
    std::string name;
    student() : name("Unknown") {
        std::cout << "Non-parameterized constructor\n";
    }
    student(const std::string& studentName) : name(studentName) {
        std::cout << "Parameterized constructor\n";
    }
};

int main() {
    student s1;          // Calls student().
    student s2("Kapil"); // Calls student(const std::string&).
    std::cout << "s1 name: " << s1.name << '\n';
    std::cout << "s2 name: " << s2.name << '\n';
    return 0;
}
