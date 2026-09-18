// Operator overloading gives + a meaning for the user-defined Score type.
#include <iostream>

class Score {
public:
    int points;
    Score(int startingPoints) : points(startingPoints) {}
    Score operator+(const Score& other) const {
        return Score(points + other.points);
    }
};

int main() {
    Score first(20);
    Score second(30);
    Score total = first + second; // Calls first.operator+(second).
    std::cout << "Total points: " << total.points << '\n';
    std::cout << "Original points: " << first.points << ", " << second.points << '\n';
    return 0;
}
