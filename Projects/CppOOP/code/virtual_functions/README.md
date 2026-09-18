# Virtual functions and runtime polymorphism

**Interview definition (summary):** Runtime polymorphism lets a virtual call through a base interface select the implementation belonging to the actual derived object. A virtual function establishes that interface; overriding supplies the derived behavior.

[Runnable source](main.cpp) | [Companion PDF, page 17](../../cpp-oop-notes.pdf#page=17)

Your original parent has a non-virtual getinfo and a virtual hello. Child supplies functions with both names. Its getinfo hides the base function; its hello overrides the virtual base function. The runnable example preserves this distinction.

```cpp
// Within parent:
void getinfo() const { std::cout << "parent class\n"; }
virtual void hello() const { std::cout << "hello from parent\n"; }

// Within child:
void getinfo() const { std::cout << "child class\n"; }
void hello() const override { std::cout << "hello from child\n"; }
```

Calling c1.hello directly prints hello from child. A base pointer or reference makes the reason for virtual behavior easier to observe:

```cpp
child c1;
parent* p1 = &c1;
p1->getinfo(); // parent class: non-virtual
p1->hello();   // hello from child: virtual
parent& ref = c1;
ref.hello();   // hello from child
```

The declared pointer type is parent*, while the complete object it denotes is a child. These are the static type and dynamic type relevant to the calls. The non-virtual call uses the parent interface's function. The virtual call follows the actual object's overriding implementation.

| Call in the verified program | Output |
| --- | --- |
| c1.getinfo() | child class |
| c1.hello() | hello from child |
| p1->getinfo() or ref.getinfo() | parent class |
| p1->hello() or ref.hello() | hello from child |

The pointer and reference both refer to the existing c1; neither makes a copy. A by-value parent copy would be a separate parent object and would lose the child-specific portion. Use the reference/pointer form shown here when studying dispatch.

The book's diagram shows a typical implementation using a virtual-function table. C++ specifies which function a virtual call selects; that particular table layout is an implementation technique. Keep this behavioral rule separate from compile-time selection of function or operator overloads.

```powershell
& ./Projects/CppOOP/code/run.ps1 -Topic virtual_functions
```

**Sources:** Stroustrup, [A Tour of C++, 3rd edition, section 5.4 Virtual Functions, PDF page 103](../../../../book/A%20Tour%20of%20C%2B%2B%20-%203rd%20Edition.pdf#page=103); [C++ working draft, class.virtual](https://eel.is/c++draft/class.virtual).
