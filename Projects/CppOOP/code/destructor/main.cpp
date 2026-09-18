// A destructor performs cleanup when an object's lifetime ends.
#include <iostream>
#include <string>

class student {
public:
    std::string name;
    double* cgpaptr;

    student(const std::string& studentName, double cgpa)
        : name(studentName), cgpaptr(new double(cgpa)) {
        std::cout << "Constructor called for " << name << '\n';
    }
    // This isolated cleanup example is not copyable.
    student(const student&) = delete;
    student& operator=(const student&) = delete;

    ~student() {
        std::cout << "Destructor called for " << name << '\n';
        delete cgpaptr; // new double pairs with delete, not delete[].
    }
};

int main() {
    student s1("Rahul", 8.19);
    {
        student s2("Kapil", 9.2);
        std::cout << "Leaving inner block\n";
    } // s2 is destroyed before the next output statement.
    std::cout << "Leaving main\n";
    return 0; // s1 is destroyed as main exits.
}
