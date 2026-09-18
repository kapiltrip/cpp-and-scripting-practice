# Abstraction and abstract classes

**Interview definition (summary):** Abstraction presents an essential interface while keeping implementation details behind it. An abstract class cannot be instantiated because at least one of its virtual operations remains pure virtual.

[Runnable source](main.cpp) | [Companion PDF, page 18](../../cpp-oop-notes.pdf#page=18)

Your shape example can express the operation every drawable shape must provide. The caller needs to know that draw is available. The derived circle decides how drawing is implemented; this first version prints a message.

```cpp
class shape {
public:
    virtual void draw() const = 0;
    virtual ~shape() = default;
};
class circle : public shape {
public:
    void draw() const override { std::cout << "Drawing a circle\n"; }
};
```

The = 0 syntax declares draw pure virtual. Shape is abstract because its draw has no concrete overriding implementation in shape. Circle provides that override, so circle is a concrete type in this example. A derived class that leaves a required pure virtual function unimplemented remains abstract.

```cpp
void showShape(const shape& item) {
    item.draw();
}
circle c1;
showShape(c1); // prints Drawing a circle
```

showShape depends on shape's public interface. It can work with another derived shape that implements draw, without changing its own body. The actual circle can be a local object; using an abstract interface does not itself require new or heap allocation.

| Declaration or use | Result |
| --- | --- |
| shape s1 | Rejected: shape is abstract |
| circle c1 | Allowed: circle implements draw |
| const shape& item bound to c1 | Allowed: refers to an existing circle |
| item.draw() | Calls circle's implementation |

An abstract class may also have data members, constructors, and implemented member functions. It is commonly used as a base interface, but it need not contain only pure virtual declarations. Its base subobject exists inside a concrete derived object even though a standalone shape object cannot be created.

Abstraction is the broader design idea. Your earlier Teacher interface also offers abstraction through operations such as setSalary; an abstract class is one language tool for expressing an interface shared by derived types.

```powershell
& ./Projects/CppOOP/code/run.ps1 -Topic abstraction
```

**Sources:** Stroustrup, [A Tour of C++, 3rd edition, section 5.3 Abstract Types, PDF pages 99-100](../../../../book/A%20Tour%20of%20C%2B%2B%20-%203rd%20Edition.pdf#page=99); [C++ working draft, class.abstract](https://eel.is/c++draft/class.abstract).
