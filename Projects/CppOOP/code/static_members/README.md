# Static data members and member functions

**Interview definition (summary):** A static data member is shared by the class's objects instead of being stored separately in each object. A static member function belongs to the class and has no this pointer or implicit current object.

[Runnable source](main.cpp) | [Companion PDF, page 20](../../cpp-oop-notes.pdf#page=20)

Each student still has its own name. A shared totalCreated counter records calls to the named constructor in this program. The class's static getter reads that counter even before any student exists.

```cpp
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
int student::totalCreated = 0;
```

The declaration inside student identifies the shared member. The out-of-class definition supplies the storage and initial value for this non-inline static data member. The static keyword is not repeated in that definition. The :: operator qualifies the member name with its class.

```cpp
student::getTotalCreated(); // 0 before construction
student s1("Kapil");
student s2("Rahul");
student::getTotalCreated(); // 2 after the two constructor calls
```

| State in the verified program | s1.name | s2.name | Shared totalCreated |
| --- | --- | --- | --- |
| Before construction | No object yet | No object yet | 0 |
| After creating s1 | Kapil | No object yet | 1 |
| After creating s2 | Kapil | Rahul | 2 |

The constructor body runs for each newly constructed student in these declarations. The shared counter is initialized once, then updated by those calls. It records these constructions; this example does not decrement it at destruction or claim to count currently live objects.

getTotalCreated can access the private static counter because it is a student member. It cannot use name as an implicit current object's member: there is no this pointer. If a static function needs an individual student's name, it must be given an object, pointer, or reference explicitly.

Static member functions may be called many times. Static does not make them run only once, and a static member function cannot be virtual. Ordinary virtual dispatch operates on a particular object.

```powershell
& ./Projects/CppOOP/code/run.ps1 -Topic static_members
```

**Sources:** Stroustrup, [The C++ Programming Language, 4th edition, section 16.2.12 Static Members, PDF pages 638-639](../../../../book/The%20C%2B%2B%20Programming%20Language%20-%204th%20Edition.pdf#page=638); [C++ working draft, class.static](https://eel.is/c++draft/class.static).
