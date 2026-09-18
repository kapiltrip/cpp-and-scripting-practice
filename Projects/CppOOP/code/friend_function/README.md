# Friend functions

**Interview definition (summary):** A friend function is a function granted access to a class's private and protected members by a friend declaration. A non-member friend remains an ordinary non-member function.

[Runnable source](main.cpp) | [Companion PDF, page 21](../../cpp-oop-notes.pdf#page=21)

Keep your Teacher salary private. In this separate example, Teacher permits exactly the named showSalary function to read that private member. Code outside the class does not gain general access to salary.

```cpp
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
```

The friend declaration is written inside the class granting access. The function's definition is outside that class. Its body can read teacher.salary because Teacher has named it as a friend. The const reference supplies the existing Teacher object and prevents this function from changing its ordinary members through that reference.

```cpp
Teacher t1(20000);
showSalary(t1); // prints Salary: 20000
```

This is an ordinary function call. showSalary has no implicit Teacher this pointer and is not called as t1.showSalary(). It obtains the particular object through its explicit teacher parameter.

| Function kind | Access to Teacher's private members | Implicit Teacher this |
| --- | --- | --- |
| Ordinary Teacher member | Yes | Yes |
| Static Teacher member | Yes | No |
| This non-member friend | Yes | No |
| Unrelated non-member | No | No |

Friendship controls who may use the representation; it does not make the representation public. A friend declaration may be placed in the private or public part of the granting class, with the same access effect. In the earlier encapsulation lesson, the setter/getter remains a simple public interface; friendship is a separate, explicitly granted relationship.

Friendship is neither automatically reciprocal nor transitive. If Teacher grants one function access, that function cannot pass the same privilege to unrelated functions just by calling them. The granting class determines its friends.

```powershell
& ./Projects/CppOOP/code/run.ps1 -Topic friend_function
```

**Sources:** Stroustrup, [The C++ Programming Language, 4th edition, section 19.4 Friends, PDF pages 772-773](../../../../book/The%20C%2B%2B%20Programming%20Language%20-%204th%20Edition.pdf#page=772); [C++ working draft, class.friend](https://eel.is/c++draft/class.friend).
