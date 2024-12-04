# Producer-Consumer Program with Thread-Safe Circular Buffer

## Overview
This project implements a multithreaded **Producer-Consumer** system using a thread-safe circular buffer. The system models a warehouse where a producer manufactures vehicles (cars or trucks) and stores them in the warehouse, while multiple consumers retrieve and process these vehicles.  
The project demonstrates proficiency in:
- Thread synchronization using **mutexes** and **condition variables**.
-	Object-oriented programming with polymorphism and abstract base classes.
-	Efficient use of a fixed-size circular buffer.
-	Multithreaded programming with dynamic producer-consumer rates.
________________________________________

## Features
1.	**Vehicle Hierarchy**:
    - **Vehicle**: An abstract base class for all vehicle types.
    - **Car**: Inherits from Vehicle and includes a maximum passenger count.
    - **Truck**: Inherits from Vehicle and includes a maximum load capacity.
2.	**Thread-Safe Circular Buffer**:
    - Implemented with a fixed-size array, ensuring thread-safe access for both producers and consumers.
    - Dynamically handles scenarios where:
      - The producer is faster than the consumers.
      - The consumers are faster than the producer.
3.	**Dynamic Multithreading**:
    - One producer thread manufactures vehicles at random intervals.
    - Multiple consumer threads retrieve and print vehicle information to the terminal.
4.	**Scalability**:
    - The number of consumer threads and the warehouse capacity can be adjusted during compilation and runtime.
________________________________________

## How It Works
1. **Producer**:
    - Randomly manufactures either a car or a truck.
    - Waits if the warehouse is full, ensuring no data is lost.
2. **Consumers**:
    - Multiple threads retrieve vehicles from the warehouse.
    - Wait if the warehouse is empty until a new vehicle is produced.
3.	**Warehouse**:
    - A circular buffer implemented with an array, where elements are stored and retrieved in a FIFO manner.
    - Synchronization ensures thread safety using mutexes and condition variables.
________________________________________

## Usage
### Compilation ###
To compile the program, ensure the `CAPACITY` macro is defined (must be ≥8). Use the following command:  
```bash g++ -std=c++17 -pthread -DCAPACITY=10 main.cpp -o main```

### Execution
Run the compiled program with the desired number of consumers (at least 2):  
```bash./main <number_of_consumers>```

**Example**:  
```bash./main 3```
### Example Output  
```yaml
========== Dealer 1 ==========
ID: 1001
Type: Car
Model: Tesla
Max. Passengers: 5
========== Dealer 2 ==========
ID: 1002
Type: Truck
Model: Volvo
Max. Load Weight: 1500 kg
```
________________________________________
## Project Structure 
```plaintext
├── Warehouse.h          // Circular buffer implementation
├── Vehicle.h            // Abstract base class and derived classes (Car, Truck)
├── ProducerConsumer.cpp // Producer and consumer thread functions
├── main.cpp             // Program entry point
└── README.md            // Project description
```
________________________________________
## Contact  
Developed by Pontus Brusewitz
________________________________________
### Potential Enhancements
- Add logging for producer/consumer actions.
- Support for additional vehicle types.
- Implement a configurable production rate.

