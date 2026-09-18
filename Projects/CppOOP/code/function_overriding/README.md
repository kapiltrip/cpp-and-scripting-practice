# Function overriding

**Interview definition (summary):** Function overriding provides a derived-class implementation of a virtual base-class function. A virtual call can select that implementation through the base interface.

[Runnable source](main.cpp) | [Companion PDF, page 16](../../cpp-oop-notes.pdf#page=16)

Your parent and child classes make the relationship clear. Here getinfo is declared virtual in parent and overridden in child. Each function below prints a class-specific message.

```cpp
class parent {
public:
    virtual void getinfo() const { std::cout << "parent class\n"; }
    virtual ~parent() = default;
};
class child : public parent {
public:
    void getinfo() const override { std::cout << "child class\n"; }
};
```

The derived function has the same name, parameter list, and const qualification as the base function. Its void return type also matches. The override specifier asks the compiler to check that this declaration really overrides a virtual base function. It is useful even though a valid override remains virtual without repeating the virtual keyword.

```cpp
child c1;
parent& p1 = c1;
p1.getinfo(); // prints child class
```

p1 is a parent reference bound to the parent portion of c1. No second object is constructed. The virtual call reaches child's implementation because the complete object is a child.

| Declaration change | Meaning |
| --- | --- |
| Matching getinfo() const override | Overrides the virtual base function |
| getinfo(int) without override | Different parameters; hides the base name |
| getinfo() without const and without override | Different qualification; does not override this const function |
| Either mismatch marked override | Compiler rejects the declaration |

Overloading selects among different parameter lists. Overriding supplies an implementation along an inheritance relationship. A same-name function in a derived class hides a non-virtual base function; that alone does not create virtual dispatch.

The defaulted virtual destructor gives this base an appropriate destructor interface for deleting a derived object through a base pointer. This program uses a local child object and a reference, with no explicit dynamic allocation.

Run from the repository root:

```powershell
& ./Projects/CppOOP/code/run.ps1 -Topic function_overriding
```

**Sources:** Stroustrup, [A Tour of C++, 3rd edition, section 5.3 Abstract Types, PDF page 100](../../../../book/A%20Tour%20of%20C%2B%2B%20-%203rd%20Edition.pdf#page=100), for the override example; [C++ working draft, class.virtual](https://eel.is/c++draft/class.virtual), for overriding and signature checks.
