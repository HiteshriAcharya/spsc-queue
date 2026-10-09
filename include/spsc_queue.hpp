// spsc_queue.hpp
#pragma once

#include <stdexcept>
#include <mutex>
#include <memory>
#include <cstddef>
#include <condition_variable>

class RingBuffer{
private:

    std::size_t capacity_;
    std::unique_ptr<int[]> buffer_;

    std::size_t head_;
    std::size_t tail_;

    std::mutex m_;

    std::condition_variable not_full_;
    std::condition_variable not_empty_;

    bool empty() const{
        return head_ == tail_;
    }

    bool full() const{
        return (tail_ + 1)%capacity_ == head_;
    }

public:
    explicit RingBuffer(std::size_t capacity) : capacity_(capacity), 
                               buffer_(nullptr), 
                               head_(0),
                               tail_(0)
    {
        if(capacity_ <= 1){
            throw std::invalid_argument("RingBuffer capacity_ must be at least 2");
        }

        buffer_ = std::make_unique<int[]>(capacity_);
    }

    RingBuffer(const RingBuffer& other) = delete;
    RingBuffer& operator=(const RingBuffer& other) = delete;

    RingBuffer(RingBuffer&& other) = delete;
    RingBuffer& operator=(RingBuffer&& other) = delete;

    bool push(int data){

         std::lock_guard<std::mutex> l(m_);

        if(full())
            return false;

        buffer_[tail_] = data;
        tail_ = (tail_ + 1) % capacity_;

        return true;    
    }

    bool pop(int& data){

        std::lock_guard<std::mutex> l(m_);

        if(empty())
            return false;

        data = buffer_[head_];
        head_ = (head_ + 1) % capacity_;
        return true;
    }

    bool pushWait(int data){

        std::unique_lock<std::mutex> ul(m_);
        not_full_.wait(ul, [&](){
            return !full();
        });

        buffer_[tail_] = data;
        tail_ = (tail_ + 1) % capacity_;

        ul.unlock();
        not_empty_.notify_one();

        return true;
    }

    bool popWait(int& data){

        std::unique_lock<std::mutex> ul(m_);
        not_empty_.wait(ul, [&](){
            return !empty();
        });

        data = buffer_[head_];
        head_ = (head_ + 1) % capacity_;

        ul.unlock();
        not_full_.notify_one();

        return true;
    }
};