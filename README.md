Smart City Management System

Smart City Management System is a C++ console based project for managing different city sectors from one menu driven application. It uses common data structures such as graphs, linked lists, queues, stacks, heaps, and hash tables to store, search, and process city related data.

Project Overview

The system provides separate modules for important city services. Each module allows the user to view records, search data, add new records, and perform operations related to that sector.

Main Sectors

Medical Sector
Manage hospitals, pharmacies, doctors, patients, medicines, emergency beds, and nearest hospital searches.

Facilities Sector
Manage public facilities and find nearest facilities by type or by location.

Commercial Sector
Manage malls, products, product categories, and nearest mall searches.

Airport Sector
Manage airports, flights, and shortest flight routes.

Railway Sector
Manage railway stations, journeys, and nearest station searches.

Education Sector
Manage schools, students, faculty, school searches, subject searches, and nearest school searches.

Population Sector
Manage houses, families, citizens, population reports, and housing statistics.

Transport Sector
Manage bus stops, routes, buses, passenger queues, shortest paths, travel history, and journey simulation.

Data Structures Used

Graph for routes, distances, and shortest path operations.

Hash table for fast searching of records.

Linked list for dynamic record storage.

Queue for passenger management.

Stack for travel history.

Heap for priority based operations such as emergency bed availability.

Data Files

The project reads sample data from the Data folder.

facilities.csv
hospitals.csv
malls.csv
pharmacies.csv
population.csv
products.csv
schools.csv
stops.csv

How To Run

Open the project in Visual Studio.

Open Project1.sln.

Build the solution.

Run the project from Visual Studio.

You can also compile the code manually with a C++ compiler that supports the features used in the project.

Main File

The program starts from main.cpp.

main.cpp creates a SmartCity object and calls its run function.

Project Structure

main.cpp contains the program entry point.

SmartCity.h contains the main menu and connects all sectors.

Data contains CSV files used by the system.

Sector header files contain the logic for each city module.

Utility and data structure files contain reusable structures and helper code.

Notes

This project is designed for a DSA course and focuses on applying data structures in a practical smart city management scenario.

Generated build files and user specific Visual Studio files are ignored through .gitignore.
