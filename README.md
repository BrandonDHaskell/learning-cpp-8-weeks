# Learning C++23 and CMake (3.31.5) in 8 weeks


## Week 1 - Setup & C++ Foundations

### Objectives:
* Establish a working C++ development environment (compiler + CMake + IDE)
* Build fundamental C++ skills including syntax, data types, control flow, and basic I/O

### Key Concepts:
* Syntax and Fundemental data types
* Basic I/O (`std::cin` and `std::cout`)
* Functions (overloading, default args, inline func)
* Namespace (When/Why)
* Control Flow: Conditionals (`if`/`else`, `switch`), loops (`for`, `while`, `range-based for`)

### Generic Tasks:
* Setup IDE (VS Code [Linux - Laptop, Windows - PC])
* Setup and config GCC compiler v14.2
* Setup and config CMake v3.31.5
* Setup and config Git v2.48.1

### Coding Tasks:
* Create a simple CMake project
    * Minimum `CMakeLists.txt` structure
* Hello World app:
    * Using C++23 standard
    * Using CMake to compile
    * Using `std::cin` and `std::cout`
    * Takes console input to output name and hello text
* Even & Odd app (Optional):
    * Using C++23 standard
    * Using CMake to compile
    * Using basic I/O and Flow controls
    * Console program that prompts the user for how many integers to enter
    * Reads in each integers and stores them in a `std::vector<int>`
    * Prints how many even and odd numbers were entered
* Guess the number app (Optional):
    * Using C++23 standard
    * Using CMake to compile
    * Using basic I/O and Flow controls
    * Console program that generates a random number between 1 and 10 and prompts the user with High or Low each time they guess


## Week 2 - OOP & Basic STL

### Objectives:
* Learn how to design programs using classes, inheritance, and polymorphism in C++
* Explore basic STL containers and algorithms
* Improve CMake project organization

### Key Concepts:
* OOP
    * Classes & Structs
    * Constructors & Destructors
    * Encapsulation
    * Inheritance
    * Polymorphism
* Standard Template Library (STL)
    * Containers
    * Iterators & Algorithms
* CMake Project Structure
    * Organizing Source Files
    * Intro to Targets (dirs and libs)

### Coding Tasks:
* InventoryManager app:
    * Have at least 1 default and parameterized constructor
    * Have at least 1 virtual destructor in the base class of polymorphic classes
    * Break out header files from source files
    * Bonus: use a vector of pointers
    * Bonus: use a map keyed on `id` for quick lookups
    * Create a `Product` base class with attr (id, name, price, etc.)
    * Create a Derived class: `Perishable` with attr (expirationDate)
    * Store all products in `std::vector<Product>`
    * Use `std::sort` or `std::transform` to manipulate product lists
    * Create a `printInfo()` function that prints product info (overriden in ea derived Product)
* Employee Roster app (optional):
    * Have at least 1 default and parameterized constructor
    * Have at least 1 virtual destructor in the base class of polymorphic classes
    * Break out header files from source files
    * Bonus: use a vector of pointers
    * Bonus: use a map keyed on `id` for quick lookups
    * Create an `Employee` base class with attr (employeeId, name)
    * Create a Derived classes: `hourly` and `salary` (salary, hourly rate, hours worked, etc.)
    * Store all products in `std::vector<Employee>`
    * Use `std::sort` or `std::transform` to manipulate product lists
    * Create a `calculatPay()` function that prints product info (overriden in ea derived Employee)


## Week 3 - Memory Management & RAII

### Objectives:
* Master modern C++ memory management techniques (smart pointers, RAII, move semantics)
* Deepen understanding of CMake’s handling of libraries and build configurations

### Key Concepts:
* Memory Management & RAII
    * Stack vs. Heap
    * Smart Pointers (when and how to use)
    * Resource Acquisition Is Initialization (RAII)
* Intermediate CMake
    * Handling Libraries
        * Statically vs Dynamically linked libraries
        * `add_library()` usage
        * External libraries (`find_package()` for additional libs)
    * Build Types & Configs: Debug v Release and setting flags (`-Wall -Wextra`, etc.)
* C++ Patterns
    * Rule of Three/Five/Zero
    * Move Semantics

### Coding Tasks:
* In-Memory Cache System
    * Implement a `CacheManager` class that allocates internal structures in its contructor and frees them in its destructor
    * Store records in `std::vector<std::unique_ptr<Record>>` and provide methods to insert, retrieve, and remove records (ensuing no memory leaks)
    * Possibly use `std::shared_ptr` for shared caching references with multiple owners
    * CMake: create a lib target and create an executable that links to `DatabaseLib`
    * (Optional) CMake: Wrap your lib in either a static or shared library and toggle between them in the build
    * CMake: Integrate an external library into this project
        * Use `find_package(nlohmann_json REQUIRED) or fetch it
    * CMake: Add custom compiler flags in Debug (like -DDEBUG) and in Release (like `-O3`), and `assert` or a debug log that is disabled in release builds
* Sound Resource Loader (optional)
    * Implement a small console (or minimal GUI) program that loads an image/sound and does something with it (print basic info, dimensions, or play a short sound)
    * Program should open a file and loads data, then frees it in the destructor (Ex. [PortAudio](https://www.portaudio.com/))
    * use `std::unique_ptr<SoundClip>`
    * CMake: Integrate an external library into this project [PortAudio](https://www.portaudio.com/)
        * Use `find_package()` or `FetchContent`
    * (Optional) Compile with different build types to see how optimization affects load speed


## Week 4 - Templates and Testing

### Objectives:
* Understand the fundamentals of function templates, class templates, and variadic templates
* Introduce automated testing frameworks and integration with CMake

### Key Concepts:
* Template fundamentals
    * Function
    * Class
    * Variadic
* Testing & Continuous Integration
    * Unit Testing (Ex. Google Test, or Catch2)
    * CMake Integration
        * Write and link a test target (`add_executable(testFoo ...)`, add_test(...)`)

### Coding Tasks
* Implement a Basic `printf()`-like formatting function that takes in a string with markers and a list of arguments and prints the formatted string to the screen
    * Use a Variadic template as part of the implementation
    * Parse the string and substitute arguements
    * Consider wrapping [fmt](https://github.com/fmtlib/fmt) in this project
    * Implement a test to test the output
        * Include edge cases (Ex. no args, too many args)
    * Use CMake and implement a test with CMake
* 
* (Optional) set up a **GitHub Actions** workflow that: 1) checks your code, 2) runs CMake, 3) builds, then, 4) runs tests


## Week 5 - C++23 Features

### Objectives
* Explore C++23 specific items including `std::ranges`, `std::format`, `std::expected`, and modules
* Learn how to use modules in CMake

### Key Concepts
* New Utility functions: `std::ranges`, `std::format`, `constexpr`, `std::expected`
* Modules
    * Difference from headers
    * Creating and importing Modules with CMake
    * Advantages / Disadvantages

### Coding Tasks
* Text Processing app
    * Create a mini text-processing utility that reads a file (or standard input) and filters or transforms lines using C++23 `std::ranges`
    * Use `std::ranges::filter_view` or `std::ranges::transform_view` to filter lines or transform text
    * Format the output lines with a prefix or index number (Ex. `std::format("Line {}] {}", lineNumber, lineContents)`)
    * Implement code in C++ Module
    * CMake use compiler flags: `-fmodules-ts` and `-std=c++23`
    * Use `std::expected` to return 
    * (Optional) Use `std::ranges::views::split` or `std::ranges::join`
    * Example starter module code:
        * ```c++
            export module TextProcessor;

            import <string>;
            import <vector>;

            export class TextProcessor {
                public:
                    TextProcessor() = default;
                    std::vector<std::string> filterAndTransform(
                            const std::vector<std::string>& lines);
                private:
                    // ...
            };
        ```
* (Optional) Config Loader app
    * Build a configuration loader that reads key-value pairs from a file
    * Use `std::expected` to return an error if parsing fails
        * Use `std::format` to produce dynamic error messaging
            * ex. `std::format("Error: Cannot open file '{}'", filename)`
    * Implement code in C++ Module
    * CMake library targets for the module and executable that uses it


## Week 6 - Concurrency & Parallelism

### Objectives:
* Gain a working knowledge of multithreading (threads, mutexes, futures *[possibly corroutines]*)
* Learn how to create and manage parallel tasks
* Understand concurrency-related CMake considerations


### Key Concepts
* Multithreading
    * Threads: `std:thread`, launching, joining/dtaching
    * Synchronoization: Mutexes & locks
    * Thread-Safe Data Structures
* Concurrency Tools
    * `std::async`, `std::future`, `std::promise`
    * Coroutines?
* CMake Concurrancy

### Coding Tasks
* Parallel Sort or Search app
    * Create an app that searches a larged data list or mergesorts a largelist
    * Thread Splitting:
        * Mergesort: if the array is large, spawn threads to sort halves concurrently
        * Search: implement a parallel BFS/DFS for searching a tree or graph
    * Synchronoization:
        * Use `std::barrier` or `join()` to merge data
    * (Optional) Use coroutines
    * CMake: Setup project with threading library linking as needed
* (Optional) Parallel File Parser
    * Create a parallel file-parsing tool (e.g., analyzing a large log file). Split the file into chunks and process them concurrently in multiple threads
    * Create a global data structure for counting occurances certain words or errors, and protect it with a mutex or some thread-safe design
        * Ex. `std::map<std::string, int>`
    * CMake: Setup project with threading library linking as needed
    

## Week 7 - Advanced Topics & Best Practices

### Objectives:
* Dive deeper into the following:
    * Advanced STL usage
    * Design patterns (Factory, Strategy, Observer, etc.)
    * Error handling strategies
    * C++ performance optimizations
* Solidify advanced CMake practices (packaging, cross-platform builds)

### Key Concepts
* Advanced STL & Best Practices
    * `<algorithm>`, `<functional>`, `<numeric>`
    * Design Patterns: Singleton, Factory, Strategy, Observer
    * Error Handling best practices (when to throw vs return an error)
* Memory & Performance optimization
    * Profiling: `valigrind`, `gprof`, VS Profiler, etc.
    * Reducing copies, moves etc.
* Deep Dive into CMake
    * CMake Best Proactices
        * `FetchContent`, grouping targets, installing targets, and packaging (CPack)
        * Building for multiple platforms
* Review [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) and [Sleeping Barber problem](https://en.wikipedia.org/wiki/Sleeping_barber_problem)

### Coding Tasks
* Task Schedulet app
    * Create a task scheduler that receives tasks (jobs) and distributes them among worker threads. Incorporate advanced STL for scheduling logic, one or more design patterns, robust error handling, and a final CMake package
    * Create a pool of worker threads
    * Create a concurent queue of tasks protected by a mutex + condition variable
        * Use more sophisticated scheduling (priority, round-robin, etc.)
    * Create a **TaskFactory** to generate different types of tasks (I/O, CPU, etc.)
    * Use `<functional>` to store tasks as `std::function`
    * Use `<algorithm>` to reorder tasks or filter them
    * Implement Error handling for task failures
    * Profile the schedule to determine performance
    * (Optional) Break scheduler and tasks into separate libraries
    * (Optional) Use `<numeric>` to gather metrics (Ex. total tasks, avg wait time, etc.)
    * (Optional) Implement different scheduling algorithms (FIFO, priority-based, least-loaded) and switch at runtime



## Week 8 - Final Project &  Review

### Objectives:
* Consolidate all knowledge into a final project that demonstrates mastery of:
    * Modern C++ features
    * Memory management
    * Concurrency
    * Testing
    * CMake builds

### Project(s)
* Finalize Pet Shop project
* Implement Analytics Engine