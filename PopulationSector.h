#pragma once
#include<iostream>
#include<string>
using namespace std;

class CitizenHashTable;

class IndividualNode {
    string CNIC;
    string Name;
    int Age;
    string Occupation;
    string Gender;
    IndividualNode* next;

public:
    IndividualNode(string cnic = "", string name = "", int age = 0, string occup = "", string gender = "")
    {
        CNIC = cnic;
        Name = name;
        Age = age;
        Occupation = occup;

        GenderInputHandling(gender);    //if gender isnot male or female then it is set as unidentified 

        next = nullptr;
    }

    string GetCNIC()
    {
        return CNIC;
    }
    string GetName()
    {
        return Name;
    }
    int GetAge()
    {
        return Age;
    }
    string GetOccupation()
    {
        return Occupation;
    }
    string GetGender()
    {
        return Gender;
    }
    IndividualNode* GetNext()
    {
        return next;
    }
    void SetNext(IndividualNode* ptr)
    {
        next = ptr;
    }

    void SetCNIC(string cnic)
    {
        CNIC = cnic;
    }
    void SetName(string name)
    {
        Name = name;
    }
    void SetAge(int age)
    {
        Age = age;
    }
    void SetOccupation(string occup)
    {
        Occupation = occup;
    }
    void SetGender(string gender)
    {
        GenderInputHandling(gender);
    }


    void GenderInputHandling(string gender)
    {
        //input handling for gender; if gender is not male or female then it is unidentified .

         //so for this ive converted the entered gender into lowercase first , so that it can be easily read for male or female.

        for (int i = 0; i < gender.length(); i++)
        {
            if (gender[i] >= 'A' && gender[i] <= 'Z')
            {
                gender[i] += 32;
            }
        }

        //now input handle for gender 
        if (gender != "male" && gender != "female")
            Gender = "unidentified";

        else
            Gender = gender;
    }
};

class FamilyNode {
    int NoOfMembers;
    FamilyNode* next;
    IndividualNode* child;

public:
    FamilyNode(int members = 0)
    {
        NoOfMembers = members;
        next = nullptr;
        child = nullptr;
    }

    void AddMember(string cnic = "", string name = "", int age = 0, string occup = "", string gender = "")
    {
        IndividualNode* newMember = new IndividualNode(cnic, name, age, occup, gender);

        if (child == nullptr)
        {
            child = newMember;
        }
        else
        {
            IndividualNode* temp = child;
            while (temp->GetNext() != nullptr)
            {
                temp = temp->GetNext();
            }
            temp->SetNext(newMember);
        }
        NoOfMembers++;
    }

    IndividualNode* GetChild()
    {
        return child;
    }
    FamilyNode* GetNext()
    {
        return next;
    }
    void SetNext(FamilyNode* ptr)
    {
        next = ptr;
    }
    int GetMemberCount()
    {
        return NoOfMembers;
    }

};

class HouseNode {
    string Street;
    int HouseNo;
    string Sector;
    HouseNode* next;
    FamilyNode* child;

public:
    HouseNode(string street = "", int house = 0, string sector = "")
    {
        Street = street;
        HouseNo = house;
        Sector = sector;
        next = nullptr;
        child = nullptr;
    }

    void AddFamily(int members = 0)
    {
        FamilyNode* newFamily = new FamilyNode(members);

        if (child == nullptr)
        {
            child = newFamily;
        }
        else
        {
            FamilyNode* temp = child;
            while (temp->GetNext() != nullptr)
            {
                temp = temp->GetNext();
            }
            temp->SetNext(newFamily);
        }
    }

    void AddMemberToFamily(string cnic = "", string name = "", int age = 0, string occup = "", string gender = "")
    {
        if (child == nullptr)
        {
            AddFamily(0);
        }

        FamilyNode* temp = child;
        while (temp->GetNext() != nullptr)
        {
            temp = temp->GetNext();
        }
        temp->AddMember(cnic, name, age, occup, gender);
    }

    HouseNode* GetNext()
    {
        return next;
    }
    void SetNext(HouseNode* ptr)
    {
        next = ptr;
    }
    FamilyNode* GetChild()
    {
        return child;
    }
    string GetStreet()
    {
        return Street;
    }
    int GetHouseNo()
    {
        return HouseNo;
    }
    string GetSector()
    {
        return Sector;
    }
};

class CitizenHashTable {


    struct CitizenTableNode
    {
        string CNIC;
        string Name;
        int Age;
        string Occupation;
        string Gender;
        string Sector;
        string Street;
        int HouseNo;
        bool isOccupied;
        int index;
        CitizenTableNode* right;

        CitizenTableNode(string cnic = "", string name = "", int age = 0, string occup = "", string gender = "", string sector = "", string street = "", int house = 0, int idx = 0)
        {
            CNIC = cnic;
            Name = name;
            Age = age;
            Occupation = occup;
            Gender = gender;
            Sector = sector;
            Street = street;
            HouseNo = house;
            index = idx;
            isOccupied = false;
            right = nullptr;
        }

        string GetCNIC()
        {
            return CNIC;
        }
        string GetName()
        {
            return Name;
        }
        int GetAge()
        {
            return Age;
        }
        string GetOccupation()
        {
            return Occupation;
        }
        string GetGender()
        {
            return Gender;
        }
        string GetSector()
        {
            return Sector;
        }
        string GetStreet()
        {
            return Street;
        }
        int GetHouseNo()
        {
            return HouseNo;
        }
        bool IfOccupied()
        {
            return isOccupied;
        }
        int GetIndex()
        {
            return index;
        }
        CitizenTableNode* GetRight()
        {
            return right;
        }

        void SetOccupied(bool val)
        {
            isOccupied = val;
        }
        void SetRight(CitizenTableNode* ptr)
        {
            right = ptr;
        }
    };

    CitizenTableNode* CitizenTable;
    int TableSize;

public:
    CitizenHashTable(int size = 10) //keeping default size 10. resize not required because if collisions occur then it is saved as linked list .
    {
        if (size <= 0)
            size = 10;
        TableSize = size;
        CitizenTable = new CitizenTableNode[TableSize];
    }

    int HashFunction(string key)
    {
        long long hash = 0;
        long long p = 31;
        long long pow = 1;
        int mod = TableSize;
        if (mod <= 1) mod = 1;

        for (int i = 0; key[i] != '\0'; i++)
        {
            hash = (hash + ((long long)(unsigned char)key[i] * pow)) % mod;
            pow = (pow * p) % mod;
        }
        return (int)hash;
    }

    void AddCitizen(string cnic = "", string name = "", int age = 0, string occup = "", string gender = "", string sector = "", string street = "", int house = 0)
    {
        if (cnic == "")
            return;

        int Index = HashFunction(cnic);

        if (CitizenTable[Index].IfOccupied() == false)
        {
            CitizenTable[Index].CNIC = cnic;
            CitizenTable[Index].Name = name;
            CitizenTable[Index].Age = age;
            CitizenTable[Index].Occupation = occup;
            CitizenTable[Index].Gender = gender;
            CitizenTable[Index].Sector = sector;
            CitizenTable[Index].Street = street;
            CitizenTable[Index].HouseNo = house;
            CitizenTable[Index].index = Index;
            CitizenTable[Index].SetOccupied(true);
            CitizenTable[Index].SetRight(nullptr);
        }
        else
        {
            CitizenTableNode* temp = &CitizenTable[Index];
            while (temp != nullptr)
            {
                if (temp->GetCNIC() == cnic)
                    return;
                if (temp->GetRight() == nullptr)
                    break;
                temp = temp->GetRight();
            }
            temp->SetRight(new CitizenTableNode(cnic, name, age, occup, gender, sector, street, house, Index));
        }
    }

    bool SearchByCNIC(string cnic, string& name, int& age, string& occup, string& gender, string& sector, string& street, int& house)
    {
        if (cnic == "")
            return false;

        int idx = HashFunction(cnic);
        CitizenTableNode* head = &CitizenTable[idx];

        while (head != nullptr)
        {
            if (head->GetCNIC() == cnic && head->IfOccupied())
            {
                name = head->GetName();
                age = head->GetAge();
                occup = head->GetOccupation();
                gender = head->GetGender();
                sector = head->GetSector();
                street = head->GetStreet();
                house = head->GetHouseNo();
                return true;
            }
            head = head->GetRight();
        }
        return false;
    }

    CitizenTableNode** SearchByName(string name, int& count)    //what if multiple people with the same name? so returning the stored names
    {
        if (name == "")
        {
            count = 0;
            return nullptr;
        }

        count = 0;
        for (int i = 0; i < TableSize; i++)
        {
            CitizenTableNode* current = &CitizenTable[i];
            while (current != nullptr)
            {
                if (current->IfOccupied() && current->GetName() == name)
                    count++;
                current = current->GetRight();
            }
        }

        if (count == 0)
            return nullptr;

        CitizenTableNode** results = new CitizenTableNode * [count];
        int idx = 0;

        for (int i = 0; i < TableSize; i++)
        {
            CitizenTableNode* current = &CitizenTable[i];
            while (current != nullptr)
            {
                if (current->IfOccupied() && current->GetName() == name)
                {
                    results[idx] = current;
                    idx++;
                }
                current = current->GetRight();
            }
        }

        return results;
    }

    string GenerateGenderRatio()
    {
        int male = 0, female = 0, unidentified = 0;

        for (int i = 0; i < TableSize; i++)
        {
            CitizenTableNode* current = &CitizenTable[i];
            while (current != nullptr)
            {
                if (current->IfOccupied())
                {
                    string gender = current->GetGender();
                    if (gender == "male")
                        male++;
                    else if (gender == "female")
                        female++;
                    else unidentified++;
                }
                current = current->GetRight();
            }
        }

        return to_string(male) + ":" + to_string(female) + ":" + to_string(unidentified);
    }

    ~CitizenHashTable()
    {
        if (CitizenTable)
        {
            for (int i = 0; i < TableSize; i++)
            {
                CitizenTableNode* head = CitizenTable[i].GetRight();
                while (head != nullptr)
                {
                    CitizenTableNode* nxt = head->GetRight();
                    delete head;
                    head = nxt;
                }
            }
            delete[] CitizenTable;
            CitizenTable = nullptr;
        }
    }

    string GenerateSectorPopulationSummary()
    {
        string* sectors = nullptr;
        int* counts = nullptr;
        int sectorCount = 0;
        int capacity = 0;

        for (int i = 0; i < TableSize; i++)
        {
            CitizenTableNode* current = &CitizenTable[i];
            while (current != nullptr)
            {
                if (current->IfOccupied())
                {
                    string sector = current->GetSector();
                    bool found = false;

                    for (int j = 0; j < sectorCount; j++)
                    {
                        if (sectors[j] == sector)
                        {
                            counts[j]++;
                            found = true;
                            break;
                        }
                    }

                    if (!found)
                    {
                        if (sectorCount == capacity)
                        {
                            int newCapacity;
                            if (capacity == 0)
                            {
                                newCapacity = 1;
                            }
                            else
                            {
                                newCapacity = capacity * 2;
                            }

                            string* newSectors = new string[newCapacity];
                            int* newCounts = new int[newCapacity];

                            for (int k = 0; k < sectorCount; k++)
                            {
                                newSectors[k] = sectors[k];
                                newCounts[k] = counts[k];
                            }

                            delete[] sectors;
                            delete[] counts;
                            sectors = newSectors;
                            counts = newCounts;
                            capacity = newCapacity;
                        }

                        sectors[sectorCount] = sector;
                        counts[sectorCount] = 1;
                        sectorCount++;
                    }
                }
                current = current->GetRight();
            }
        }

        string result = "";
        for (int i = 0; i < sectorCount; i++)
        {
            result += sectors[i] + ": " + to_string(counts[i]) + " people\n";
        }

        delete[] sectors;
        delete[] counts;

        return result;
    }

    string GenerateOccupationSummary()
    {
        struct OccEntry {
            string occupation;
            int count;
            OccEntry* next;
        };

        OccEntry* occHead = nullptr;
        int uniqueOccCount = 0;
        int totalPeople = 0;

        for (int i = 0; i < TableSize; i++)
        {
            CitizenTableNode* current = &CitizenTable[i];
            while (current != nullptr)
            {
                if (current->IfOccupied())
                {
                    totalPeople++;
                    string occ = current->GetOccupation();

                    if (occ == "")  // Handle empty occupation
                        occ = "Unemployed/Not Specified";

                    OccEntry* temp = occHead;
                    OccEntry* prev = nullptr;

                    bool found = false;
                    while (temp != nullptr)
                    {
                        if (temp->occupation == occ)
                        {
                            temp->count++;
                            found = true;
                            break;
                        }
                        prev = temp;
                        temp = temp->next;
                    }

                    if (!found)
                    {
                        OccEntry* newEntry = new OccEntry();
                        newEntry->occupation = occ;
                        newEntry->count = 1;
                        newEntry->next = nullptr;

                        if (occHead == nullptr)
                            occHead = newEntry;
                        else
                            prev->next = newEntry;

                        uniqueOccCount++;
                    }
                }
                current = current->GetRight();
            }
        }

        string result = "Total People: " + to_string(totalPeople) + "\n";
        result += "Unique Occupations: " + to_string(uniqueOccCount) + "\n\n";

        OccEntry* current = occHead;
        while (current != nullptr)
        {
            double percentage = (current->count * 100.0) / totalPeople;
            result += current->occupation + ": " + to_string(current->count)
                + " (" + to_string(percentage).substr(0, 4) + "%)\n";
            OccEntry* next = current->next;
            delete current;
            current = next;
        }

        return result;
    }

    string GenerateAgeDistribution()
    {
        string* sectors = nullptr;
        int* totalAges = nullptr;
        int* personCounts = nullptr;
        int sectorCount = 0;
        int capacity = 0;

        for (int i = 0; i < TableSize; i++)
        {
            CitizenTableNode* current = &CitizenTable[i];
            while (current != nullptr)
            {
                if (current->IfOccupied())
                {
                    string sector = current->GetSector();
                    int age = current->GetAge();
                    bool found = false;

                    for (int j = 0; j < sectorCount; j++)
                    {
                        if (sectors[j] == sector)
                        {
                            totalAges[j] += age;
                            personCounts[j]++;
                            found = true;
                            break;
                        }
                    }

                    if (!found)
                    {
                        if (sectorCount == capacity)
                        {
                            int newCapacity;
                            if (capacity == 0)
                            {
                                newCapacity = 1;
                            }
                            else
                            {
                                newCapacity = capacity * 2;
                            }

                            string* newSectors = new string[newCapacity];
                            int* newTotalAges = new int[newCapacity];
                            int* newPersonCounts = new int[newCapacity];

                            for (int k = 0; k < sectorCount; k++)
                            {
                                newSectors[k] = sectors[k];
                                newTotalAges[k] = totalAges[k];
                                newPersonCounts[k] = personCounts[k];
                            }

                            delete[] sectors;
                            delete[] totalAges;
                            delete[] personCounts;
                            sectors = newSectors;
                            totalAges = newTotalAges;
                            personCounts = newPersonCounts;
                            capacity = newCapacity;
                        }

                        sectors[sectorCount] = sector;
                        totalAges[sectorCount] = age;
                        personCounts[sectorCount] = 1;
                        sectorCount++;
                    }
                }
                current = current->GetRight();
            }
        }

        string result = "";
        for (int i = 0; i < sectorCount; i++)
        {
            double averageAge = (double)totalAges[i] / personCounts[i];
            result += sectors[i] + ": " + to_string(averageAge) + " years average\n";
        }

        delete[] sectors;
        delete[] totalAges;
        delete[] personCounts;

        return result;
    }
    string CalculatePopulationDensity()
    {
        string* sectors = nullptr;
        int* personCounts = nullptr;
        int sectorCount = 0;
        int capacity = 0;

        for (int i = 0; i < TableSize; i++)
        {
            CitizenTableNode* current = &CitizenTable[i];
            while (current != nullptr)
            {
                if (current->IfOccupied())
                {
                    string sector = current->GetSector();
                    bool found = false;

                    for (int j = 0; j < sectorCount; j++)
                    {
                        if (sectors[j] == sector)
                        {
                            personCounts[j]++;
                            found = true;
                            break;
                        }
                    }

                    if (!found)
                    {
                        if (sectorCount == capacity)
                        {
                            int newCapacity;
                            if (capacity == 0)
                            {
                                newCapacity = 1;
                            }
                            else
                            {
                                newCapacity = capacity * 2;
                            }

                            string* newSectors = new string[newCapacity];
                            int* newPersonCounts = new int[newCapacity];

                            for (int k = 0; k < sectorCount; k++)
                            {
                                newSectors[k] = sectors[k];
                                newPersonCounts[k] = personCounts[k];
                            }

                            delete[] sectors;
                            delete[] personCounts;
                            sectors = newSectors;
                            personCounts = newPersonCounts;
                            capacity = newCapacity;
                        }

                        sectors[sectorCount] = sector;
                        personCounts[sectorCount] = 1;
                        sectorCount++;
                    }
                }
                current = current->GetRight();
            }
        }

        int maxPopulation = 0;
        for (int i = 0; i < sectorCount; i++)
        {
            if (personCounts[i] > maxPopulation)
                maxPopulation = personCounts[i];
        }

        string result = "";
        result += "=== POPULATION DENSITY HEATMAP ===\n";
        result += "Color Guide: \033[32mLow\033[0m | \033[33mMedium\033[0m | \033[31mHigh\033[0m\n";
        result += "==================================\n\n";

        for (int i = 0; i < sectorCount; i++)
        {
            double densityPercent = (personCounts[i] * 100.0) / maxPopulation;
            string colorCode;

            if (densityPercent < 33.0)
                colorCode = "\033[32m";
            else if (densityPercent < 66.0)
                colorCode = "\033[33m";
            else
                colorCode = "\033[31m";

            int barLength = (int)((personCounts[i] * 10.0) / maxPopulation);
            if (barLength < 1) barLength = 1;

            string bar = "";
            for (int j = 0; j < barLength; j++)
                bar += "#";

            result += sectors[i] + ": " + colorCode + bar + "\033[0m (" +
                to_string(personCounts[i]) + " people)\n";
        }

        delete[] sectors;
        delete[] personCounts;

        return result;
    }

};

class HousingSystem {
    HouseNode* head;    //only 1 housing system for all of islamabad so it has no sibling pointer . it handles all houses 
    CitizenHashTable* citizenTable;
    Graph* cityGraph;

public:
    HousingSystem(Graph* graph)
    {
        cityGraph = graph;
        head = nullptr;
        citizenTable = new CitizenHashTable();
    }

    void AddHouse(string street = "", int house = 0, string sector = "")
    {

        if (!cityGraph) {
            cout << "Error: City graph is not initialized yet" << endl;
            return;
        }

        // Check if house already exists
        HouseNode* existing = FindHouse(street, house, sector);
        if (existing != nullptr)
        {
            cout << "House already exists at " << sector << ", " << street << " " << house << endl;
            return;
        }

        HouseNode* newHouse = new HouseNode(street, house, sector);

        if (head == nullptr)
        {
            head = newHouse;
        }
        else
        {
            HouseNode* temp = head;
            while (temp->GetNext() != nullptr)
            {
                temp = temp->GetNext();
            }
            temp->SetNext(newHouse);
        }

        cout << "House added successfully." << endl;
    }

    void AddMemberToHouse(string street = "", int house = 0, string sector = "", string cnic = "", string name = "", int age = 0, string occup = "", string gender = "", int familyNumber = -1)
    {
        HouseNode* temp = head;
        while (temp != nullptr)
        {
            if (temp->GetStreet() == street && temp->GetHouseNo() == house && temp->GetSector() == sector)
            {
                if (temp->GetChild() == nullptr)
                {
                    // No families exist
                    cout << "Error: No families in this house. Add family first." << endl;
                    return;
                }

                FamilyNode* targetFamily = temp->GetChild();

                // If familyNumber specified, find that specific family
                if (familyNumber > 0)
                {
                    int currentFamily = 1;
                    while (targetFamily != nullptr && currentFamily < familyNumber)
                    {
                        targetFamily = targetFamily->GetNext();
                        currentFamily++;
                    }

                    if (targetFamily == nullptr)
                    {
                        cout << "Error: Family " << familyNumber << " not found." << endl;
                        return;  // Don't add anywhere
                    }
                }
                else
                {
                    // familyNumber = -1 means add to last family (original behavior)
                    while (targetFamily->GetNext() != nullptr)
                    {
                        targetFamily = targetFamily->GetNext();
                    }
                }

                // Add member to the selected family
                targetFamily->AddMember(cnic, name, age, occup, gender);
                citizenTable->AddCitizen(cnic, name, age, occup, gender, sector, street, house);
                return;
            }
            temp = temp->GetNext();
        }

        cout << "Error: House not found in " << sector << ", " << street << " " << house << endl;
    }

    bool ValidateCNIC(string cnic)
    {
        if (cnic.length() != 15)
            return false;

        if (cnic[5] != '-' || cnic[13] != '-')
            return false;

        for (int i = 0; i < cnic.length(); i++)
        {
            if (i == 5 || i == 13)
                continue;

            if (cnic[i] < '0' || cnic[i] > '9')
                return false;
        }

        return true;
    }

    HouseNode* FindHouse(string street = "", int house = 0, string sector = "")
    {
        HouseNode* temp = head;
        while (temp != nullptr)
        {
            if (temp->GetStreet() == street && temp->GetHouseNo() == house && temp->GetSector() == sector)
            {
                return temp;
            }
            temp = temp->GetNext();
        }
        return nullptr;
    }

    void SearchCitizenByName(string name)
    {
        if (name == "")
        {
            cout << "Error: Empty name provided" << endl;
            return;
        }

        bool found = false;
        HouseNode* currentHouse = head;

        while (currentHouse != nullptr)
        {
            FamilyNode* currentFamily = currentHouse->GetChild();

            while (currentFamily != nullptr)
            {
                IndividualNode* currentPerson = currentFamily->GetChild();

                while (currentPerson != nullptr)
                {
                    if (currentPerson->GetName() == name)
                    {
                        if (!found)
                        {
                            cout << "Citizens found with name '" << name << "':" << endl;
                            cout << "====================================" << endl;
                            found = true;
                        }

                        cout << "Name: " << currentPerson->GetName() << endl;
                        cout << "CNIC: " << currentPerson->GetCNIC() << endl;
                        cout << "Age: " << currentPerson->GetAge() << endl;
                        cout << "Occupation: " << currentPerson->GetOccupation() << endl;
                        cout << "Gender: " << currentPerson->GetGender() << endl;
                        cout << "Address: " << currentHouse->GetSector() << ", "
                            << currentHouse->GetStreet() << " "
                            << currentHouse->GetHouseNo() << endl;
                        cout << "------------------------------------" << endl;
                    }
                    currentPerson = currentPerson->GetNext();
                }
                currentFamily = currentFamily->GetNext();
            }
            currentHouse = currentHouse->GetNext();
        }

        if (!found)
        {
            cout << "No citizen found with name: " << name << endl;
        }
    }

    void DisplayHousesInSector(string sector)
    {
        if (sector == "")
        {
            cout << "Error: Empty sector provided" << endl;
            return;
        }

        int houseCount = 0;
        int residentCount = 0;

        cout << "\n=== HOUSES IN SECTOR: " << sector << " ===" << endl;

        HouseNode* current = head;
        while (current != nullptr)
        {
            if (current->GetSector() == sector)
            {
                houseCount++;
                int peopleInHouse = 0;

                // Count people in this house
                FamilyNode* family = current->GetChild();
                while (family != nullptr)
                {
                    peopleInHouse += family->GetMemberCount();
                    family = family->GetNext();
                }

                residentCount += peopleInHouse;

                cout << houseCount << ". House No: " << current->GetHouseNo()
                    << ", Street: " << current->GetStreet()
                    << ", Residents: " << peopleInHouse << endl;
            }
            current = current->GetNext();
        }

        if (houseCount == 0)
        {
            cout << "No houses found in sector: " << sector << endl;
        }
        else
        {
            cout << "\nSUMMARY:" << endl;
            cout << "Total Houses: " << houseCount << endl;
            cout << "Total Residents: " << residentCount << endl;
            cout << "Average per house: " << (residentCount * 1.0 / houseCount) << " people" << endl;
        }
    }

    void DisplayHousingHierarchy()
    {
        if (head == nullptr)
        {
            cout << "No housing data available." << endl;
            return;
        }

        cout << "\n=== HOUSING HIERARCHY ===" << endl;
        cout << "Islamabad Housing System" << endl;
        cout << "========================\n" << endl;

        int totalHouses = 0;
        int totalFamilies = 0;
        int totalIndividuals = 0;

        HouseNode* currentHouse = head;
        while (currentHouse != nullptr)
        {
            totalHouses++;

            cout << "HOUSE: " << currentHouse->GetHouseNo()
                << ", Sector: " << currentHouse->GetSector()
                << ", Street: " << currentHouse->GetStreet() << endl;

            FamilyNode* currentFamily = currentHouse->GetChild();
            int familyNum = 0;

            while (currentFamily != nullptr)
            {
                totalFamilies++;
                familyNum++;

                cout << "  Family " << familyNum
                    << " (Members: " << currentFamily->GetMemberCount() << ")" << endl;

                IndividualNode* currentPerson = currentFamily->GetChild();
                int personNum = 0;

                while (currentPerson != nullptr)
                {
                    totalIndividuals++;
                    personNum++;

                    cout << "    - Person " << personNum << ": "
                        << currentPerson->GetName()
                        << ", CNIC: " << currentPerson->GetCNIC()
                        << ", Age: " << currentPerson->GetAge()
                        << ", " << currentPerson->GetOccupation() << endl;

                    currentPerson = currentPerson->GetNext();
                }

                currentFamily = currentFamily->GetNext();
            }

            cout << endl;
            currentHouse = currentHouse->GetNext();
        }

        cout << "========================" << endl;
        cout << "SUMMARY:" << endl;
        cout << "Total Houses: " << totalHouses << endl;
        cout << "Total Families: " << totalFamilies << endl;
        cout << "Total Individuals: " << totalIndividuals << endl;
        cout << "========================" << endl;
    }

    int GetTotalHouses()
    {
        int count = 0;
        HouseNode* current = head;
        while (current != nullptr)
        {
            count++;
            current = current->GetNext();
        }
        return count;
    }

    int GetTotalFamilies()
    {
        int count = 0;
        HouseNode* house = head;
        while (house != nullptr)
        {
            FamilyNode* family = house->GetChild();
            while (family != nullptr)
            {
                count++;
                family = family->GetNext();
            }
            house = house->GetNext();
        }
        return count;
    }

    int GetFamiliesInSector(string sector)
    {
        int count = 0;
        HouseNode* house = head;
        while (house != nullptr)
        {
            if (house->GetSector() == sector)
            {
                FamilyNode* family = house->GetChild();
                while (family != nullptr)
                {
                    count++;
                    family = family->GetNext();
                }
            }
            house = house->GetNext();
        }
        return count;
    }

    string GetGenderRatioReport()
    {
        return citizenTable->GenerateGenderRatio();
    }

    string GetSectorPopulationReport()
    {
        return citizenTable->GenerateSectorPopulationSummary();
    }

    string GetOccupationReport()
    {
        return citizenTable->GenerateOccupationSummary();
    }

    string GetAgeDistributionReport()
    {
        return citizenTable->GenerateAgeDistribution();
    }

    string GetPopulationDensityReport()
    {
        return citizenTable->CalculatePopulationDensity();
    }

    void SearchCitizenByCNIC(string cnic)
    {
        string name, occup, gender, sector, street;
        int age, house;

        bool found = citizenTable->SearchByCNIC(cnic, name, age, occup, gender, sector, street, house);

        if (!found)
        {
            cout << "No citizen found with CNIC: " << cnic << endl;
        }
        else
        {
            cout << "=== CITIZEN FOUND ===" << endl;
            cout << "CNIC: " << cnic << endl;
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Occupation: " << occup << endl;
            cout << "Gender: " << gender << endl;
            cout << "Address: " << sector << ", " << street << " " << house << endl;
        }
    }

    int GetTotalPopulation()
    {
        int count = 0;
        HouseNode* current = head;
        while (current != nullptr)
        {
            FamilyNode* family = current->GetChild();
            while (family != nullptr)
            {
                count += family->GetMemberCount();
                family = family->GetNext();
            }
            current = current->GetNext();
        }
        return count;
    }

    void GenerateSurveyReport()
    {
        cout << "\n=== SMART CITY POPULATION SURVEY ===" << endl;
        cout << "=====================================" << endl;

        cout << "\n1. GENDER RATIO (Male:Female:Unidentified):" << endl;
        cout << GetGenderRatioReport() << endl;

        cout << "\n2. SECTOR POPULATION DISTRIBUTION:" << endl;
        cout << GetSectorPopulationReport();

        cout << "\n3. OCCUPATION SUMMARY:" << endl;
        cout << GetOccupationReport();

        cout << "\n4. AGE DISTRIBUTION (Average Age per Sector):" << endl;
        cout << GetAgeDistributionReport();

        cout << "\n5. POPULATION DENSITY (People per Sector):" << endl;
        cout << GetPopulationDensityReport();

        cout << "\n6. TOTAL POPULATION COUNT:" << endl;
        cout << "Total Residents: " << GetTotalPopulation() << endl;

        cout << "\n=====================================" << endl;
        cout << "=== SURVEY COMPLETE ===" << endl;
    }

    ~HousingSystem()
    {
        HouseNode* current = head;
        while (current != nullptr)
        {
            HouseNode* nextHouse = current->GetNext();

            FamilyNode* family = current->GetChild();
            while (family != nullptr)
            {
                FamilyNode* nextFamily = family->GetNext();

                IndividualNode* person = family->GetChild();
                while (person != nullptr)
                {
                    IndividualNode* nextPerson = person->GetNext();
                    delete person;
                    person = nextPerson;
                }

                delete family;
                family = nextFamily;
            }

            delete current;
            current = nextHouse;
        }
        delete citizenTable;
    }

    void DisplayMainMenu()
    {
        cout << "\n=== SMART CITY HOUSING MANAGEMENT SYSTEM ===" << endl;
        cout << "1. Add New House" << endl;
        cout << "2. Add Family to House" << endl;
        cout << "3. Add Member to Family" << endl;
        cout << "4. Search Citizen by CNIC" << endl;
        cout << "5. Search Citizen by Name" << endl;
        cout << "6. View Houses in Sector" << endl;
        cout << "7. Display Housing Hierarchy" << endl;
        cout << "8. Generate Survey Reports" << endl;
        cout << "9. Display Statistics" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter your choice (1-10): ";
    }

    void DisplaySurveyMenu()
    {
        cout << "\n=== SURVEY REPORTS ===" << endl;
        cout << "1. Gender Ratio Report" << endl;
        cout << "2. Occupation Summary Report" << endl;
        cout << "3. Age Distribution Report" << endl;
        cout << "4. Population Density Report" << endl;
        cout << "5. Sector Population Report" << endl;
        cout << "6. All Reports (Complete Survey)" << endl;
        cout << "7. Back to Main Menu" << endl;
        cout << "Enter your choice (1-7): ";
    }

    void DisplayStatsMenu()
    {
        cout << "\n=== SYSTEM STATISTICS ===" << endl;
        cout << "1. Total Population" << endl;
        cout << "2. Total Houses" << endl;
        cout << "3. Total Families" << endl;
        cout << "4. Families in Specific Sector" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice (1-5): ";
    }
};

//int main()
//{
//    HousingSystem city;
//    int choice;
//    bool running = true;
//
//
//    while (running)
//    {
//        DisplayMainMenu();
//        cin >> choice;
//
//        switch (choice)
//        {
//        case 1: // Add New House
//        {
//            string street, sector;
//            int houseNo;
//            cout << "Enter Sector: ";
//            cin >> sector;
//            cout << "Enter Street: ";
//            cin >> street;
//            cout << "Enter House Number: ";
//            cin >> houseNo;
//
//            city.AddHouse(street, houseNo, sector);
//            break;
//        }
//
//        case 2: // Add Family to House
//        {
//            string street, sector;
//            int houseNo;
//            cout << "Enter Sector: ";
//            cin >> sector;
//            cout << "Enter Street: ";
//            cin >> street;
//            cout << "Enter House Number: ";
//            cin >> houseNo;
//
//            // Check if house exists
//            HouseNode* existingHouse = city.FindHouse(street, houseNo, sector);
//
//            if (existingHouse == nullptr)
//            {
//                char choice;
//                cout << "House does not exist. Create it first? (y/n): ";
//                cin >> choice;
//
//                if (choice == 'y' || choice == 'Y')
//                {
//                    city.AddHouse(street, houseNo, sector);
//                    existingHouse = city.FindHouse(street, houseNo, sector);
//
//                    if (existingHouse != nullptr)
//                    {
//                        existingHouse->AddFamily();
//                        cout << "House created and first family added." << endl;
//                    }
//                }
//                else
//                {
//                    cout << "Operation cancelled." << endl;
//                }
//            }
//            else
//            {
//                // House exists, add family to it
//                existingHouse->AddFamily();
//                cout << "New family added to existing house." << endl;
//            }
//            break;
//        }
//
//
//        case 3:
//        {
//            string street, sector, cnic, name, occupation, gender;
//            int houseNo, age, familyChoice;
//
//            cout << "Enter Sector: ";
//            cin >> sector;
//            cout << "Enter Street: ";
//            cin >> street;
//            cout << "Enter House Number: ";
//            cin >> houseNo;
//
//            HouseNode* houseNode = city.FindHouse(street, houseNo, sector);
//
//            if (houseNode == nullptr)
//            {
//                cout << "Error: House does not exist." << endl;
//                break;
//            }
//
//            int familyCount = 0;
//            FamilyNode* familyTemp = houseNode->GetChild();
//            while (familyTemp != nullptr)
//            {
//                familyCount++;
//                familyTemp = familyTemp->GetNext();
//            }
//
//            if (familyCount == 0)
//            {
//                cout << "No families in this house." << endl;
//                break;
//            }
//
//            cout << "This house has " << familyCount << " family/families." << endl;
//            cout << "Enter family number to add member to (1 to " << familyCount << "): ";
//            cin >> familyChoice;
//
//            if (familyChoice < 1 || familyChoice > familyCount)
//            {
//                cout << "Invalid family number." << endl;
//                break;
//            }
//
//            cout << "Enter CNIC ";
//            cin >> cnic;
//            cout << "Enter Name: ";
//            cin.ignore();
//            getline(cin, name);
//            cout << "Enter Age: ";
//            cin >> age;
//            cout << "Enter Occupation: ";
//            cin.ignore();
//            getline(cin, occupation);
//            cout << "Enter Gender (male/female): ";
//            cin >> gender;
//
//            city.AddMemberToHouse(street, houseNo, sector, cnic, name, age, occupation, gender, familyChoice);
//            break;
//        }
//
//        case 4: // Search Citizen by CNIC
//        {
//            string cnic;
//            cout << "Enter CNIC to search: ";
//            cin >> cnic;
//
//            city.SearchCitizenByCNIC(cnic);
//            break;
//        }
//
//        case 5: // Search Citizen by Name
//        {
//            string name;
//            cout << "Enter name to search: ";
//            cin.ignore();
//            getline(cin, name);
//
//            city.SearchCitizenByName(name);
//            break;
//        }
//
//        case 6: // View Houses in Sector
//        {
//            string sector;
//            cout << "Enter sector to view houses: ";
//            cin >> sector;
//
//            city.DisplayHousesInSector(sector);
//            break;
//        }
//
//        case 7: // Display Housing Hierarchy
//        {
//            city.DisplayHousingHierarchy();
//            break;
//        }
//
//        case 8: // Generate Survey Reports
//        {
//            int surveyChoice;
//            bool surveyRunning = true;
//
//            while (surveyRunning)
//            {
//                DisplaySurveyMenu();
//                cin >> surveyChoice;
//
//                switch (surveyChoice)
//                {
//                case 1: // Gender Ratio Report
//                {
//                    string ratio = city.GetGenderRatioReport();
//                    cout << "Gender Ratio (Male:Female:Unidentified): " << ratio << endl;
//                    break;
//                }
//                case 2: // Occupation Summary Report
//                {
//                    string report = city.GetOccupationReport();
//                    cout << "=== OCCUPATION SUMMARY ===" << endl;
//                    cout << report << endl;
//                    break;
//                }
//                case 3: // Age Distribution Report
//                {
//                    string report = city.GetAgeDistributionReport();
//                    cout << "=== AGE DISTRIBUTION ===" << endl;
//                    cout << report << endl;
//                    break;
//                }
//                case 4: // Population Density Report
//                {
//                    string report = city.GetPopulationDensityReport();
//                    // Already has headers in the function
//                    cout << report << endl;
//                    break;
//                }
//                case 5: // Sector Population Report
//                {
//                    string report = city.GetSectorPopulationReport();
//                    cout << "=== SECTOR POPULATION ===" << endl;
//                    cout << report << endl;
//                    break;
//                }
//                case 6:
//                    city.GenerateSurveyReport();
//                    break;
//                case 7:
//                    surveyRunning = false;
//                    break;
//                default:
//                    cout << "Invalid choice. Try again." << endl;
//                }
//            }
//            break;
//        }
//
//        case 9: // Display Statistics
//        {
//            int statsChoice;
//            bool statsRunning = true;
//
//            while (statsRunning)
//            {
//                DisplayStatsMenu();
//                cin >> statsChoice;
//
//                switch (statsChoice)
//                {
//                case 1:
//                    cout << "Total Population: " << city.GetTotalPopulation() << endl;
//                    break;
//                case 2:
//                    cout << "Total Houses: " << city.GetTotalHouses() << endl;
//                    break;
//                case 3:
//                    cout << "Total Families: " << city.GetTotalFamilies() << endl;
//                    break;
//                case 4:
//                {
//                    string sector;
//                    cout << "Enter sector: ";
//                    cin >> sector;
//                    cout << "Families in " << sector << ": " << city.GetFamiliesInSector(sector) << endl;
//                    break;
//                }
//                case 5:
//                    statsRunning = false;
//                    break;
//                default:
//                    cout << "Invalid choice. Try again." << endl;
//                }
//            }
//            break;
//        }
//
//        case 10: // Exit
//            cout << "Exiting system. Goodbye!" << endl;
//            running = false;
//            break;
//
//        default:
//            cout << "Invalid choice. Please enter 1-10." << endl;
//        }
//    }
//
//    return 0;
//}