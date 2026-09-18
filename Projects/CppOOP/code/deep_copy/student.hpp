#pragma once
// Deep copy gives each object separate owned storage containing the copied value.
#include <iostream>
#include <string>

class student {
public:
    std::string name;
    double* cgpaptr; // Owning pointer kept visible for this pointer lesson.

    student(const std::string& studentName, double cgpa)
        : name(studentName), cgpaptr(new double(cgpa)) {}

    student(const student& obj)
        : name(obj.name), cgpaptr(new double(*obj.cgpaptr)) {
        std::cout << "Deep-copy constructor\n";
    }

    // Disable assignment: an accidental s2 = s1 must not share an owned pointer.
    student& operator=(const student&) = delete;

    void getInfo() const {
        std::cout << "Name: " << name << '\n';
        std::cout << "CGPA: " << *cgpaptr << '\n';
    }

    ~student() {
        std::cout << "Destructor called for " << name << '\n';
        delete cgpaptr; // Release the one double allocated for this object.
    }
};
