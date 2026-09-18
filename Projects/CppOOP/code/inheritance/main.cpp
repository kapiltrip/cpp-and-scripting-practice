// Public inheritance models "is a": gradStudent is a student, who is a person.
#include <iostream>
#include <string>

class person {
public:
    std::string name;
    int age;
    person(const std::string& personName, int personAge)
        : name(personName), age(personAge) {
        std::cout << "person constructor\n";
    }
    ~person() { std::cout << "person destructor\n"; }
};

// Public inheritance: a student is a person.
class student : public person {
public:
    int rollno;
    // The initializer list constructs person first, then initializes rollno.
    student(const std::string& studentName, int studentAge, int studentRollno)
        : person(studentName, studentAge), rollno(studentRollno) {
        std::cout << "student constructor\n";
    }
    void getInfo() const {
        std::cout << "Name: " << name << '\n';
        std::cout << "Age: " << age << '\n';
        std::cout << "Roll number: " << rollno << '\n';
    }
    ~student() { std::cout << "student destructor\n"; }
};

// Multilevel inheritance: student already has a person base subobject.
class gradStudent : public student {
public:
    std::string researchArea;
    gradStudent(const std::string& studentName, int studentAge,
                int studentRollno)
        : student(studentName, studentAge, studentRollno) {
        // researchArea is default-initialized to an empty string.
        std::cout << "gradStudent constructor\n";
    }
    ~gradStudent() { std::cout << "gradStudent destructor\n"; }
};

int main() {
    gradStudent s1("Kapil", 26, 33);
    s1.researchArea = "VLSI";
    s1.getInfo(); // Inherited public member function.
    std::cout << "Research area: " << s1.researchArea << '\n';
    return 0; // Cleanup: gradStudent, then student, then person.
}
