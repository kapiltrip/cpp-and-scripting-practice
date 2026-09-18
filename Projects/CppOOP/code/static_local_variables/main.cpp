// A local static variable keeps its value between calls.
#include <iostream>

void trackVisits() {
    static int visits = 0; // One variable with static storage duration.
    int localVisits = 0;   // A fresh automatic variable on each call.
    ++visits;
    ++localVisits;
    std::cout << "Static visits: " << visits
              << ", automatic visits: " << localVisits << '\n';
}

int main() {
    trackVisits();
    trackVisits();
    trackVisits();
    return 0;
}
