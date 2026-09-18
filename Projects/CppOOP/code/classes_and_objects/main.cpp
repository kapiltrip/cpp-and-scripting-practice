// A class defines a type; each object has its own non-static data members.
#include <iostream>
#include <string>

class Teacher {
public:
    std::string name;
    std::string dept;
    std::string subject;

    void changeDepartment(const std::string& newDept) { dept = newDept; }

    void getInfo() const {
        std::cout << "Name: " << name << '\n';
        std::cout << "Department: " << dept << '\n';
        std::cout << "Subject: " << subject << '\n';
    }
};

int main() {
    Teacher t1;
    t1.name = "Kapil";
    t1.dept = "Computer Science";
    t1.subject = "C++";
    Teacher t2;
    t2.name = "Rahul";
    t2.dept = "Mathematics";
    t2.subject = "Calculus";
    t1.changeDepartment("Digital Electronics");
    t1.getInfo();
    t2.getInfo(); // t2's department remains Mathematics.
    return 0;    // Report successful completion to the operating system.
}
