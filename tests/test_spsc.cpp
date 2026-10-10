#include <iostream>
#include <cassert>
#include <thread>
#include <string>
#include <spsc_queue.hpp>

void testBlockingWithStringFIFO(){

    RingBuffer<std::string> q(10);

    std::thread producer ([&](){
        for(int i = 0; i <= 999; i++){
            q.pushWait("hello" + std::to_string(i));
        }
    });

    std::thread consumer ([&](){

        std::string data;

        for(int i = 0; i <= 999; i++){
            q.popWait(data);
            assert(data == "hello" + std::to_string(i));
        }
    });

    producer.join();
    consumer.join();
}

void testBlockingFIFO(){

    RingBuffer<int> q(10);

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

    RingBuffer<int> q(10);

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
    testBlockingWithStringFIFO();

    std::cout << "All tests passed\n";
}