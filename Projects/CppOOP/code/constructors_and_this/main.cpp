// A constructor initializes a new object. this points to the current object.
#include <iostream>
#include <string>

class Teacher {
    double salary = 0.0;
public:
    std::string name;
    std::string dept;
    std::string subject;

    Teacher() : dept("Computer Science") {
        std::cout << "Default constructor\n";
    }

    Teacher(const std::string& teacherName, const std::string& department,
            const std::string& teachingSubject, double startingSalary)
        : salary(startingSalary), name(teacherName), dept(department),
          subject(teachingSubject) {
        std::cout << "Parameterized constructor\n";
    }

    void setName(const std::string& newName) {
        this->name = newName; // The object receiving this call is the target.
    }

    void getInfo() const {
        std::cout << "Name: " << name << '\n';
        std::cout << "Department: " << dept << '\n';
        std::cout << "Subject: " << subject << '\n';
        std::cout << "Salary: " << salary << '\n';
    }
};

int main() {
    Teacher t1; // Calls Teacher(); other strings start empty, salary at zero.
    t1.setName("Kapil");
    t1.getInfo(); // Parentheses perform the function call.
    Teacher t2("Rahul", "Digital Electronics", "HDL", 20000.0);
    t2.getInfo();
    return 0;
}
