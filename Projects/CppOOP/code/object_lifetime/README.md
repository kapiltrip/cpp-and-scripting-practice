# Object lifetime and storage duration

**Interview definition (summary):** Object lifetime is the period in which an object exists as that object. Storage duration describes how long its storage persists. For the student class here, lifetime begins after initialization completes and ends when its destructor call starts.

[Runnable source](main.cpp) | [Companion PDF, page 23](../../cpp-oop-notes.pdf#page=23)

Your constructor establishes name and your destructor prints a cleanup message. Follow the braces and function returns to identify when each local student finishes its lifetime. The runnable example uses automatic objects, with no explicit new or delete.

```cpp
student s1("Kapil");
{
    student s2("Rahul");
    std::cout << "Leaving inner block\n";
} // s2 is destroyed; s1 still exists
visit(); // its local visitor is destroyed when visit returns
std::cout << "Still in main: " << s1.name << '\n';
```

visit creates a local student named Visitor, prints Returning from visit, and returns. The program's destructor messages therefore follow the objects' actual blocks rather than one shared end point.

| Object | Where it is created | Destructor body runs |
| --- | --- | --- |
| s2, named Rahul | Inner block in main | At that block's exit |
| visitor, named Visitor | visit function | As visit returns |
| s1, named Kapil | Outer block in main | As main returns |

Construction of s1 happens first, then s2, then visitor after the inner block has ended. Their lifetimes overlap only where those objects are still alive. After s2's block exits, s1's name can still be printed; the program never uses s2 after its destruction.

| Storage duration | What determines storage persistence |
| --- | --- |
| Automatic | The relevant block's execution |
| Static | Program duration, including the earlier local static counter |
| Thread | Duration of the associated thread |
| Dynamic | Allocation and release, such as new and matching delete |

Scope governs where a name can be used. The static counter's name has block scope, yet its state persists between calls. A dynamically created student can also outlive the local pointer that originally named its address; ownership must determine who eventually deletes it.

Calling a function through a pointer or reference uses an existing object. Those aliases do not by themselves extend its lifetime. A virtual function changes which implementation is selected; it does not keep an otherwise destroyed object alive.

```powershell
& ./Projects/CppOOP/code/run.ps1 -Topic object_lifetime
```

**Sources:** Stroustrup, [A Tour of C++, 3rd edition, section 1.5 Scope and Lifetime, PDF page 30](../../../../book/A%20Tour%20of%20C%2B%2B%20-%203rd%20Edition.pdf#page=30); [C++ working draft, basic.life](https://eel.is/c++draft/basic.life), for precise lifetime boundaries.
