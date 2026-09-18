// A copy constructor initializes a new object from an existing same-class object.
#include <iostream>
#include <string>

class Teacher {
    double salary = 0.0;
public:
    std::string name;
    std::string dept;
    std::string subject;

    Teacher(const std::string& teacherName, const std::string& department,
            const std::string& teachingSubject, double startingSalary)
        : salary(startingSalary), name(teacherName), dept(department),
          subject(teachingSubject) {}

    Teacher(const Teacher& obj)
        : salary(obj.salary), name(obj.name), dept(obj.dept),
          subject(obj.subject) {
        // obj refers to the source; this points to the new destination.
        // In a constructor body, this->name = obj.name assigns the same value.
        std::cout << "Copy constructor\n";
    }

    void getInfo() const {
        std::cout << "Name: " << name << '\n';
        std::cout << "Subject: " << subject << '\n';
        std::cout << "Salary: " << salary << '\n';
    }
};

int main() {
    const Teacher t1("Kapil", "Digital Electronics", "HDL", 20000.0);
    Teacher t2(t1); // Constructs t2 without modifying t1.
    t2.name = "Rahul";
    t1.getInfo();
    t2.getInfo();
    // For these string and double members, the compiler-generated copy
    // constructor would also copy the values correctly.
    return 0;
}
