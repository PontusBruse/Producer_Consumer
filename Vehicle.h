/**
 * @file Vehicle.h
 * @author Pontus Brusewitz (brusewitz_94@hotmail.com)
 * @brief Abstract base class for all vehicle types
 * @version 0.1
 * @date 2024-11-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
#include <memory>

class Vehicle
{
protected:
    static int next_id;
    int id;
    std::string model;

public:
    /**
     * @brief Construct a new Vehicle object
     * Automatically assigns a unique ID to the vehicle.
     * @param model Name of the vehicle model.
     */
    Vehicle(const std::string &model) : id(next_id++), model(model) {}

    // Virtual destructor for the base class to ensure proper cleanup in derived classes
    virtual ~Vehicle() = default;

    // Pure virtual function to print details about the vehicle.
    //*Must be implemented by derived classes.
    virtual void print() const = 0;

    int get_id() const { return id; }
};

int Vehicle::next_id = 1001; // initiate the first ID

class Car : public Vehicle
{
    int max_passengers;

public:
    /**
     * @brief Construct a new Car object
     *
     * @param model Name of the car model
     * @param passengers Maximum number of passengers
     */
    Car(const std::string &model, int passengers)
        : Vehicle(model), max_passengers(passengers) {}

    void print() const override
    {
        std::cout << "ID: " << id << "\nType: Car\nModel: " << model
                  << "\nMax. Passengers: " << max_passengers << "\n";
    }
};

class Truck : public Vehicle
{
    float max_load_weight;

public:
    /**
     * @brief Construct a new Truck object
     *
     * @param model Name of the truck model.
     * @param load_weight Maximum load capacity in kilograms.
     */
    Truck(const std::string &model, float load_weight)
        : Vehicle(model), max_load_weight(load_weight) {}

    void print() const override
    {
        std::cout << "ID: " << id << "\nType: Truck\nModel: " << model
                  << "\nMax. Load Weight: " << max_load_weight << " kg\n";
    }
};

#endif // VEHICLE_H
