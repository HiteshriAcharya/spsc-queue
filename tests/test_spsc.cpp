#include <iostream>
#include <cassert>
#include <spsc_queue.hpp>

int main() {

    RingBuffer q(5);

    assert(q.empty());

    assert(q.push(1));
    assert(q.push(2));
    assert(q.push(3));
    assert(q.push(4));

    assert(q.full());
    assert(!q.push(5));

    int value;

    assert(q.pop(value));
    assert(value == 1);

    assert(q.pop(value));
    assert(value == 2);


    assert(q.push(5));
    assert(q.push(6));


    assert(q.pop(value));
    assert(value == 3);

    assert(q.pop(value));
    assert(value == 4);

    assert(q.pop(value));
    assert(value == 5);

    assert(q.pop(value));
    assert(value == 6);

    assert(q.empty());

    assert(!q.pop(value));

    std::cout << "All tests passed\n";

}