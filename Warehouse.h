/**
 * @file Warehouse.h
 * @author Pontus Brusewitz (brusewitz_94@hotmail.com)
 * @brief A thread-safe circular buffer implemented with a fixed-size array.
 * @tparam T The type of elements stored in the buffer.
 * @tparam Capacity The maximum capacity of the buffer, which must be defined during compilation.
 * @version 0.1
 * @date 2024-11-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <mutex>
#include <condition_variable>
#include <array>
#include <cassert>

#ifndef CAPACITY
#error "CAPACITY must be defined during compilation using -DCAPACITY=<value>"
#endif

static_assert(CAPACITY >= 8, "CAPACITY must be at least 8");

template <typename T, size_t Capacity>

class Warehouse
{
    T buffer[Capacity];                          // Array for circular buffer
    size_t head{0}, tail{0}, count{0};           // Indexes and counter
    std::mutex mtx;                              // Mutex for synchronization
    std::condition_variable not_full, not_empty; // Synchronization mechanism

public:
    // Constructor and copy prevention
    Warehouse() = default;
    Warehouse(const Warehouse &) = delete;
    Warehouse &operator=(const Warehouse &) = delete;

    /**
     * @brief Adds an item to the warehouse. If the buffer is full, the method waits until space becomes available.
     *
     * @param item The item that should be implemented to the buffer
     */
    void add(T item)
    {
        std::unique_lock<std::mutex> lock(mtx);
        // If buffer is full, this thread is locked untill buffer isn't full
        not_full.wait(lock, [this]()
                      { return count < Capacity; });

        // Move tail and add item
        buffer[tail] = std::move(item);
        tail = (tail + 1) % Capacity;
        ++count;

        not_empty.notify_one();
    }

    /**
     * @brief Removes an item from the warehouse. If the buffer is empty, the method waits until an item becomes available.
     *
     * @return T is the item removed from the warehouse buffer.
     */
    T remove()
    {
        std::unique_lock<std::mutex> lock(mtx);
        // If buffer is empty, this thread is locked untill buffer isn't empty
        not_empty.wait(lock, [this]()
                       { return count > 0; });

        // Save item, and move head
        T item = std::move(buffer[head]);
        head = (head + 1) % Capacity;
        --count;

        not_full.notify_one();
        return item;
    }
};

#endif // WAREHOUSE_H
