// Copying a pointer member copies its address. These pointers borrow local data.
#include <iostream>
#include <string>

class student {
public:
    std::string name;
    double* cgpaptr;

    student(const std::string& studentName, double& cgpa)
        : name(studentName), cgpaptr(&cgpa) {}

    // The compiler-generated copy constructor copies name and cgpaptr.
    void getInfo() const {
        std::cout << "Name: " << name << '\n';
        std::cout << "CGPA: " << *cgpaptr << '\n';
    }
};

int main() {
    double cgpa = 8.19; // Outlives both students because it is created first.
    student s1("Rahul", cgpa);
    student s2(s1);
    std::cout << "Same CGPA address: " << std::boolalpha
              << (s1.cgpaptr == s2.cgpaptr) << '\n';
    *s2.cgpaptr = 9.2;
    s1.getInfo(); // Both print 9.2 because they share this double.
    s2.getInfo();
    // No delete: cgpa is a local object, not an allocation made with new.
    return 0;
}
