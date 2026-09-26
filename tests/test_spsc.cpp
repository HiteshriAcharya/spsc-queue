#include <iostream>
#include <spsc_queue.hpp>

#include <iostream>
#include "spsc_queue.hpp"

int main() {
    RingBuffer q(5);

    std::cout << std::boolalpha;

    // Empty initially
    std::cout << "Initially empty: " << q.empty() << '\n';

    // Normal push
    std::cout << "Push 1: " << q.push(1) << '\n';
    std::cout << "Push 2: " << q.push(2) << '\n';
    std::cout << "Push 3: " << q.push(3) << '\n';
    std::cout << "Push 4: " << q.push(4) << '\n';

    std::cout << "Push 5 when full: " << q.push(5) << '\n';

    int value;

    q.pop(value);
    std::cout << "Popped: " << value << '\n';

    q.pop(value);
    std::cout << "Popped: " << value << '\n';

    std::cout << "Push 5: " << q.push(5) << '\n';
    std::cout << "Push 6: " << q.push(6) << '\n';


    while (q.pop(value)) {
        std::cout << "Popped: " << value << '\n';
    }

    std::cout << "Finally empty: " << q.empty() << '\n';

    std::cout << "Pop from empty: " << q.pop(value) << '\n';

    return 0;
}