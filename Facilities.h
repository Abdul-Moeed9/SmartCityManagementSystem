#pragma once
#include "Graph.h"
#include "HashTable.h"
#include "MinHeap.h"
#include "Utilities.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

// Facility structure
struct Facility {
	string id;
	string name;
	string type;
	string sector;
	double latitude;
	double longitude;

	Facility(string i, string n, string t, string s, double lat, double lon) {
		id = i;
		name = n;
		type = t;
		sector = s;
		latitude = lat;
		longitude = lon;
	}
};

class FacilitySystem {
private:
	HashTable facilityTable;
	HashTable facilityByType;
	Graph* cityGraph;
    Graph* facilityGraph;
	int facilityCount;

	const double MIN_LAT = 33.60;
	const double MAX_LAT = 33.80;
	const double MIN_LON = 72.90;
	const double MAX_LON = 73.20;

public:
	FacilitySystem(Graph* graph): facilityTable(100), facilityByType(100), cityGraph(graph){
		facilityCount = 0;
        facilityGraph = new Graph;
	}

	void displayAllFacilities() {

		cout << endl << "--- All Facilities ---" << endl;
		cout << "-----------------------------" << endl;
		int keycount = 0;
		string* keys = facilityTable.getAllKeys(keycount);

		if (keycount == 0) {
			cout << "No facilities available." << endl;
			delete[]keys;
			return;
		}
		for (int i = 0; i < keycount; i++) {
			Facility* facility = (Facility*)facilityTable.search(keys[i]);
			if (facility) {
				cout << endl << i + 1 << ". " << facility->name << endl;
				cout << "   Type: " << facility->type << endl;
				cout << "   Sector: " << facility->sector << endl;
				cout << "   Location: (" << StringUtils::toString(facility->latitude,6)
					<< ", " << StringUtils::toString(facility->longitude, 6) << ")" << endl;
			}
		}
		cout << "Total Facilities: " << keycount << endl;
		cout << "------------------------------" << endl;
		delete[]keys;
	}

    // Find nearest facility by type
    void findNearestFacility(double lat, double lon, string type) {
        
        if (!InputValidator::isValidLatitude(lat) || !InputValidator::isValidLongitude(lon)) {
            cout << endl << "Error: Invalid coordinates!" << endl;
            return;
        }

        if (!InputValidator::isValidString(type)) {
            cout << endl << "Error: Invalid facility type!" << endl;
            return;
        }

        LinkedList* facilities = (LinkedList*)facilityByType.search(type);

        if (!facilities || facilities->isEmpty()) {
            cout << endl << "No " << type << " facilities found!" << endl;
            return;
        }

        cout << endl << "========================================" << endl;
        cout << "    NEAREST " << type << " FINDER" << endl;
        cout << "========================================" << endl;
        cout << "Your Location: (" << lat << ", " << lon << ")" << endl;
        cout << "----------------------------------------" << endl;

        MinHeap nearestFacilities(100);

        Node* temp = facilities->getHead();
        while (temp) {
            Facility* facility = (Facility*)temp->data;
            if (facility) {
                double distance = MathUtils::calculateDistance(lat, lon, facility->latitude, facility->longitude);
                if (distance >= 0) {
                    nearestFacilities.insert(distance, (void*)facility);
                }
            }
            temp = temp->next;
        }

        cout << endl << "Nearest " << type << " (Top 5):" << endl;
        int count = 0;
        while (!nearestFacilities.isEmpty() && count < 5) {
            HeapNode node = nearestFacilities.extractMin();
            Facility* facility = (Facility*)node.data;
            if (facility) {
                cout << endl << (count + 1) << ". " << facility->name << endl;
                cout << "   Sector: " << facility->sector << endl;
                cout << "   Distance: " << StringUtils::toString(node.priority, 2) << " km" << endl;
                count++;
            }
        }
        cout << "========================================" << endl;
    }

    // Find nearest facility (any type)
    void findNearestAnyFacility(double lat, double lon) {

        if (!InputValidator::isValidLatitude(lat) || !InputValidator::isValidLongitude(lon)) {
            cout << endl << "Error: Invalid coordinates!" << endl;
            return;
        }

        cout << "========================================" << endl;
        cout << "    NEAREST FACILITY FINDER (All Types)" << endl;
        cout << "========================================" << endl;
        cout << "Your Location: (" << lat << ", " << lon << ")" << endl;
        cout << "----------------------------------------" << endl;

        MinHeap nearestFacilities(100);

        int keyCount = 0;
        string* keys = facilityTable.getAllKeys(keyCount);

        if (keyCount == 0) {
            cout << endl << "No facilities in system!" << endl;
            delete[] keys;
            return;
        }

        for (int i = 0; i < keyCount; i++) {
            Facility* facility = (Facility*)facilityTable.search(keys[i]);
            if (facility) {
                double distance = MathUtils::calculateDistance(lat, lon, facility->latitude, facility->longitude);
                if (distance >= 0) {
                    nearestFacilities.insert(distance, (void*)facility);
                }
            }
        }

        cout << endl << "Nearest Facilities (Top 5):" << endl;
        int count = 0;
        while (!nearestFacilities.isEmpty() && count < 5) {
            HeapNode node = nearestFacilities.extractMin();
            Facility* facility = (Facility*)node.data;
            if (facility) {
                cout << endl << (count + 1) << ". " << facility->name
                    << " (" << facility->type << ")" << endl;
                cout << "   Sector: " << facility->sector << endl;
                cout << "   Distance: " << StringUtils::toString(node.priority, 2) << " km" << endl;
                count++;
            }
        }
        cout << "========================================" << endl;
    }

    void addFacility(/*const string& csvFilename = "Data/facilities.csv"*/) {

        if (!cityGraph) {
            cout << "Error: City graph is not initialized yet" << endl;
            return;
        }

        string id, name, type, sector;
        double lat, lon;

        cout << "\n--- Add New Facility ---" << endl;
        cout << "Enter Facility ID: ";
        cin >> id;
        cin.ignore();

        if (!InputValidator::isValidString(id)) {
            cout << "Error: Invalid Facility ID!" << endl;
            return;
        }
        if (facilityTable.contains(id)) {
            cout << "Error: Facility with ID " << id << " already exists!" << endl;
            return;
        }

        cout << "Enter Facility Name: ";
        if (!SafeInput::getString(name)) {
            cout << "Error: Invalid name!" << endl;
            return;
        }

        cout << "Enter Facility Type (Mosque/Park/Water): ";
        if (!SafeInput::getString(type)) {
            cout << "Error: Invalid type!" << endl;
            return;
        }

        cout << "Enter Sector: ";
        if (!SafeInput::getString(sector)) {
            cout << "Error: Invalid sector!" << endl;
            return;
        }

        cout << "Enter Latitude (-90 to 90) or 0 for auto assign: ";
        if (!SafeInput::getDouble(lat, -90.0, 90.0)) {
            cout << "Invalid latitude! Auto-assigning." << endl;
            lat = randomDoubleInRange(MIN_LAT, MAX_LAT);
        }
        if (lat == 0) lat = randomDoubleInRange(MIN_LAT, MAX_LAT);

        cout << "Enter Longitude (-180 to 180) or 0 for auto assign: ";
        if (!SafeInput::getDouble(lon, -180.0, 180.0)) {
            cout << "Invalid longitude! Auto-assigning." << endl;
            lon = randomDoubleInRange(MIN_LON, MAX_LON);
        }
        if (lon == 0) lon = randomDoubleInRange(MIN_LON, MAX_LON);

        if (!SafeInput::getConfirmation("Add this facility?")) {
            cout << "Operation cancelled." << endl;
            return;
        }

        if (!cityGraph->hasFreeSlots()) {
            cout << "Error: Cannot have more buildings in the city" << endl;
            return;
        }
        if (cityGraph->containsLocationId(id)) {
            cout << "Error: City already has a building with ID " << id << endl;
            return;
        }
        if (cityGraph->hasNonStopAtLocation(lat, lon)) {
            cout << "Error: City already has a building at (" << lat << ", " << lon << ")" << endl;
            return;
        }
        if (!cityGraph->addLocation(id, name, lat, lon)) {
            cout << "Error: Facility could not be added to the city" << endl;
            return;
        }

        Facility* facility = new Facility(id, name, type, sector, lat, lon);
        facilityTable.insert(id, (void*)facility);

        LinkedList* typeList = (LinkedList*)facilityByType.search(type);
        if (!typeList) {
            typeList = new LinkedList();
            facilityByType.insert(type, (void*)typeList);
        }
        typeList->insert((void*)facility);

        facilityGraph->addNode(id, name, lat, lon);

        facilityCount++;
        cout << endl << "Facility added successfully!" << endl;
    }

    int getTotalFacilities() const { 
        return facilityCount; 
    }

    ~FacilitySystem() {
        if (facilityGraph) delete facilityGraph; facilityGraph = nullptr;
        cityGraph = nullptr;
    }
};