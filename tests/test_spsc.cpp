#include <iostream>
#include <cassert>
#include <thread>
#include <spsc_queue.hpp>

void testBlockingFIFO(){

    RingBuffer q(10);

    std::thread producer ([&](){
        for(int i = 0; i <= 999; i++){
            q.pushWait(i);
        }
    });

    std::thread consumer ([&](){
        int data;

        for(int i = 0; i <= 999; i++){
            q.popWait(data);
            assert(data == i);
        }
    });

    producer.join();
    consumer.join();
}

void testConcurrentFIFO(){

    RingBuffer q(10);

    std::thread producer([&](){
        for(int i = 0; i <= 999; i++){
            while(!q.push(i)) {}
        }
    });

    std::thread consumer([&](){
        int data;

        for(int i = 0; i <= 999; i++){
            while(!q.pop(data)) {}
            assert(data == i);
        }
    });

    producer.join();
    consumer.join();

}

int main() {

    testConcurrentFIFO();
    testBlockingFIFO();

    std::cout << "All tests passed\n";
}