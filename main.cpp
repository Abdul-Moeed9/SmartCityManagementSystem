//#include <iostream>
//#include <iostream>
//#include "Medical.h"
//#include "Utilities.h"
//#include "Facilities.h"
//#include <cstdlib>
//#include <ctime>
//using namespace std;
//
//void displayFacilityMenu() {
//    cout << "\n--- Facility Sector ---<<endl" << endl;
//    cout << "1. Display All Facilities" << endl;
//    cout << "2. Add Facility" << endl;
//    cout << "3.  Find Nearest Facility By Type" << endl;
//    cout << "4.   Find Nearest Facility (Any Type)" << endl;
//    cout << "5.   Exit" << endl;
//    cout << "Enter your Choice(1-5)" << endl;
//}
//
//void handleFacilitiesModule(FacilitySystem& facilities) {
//    int choice;
//    while (true) {
//        displayFacilityMenu();
//        if (!SafeInput::getInt(choice, 1, 5)) { cout << "Invalid input!\n"; continue; }
//        switch (choice) {
//        case 1:
//            facilities.displayAllFacilities();
//            break;
//        case 2:
//            facilities.addFacility();
//            break;
//        case 3: {
//            string type;
//            double lat, lon;
//            cout << "Enter facility type (e.g., Mosque, Park, Water): ";
//            cin.ignore();
//            getline(cin, type);
//            cout << "Enter latitude: ";
//            if (!SafeInput::getDouble(lat, -90, 90)) { cout << "Invalid latitude\n"; break; }
//            cout << "Enter longitude: ";
//            if (!SafeInput::getDouble(lon, -180, 180)) { cout << "Invalid longitude\n"; break; }
//            facilities.findNearestFacility(lat, lon, type);
//            break;
//        }
//        case 4: {
//            double lat, lon;
//            cout << "Enter latitude: ";
//            if (!SafeInput::getDouble(lat, -90, 90)) { cout << "Invalid latitude\n"; break; }
//            cout << "Enter longitude: ";
//            if (!SafeInput::getDouble(lon, -180, 180)) { cout << "Invalid longitude\n"; break; }
//            facilities.findNearestAnyFacility(lat, lon);
//            break;
//        }
//        case 5:
//            exit(0);
//        default:
//            cout << "Invalid choice!" << endl;
//        }
//    }
//}
//
//void displayMedicalMenu() {
//    cout << "\n--- MEDICAL SECTOR ---" << endl;
//    cout << "1. View All Hospitals" << endl;
//    cout << "2. Check Emergency Bed Availability (Max-Heap)" << endl;
//    cout << "3. Search Medicine by Name" << endl;
//    cout << "4. Search Medicine by Formula" << endl;
//    cout << "5. View All Pharmacies" << endl;
//    cout << "6. Find Hospital by Specialization" << endl;
//    cout << "7. Find Nearest Hospital" << endl;
//    cout << "8. View All Doctors" << endl;
//    cout << "9. Find Doctors by Specialization" << endl;
//    cout << "10. View Patient Record" << endl;
//    cout << "11. Add New Hospital" << endl;
//    cout << "12. Add New Pharmacy" << endl;
//    cout << "13. Add New Medicine To A Pharmacy" << endl;
//    cout << "14. Add New Doctor" << endl;
//    cout << "15. Add New Patient" << endl;
//    cout << "16. Exit" << endl;
//    cout << "Enter your choice (1-16): ";
//}
//void handleMedicalModule(MedicalSystem& medical) {
//    int choice;
//    while (true) {
//        displayMedicalMenu();
//        if (!SafeInput::getInt(choice, 1, 16)) {
//            cout << "Invalid Input! Please Enter a number 1-17" << endl;
//            continue;
//        }
//        switch (choice) {
//        case 1:
//            medical.displayAllHospitals();
//            break;
//
//        case 2:
//            medical.displayEmergencyBeds();
//            break;
//
//        case 3: {
//            string name;
//            cout << "\nEnter Medicine Name: ";
//            cin.ignore();
//            getline(cin, name);
//            medical.searchMedicineByName(name);
//            break;
//        }
//
//        case 4: {
//            string formula;
//            cout << "\nEnter Medicine Formula: ";
//            cin.ignore();
//            getline(cin, formula);
//            medical.searchMedicineByFormula(formula);
//            break;
//        }
//
//        case 5:
//            medical.displayAllPharmacies();
//            break;
//
//        case 6: {
//            string specialization;
//            cout << "\nEnter Specialization: ";
//            cin.ignore();
//            getline(cin, specialization);
//            medical.findHospitalsBySpecialization(specialization);
//            break;
//        }
//
//        case 7: {
//            double lat, lon;
//            cout << "\nEnter Your Latitude (-90 to 90): ";
//            if (!SafeInput::getDouble(lat, -90, 90)) {
//                cout << "Invalid latitude!" << endl;
//                break;
//            }
//            cout << "Enter Your Longitude (-180 to 180): ";
//            if (!SafeInput::getDouble(lon, -180, 180)) {
//                cout << "Invalid longitude!" << endl;
//                break;
//            }
//            cin.ignore();
//            medical.findNearestHospital(lat, lon);
//            break;
//        }
//
//        case 8:
//            medical.displayAllDoctors();
//            break;
//
//        case 9: {
//            string specialization;
//            cout << "\nEnter Doctor Specialization: ";
//            cin.ignore();
//            getline(cin, specialization);
//            medical.findDoctorsBySpecialization(specialization);
//            break;
//        }
//
//        case 10: {
//            string cnic;
//            cout << "\nEnter Patient CNIC (xxxxx-xxxxxxx-x): ";
//            cin.ignore();
//            getline(cin, cnic);
//            medical.displayPatientRecord(cnic);
//            break;
//        }
//
//        case 11:
//            medical.addHospital();
//            break;
//
//        case 12:
//            medical.addpharmacy();
//            break;
//
//        case 13:
//            medical.addMedicineToPharmacy();
//            break;
//
//        case 14:
//            medical.addDoctor();
//            break;
//
//        case 15:
//            medical.addPatient();
//            break;
//
//        case 16:
//            cout << "Exiting Medical System..." << endl;
//            exit(0);
//
//        default:
//            cout << "Invalid choice!" << endl;
//        }
//
//    }
//}
//int main() {
//
//    srand((unsigned)time(NULL));
//    cout << "\n--------------------------------------" << endl;
//    cout << "  | SMART CITY MANAGEMENT SYSTEM v2.0   |" << endl;
//    cout << "  |        Initializing System...         |" << endl;
//    cout << "------------------------------------------" << endl;
//
//    Graph g1;
//    // Initialize Medical System
//    cout << "\n Loading Medical System..." << endl;
//    MedicalSystem medical(&g1);
//
//    //Initialize Facility System
//    cout << "\n Loading Facility System..." << endl;
//    FacilitySystem facility(&g1);
//    if (!medical.loadHospitals("Data/hospitals.csv")) {
//        cout << "Warning: Could not load hospitals data." << endl;
//    }
//    if (!medical.loadPharmacies("Data/pharmacies.csv")) {
//        cout << "Warning: Could not load pharmacies data." << endl;
//    }
//    cout << "✓ Medical System Loaded" << endl;
//   
//    handleMedicalModule(medical);
//    handleFacilitiesModule(facility);
//    return 0;
//}

#include "SmartCity.h"

int main() {
	SmartCity smartCity;
	smartCity.run();
}