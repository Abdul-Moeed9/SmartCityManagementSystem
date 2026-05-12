#pragma once
#include <iostream>
#include <string>
using namespace std;

const int maxNodes = 500;
class CityNode {
private:
	int id;
	string name;
	string sector;
	string type;
	double longitude;
	double latitude;
	int internalId;

public:
	CityNode() {
		id = -1;
		name = "";
		sector = "";
		type = "";
		longitude = latitude = 0;
		internalId = -1;
	}

	void setId(int id) {
		this->id = id;
	}
	void setName(string name) {
		this->name = name;
	}
	void setSector(string sector) {
		this->sector = sector;
	}
	void setType(string type) {
		this->type = type;
	}
	void setLongitude(double longitude) {
		this->longitude = longitude;
	}
	void setLatitude(double latitude) {
		this->latitude = latitude;
	}
	void setInternalId(int internalId) {
		this->internalId = internalId;
	}

	int getId() {
		return id;
	}
	string getName() {
		return name;
	}
	string getSector() {
		return sector;
	}
	string getType() {
		return type;
	}
	double getLongitude() {
		return longitude;
	}
	double getLatitude() {
		return latitude;
	}
	int getInternalId() {
		return internalId;
	}
};
class Edge {
private:
	int to;
	double distance;

public:
	Edge(int t = -1, double d = 0) {
		to = t;
		distance = d;
	}

	void setTo(int to) {
		this->to = to;
	}
	void setDistance(double distance) {
		this->distance = distance;
	}

	int getTo() {
		return to;
	}
	double getDistance() {
		return distance;
	}
};
class List {
private:
	Edge* edges;
	int currentEdges;
	int totalEdges;

public:
	List() {
		edges = nullptr;
		currentEdges = 0;
		totalEdges = 0;
	}

	Edge* getEdges() {
		return edges;
	}
	int getCurrentEdges() {
		return currentEdges;
	}
	int getTotalEdges() {
		return totalEdges;
	}

	void setEdges(Edge* edges) {
		this->edges = edges;
	}
	void setCurrentEdges(int currentEdges) {
		this->currentEdges = currentEdges;
	}
	void setTotalEdges(int totalEdges) {
		this->totalEdges = totalEdges;
	}
};

class CityGraph {
private:
	CityNode* nodes;
	List* list;
	int currentNodes;

	void capacityCheck(int id) {

		if (id < 0 || id >= currentNodes || nodes[id].getId() == -1) return;
		if (list[id].getTotalEdges() == 0) {
			list[id].setTotalEdges(4);
			list[id].setEdges(new Edge[list[id].getTotalEdges()]);
		}
		else if (list[id].getCurrentEdges() >= list[id].getTotalEdges()) {

			int oldCap = list[id].getTotalEdges();
			int occupied = list[id].getCurrentEdges();
			int newCap = oldCap * 2;

			Edge* newEdges = new Edge[newCap];
			for (int i = 0; i < occupied; i++) newEdges[i] = list[id].getEdges()[i];

			delete[]list[id].getEdges();
			list[id].setEdges(newEdges);
			list[id].setTotalEdges(newCap);
		}

	}

public:
	CityGraph() {
		nodes = new CityNode[maxNodes];
		list = new List[maxNodes];
		currentNodes = 0;
		for (int i = 0; i < maxNodes; i++) nodes[i].setId(-1);
	}
	~CityGraph() {
		for (int i = 0; i < maxNodes; i++) {
			if (list[i].getEdges()) {
				delete[]list[i].getEdges();
				list[i].setEdges(nullptr);
				list[i].setCurrentEdges(0);
				list[i].setTotalEdges(0);
			}
		}
		delete[]nodes;
		delete[]list;
	}

	int addNode(string name, string sector, string type, double latitude, double longitude, int internalId = -1) {

		if (currentNodes >= maxNodes) {
			cout << "City is already full so cannot add more nodes in City graph..." << endl;
			return -1;
		}

		nodes[currentNodes].setId(currentNodes);
		nodes[currentNodes].setName(name);
		nodes[currentNodes].setSector(sector);
		nodes[currentNodes].setType(type);
		nodes[currentNodes].setLatitude(latitude);
		nodes[currentNodes].setLongitude(longitude);
		nodes[currentNodes].setInternalId(internalId);
		currentNodes++;
		return currentNodes - 1;
	}

	CityNode* getNode(int id) {
		if (id < 0 || id >= currentNodes || nodes[id].getId() == -1) return nullptr;
		return &nodes[id];
	}
	int getNodesCount() {
		return currentNodes;
	}

	void addEdgeUndirected(int from, int to, double distance) {
		addEdgeDirected(from, to, distance);
		addEdgeDirected(to, from, distance);
	}
	void addEdgeDirected(int from, int to, double distance) {

		if (from < 0 || from >= currentNodes || nodes[from].getId() == -1) return;
		if (to < 0 || to >= currentNodes || nodes[to].getId() == -1) return;

		capacityCheck(from);

		Edge* edges = list[from].getEdges();
		int idx = list[from].getCurrentEdges();
		edges[idx].setTo(to);
		edges[idx].setDistance(distance);
		list[from].setCurrentEdges(idx + 1);
	}

	void displayNeighbours(int id) {
		if (id < 0 || id >= currentNodes || nodes[id].getId() == -1) return;

		cout << "Neighbours of node " << id << " (" << nodes[id].getName() << "):" << endl;
		for (int i = 0; i < list[id].getCurrentEdges(); i++) {

			int to = list[id].getEdges()[i].getTo();
			double distance = list[id].getEdges()[i].getDistance();

			if (to < 0 || to >= currentNodes || nodes[to].getId() == -1) continue;
			cout << " -> " << to << " (" << nodes[to].getName() << "), distance = " << distance << endl;
		}
	}
	void displayGraphDetails() {
		cout << "City Graph Details: (Total Nodes = " << currentNodes << ")" << endl;
		for (int i = 0; i < currentNodes; i++) {
			cout << "Node " << i << ": " << nodes[i].getName() << " (" << nodes[i].getSector() <<
				"/" << nodes[i].getType() << ")" << endl;
		}
	}
	void displayNode(int id) {

		if (id < 0 || id >= currentNodes || nodes[id].getId() == -1) return;

		cout << "(Id, Name, Sector, Type, Latitude, Longitude, Internal Id) = (" << id << ", "
			<< nodes[id].getName() << ", " << nodes[id].getSector() << ", " << nodes[id].getType() << ", "
			<< nodes[id].getLatitude() << ", " << nodes[id].getLongitude() << ", "
			<< nodes[id].getInternalId() << ")" << endl;
	}

	void shortestDistance(int source, double distance[]) {

	}
};











