// Automatic student objects are destroyed when their blocks exit normally.
#include <iostream>
#include <string>

class student {
public:
    std::string name;
    student(const std::string& studentName) : name(studentName) {
        std::cout << "Constructing " << name << '\n';
    }
    ~student() { std::cout << "Destroying " << name << '\n'; }
};

void visit() {
    student visitor("Visitor");
    std::cout << "Returning from visit\n";
}

int main() {
    student s1("Kapil");
    {
        student s2("Rahul");
        std::cout << "Leaving inner block\n";
    } // s2 is destroyed; s1 still exists.
    visit(); // visitor is destroyed when visit returns.
    std::cout << "Still in main: " << s1.name << '\n';
    std::cout << "Leaving main\n";
    return 0; // s1 is destroyed as main exits.
}
