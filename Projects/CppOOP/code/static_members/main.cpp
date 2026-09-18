// Static data is shared by the class; a static function has no this pointer.
#include <iostream>
#include <string>

class student {
private:
    static int totalCreated;
public:
    std::string name;
    student(const std::string& studentName) : name(studentName) {
        ++totalCreated;
    }
    static int getTotalCreated() { return totalCreated; }
};

int student::totalCreated = 0; // Definition of the one shared counter.

int main() {
    std::cout << "Before construction: " << student::getTotalCreated() << '\n';
    student s1("Kapil");
    student s2("Rahul");
    std::cout << "Names: " << s1.name << ", " << s2.name << '\n';
    std::cout << "Total created: " << student::getTotalCreated() << '\n';
    return 0;
}
