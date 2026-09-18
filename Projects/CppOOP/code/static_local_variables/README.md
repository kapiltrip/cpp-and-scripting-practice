# Local static variables

**Interview definition (summary):** A local static variable has block scope and static storage duration. The same variable retains its value between calls instead of being recreated as an ordinary automatic local variable is.

[Runnable source](main.cpp) | [Companion PDF, page 19](../../cpp-oop-notes.pdf#page=19)

Initialization gives the static object its starting state once. The function can run repeatedly, and the stored value can change on every call.

```cpp
void trackVisits() {
    static int visits = 0;
    int localVisits = 0;
    ++visits;
    ++localVisits;
    std::cout << "Static visits: " << visits
              << ", automatic visits: " << localVisits << '\n';
}
```

visits supplies one persistent counter. localVisits is a new automatic variable for each call and starts at zero each time. Both are incremented before printing. Their behavior is visible after three calls:

| Call | visits after increment | localVisits after increment |
| --- | --- | --- |
| First | 1 | 1 |
| Second | 2 | 1 |
| Third | 3 | 1 |

Scope and lifetime answer different questions. The name visits is usable inside its block, while its stored state survives the function's return. Keeping a name local does not require its object to have automatic storage duration.

Initialization establishes a starting state; incrementing the variable later is an ordinary update. A zero-initialized integer can receive its initial state during static initialization. When a local static needs dynamic initialization, that initialization is performed the first time execution reaches its declaration and succeeds. Subsequent calls use the initialized object.

The localVisits object is destroyed as the function exits. The static visits object persists for the program's execution. This int needs no visible destructor action; a local static class object with a nontrivial destructor would be cleaned up during normal program termination if it had been constructed.

This usage of static belongs to a function's local variable. A class static member has a different scope and sharing relationship, explained on the next page.

```powershell
& ./Projects/CppOOP/code/run.ps1 -Topic static_local_variables
```

**Sources:** Stroustrup, [The C++ Programming Language, 4th edition, section 12.1.8 Local Variables, PDF pages 443-444](../../../../book/The%20C%2B%2B%20Programming%20Language%20-%204th%20Edition.pdf#page=443); [C++ working draft, stmt.dcl](https://eel.is/c++draft/stmt.dcl).
