# Operator overloading

**Interview definition (summary):** Operator overloading defines how an existing C++ operator works with a user-defined type. The compiler selects an applicable operator function using the operands' types.

[Runnable source](main.cpp) | [Companion PDF, page 15](../../cpp-oop-notes.pdf#page=15)

A small Score type keeps this example close to student data. Each object holds points. Adding two Score objects produces another Score whose points equal the sum; the two operands retain their original values.

```cpp
class Score {
public:
    int points;
    Score(int startingPoints) : points(startingPoints) {}
    Score operator+(const Score& other) const {
        return Score(points + other.points);
    }
};
```

The name operator+ declares the function associated with +. In this member version, the left operand is the current object, and other refers to the right operand. The final const means this operation does not modify the left object's ordinary members. The parameter's const reference allows the right operand to be read without copying it into the parameter.

```cpp
Score first(20);
Score second(30);
Score total = first + second; // first.operator+(second)
```

| Part of the expression | Value or result |
| --- | --- |
| Left object's points | 20 |
| other.points | 30 |
| Built-in integer addition inside the function | 20 + 30 = 50 |
| Returned Score's points | 50 |
| Original operand values after addition | 20 and 30 |

The overloaded + works on Score operands. The addition inside its body still uses the built-in integer +. Keep an operator's meaning consistent with what readers expect: addition should combine values in a sensible way.

Overloading does not invent an operator or change its precedence. For example, C++ does not gain a new ** operator for powers, and + still has its usual precedence relative to *. This lesson uses only the small point values shown above.

Run from the repository root:

```powershell
& ./Projects/CppOOP/code/run.ps1 -Topic operator_overloading
```

**Source:** Stroustrup, [A Tour of C++, 3rd edition, section 6.4 Operator Overloading, PDF pages 126-127](../../../../book/A%20Tour%20of%20C%2B%2B%20-%203rd%20Edition.pdf#page=126). The book uses complex and Matrix; Score is the added lesson example.
