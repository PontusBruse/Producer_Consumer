#include "Warehouse.h"
#include "Vehicle.h"
#include <thread>
#include <random>
#include <chrono>

/**
 * @brief Produces vehicles (either Cars or Trucks) and adds them to the warehouse.
 *
 * @param warehouse
 */
void producer(Warehouse<std::unique_ptr<Vehicle>, CAPACITY> &warehouse)
{
    // Random number generator for selecting vehicle type and attributes
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> type_dist(0, 1);                // Randomly choose between Car (0) and Truck (1)
    std::uniform_int_distribution<> passenger_dist(2, 7);           // Random passenger capacity for Car
    std::uniform_real_distribution<> load_dist(500.0, 5000.0);      // Random load weight for Truck
    std::uniform_int_distribution<> producer_delay_dist(100, 1000); // Random delay (ms) between producing vehicles

    while (true)
    {
        if (type_dist(gen) == 0)
        {
            auto car = std::make_unique<Car>("Tesla", passenger_dist(gen));
            warehouse.add(std::move(car)); // Add the Car to the warehouse
        }
        else
        {
            auto truck = std::make_unique<Truck>("Volvo", load_dist(gen));
            warehouse.add(std::move(truck)); // Add the Truck to the warehouse
        }
        // Random delay before producing the next vehicle
        std::this_thread::sleep_for(std::chrono::milliseconds(producer_delay_dist(gen)));
    }
}
/**
 * @brief Consumes vehicles from the warehouse.
 *
 * @param warehouse Reference to the warehouse from where vehicles are consumed.
 * @param id Unique identifier for the consumer.
 */
void consumer(Warehouse<std::unique_ptr<Vehicle>, CAPACITY> &warehouse, int id)
{
    // Random number generator for determining delay between consuming vehicles
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> consumer_delay_dist(200, 1200); // Random delay (ms) between consuming vehicles

    while (true)
    {
        auto vehicle = warehouse.remove(); // Remove a vehicle from the warehouse
        std::cout << "========== Dealer " << id << " ==========\n";
        vehicle->print();
        std::this_thread::sleep_for(std::chrono::milliseconds(consumer_delay_dist(gen)));
    }
}
