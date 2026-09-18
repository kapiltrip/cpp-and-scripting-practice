// Teacher grants one non-member function access to its private salary.
#include <iostream>

class Teacher {
private:
    double salary;
public:
    Teacher(double startingSalary) : salary(startingSalary) {}
    friend void showSalary(const Teacher& teacher);
};

void showSalary(const Teacher& teacher) {
    std::cout << "Salary: " << teacher.salary << '\n';
}

int main() {
    Teacher t1(20000);
    showSalary(t1); // Ordinary function call; showSalary is not a Teacher member.
    return 0;
}
