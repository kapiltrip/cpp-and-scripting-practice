# Friend classes

**Interview definition (summary):** A friend class is a class whose member functions are granted access to another class's private and protected members. The class holding those members declares the friendship.

[Runnable source](main.cpp) | [Companion PDF, page 22](../../cpp-oop-notes.pdf#page=22)

Teacher can grant the related Payroll class access to its private salary. This example keeps one small Payroll operation so the access relationship is easy to inspect.

```cpp
// Within Teacher, alongside its private salary:
friend class Payroll;

class Payroll {
public:
    void printSalary(const Teacher& teacher) const {
        std::cout << "Payroll salary: " << teacher.salary << '\n';
    }
};
```

Teacher's friend declaration authorizes the member functions of Payroll. The access check is therefore satisfied when Payroll::printSalary reads teacher.salary. Teacher's salary remains private for unrelated callers.

```cpp
Teacher t1(20000);
Payroll payroll;
payroll.printSalary(t1); // prints Payroll salary: 20000
```

payroll is the current object for the Payroll member function. Its this pointer refers to that Payroll object. The Teacher object is supplied separately through teacher, so Teacher access does not imply that Payroll contains or inherits a Teacher.

| Relationship | What it supplies |
| --- | --- |
| friend void showSalary(...) in Teacher | Access for that nominated function |
| friend class Payroll in Teacher | Access for Payroll's member functions |
| student : public person | A base/derived relationship and base subobject |
| An unrelated object merely holding Teacher& | A reference, with no friendship privilege |

Friendship does not create inheritance, insert a Payroll object into Teacher, or add a shared static member. These are separate language mechanisms. Use friendship to express a specific collaboration between related types.

The relationship is directional: Teacher grants Payroll access, and Payroll does not automatically grant Teacher access in return. Friendship is not inherited by Payroll's derived classes and does not automatically extend to Payroll's other friends. Choose the narrower friend-function form when only a single operation needs access.

```powershell
& ./Projects/CppOOP/code/run.ps1 -Topic friend_class
```

**Sources:** Stroustrup, [The C++ Programming Language, 4th edition, section 19.4 Friends, PDF page 774](../../../../book/The%20C%2B%2B%20Programming%20Language%20-%204th%20Edition.pdf#page=774); [C++ working draft, class.friend](https://eel.is/c++draft/class.friend).
