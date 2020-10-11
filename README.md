## Identifying Information: 
1. AJ Keenan
1. Student ID: 2316808
1. akeenan@chapman.edu
1. CPSC 350-02
1. Assignment: Assignment 2

## Application Purpose
The purpose of this application is to run the game of life simulation. It will start by asking the user if they wish to input the cell data for the game of life simulation using either a file in a certain format or using numbers they input. Afterwards, it will ask if the user wants to get a file output with the results of the simulation. Next, if the user requested to use numbers to setup the grid, the user will put in that data (height of grid, width of grid, and population density of grid). If the user requested to use the file, it will be asked to input the file path instead. Once that is done, the user will put in the name of the output file (should they want one). Then, the user will be asked if they want the simulation to run in classic mode (cell neighbors are bound by the cell walls), doughnut mode (cell neighbors include those wrapped around on the otherside of the grid), or mirror mode (cell reflections off the edge of the cell array count as neighbors). Finally, the user will be asked if they wish to pause between generations. Once all of that is done, the original grid is displayed back to the user and they press enter to start the program. The simulation will then run (with pauses in between if the user requested) until the grid is empty, it stabilizes, or the user quits because the grid will never be either. Each grid will be displayed to the user and output to the file (should the user have requested it). When the simulation ends, the user is told so. When they acknowledge the simulation is done, the program will close.

## Source Files 
1. Cell.cpp
1. Cell.h
1. ClassicMode.cpp
1. ClassicMode.h
1. DoughnutMode.cpp
1. DoughnutMode.h
1. FileIO.cpp
1. FileIO.h
1. GameMode.cpp
1. GameMode.h
1. Grid.cpp
1. Grid.h
1. main.cpp
1. MirrorMode.cpp
1. MirrorMode.h
1. Simulation.cpp
1. Simulation.h

## Known Errors: 
   None

## References
1. Class Notes
1. Stack Overflow (rand() returns the same number each time the program is run, Press Enter to Continue, Deleting a dynamically allocated 2D array [duplicate], How to allocate a 2D array of pointers in C++, Get The Object Pointer Is Pointing To, How to generate dynamic empty 2D array without default constructor in C++, C++ Dereferencing pointer to object [closed], what's the difference between object * x and object& x in c++ [duplicate], Get The Object Pointer Is Pointing To, Declaring an object before initializing it in c++, reusing a stringstream to parse values from multiple strings in succession, How to determine if a string is a number with C++?, Go back one line on a text file C++)
1. GeeksforGeeks (Virtual Destructor, How to initialize Array of objects with parameterized constructors in C++, How to create a dynamic 2D array inside a class in C++, Converting Strings to Numbers in C/C++)
1. Cplusplus.com (srand, Polymorphism, deque, shared_ptr::get, Creating 2D array in header, isdigit, stod, string::compare, ofstream)
1. Tutorials Point (Pure Virtual Functions and Abstract Classes in C++, Interfaces in C++ (Abstract Classes), How do I find the length of an array in C/C++?)
1. Study Tonight (Order of Constructor Call with Inheritance in C++)
1. LearnCpp.com (11.4 - Constructors and initialization of derived classes)
1. Cppreference.com (Abstract Classes)
1. Quora (How can I check if a std: :string is a floating point number (in C++))
1. w3schools.com (C++ String Length)


## Compilation Instructions
Use the "make all" command, courtesy of the included MAKEFILE, to compile all source files. To run the program, run the assignment2.exe program from any linux terminal, such as in docker.


