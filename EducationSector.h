#pragma once
#include "Graph.h"
#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
using namespace std;



class StudentTableNode {

	string name;
	int age;
	string StudentID;
	bool isOccupied;

	string schoolID;
	string deptName;
	string className;

	int index;
	StudentTableNode* right;

public:
	StudentTableNode(string Name = "", int Age = 0, string ID = "",
		string schID = "", string dept = "", string cls = "", int idx = 0)
	{
		name = Name;
		age = Age;
		StudentID = ID;
		schoolID = schID;
		deptName = dept;
		className = cls;
		index = idx;
		isOccupied = 0;
		right = nullptr;
	}

	bool IfOccupied()
	{
		return isOccupied;
	}

	string GetName()
	{
		return name;
	}

	string GetID()
	{
		return StudentID;
	}

	int GetAge()
	{
		return age;
	}

	string GetSchoolID()
	{
		return schoolID;
	}

	string GetDeptName()
	{
		return deptName;
	}

	string GetClassName()
	{
		return className;
	}

	int GetIndex()
	{
		return index;
	}

	void SetIndex(int idx)
	{
		if (idx < 0)
			idx = 0;

		index = idx;
	}

	StudentTableNode* GetRightPtr()
	{
		return right;
	}

	void SetRightPtr(StudentTableNode* ptr)
	{
		right = ptr;
	}

	void SetOccupied(bool val)
	{
		isOccupied = val;
	}
};

class StudentHashTable {

	StudentTableNode* StudentTable;
	int TableSize;

public:
	StudentHashTable(int size = 5)
	{
		if (size <= 0)
			size = 5;

		TableSize = size;
		StudentTable = new StudentTableNode[TableSize];
	}

	int HashFunction(string key)
	{
		long long hash = 0;
		long long p = 31;
		long long pow = 1;
		int mod = TableSize;
		if (mod <= 1)
			mod = 1;

		for (int i = 0; key[i] != '\0'; i++)
		{
			hash = (hash + ((long long)(unsigned char)key[i] * pow)) % mod;
			pow = (pow * p) % mod;
		}

		return (int)hash;
	}

	void AddStudent(string Name = "", int Age = 0, string ID = "",
		string schID = "", string dept = "", string cls = "")
	{
		if (ID == "")
			return;

		int Index = HashFunction(ID);

		if (StudentTable[Index].IfOccupied() == 0)
		{
			StudentTable[Index] = StudentTableNode(Name, Age, ID, schID, dept, cls, Index);
			StudentTable[Index].SetOccupied(true);
		}
		else
		{
			StudentTableNode* temp = &StudentTable[Index];

			while (temp != nullptr)
			{
				if (temp->GetID() == ID && temp->IfOccupied())
				{
					return;
				}
				if (temp->GetRightPtr() == nullptr)
				{
					break;
				}
				temp = temp->GetRightPtr();
			}

			StudentTableNode* newNode = new StudentTableNode(Name, Age, ID, schID, dept, cls, Index);
			newNode->SetOccupied(true);
			temp->SetRightPtr(newNode);
		}
	}

	StudentTableNode* SearchByID(string ID)
	{
		if (ID == "")
			return nullptr;

		int idx = HashFunction(ID);
		StudentTableNode* head = &StudentTable[idx];

		while (head != nullptr)
		{
			if (head->GetID() == ID && head->IfOccupied())
				return head;

			head = head->GetRightPtr();
		}
		return nullptr;
	}

	int CountStudents()
	{
		int count = 0;
		for (int i = 0; i < TableSize; i++)
		{
			if (StudentTable[i].IfOccupied())
			{
				count++;
				StudentTableNode* temp = StudentTable[i].GetRightPtr();
				while (temp != nullptr)
				{
					if (temp->IfOccupied())
					{
						count++;
					}
					temp = temp->GetRightPtr();
				}
			}
		}
		return count;
	}

	void DisplayAllStudents() {
		for (int i = 0; i < TableSize; i++)
		{
			if (StudentTable[i].IfOccupied())
			{
				StudentTableNode* temp = &StudentTable[i];
				while (temp != nullptr)
				{
					if (temp->IfOccupied())
					{
						cout << "Name: " << temp->GetName()
							<< ", ID: " << temp->GetID()
							<< ", School: " << temp->GetSchoolID() << endl;
					}
					temp = temp->GetRightPtr();
				}
			}
		}
	}


	~StudentHashTable()
	{
		if (StudentTable)
		{
			for (int i = 0; i < TableSize; i++)
			{
				StudentTableNode* head = StudentTable[i].GetRightPtr();
				while (head != nullptr)
				{
					StudentTableNode* nxt = head->GetRightPtr();
					delete head;
					head = nxt;
				}
			}
			delete[] StudentTable;
			StudentTable = nullptr;
		}
	}
};

class FacultyTableNode {

	string name;
	string FacultyID;
	string specialization;
	bool isOccupied;

	string schoolID;
	string deptName;

	int index;
	FacultyTableNode* right;

public:
	FacultyTableNode(string Name = "", string ID = "", string Specialization = "", string schID = "", string dept = "", int idx = 0)
	{
		name = Name;
		FacultyID = ID;
		specialization = Specialization;
		schoolID = schID;
		deptName = dept;
		index = idx;
		isOccupied = 0;
		right = nullptr;
	}

	bool IfOccupied()
	{
		return isOccupied;
	}

	string GetName()
	{
		return name;
	}

	string GetID()
	{
		return FacultyID;
	}

	string GetSpecialization()
	{
		return specialization;
	}

	string GetSchoolID()
	{
		return schoolID;
	}

	string GetDeptName()
	{
		return deptName;
	}

	int GetIndex()
	{
		return index;
	}

	void SetIndex(int idx)
	{
		if (idx < 0)
			idx = 0;

		index = idx;
	}

	FacultyTableNode* GetRightPtr()
	{
		return right;
	}

	void SetRightPtr(FacultyTableNode* ptr)
	{
		right = ptr;
	}

	void SetOccupied(bool val)
	{
		isOccupied = val;
	}
};


class FacultyHashTable {

	FacultyTableNode* FacultyTableArray;
	int TableSize;

public:
	FacultyHashTable(int size = 5)
	{
		if (size <= 0)
			size = 5;

		TableSize = size;
		FacultyTableArray = new FacultyTableNode[TableSize];
	}

	int HashFunction(string key)
	{
		long long hash = 0;
		long long p = 31;
		long long pow = 1;
		int mod = TableSize;
		if (mod <= 1)
			mod = 1;

		for (int i = 0; key[i] != '\0'; i++)
		{
			hash = (hash + ((long long)(unsigned char)key[i] * pow)) % mod;
			pow = (pow * p) % mod;
		}

		return (int)hash;
	}

	void AddFaculty(string Name = "", string ID = "", string Specialization = "",
		string schID = "", string dept = "")
	{
		if (ID == "")
			return;

		int Index = HashFunction(ID);

		if (FacultyTableArray[Index].IfOccupied() == 0)
		{
			FacultyTableArray[Index] = FacultyTableNode(Name, ID, Specialization, schID, dept, Index);
			FacultyTableArray[Index].SetOccupied(true);
		}
		else
		{
			FacultyTableNode* temp = &FacultyTableArray[Index];

			while (temp != nullptr)
			{
				if (temp->GetID() == ID && temp->IfOccupied())
				{
					return;
				}
				if (temp->GetRightPtr() == nullptr)
				{
					break;
				}
				temp = temp->GetRightPtr();
			}

			FacultyTableNode* newNode = new FacultyTableNode(Name, ID, Specialization, schID, dept, Index);
			newNode->SetOccupied(true);
			temp->SetRightPtr(newNode);
		}
	}

	FacultyTableNode* SearchByID(string ID)
	{
		if (ID == "")
			return nullptr;

		int idx = HashFunction(ID);
		FacultyTableNode* head = &FacultyTableArray[idx];

		while (head != nullptr)
		{
			if (head->GetID() == ID && head->IfOccupied())
				return head;

			head = head->GetRightPtr();
		}
		return nullptr;
	}

	int CountFaculty()
	{
		int count = 0;
		for (int i = 0; i < TableSize; i++)
		{
			if (FacultyTableArray[i].IfOccupied())
			{
				count++;
				FacultyTableNode* temp = FacultyTableArray[i].GetRightPtr();
				while (temp != nullptr)
				{
					if (temp->IfOccupied())
					{
						count++;
					}
					temp = temp->GetRightPtr();
				}
			}
		}
		return count;
	}

	void DisplayAllFaculty() {
		for (int i = 0; i < TableSize; i++) {
			if (FacultyTableArray[i].IfOccupied()) {
				FacultyTableNode* temp = &FacultyTableArray[i];
				while (temp != nullptr) {
					if (temp->IfOccupied()) {
						cout << "Name: " << temp->GetName()
							<< ", ID: " << temp->GetID()
							<< ", Specialization: " << temp->GetSpecialization() << endl;
					}
					temp = temp->GetRightPtr();
				}
			}
		}
	}

	~FacultyHashTable()
	{
		if (FacultyTableArray)
		{
			for (int i = 0; i < TableSize; i++)
			{
				FacultyTableNode* head = FacultyTableArray[i].GetRightPtr();
				while (head != nullptr)
				{
					FacultyTableNode* nxt = head->GetRightPtr();
					delete head;
					head = nxt;
				}
			}
			delete[] FacultyTableArray;
			FacultyTableArray = nullptr;
		}
	}
};


class School;


class ClassNode {

	string ClassName;
	ClassNode* next;

	// Track student IDs in this class
	string* studentIDs;
	int studentCount;
	int studentCapacity;

	void IncreaseStudentCapacity()
	{
		int NewCapacity =
			studentCapacity * 2;
		if (NewCapacity == 0)
			NewCapacity = 1;

		string* temp = new string[NewCapacity];
		for (int i = 0; i < studentCount; i++)
		{
			temp[i] = studentIDs[i];
		}

		delete[] studentIDs;
		studentIDs = temp;
		studentCapacity = NewCapacity;
	}

public:
	ClassNode(string classname = "")
	{
		next = nullptr;
		ClassName = classname;

		studentCapacity = 2;
		studentIDs = new string[studentCapacity];
		studentCount = 0;
	}

	~ClassNode()
	{
		delete[] studentIDs;
	}

	void AddStudentID(string studentID)
	{
		if (studentCount == studentCapacity)
		{
			IncreaseStudentCapacity();
		}

		studentIDs[studentCount] = studentID;
		studentCount++;
	}

	string GetClassName()
	{
		return ClassName;
	}

	int GetStudentCount()
	{
		return studentCount;
	}

	string GetStudentID(int index)
	{
		if (index < 0 || index >= studentCount)
			return "";
		return studentIDs[index];
	}

	ClassNode* GetNext()
	{
		return next;
	}

	void SetNext(ClassNode* ptr)
	{
		next = ptr;
	}

};

class DepartmentNode {

	string DeptName;
	DepartmentNode* next;
	ClassNode* ClassHeadPtr;

	string* Subjects;
	int SubjectCount;
	int SubjectSize;

	void IncreaseSubjectSize()
	{
		int NewSize = SubjectSize * 2;
		string* temp = new string[NewSize];

		for (int i = 0; i < SubjectCount; i++)
		{
			temp[i] = Subjects[i];
		}

		delete[] Subjects;
		Subjects = temp;
		SubjectSize = NewSize;
	}

public:

	DepartmentNode(string deptname = "")
	{
		DeptName = deptname;
		next = nullptr;
		ClassHeadPtr = nullptr;

		SubjectSize = 1;
		Subjects = new string[SubjectSize];
		Subjects[0] = "";
		SubjectCount = 0;
	}

	void AddClass(string ClassName = "")
	{
		ClassNode* ClassPtr = new ClassNode(ClassName);

		if (ClassHeadPtr == nullptr)
		{
			ClassHeadPtr = ClassPtr;
		}
		else
		{
			ClassNode* temp = ClassHeadPtr;

			while (temp->GetNext() != nullptr)
			{
				temp = temp->GetNext();
			}

			temp->SetNext(ClassPtr);
		}
	}

	ClassNode* FindOrCreateClass(string className)
	{
		ClassNode* temp = ClassHeadPtr;
		ClassNode* prev = nullptr;

		while (temp != nullptr)
		{
			if (temp->GetClassName() == className)
			{
				return temp;
			}
			prev = temp;
			temp = temp->GetNext();
		}

		ClassNode* newClass = new ClassNode(className);
		if (prev == nullptr)
		{
			ClassHeadPtr = newClass;
		}
		else
		{
			prev->SetNext(newClass);
		}
		return newClass;
	}

	void AddStudent(string className, string studentID)
	{
		ClassNode* cls = FindOrCreateClass(className);
		cls->AddStudentID(studentID);
	}

	void AddSubject(string s)
	{
		if (SubjectCount == SubjectSize)
		{
			IncreaseSubjectSize();
		}

		Subjects[SubjectCount] = s;
		SubjectCount++;
	}

	string GetDeptName()
	{
		return DeptName;
	}

	string GetSubject(int i = 0)
	{
		if (i >= SubjectCount)
		{
			return "";
		}

		else
		{
			return Subjects[i];
		}
	}

	int GetSubjectCount()
	{
		return SubjectCount;
	}

	DepartmentNode* GetNext()
	{
		return next;
	}

	void SetNext(DepartmentNode* ptr)
	{
		next = ptr;
	}

	ClassNode* GetFirstClass()
	{
		return ClassHeadPtr;
	}

	~DepartmentNode()
	{
		ClassNode* currentClass = ClassHeadPtr;
		while (currentClass != nullptr)
		{
			ClassNode* nextClass = currentClass->GetNext();
			delete currentClass;
			currentClass = nextClass;
		}

		delete[] Subjects;
	}
};


class SchoolNode {

	string SchoolID;
	string name;
	string sector;
	float latitude;
	float longitude;
	float rating;
	SchoolNode* next;
	DepartmentNode* DepartmentHeadPtr;

public:
	SchoolNode(string ID = "", string Name = "", string Sector = "", float lat = 0, float longit = 0, float rate = 0)
	{
		SchoolID = ID;
		name = Name;
		sector = Sector;
		latitude = lat;
		longitude = longit;
		rating = rate;
		next = nullptr;
		DepartmentHeadPtr = nullptr;
	}

	DepartmentNode* FindOrCreateDepartment(string deptName)
	{
		DepartmentNode* dept = DepartmentHeadPtr;
		DepartmentNode* prev = nullptr;

		while (dept != nullptr)
		{
			if (dept->GetDeptName() == deptName)
			{
				return dept;
			}
			prev = dept;
			dept = dept->GetNext();
		}

		DepartmentNode* newDept = new DepartmentNode(deptName);
		if (prev == nullptr)
		{
			DepartmentHeadPtr = newDept;
		}
		else {
			prev->SetNext(newDept);
		}
		return newDept;
	}

	void AddStudent(string deptName, string className, string studentID)
	{
		if (deptName == "")
		{
			return;
		}

		DepartmentNode* dept = FindOrCreateDepartment(deptName);
		dept->AddStudent(className, studentID);
	}

	bool SearchSubject(string SubjectToFind)
	{
		if (DepartmentHeadPtr == nullptr)
		{
			throw out_of_range("no department exists yet");
		}

		else
		{
			DepartmentNode* dept = DepartmentHeadPtr;
			int i = 0;

			while (dept != nullptr)
			{
				while (i < dept->GetSubjectCount())
				{
					if (dept->GetSubject(i) == SubjectToFind)
					{
						return 1;
					}
					i++;
				}
				i = 0;
				dept = dept->GetNext();
			}

			return 0;
		}
	}

	SchoolNode* GetNext()
	{
		return next;
	}

	void SetNext(SchoolNode* ptr)
	{
		next = ptr;
	}

	float GetLatitude()
	{
		return latitude;
	}

	float GetLongitude()
	{
		return longitude;
	}

	string GetSchoolID() {
		return SchoolID;
	}

	string GetName() {
		return name;
	}

	string GetSector() {
		return sector;
	}

	float GetRating() {
		return rating;
	}

	DepartmentNode* GetFirstDepartment()
	{
		return DepartmentHeadPtr;
	}

	void SetRating(float rate) {
		rating = rate;
	}

	void SetLatitude(float lat) {
		latitude = lat;
	}

	void SetLongitude(float longit) {
		longitude = longit;
	}

	void SetSector(string sec) {
		sector = sec;
	}

	~SchoolNode()
	{
		DepartmentNode* d = DepartmentHeadPtr;
		while (d != nullptr)
		{
			DepartmentNode* nx = d->GetNext();
			delete d;
			d = nx;
		}
	}

};

class SchoolTableNode {

	SchoolNode* schoolPtr;
	string schoolID;
	bool isOccupied;
	int index;
	SchoolTableNode* right;

public:
	SchoolTableNode(SchoolNode* school = nullptr, string ID = "", int idx = 0)
	{
		schoolPtr = school;
		schoolID = ID;
		index = idx;
		isOccupied = 0;
		right = nullptr;
	}

	bool IfOccupied()
	{
		return isOccupied;
	}

	SchoolNode* GetSchool()
	{
		return schoolPtr;
	}

	string GetSchoolID()
	{
		return schoolID;
	}

	int GetIndex()
	{
		return index;
	}

	SchoolTableNode* GetRightPtr()
	{
		return right;
	}

	void SetSchool(SchoolNode* school)
	{
		schoolPtr = school;
	}

	void SetOccupied(bool val)
	{
		isOccupied = val;
	}

	void SetRightPtr(SchoolTableNode* ptr)
	{
		right = ptr;
	}
};

class SchoolHashTable {

	SchoolTableNode* SchoolTable;
	int TableSize;

public:
	SchoolHashTable(int size = 5)
	{
		if (size <= 0)
			size = 5;

		TableSize = size;
		SchoolTable = new SchoolTableNode[TableSize];
	}

	int HashFunction(string key)
	{
		long long hash = 0;
		long long p = 31;
		long long pow = 1;
		int mod = TableSize;
		if (mod <= 1)
			mod = 1;

		for (int i = 0; key[i] != '\0'; i++)
		{
			hash = (hash + ((long long)(unsigned char)key[i] * pow)) % mod;
			pow = (pow * p) % mod;
		}

		return (int)hash;
	}

	void AddSchool(SchoolNode* school, string schoolID)
	{
		if (schoolID == "")
			return;

		int Index = HashFunction(schoolID);

		if (SchoolTable[Index].IfOccupied() == 0)
		{
			SchoolTable[Index] = SchoolTableNode(school, schoolID, Index);
			SchoolTable[Index].SetOccupied(true);
		}
		else
		{
			SchoolTableNode* temp = &SchoolTable[Index];

			while (temp != nullptr)
			{
				if (temp->GetSchoolID() == schoolID && temp->IfOccupied())
				{
					return;
				}
				if (temp->GetRightPtr() == nullptr)
				{
					break;
				}
				temp = temp->GetRightPtr();
			}

			SchoolTableNode* newNode = new SchoolTableNode(school, schoolID, Index);
			newNode->SetOccupied(true);
			temp->SetRightPtr(newNode);
		}
	}

	SchoolNode* SearchByID(string schoolID)
	{
		if (schoolID == "")
			return nullptr;

		int idx = HashFunction(schoolID);
		SchoolTableNode* head = &SchoolTable[idx];

		while (head != nullptr)
		{
			if (head->GetSchoolID() == schoolID && head->IfOccupied())
				return head->GetSchool();

			head = head->GetRightPtr();
		}
		return nullptr;
	}

	int CountSchools()
	{
		int count = 0;
		for (int i = 0; i < TableSize; i++)
		{
			if (SchoolTable[i].IfOccupied())
			{
				count++;
				SchoolTableNode* temp = SchoolTable[i].GetRightPtr();
				while (temp != nullptr)
				{
					if (temp->IfOccupied())
					{
						count++;
					}
					temp = temp->GetRightPtr();
				}
			}
		}
		return count;
	}

	void DisplayAllSchools() {
		for (int i = 0; i < TableSize; i++) {
			if (SchoolTable[i].IfOccupied()) {
				SchoolTableNode* temp = &SchoolTable[i];
				while (temp != nullptr) {
					if (temp->IfOccupied()) {
						SchoolNode* school = temp->GetSchool();
						if (school) {
							cout << "Name: " << school->GetName()
								<< ", ID: " << school->GetSchoolID()
								<< ", Sector: " << school->GetSector() << endl;
						}
					}
					temp = temp->GetRightPtr();
				}
			}
		}
	}

	~SchoolHashTable()
	{
		if (SchoolTable)
		{
			for (int i = 0; i < TableSize; i++)
			{
				SchoolTableNode* head = SchoolTable[i].GetRightPtr();
				while (head != nullptr)
				{
					SchoolTableNode* nxt = head->GetRightPtr();
					delete head;
					head = nxt;
				}
			}
			delete[] SchoolTable;
			SchoolTable = nullptr;
		}
	}
};


class SchoolGraph {
	struct Edge {
		int targetSchool;
		float distance;
		Edge* next;

		Edge(int target, float dist) {
			targetSchool = target;
			distance = dist;
			next = nullptr;
		}
	};

	SchoolNode** schools;
	Edge** connections;
	int totalSchools;

public:
	SchoolGraph(int n) {
		totalSchools = n;
		schools = new SchoolNode * [totalSchools];
		connections = new Edge * [totalSchools];

		for (int i = 0; i < totalSchools; i++) {
			schools[i] = nullptr;
			connections[i] = nullptr;
		}
	}

	void AddSchool(int index, SchoolNode* school) {
		if (index < 0 || index >= totalSchools)
			return;
		schools[index] = school;
	}

	void ConnectSchools(int from, int to) {
		if (from < 0 || from >= totalSchools)
			return;
		if (to < 0 || to >= totalSchools)
			return;
		if (schools[from] == nullptr || schools[to] == nullptr)
			return;

		float fromLat = schools[from]->GetLatitude();
		float fromLon = schools[from]->GetLongitude();
		float toLat = schools[to]->GetLatitude();
		float toLon = schools[to]->GetLongitude();

		float straightDist = sqrt(pow(fromLat - toLat, 2) + pow(fromLon - toLon, 2));

		string fromSector = schools[from]->GetSector();
		string toSector = schools[to]->GetSector();

		float roadMultiplier = 1.0f;

		if (fromSector == toSector) {
			roadMultiplier = 1.2f;
		}
		else {
			roadMultiplier = 1.8f;

			if (fromSector.length() >= 2 && toSector.length() >= 2) {
				if (fromSector[0] == toSector[0]) {
					roadMultiplier = 1.5f;
				}
			}
		}

		float roadDist = straightDist * roadMultiplier;


		float variation = 0.9f + 0.2f * (((from * 13 + to * 17) % 100) / 100.0f);
		roadDist *= variation;

		Edge* newEdge = new Edge(to, roadDist);
		newEdge->next = connections[from];
		connections[from] = newEdge;

		Edge* reverseEdge = new Edge(from, roadDist);
		reverseEdge->next = connections[to];
		connections[to] = reverseEdge;
	}

	SchoolNode* FindNearestSchoolDijkstra(int startSchoolIndex) {
		if (startSchoolIndex < 0 || startSchoolIndex >= totalSchools)
			return nullptr;
		if (schools[startSchoolIndex] == nullptr)
			return nullptr;

		float* distanceArray = new float[totalSchools];
		bool* visitedArray = new bool[totalSchools];

		for (int i = 0; i < totalSchools; i++) {
			distanceArray[i] = 9999999.0f;
			visitedArray[i] = false;
		}
		distanceArray[startSchoolIndex] = 0;

		for (int count = 0; count < totalSchools; count++) {
			int currentIndex = -1;
			float minDistance = 9999999.0f;

			for (int i = 0; i < totalSchools; i++) {
				if (!visitedArray[i] && distanceArray[i] < minDistance) {
					minDistance = distanceArray[i];
					currentIndex = i;
				}
			}

			if (currentIndex == -1)
				break;

			visitedArray[currentIndex] = true;

			Edge* currentEdge = connections[currentIndex];
			while (currentEdge != nullptr) {
				int neighborIndex = currentEdge->targetSchool;
				float edgeDistance = currentEdge->distance;

				if (!visitedArray[neighborIndex] && distanceArray[currentIndex] + edgeDistance < distanceArray[neighborIndex]) {
					distanceArray[neighborIndex] = distanceArray[currentIndex] + edgeDistance;
				}
				currentEdge = currentEdge->next;
			}
		}

		int nearestIndex = -1;
		float minDistanceFound = 9999999.0f;
		for (int i = 0; i < totalSchools; i++) {
			if (i != startSchoolIndex && schools[i] != nullptr && distanceArray[i] < minDistanceFound) {
				minDistanceFound = distanceArray[i];
				nearestIndex = i;
			}
		}

		delete[] distanceArray;
		delete[] visitedArray;

		if (nearestIndex != -1)
			return schools[nearestIndex];
		else
			return nullptr;
	}



	~SchoolGraph()
	{
		for (int i = 0; i < totalSchools; i++)
		{
			Edge* current = connections[i];
			while (current != nullptr)
			{
				Edge* next = current->next;
				delete current;
				current = next;
			}
		}
		delete[] schools;
		delete[] connections;
	}
};

class SchoolSystem {
private:
	SchoolNode** schoolsArray;
	int schoolsCount;
	int schoolsCapacity;
	SchoolGraph* schoolGraph;
	Graph* cityGraph;

	StudentHashTable* allStudents;
	FacultyHashTable* allFaculty;
	SchoolHashTable* allSchools;

	void ResizeSchoolsArray()
	{
		int newCapacity;
		if (schoolsCapacity == 0)
		{
			newCapacity = 1;
		}
		else
		{
			newCapacity = schoolsCapacity * 2;
		}

		SchoolNode** newArray = new SchoolNode * [newCapacity];
		for (int i = 0; i < schoolsCount; i++)
		{
			newArray[i] = schoolsArray[i];
		}

		if (schoolsArray != nullptr)
		{
			delete[] schoolsArray;
		}
		schoolsArray = newArray;
		schoolsCapacity = newCapacity;
	}

public:
	SchoolSystem(Graph* cityGraph)
	{
		this->cityGraph = cityGraph;

		schoolsArray = nullptr;
		schoolsCount = 0;
		schoolsCapacity = 0;
		schoolGraph = nullptr;

		allStudents = new StudentHashTable(101);
		allFaculty = new FacultyHashTable(101);
		allSchools = new SchoolHashTable(101);
	}

	void LoadFromFile(const string& filename)
	{
		ifstream file(filename);
		if (!file.is_open())
		{
			throw runtime_error("Cannot open file: " + filename);
		}

		char line[1000];
		file.getline(line, 1000);

		if (schoolsArray != nullptr)
		{
			for (int i = 0; i < schoolsCount; i++)
			{
				delete schoolsArray[i];
			}
			delete[] schoolsArray;
			schoolsArray = nullptr;
		}

		schoolsCount = 0;
		schoolsCapacity = 0;

		float usedCoords[100][2];
		int usedCount = 0;

		while (file.getline(line, 1000))
		{
			if (line[0] == '\0') continue;

			if (schoolsCount == schoolsCapacity)
			{
				ResizeSchoolsArray();
			}

			string schoolID = "";
			string name = "";
			string sector = "";
			string ratingStr = "";
			string subjectsStr = "";

			int fieldCount = 0;
			bool inQuotes = false;
			string currentField = "";

			for (int pos = 0; line[pos] != '\0'; pos++)
			{
				char c = line[pos];

				if (c == '"')
				{
					inQuotes = !inQuotes;
					continue;
				}

				if (c == ',' && !inQuotes)
				{
					switch (fieldCount)
					{
					case 0: schoolID = currentField; break;
					case 1: name = currentField; break;
					case 2: sector = currentField; break;
					case 3: ratingStr = currentField; break;
					case 4: subjectsStr = currentField; break;
					}
					currentField = "";
					fieldCount++;
				}
				else
				{
					currentField += c;
				}
			}

			if (fieldCount == 4)
			{
				subjectsStr = currentField;
			}
			else if (fieldCount == 3)
			{
				ratingStr = currentField;
			}

			float rating = 0.0f;
			if (!ratingStr.empty())
			{
				float num = 0.0f;
				float decimal = 0.0f;
				float decimalPlace = 0.1f;
				bool afterDecimal = false;

				for (int i = 0; i < ratingStr.length(); i++)
				{
					if (ratingStr[i] == '.')
					{
						afterDecimal = true;
					}
					else if (ratingStr[i] >= '0' && ratingStr[i] <= '9')
					{
						if (!afterDecimal)
						{
							num = num * 10.0f + (ratingStr[i] - '0');
						}
						else
						{
							decimal = decimal + (ratingStr[i] - '0') * decimalPlace;
							decimalPlace *= 0.1f;
						}
					}
				}
				rating = num + decimal;
			}

			float latitude = 0.0f;
			float longitude = 0.0f;

			if (sector == "G-10")
			{
				latitude = 33.684f;
				longitude = 73.025f;
			}
			else if (sector == "F-8")
			{
				latitude = 33.709f;
				longitude = 73.037f;
			}
			else if (sector == "F-6")
			{
				latitude = 33.727f;
				longitude = 73.075f;
			}
			else if (sector == "G-9")
			{
				latitude = 33.700f;
				longitude = 73.030f;
			}
			else if (sector == "F-7")
			{
				latitude = 33.721f;
				longitude = 73.052f;
			}
			else if (sector == "Blue Area")
			{
				latitude = 33.720f;
				longitude = 73.065f;
			}
			else
			{
				latitude = 33.700f;
				longitude = 73.040f;
			}

			float variation = 0.001f * (schoolsCount + 1);
			latitude += variation;
			longitude += variation;

			bool isUnique = true;
			for (int i = 0; i < usedCount; i++)
			{
				float diffLat = latitude - usedCoords[i][0];
				float diffLon = longitude - usedCoords[i][1];
				if (diffLat < 0) diffLat = -diffLat;
				if (diffLon < 0) diffLon = -diffLon;

				if (diffLat < 0.0001f && diffLon < 0.0001f)
				{
					latitude += 0.0002f;
					longitude += 0.0002f;
					break;
				}
			}

			if (!cityGraph) {
				cout << "Error: City Graph has not been initialized yet" << endl;
				return;
			}
			if (!cityGraph->hasFreeSlots()) {
				cout << "Error: City cannot have any more buildings" << endl;
				return;
			}
			if (cityGraph->containsLocationId(schoolID)) {
				cout << "Error: City already has a buidling with ID " << schoolID << endl;
				continue;
			}
			if (cityGraph->hasNonStopAtLocation(latitude, longitude)) {
				cout << "Error: City already has a buidling at latitude " << latitude << " and longitude" << longitude << endl;
				continue;
			}
			if (!cityGraph->addLocation(schoolID, name, latitude, longitude)) {
				cout << "Error: School cannot be added to the city" << endl;
				continue;
			}

			usedCoords[usedCount][0] = latitude;
			usedCoords[usedCount][1] = longitude;
			usedCount++;

			SchoolNode* newSchool = new SchoolNode(schoolID, name, sector, latitude, longitude, rating);
			schoolsArray[schoolsCount] = newSchool;

			allSchools->AddSchool(newSchool, schoolID);

			if (!subjectsStr.empty())
			{
				DepartmentNode* dept = newSchool->FindOrCreateDepartment("General");
				string currentSubject = "";
				bool inSubjectQuotes = false;

				for (int i = 0; i <= subjectsStr.length(); i++)
				{
					char c = (i < subjectsStr.length()) ? subjectsStr[i] : '\0';

					if (c == '"')
					{
						inSubjectQuotes = !inSubjectQuotes;
						continue;
					}

					if ((c == ',' && !inSubjectQuotes) || c == '\0')
					{
						if (!currentSubject.empty())
						{
							int start = 0;
							int end = currentSubject.length() - 1;

							while (start <= end && currentSubject[start] == ' ')
							{
								start++;
							}
							while (end >= start && currentSubject[end] == ' ')
							{
								end--;
							}

							if (start <= end)
							{
								string cleanSubject = "";
								for (int j = start; j <= end; j++)
								{
									cleanSubject += currentSubject[j];
								}
								dept->AddSubject(cleanSubject);
							}
						}
						currentSubject = "";
					}
					else
					{
						currentSubject += c;
					}
				}
			}

			schoolsCount++;
		}

		file.close();

		if (schoolGraph != nullptr)
		{
			delete schoolGraph;
		}
		schoolGraph = new SchoolGraph(schoolsCount);
		for (int i = 0; i < schoolsCount; i++)
		{
			schoolGraph->AddSchool(i, schoolsArray[i]);
		}

		for (int i = 0; i < schoolsCount; i++)
		{
			for (int j = i + 1; j < schoolsCount; j++)
			{
				if (schoolsArray[i]->GetSector() == schoolsArray[j]->GetSector())
				{
					schoolGraph->ConnectSchools(i, j);
				}
			}

			if (i + 1 < schoolsCount)
			{
				schoolGraph->ConnectSchools(i, (i + 1) % schoolsCount);
			}
		}
	}

public:
	void ShowSectorCoordinateRanges() {
		if (schoolsCount == 0) {
			cout << "No schools in system yet." << endl;
			return;
		}

		const int MAX_SECTORS = 100;
		string sectorNames[MAX_SECTORS];
		float minLat[MAX_SECTORS];
		float maxLat[MAX_SECTORS];
		float minLon[MAX_SECTORS];
		float maxLon[MAX_SECTORS];
		int sectorCount = 0;

		for (int i = 0; i < schoolsCount; i++) {
			string currentSector = schoolsArray[i]->GetSector();
			float currentLat = schoolsArray[i]->GetLatitude();
			float currentLon = schoolsArray[i]->GetLongitude();

			int foundIndex = -1;
			for (int j = 0; j < sectorCount; j++) {
				if (sectorNames[j] == currentSector) {
					foundIndex = j;
					break;
				}
			}

			if (foundIndex == -1) {
				if (sectorCount < MAX_SECTORS) {
					sectorNames[sectorCount] = currentSector;
					minLat[sectorCount] = currentLat;
					maxLat[sectorCount] = currentLat;
					minLon[sectorCount] = currentLon;
					maxLon[sectorCount] = currentLon;
					sectorCount++;
				}
			}
			else {
				if (currentLat < minLat[foundIndex]) {
					minLat[foundIndex] = currentLat;
				}
				if (currentLat > maxLat[foundIndex]) {
					maxLat[foundIndex] = currentLat;
				}
				if (currentLon < minLon[foundIndex]) {
					minLon[foundIndex] = currentLon;
				}
				if (currentLon > maxLon[foundIndex]) {
					maxLon[foundIndex] = currentLon;
				}
			}
		}

		cout << "\n=== SECTOR COORDINATE RANGES ===" << endl;
		cout << "Sector\t\t\tLatitude Range\t\t\tLongitude Range" << endl;
		cout << "----------------------------------------------------------------" << endl;

		for (int i = 0; i < sectorCount; i++) {
			cout << sectorNames[i];

			if (sectorNames[i].length() < 8) {
				cout << "\t\t\t";
			}
			else if (sectorNames[i].length() < 16) {
				cout << "\t\t";
			}
			else {
				cout << "\t";
			}

			// FIX: Only show "Exact" if min and max are REALLY the same
			if (maxLat[i] - minLat[i] < 0.00001f) {
				cout << minLat[i] << " (Exact)";
			}
			else {
				cout << minLat[i] << " to " << maxLat[i];
			}

			cout << "\t\t";

			if (maxLon[i] - minLon[i] < 0.00001f) {
				cout << minLon[i] << " (Exact)";
			}
			else {
				cout << minLon[i] << " to " << maxLon[i];
			}

			cout << endl;
		}

		cout << "\n=== SCHOOLS PER SECTOR ===" << endl;
		for (int i = 0; i < sectorCount; i++) {
			int count = 0;
			for (int j = 0; j < schoolsCount; j++) {
				if (schoolsArray[j]->GetSector() == sectorNames[i]) {
					count++;
				}
			}
			cout << sectorNames[i] << ": " << count << " school(s)" << endl;
		}
	}

	/*
	void AddSchool(string schoolID, string name, string sector, float lat, float lon, float rating)
	{

		// First check if coordinates already exist
		bool coordinatesExist = false;
		for (int i = 0; i < schoolsCount; i++) {
			float existingLat = schoolsArray[i]->GetLatitude();
			float existingLon = schoolsArray[i]->GetLongitude();

			float latDiff = lat - existingLat;
			float lonDiff = lon - existingLon;

			if (latDiff < 0) latDiff = -latDiff;
			if (lonDiff < 0) lonDiff = -lonDiff;

			if (latDiff < 0.0001f && lonDiff < 0.0001f) {
				coordinatesExist = true;
				cout << "ERROR: Coordinates (" << lat << ", " << lon << ") ";
				cout << "already used by school: " << schoolsArray[i]->GetName();
				cout << " (ID: " << schoolsArray[i]->GetSchoolID() << ")" << endl;
				cout << "Please choose different coordinates." << endl;
				return;
			}
		}

		// Check if sector exists and validate coordinates match sector pattern
		bool sectorExists = false;
		float minLat = 0.0f, maxLat = 0.0f, minLon = 0.0f, maxLon = 0.0f;
		int sectorSchoolCount = 0;

		for (int i = 0; i < schoolsCount; i++) {
			if (schoolsArray[i]->GetSector() == sector) {
				sectorExists = true;
				sectorSchoolCount++;

				if (sectorSchoolCount == 1) {
					minLat = schoolsArray[i]->GetLatitude();
					maxLat = schoolsArray[i]->GetLatitude();
					minLon = schoolsArray[i]->GetLongitude();
					maxLon = schoolsArray[i]->GetLongitude();
				}
				else {
					float schoolLat = schoolsArray[i]->GetLatitude();
					float schoolLon = schoolsArray[i]->GetLongitude();

					if (schoolLat < minLat) minLat = schoolLat;
					if (schoolLat > maxLat) maxLat = schoolLat;
					if (schoolLon < minLon) minLon = schoolLon;
					if (schoolLon > maxLon) maxLon = schoolLon;
				}
			}
		}

		if (sectorExists) {
			// Calculate tolerance: 10% of sector range or 0.001 minimum
			float latRange = maxLat - minLat;
			float lonRange = maxLon - minLon;

			float latTolerance = 0.001f;
			float lonTolerance = 0.001f;

			if (latRange > 0.001f) latTolerance = latRange * 0.5f;
			if (lonRange > 0.001f) lonTolerance = lonRange * 0.5f;

			// Check if coordinates are within sector range
			bool latInRange = (lat >= minLat - latTolerance && lat <= maxLat + latTolerance);
			bool lonInRange = (lon >= minLon - lonTolerance && lon <= maxLon + lonTolerance);

			if (!latInRange || !lonInRange) {
				cout << "ERROR: Coordinates (" << lat << ", " << lon << ") ";
				cout << "are not in sector " << sector << " range." << endl;
				cout << "Sector " << sector << " coordinates range:" << endl;
				cout << "  Latitude: " << minLat << " to " << maxLat << endl;
				cout << "  Longitude: " << minLon << " to " << maxLon << endl;
				cout << "School cannot be added at these coordinates." << endl;
				return;
			}

			cout << "Coordinates validated for sector " << sector << "." << endl;
		}
		else {
			// New sector - give guidance
			cout << "NOTE: Adding first school in new sector: " << sector << endl;
			cout << "Future schools in this sector should have similar coordinates." << endl;
		}

		if (schoolsCount == schoolsCapacity)
		{
			ResizeSchoolsArray();
		}

		SchoolNode* newSchool = new SchoolNode(schoolID, name, sector, lat, lon, rating);
		schoolsArray[schoolsCount] = newSchool;
		allSchools->AddSchool(newSchool, schoolID);
		schoolsCount++;

		cout << "Adding school to sector: " << sector << endl;
		cout << "Total schools in " << sector << " sector: " << (sectorSchoolCount + 1) << endl;

		if (schoolGraph != nullptr)
		{
			delete schoolGraph;
		}

		schoolGraph = new SchoolGraph(schoolsCount);
		for (int i = 0; i < schoolsCount; i++)
		{
			schoolGraph->AddSchool(i, schoolsArray[i]);
		}

		for (int i = 0; i < schoolsCount; i++)
		{
			for (int j = i + 1; j < schoolsCount; j++)
			{
				if (schoolsArray[i]->GetSector() == schoolsArray[j]->GetSector())
				{
					schoolGraph->ConnectSchools(i, j);
				}
			}

			if (i + 1 < schoolsCount)
			{
				schoolGraph->ConnectSchools(i, (i + 1) % schoolsCount);
			}
		}

		cout << "School added successfully!" << endl;
	}
	*/

	void AddSchool(string schoolID, string name, string sector, float lat, float lon, float rating) {

		if (!cityGraph) {
			cout << "Error: City graph not initialized yet" << endl;
			return;
		}

		if (!cityGraph->hasFreeSlots()) {
			cout << "Error: City cannot have anymore landmarks" << endl;
			return;
		}

		if (cityGraph->containsLocationId(schoolID)) {
			cout << "Error: A location with ID " << schoolID << " already exists in the city" << endl;
			return;
		}

		if (cityGraph->hasNonStopAtLocation(lat, lon)) {
			cout << "Error: There is already a building at (" << lat << ", " << lon << ")" << endl;
			return;
		}

		// First check if coordinates already exist
		bool coordinatesExist = false;
		for (int i = 0; i < schoolsCount; i++) {
			float existingLat = schoolsArray[i]->GetLatitude();
			float existingLon = schoolsArray[i]->GetLongitude();

			float latDiff = lat - existingLat;
			float lonDiff = lon - existingLon;

			if (latDiff < 0) latDiff = -latDiff;
			if (lonDiff < 0) lonDiff = -lonDiff;

			if (latDiff < 0.0001f && lonDiff < 0.0001f) {
				coordinatesExist = true;
				cout << "ERROR: Coordinates (" << lat << ", " << lon << ") ";
				cout << "already used by school: " << schoolsArray[i]->GetName();
				cout << " (ID: " << schoolsArray[i]->GetSchoolID() << ")" << endl;
				cout << "Please choose different coordinates." << endl;
				return;
			}
		}

		// Check if sector exists and validate coordinates match sector pattern
		bool sectorExists = false;
		float minLat = 0.0f, maxLat = 0.0f, minLon = 0.0f, maxLon = 0.0f;
		int sectorSchoolCount = 0;

		for (int i = 0; i < schoolsCount; i++) {
			if (schoolsArray[i]->GetSector() == sector) {
				sectorExists = true;
				sectorSchoolCount++;

				if (sectorSchoolCount == 1) {
					minLat = schoolsArray[i]->GetLatitude();
					maxLat = schoolsArray[i]->GetLatitude();
					minLon = schoolsArray[i]->GetLongitude();
					maxLon = schoolsArray[i]->GetLongitude();
				}
				else {
					float schoolLat = schoolsArray[i]->GetLatitude();
					float schoolLon = schoolsArray[i]->GetLongitude();

					if (schoolLat < minLat) minLat = schoolLat;
					if (schoolLat > maxLat) maxLat = schoolLat;
					if (schoolLon < minLon) minLon = schoolLon;
					if (schoolLon > maxLon) maxLon = schoolLon;
				}
			}
		}

		if (sectorExists) {
			// Calculate tolerance: 10% of sector range or 0.001 minimum
			float latRange = maxLat - minLat;
			float lonRange = maxLon - minLon;

			float latTolerance = 0.001f;
			float lonTolerance = 0.001f;

			if (latRange > 0.001f) latTolerance = latRange * 0.5f;
			if (lonRange > 0.001f) lonTolerance = lonRange * 0.5f;

			// Check if coordinates are within sector range
			bool latInRange = (lat >= minLat - latTolerance && lat <= maxLat + latTolerance);
			bool lonInRange = (lon >= minLon - lonTolerance && lon <= maxLon + lonTolerance);

			if (!latInRange || !lonInRange) {
				cout << "ERROR: Coordinates (" << lat << ", " << lon << ") ";
				cout << "are not in sector " << sector << " range." << endl;
				cout << "Sector " << sector << " coordinates range:" << endl;
				cout << "  Latitude: " << minLat << " to " << maxLat << endl;
				cout << "  Longitude: " << minLon << " to " << maxLon << endl;
				cout << "School cannot be added at these coordinates." << endl;
				return;
			}

			cout << "Coordinates validated for sector " << sector << "." << endl;
		}
		else {
			// New sector - give guidance
			cout << "NOTE: Adding first school in new sector: " << sector << endl;
			cout << "Future schools in this sector should have similar coordinates." << endl;
		}

		if (!cityGraph->addLocation(schoolID, name, lat, lon)) {
			cout << "Cannot add school at latitude " << lat << " and longitude " << lon << endl;
			return;
		}

		if (schoolsCount == schoolsCapacity) ResizeSchoolsArray();

		SchoolNode* newSchool = new SchoolNode(schoolID, name, sector, lat, lon, rating);
		schoolsArray[schoolsCount] = newSchool;
		allSchools->AddSchool(newSchool, schoolID);
		schoolsCount++;

		cout << "Adding school to sector: " << sector << endl;
		cout << "Total schools in " << sector << " sector: " << (sectorSchoolCount + 1) << endl;

		if (schoolGraph != nullptr) delete schoolGraph;

		schoolGraph = new SchoolGraph(schoolsCount);
		for (int i = 0; i < schoolsCount; i++)
		{
			schoolGraph->AddSchool(i, schoolsArray[i]);
		}

		for (int i = 0; i < schoolsCount; i++)
		{
			for (int j = i + 1; j < schoolsCount; j++)
			{
				if (schoolsArray[i]->GetSector() == schoolsArray[j]->GetSector())
				{
					schoolGraph->ConnectSchools(i, j);
				}
			}

			if (i + 1 < schoolsCount)
			{
				schoolGraph->ConnectSchools(i, (i + 1) % schoolsCount);
			}
		}
		cout << "School added successfully!" << endl;
	}

	void AddStudent(string schoolID, string deptName, string className,
		string studentName, int age, string studentID)
	{
		SchoolNode* school = allSchools->SearchByID(schoolID);
		if (school == nullptr)
		{
			return;
		}

		school->AddStudent(deptName, className, studentID);
		allStudents->AddStudent(studentName, age, studentID, schoolID, deptName, className);
	}

	void AddFaculty(string schoolID, string deptName,
		string facultyName, string facultyID, string specialization)
	{
		SchoolNode* school = allSchools->SearchByID(schoolID);
		if (school == nullptr)
		{
			return;
		}

		DepartmentNode* dept = school->FindOrCreateDepartment(deptName);
		allFaculty->AddFaculty(facultyName, facultyID, specialization, schoolID, deptName);
	}

	StudentTableNode* FindStudent(string studentID)
	{
		return allStudents->SearchByID(studentID);
	}

	FacultyTableNode* FindFaculty(string facultyID)
	{
		return allFaculty->SearchByID(facultyID);
	}

	SchoolNode* FindSchool(string schoolID)
	{
		return allSchools->SearchByID(schoolID);
	}

	void SearchBySubject(string subject)
	{
		bool found = false;
		cout << "Schools offering \"" << subject << "\":" << endl;

		for (int i = 0; i < schoolsCount; i++)
		{
			try
			{
				if (schoolsArray[i]->SearchSubject(subject))
				{
					cout << " " << schoolsArray[i]->GetName()
						<< " (ID: " << schoolsArray[i]->GetSchoolID()
						<< ", Sector: " << schoolsArray[i]->GetSector() << ")" << endl;
					found = true;
				}
			}
			catch (const out_of_range& e)
			{
				continue;
			}
		}

		if (!found)
		{
			cout << "No schools offer this subject." << endl;
		}
	}

	SchoolNode* FindNearestSchoolByID(string schoolID)
	{
		if (schoolGraph == nullptr)
		{
			return nullptr;
		}

		// Find the index of the school with given ID
		int targetIndex = -1;
		for (int i = 0; i < schoolsCount; i++)
		{
			if (schoolsArray[i]->GetSchoolID() == schoolID)
			{
				targetIndex = i;
				break;
			}
		}

		if (targetIndex == -1)
		{
			return nullptr;
		}

		return schoolGraph->FindNearestSchoolDijkstra(targetIndex);
	}

	SchoolNode* FindNearestSchoolByLocation(float lat, float lon)
	{
		if (schoolsCount == 0)
		{
			return nullptr;
		}

		int closestIndex = -1;
		float minDistance = 9999999.0f;

		for (int i = 0; i < schoolsCount; i++)
		{
			float schoolLat = schoolsArray[i]->GetLatitude();
			float schoolLon = schoolsArray[i]->GetLongitude();

			float diffLat = lat - schoolLat;
			float diffLon = lon - schoolLon;
			float distance = sqrt(diffLat * diffLat + diffLon * diffLon);

			if (distance < minDistance)
			{
				minDistance = distance;
				closestIndex = i;
			}
		}

		if (closestIndex != -1)
		{
			//return FindNearestSchoolByID(schoolsArray[closestIndex]->GetSchoolID());
			return schoolsArray[closestIndex];
		}

		return nullptr;
	}

	int GetSchoolCount()
	{
		return schoolsCount;
	}

	SchoolNode* GetSchool(int index)
	{
		if (index < 0 || index >= schoolsCount)
		{
			return nullptr;
		}
		return schoolsArray[index];
	}

	void DisplayOrganogram()
	{
		if (schoolsCount == 0)
		{
			cout << "No schools in system." << endl;
			return;
		}

		cout << "EDUCATION SYSTEM HIERARCHY" << endl;
		cout << "==========================" << endl;

		for (int i = 0; i < schoolsCount; i++)
		{
			SchoolNode* school = schoolsArray[i];
			cout << endl << "SCHOOL: " << school->GetName();
			cout << " [ID: " << school->GetSchoolID() << "]";
			cout << " [Sector: " << school->GetSector() << "]";
			cout << " [Rating: " << school->GetRating() << "]" << endl;

			DepartmentNode* dept = school->GetFirstDepartment();
			int deptNum = 1;

			while (dept != nullptr)
			{
				cout << "  |-- DEPARTMENT " << deptNum << ": " << dept->GetDeptName() << endl;

				if (dept->GetSubjectCount() > 0)
				{
					cout << "  |     Subjects: ";
					for (int s = 0; s < dept->GetSubjectCount(); s++)
					{
						cout << dept->GetSubject(s);
						if (s < dept->GetSubjectCount() - 1) cout << ", ";
					}
					cout << endl;
				}

				ClassNode* cls = dept->GetFirstClass();
				int classNum = 1;

				while (cls != nullptr)
				{
					cout << "  |     |-- CLASS " << classNum << ": " << cls->GetClassName() << endl;

					int studentCount = cls->GetStudentCount();
					cout << "  |     |     Students: " << studentCount << endl;

					cls = cls->GetNext();
					classNum++;
				}

				if (classNum == 1)
				{
					cout << "  |     |-- (No classes)" << endl;
				}

				dept = dept->GetNext();
				deptNum++;
			}

			if (deptNum == 1)
			{
				cout << "  |-- (No departments)" << endl;
			}
		}

		cout << endl << "TOTAL SCHOOLS: " << schoolsCount << endl;
		cout << "TOTAL STUDENTS: " << allStudents->CountStudents() << endl;
		cout << "TOTAL FACULTY: " << allFaculty->CountFaculty() << endl;
	}

	void DisplayAllSchoolsFromHash()
	{
		allSchools->DisplayAllSchools();
	}

	Graph* getCityGraph() {
		return cityGraph;
	}
	SchoolGraph* getSchoolGraph() {
		return schoolGraph;
	}

	~SchoolSystem()
	{
		if (schoolsArray != nullptr)
		{
			for (int i = 0; i < schoolsCount; i++)
			{
				delete schoolsArray[i];
			}
			delete[] schoolsArray;
		}
		if (schoolGraph != nullptr)
		{
			delete schoolGraph;
		}
		delete allStudents;
		delete allFaculty;
		delete allSchools;
		cityGraph = nullptr;
	}
};

//int main() {
//	SchoolSystem schoolSystem;
//
//	try {
//		schoolSystem.LoadFromFile("Data/schools.csv");
//		cout << "Education Sector System Initialized" << endl;
//		cout << "Loaded " << schoolSystem.GetSchoolCount() << " schools." << endl;
//		cout << "--------------------------------------" << endl;
//	}
//	catch (const runtime_error& e) {
//		cout << "File loading failed." << endl;
//		cout << "Starting with empty system." << endl;
//	}
//
//	int choice;
//	do {
//		cout << endl;
//		cout << "--- EDUCATION SECTOR MANAGEMENT ---" << endl;
//		cout << "1. Display Full Organogram" << endl;
//		cout << "2. Search Student by ID" << endl;
//		cout << "3. Search Faculty by ID" << endl;
//		cout << "4. Search School by ID" << endl;
//		cout << "5. Search Schools by Subject" << endl;
//		cout << "6. Find Nearest School (by ID)" << endl;
//		cout << "7. Find Nearest School (by Location)" << endl;
//		cout << "8. Show Sector Coordinate Ranges" << endl;
//		cout << "9. Add New School" << endl;
//		cout << "10. Add New Student" << endl;
//		cout << "11. Add New Faculty" << endl;
//		cout << "12. Show all Schools" << endl;
//		cout << "13. Exit" << endl;
//		cout << "--------------------------------------" << endl;
//		cout << "Enter choice: ";
//
//		int temp;
//		if (!(cin >> temp)) {
//			cin.clear();
//			cin.ignore(1000, '\n');
//			cout << "Invalid input." << endl;
//			continue;
//		}
//		choice = temp;
//		cin.ignore(1000, '\n');
//
//		switch (choice) {
//		case 1: {
//			cout << endl;
//			schoolSystem.DisplayOrganogram();
//			break;
//		}
//		case 2: {
//			cout << endl;
//			cout << "Enter Student ID: ";
//			string id;
//			getline(cin, id);
//
//			if (id == "") {
//				cout << "Student ID cannot be empty." << endl;
//				break;
//			}
//
//			StudentTableNode* student = schoolSystem.FindStudent(id);
//			if (student) {
//				cout << "Student Found." << endl;
//				cout << "Name: " << student->GetName() << endl;
//				cout << "Age: " << student->GetAge() << endl;
//				cout << "ID: " << student->GetID() << endl;
//				cout << "School ID: " << student->GetSchoolID() << endl;
//				cout << "Department: " << student->GetDeptName() << endl;
//				cout << "Class: " << student->GetClassName() << endl;
//			}
//			else {
//				cout << "Student not found." << endl;
//			}
//			break;
//		}
//		case 3: {
//			cout << endl;
//			cout << "Enter Faculty ID: ";
//			string id;
//			getline(cin, id);
//
//			if (id == "") {
//				cout << "Faculty ID cannot be empty." << endl;
//				break;
//			}
//
//			FacultyTableNode* faculty = schoolSystem.FindFaculty(id);
//			if (faculty) {
//				cout << "Faculty Found." << endl;
//				cout << "Name: " << faculty->GetName() << endl;
//				cout << "ID: " << faculty->GetID() << endl;
//				cout << "Specialization: " << faculty->GetSpecialization() << endl;
//				cout << "School ID: " << faculty->GetSchoolID() << endl;
//				cout << "Department: " << faculty->GetDeptName() << endl;
//			}
//			else {
//				cout << "Faculty not found." << endl;
//			}
//			break;
//		}
//		case 4: {
//			cout << endl;
//			cout << "Enter School ID: ";
//			string id;
//			getline(cin, id);
//
//			if (id == "") {
//				cout << "School ID cannot be empty." << endl;
//				break;
//			}
//
//			SchoolNode* school = schoolSystem.FindSchool(id);
//			if (school) {
//				cout << "School Found." << endl;
//				cout << "Name: " << school->GetName() << endl;
//				cout << "ID: " << school->GetSchoolID() << endl;
//				cout << "Sector: " << school->GetSector() << endl;
//				cout << "Rating: " << school->GetRating() << endl;
//				cout << "Location: " << school->GetLatitude() << ", " << school->GetLongitude() << endl;
//			}
//			else {
//				cout << "School not found." << endl;
//			}
//			break;
//		}
//		case 5: {
//			cout << endl;
//			cout << "Enter subject name: ";
//			string subject;
//			getline(cin, subject);
//
//			if (subject == "") {
//				cout << "Subject cannot be empty." << endl;
//				break;
//			}
//
//			schoolSystem.SearchBySubject(subject);
//			break;
//		}
//		case 6: {
//			cout << endl;
//			cout << "Enter School ID: ";
//			string id;
//			getline(cin, id);
//
//			if (id == "") {
//				cout << "School ID cannot be empty." << endl;
//				break;
//			}
//
//			SchoolNode* school = schoolSystem.FindSchool(id);
//			if (!school) {
//				cout << "School not found." << endl;
//				break;
//			}
//
//			SchoolNode* nearest = schoolSystem.FindNearestSchoolByID(id);
//			if (nearest) {
//				cout << "Nearest school: " << nearest->GetName() << endl;
//				cout << "ID: " << nearest->GetSchoolID() << endl;
//				cout << "Sector: " << nearest->GetSector() << endl;
//				cout << "Rating: " << nearest->GetRating() << endl;
//			}
//			else {
//				cout << "No other schools found." << endl;
//			}
//			break;
//		}
//		case 7: {
//			cout << endl;
//			cout << "Enter latitude: ";
//			float lat;
//			if (!(cin >> lat)) {
//				cin.clear();
//				cin.ignore(1000, '\n');
//				cout << "Invalid latitude." << endl;
//				break;
//			}
//			cout << "Enter longitude: ";
//			float lon;
//			if (!(cin >> lon)) {
//				cin.clear();
//				cin.ignore(1000, '\n');
//				cout << "Invalid longitude." << endl;
//				break;
//			}
//			cin.ignore(1000, '\n');
//
//			SchoolNode* nearest = schoolSystem.FindNearestSchoolByLocation(lat, lon);
//			if (nearest) {
//				cout << "Nearest school: " << nearest->GetName() << endl;
//				cout << "ID: " << nearest->GetSchoolID() << endl;
//				cout << "Sector: " << nearest->GetSector() << endl;
//				cout << "Rating: " << nearest->GetRating() << endl;
//				cout << "Location: " << nearest->GetLatitude() << ", " << nearest->GetLongitude() << endl;
//			}
//			else {
//				cout << "No schools found near this location." << endl;
//			}
//			break;
//		}
//		case 8: {
//			cout << endl;
//			schoolSystem.ShowSectorCoordinateRanges();
//			break;
//		}
//		case 9: {
//			cout << endl;
//			string id, name, sector;
//			float lat, lon, rating;
//
//			cout << "Enter School ID: ";
//			getline(cin, id);
//			if (id == "") {
//				cout << "School ID cannot be empty." << endl;
//				break;
//			}
//
//			if (schoolSystem.FindSchool(id)) {
//				cout << "School with this ID already exists." << endl;
//				break;
//			}
//
//			cout << "Enter School Name: ";
//			getline(cin, name);
//			if (name == "") {
//				cout << "School name cannot be empty." << endl;
//				break;
//			}
//
//			cout << "Enter Sector: ";
//			getline(cin, sector);
//			if (sector == "") {
//				cout << "Sector cannot be empty." << endl;
//				break;
//			}
//
//			cout << "Enter Latitude: ";
//			if (!(cin >> lat)) {
//				cin.clear();
//				cin.ignore(1000, '\n');
//				cout << "Invalid latitude." << endl;
//				break;
//			}
//
//			cout << "Enter Longitude: ";
//			if (!(cin >> lon)) {
//				cin.clear();
//				cin.ignore(1000, '\n');
//				cout << "Invalid longitude." << endl;
//				break;
//			}
//
//			cout << "Enter Rating: ";
//			if (!(cin >> rating)) {
//				cin.clear();
//				cin.ignore(1000, '\n');
//				cout << "Invalid rating." << endl;
//				break;
//			}
//			cin.ignore(1000, '\n');
//
//			if (rating < 0 || rating > 10) {
//				cout << "Rating must be between 0 and 10." << endl;
//				break;
//			}
//
//			schoolSystem.AddSchool(id, name, sector, lat, lon, rating);
//			break;
//		}
//		case 10: {
//			cout << endl;
//			string schoolID, deptName, className, studentName, studentID;
//			int age;
//
//			cout << "Enter School ID: ";
//			getline(cin, schoolID);
//			if (schoolID == "") {
//				cout << "School ID cannot be empty." << endl;
//				break;
//			}
//
//			SchoolNode* school = schoolSystem.FindSchool(schoolID);
//			if (!school) {
//				cout << "School not found." << endl;
//				break;
//			}
//
//			cout << "School: " << school->GetName() << endl;
//			cout << "Enter Department Name: ";
//			getline(cin, deptName);
//			if (deptName == "") {
//				cout << "Department name cannot be empty." << endl;
//				break;
//			}
//
//			cout << "Enter Class Name: ";
//			getline(cin, className);
//			if (className == "") {
//				cout << "Class name cannot be empty." << endl;
//				break;
//			}
//
//			cout << "Enter Student Name: ";
//			getline(cin, studentName);
//			if (studentName == "") {
//				cout << "Student name cannot be empty." << endl;
//				break;
//			}
//
//			cout << "Enter Student Age: ";
//			if (!(cin >> age)) {
//				cin.clear();
//				cin.ignore(1000, '\n');
//				cout << "Invalid age." << endl;
//				break;
//			}
//			cin.ignore(1000, '\n');
//
//			if (age < 3 || age > 60) {
//				cout << "Age must be between 3 and 60." << endl;
//				break;
//			}
//
//			cout << "Enter Student ID: ";
//			getline(cin, studentID);
//			if (studentID == "") {
//				cout << "Student ID cannot be empty." << endl;
//				break;
//			}
//
//			if (schoolSystem.FindStudent(studentID)) {
//				cout << "Student with this ID already exists." << endl;
//				break;
//			}
//
//			schoolSystem.AddStudent(schoolID, deptName, className, studentName, age, studentID);
//			cout << "Student added." << endl;
//			break;
//		}
//		case 11: {
//			cout << endl;
//			string schoolID, deptName, facultyName, facultyID, specialization;
//
//			cout << "Enter School ID: ";
//			getline(cin, schoolID);
//			if (schoolID == "") {
//				cout << "School ID cannot be empty." << endl;
//				break;
//			}
//
//			SchoolNode* school = schoolSystem.FindSchool(schoolID);
//			if (!school) {
//				cout << "School not found." << endl;
//				break;
//			}
//
//			cout << "School: " << school->GetName() << endl;
//			cout << "Enter Department Name: ";
//			getline(cin, deptName);
//			if (deptName == "") {
//				cout << "Department name cannot be empty." << endl;
//				break;
//			}
//
//			cout << "Enter Faculty Name: ";
//			getline(cin, facultyName);
//			if (facultyName == "") {
//				cout << "Faculty name cannot be empty." << endl;
//				break;
//			}
//
//			cout << "Enter Faculty ID: ";
//			getline(cin, facultyID);
//			if (facultyID == "") {
//				cout << "Faculty ID cannot be empty." << endl;
//				break;
//			}
//
//			if (schoolSystem.FindFaculty(facultyID)) {
//				cout << "Faculty with this ID already exists." << endl;
//				break;
//			}
//
//			cout << "Enter Specialization: ";
//			getline(cin, specialization);
//			if (specialization == "") {
//				cout << "Specialization cannot be empty." << endl;
//				break;
//			}
//
//			schoolSystem.AddFaculty(schoolID, deptName, facultyName, facultyID, specialization);
//			cout << "Faculty added." << endl;
//			break;
//		}
//
//		case 12: {
//			cout << endl;
//			schoolSystem.DisplayAllSchoolsFromHash();
//			break;
//		}
//		case 13: {
//			cout << endl;
//			cout << "Exiting..." << endl;
//			break;
//		}
//
//		default: {
//			cout << "Invalid choice." << endl;
//		}
//		}
//	} while (choice != 13);
//
//
//	return 0;
//}