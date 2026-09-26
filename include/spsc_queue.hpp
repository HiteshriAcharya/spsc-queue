// spsc_queue.hpp

#pragma once
#include <cstddef>

class RingBuffer{
private:
    std::size_t capacity;
    int* buffer;

    std::size_t head;
    std::size_t tail;

public:
    RingBuffer(std::size_t capacity) : capacity(capacity), 
                               buffer(new int[capacity]), 
                               head(0),
                               tail(0)
    {    
    }

    RingBuffer(const RingBuffer& other) = delete;
    RingBuffer& operator=(const RingBuffer& other) = delete;

    ~RingBuffer(){
        delete [] buffer;
    }

    bool empty() const{
        return head == tail;
    }

    bool full() const{
        return (tail + 1)%capacity == head;
    }

    bool push(int data){

        if(full()) return false;

        buffer[tail] = data;
        tail = (tail + 1)%capacity;

        return true;
    }

    bool pop(int& data){

        if(empty()) return false;

        data = buffer[head];
        head = (head + 1)%capacity;

        return true;
    }
};