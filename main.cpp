/**
 * @file main.cpp
 * @author Pontus Brusewitz (brusewitz_94@hotmail.com)
 * @brief Entry point for the Producer/Consumer-program.
 * The program initializes a shared warehouse, starts a producer thread,
 * and multiple consumer threads that produces and consumes vehicles.
 * @version 0.1
 * @date 2024-11-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "ProducerConsumer.cpp"
#include <iostream>
#include <vector>
#include <thread>
/**
 * @brief Main function
 *
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments(argv[1] is expected to specify the number of consumers).
 * @return int Returns 0 on success; 1 on failure
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <number_of_consumers>\n";
        return 1;
    }

    int num_consumers = std::stoi(argv[1]);
    if (num_consumers < 2)
    {
        std::cerr << "Number of consumers must be at least 2.\n";
        return 1;
    }

    // Initialize the shared warehouse with the specified capacity
    Warehouse<std::unique_ptr<Vehicle>, CAPACITY> warehouse;

    // Start a producer thread to add vehicles to the warehouse
    std::thread producer_thread(producer, std::ref(warehouse));
    // Create and start consumer threads to consume vehicles from the warehouse
    std::vector<std::thread> consumer_threads;

    for (int i = 0; i < num_consumers; ++i)
    {
        consumer_threads.emplace_back(consumer, std::ref(warehouse), i + 1);
    }

    producer_thread.join();
    for (auto &t : consumer_threads)
    {
        t.join();
    }

    return 0;
}
