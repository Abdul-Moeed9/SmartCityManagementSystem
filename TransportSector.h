#pragma once
#include "Graph.h"
#include <string>
#include <iostream>
using namespace std;

class RouteNode {
private:
	string stopId;
	RouteNode* next;

public:
	RouteNode(string i = "") {
		stopId = i;
		next = nullptr;
	}

	string getId() {
		return stopId;
	}
	RouteNode* getNext() {
		return next;
	}

	void setId(string i) {
		stopId = i;
	}
	void setNext(RouteNode* ptr) {
		next = ptr;
	}
};
class Route {
private:
	RouteNode* head;
public:
	Route() {
		head = nullptr;
	}
	RouteNode* getHead() {
		return head;
	}

	void insert(string id) {

		if (id.empty()) return;
		RouteNode* newNode = new RouteNode(id);
		if (!head) {
			head = newNode;
			return;
		}

		RouteNode* temp = head;
		while (temp->getNext()) {
			temp = temp->getNext();
		}
		temp->setNext(newNode);
	}
	void display() {

		if (!head) {
			cout << "Route is empty for now" << endl;
			return;
		}

		RouteNode* temp = head;
		while (temp) {
			cout << temp->getId();
			temp = temp->getNext();
			if (temp) cout << "->";
		}
		cout << endl;
	}
};

class Bus {
private:
	string number;
	string company;
	string currentStop;
	Route* currentRoute;

public:
	Bus(string num = "", string comp = "", string stop = "") {
		number = num;
		company = comp;
		currentStop = stop;
		currentRoute = nullptr;
	}

	void setNumber(string num) {
		if (!num.empty()) number = num;
	}
	void setCompany(string comp) {
		if (!comp.empty()) company = comp;
	}
	void setCurrentStop(string stop) {
		currentStop = stop;
	}
	void setCurrentRoute(Route* route) {
		currentRoute = route;
	}

	string getNumber() {
		return number;
	}
	string getCompany() {
		return company;
	}
	string getCurrentStop() {
		return currentStop;
	}
	Route* getCurrentRoute() {
		return currentRoute;
	}
};
class BusStop {
private:
	string id;
	string name;
	double x_cord;
	double y_cord;
	
public:
	BusStop(string i = "", string n = "", double x = 0.0, double y = 0.0) {
		id = i;
		name = n;
		x_cord = x;
		y_cord = y;
	}

	string getId() {
		return id;
	}
	string getName() {
		return name;
	}
	double getXcord() {
		return x_cord;
	}
	double getYcord() {
		return y_cord;
	}

	void setId(string i) {
		id = i;
	}
	void setName(string n) {
		name = n;
	}
	void setXcord(double x) {
		x_cord = x;
	}
	void setYcord(double y) {
		y_cord = y;
	}
};

class EdgeData {
private:
	BusStop* destination;
	int weight;

public:
	EdgeData(BusStop* stop = nullptr, int w = 0) {
		destination = stop;
		weight = w;
	}

	BusStop* getDestination() {
		return destination;
	}
	int getWeight() {
		return weight;
	}

	void setDestination(BusStop* stop) {
		destination = stop;
	}
	void setWeight(int w) {
		weight = w;
	}
};
class EdgesList {
private:
	EdgeData* edges;
	int maxEdges;
	int actualEdges;

public:
	EdgesList() {
		maxEdges = 1000;
		edges = new EdgeData[maxEdges];
		actualEdges = 0;
	}
	~EdgesList() {
		if (edges) delete[]edges; edges = nullptr;
	}

	void addEdge(BusStop* stop, int weight) {
		if (actualEdges >= maxEdges || !stop) return;
		edges[actualEdges] = EdgeData(stop, weight);
		actualEdges++;
	}

	int getEdges() {
		return actualEdges;
	}
	EdgeData* getEdge(int idx) {
		if (idx < 0 || idx >= actualEdges) return nullptr;
		return &edges[idx];
	}
};

//class GraphNode {
//private:
//	BusStop* stop;
//	EdgesList* list;
//
//public:
//	GraphNode() {
//		stop = nullptr;
//		list = new EdgesList;
//	}
//	~GraphNode() {
//		if (list) delete list; list = nullptr;
//	}
//
//	void setStop(BusStop* stop) {
//		this->stop = stop;
//	}
//	BusStop* getStop() {
//		return stop;
//	}
//	EdgesList* getList() {
//		return list;
//	}
//};
//class TransportGraph {
//private:
//	GraphNode* nodes;
//	int maxNodes;
//	int actualNodes;
//
//public:
//	TransportGraph() {
//		maxNodes = 1000;
//		nodes = new GraphNode[maxNodes];
//		actualNodes = 0;
//	}
//	~TransportGraph() {
//		for (int i = 0; i < actualNodes; i++) delete nodes[i].getStop();
//		delete[]nodes;
//	}
//
//	void addStop(BusStop*stop) {
//		if (actualNodes >= maxNodes || !stop) return;
//
//		if (findStop(stop->getId())) {
//			cout << "Stop already exists" << endl;
//			delete stop;
//			return;
//		}
//
//		nodes[actualNodes].setStop(stop);
//		actualNodes++;
//	}
//	BusStop* findStop(string id) {
//		for (int i = 0; i < actualNodes; i++) {
//			if (nodes[i].getStop()->getId() == id) {
//				return nodes[i].getStop();
//			}
//		}
//		return nullptr;
//	}
//	void connect(string from, string to, int dist) {
//
//		if (dist < 0) return;
//		BusStop* fromBusStop = findStop(from);
//		BusStop* toBusStop = findStop(to);
//
//		if (!fromBusStop || !toBusStop) return;
//		for (int i = 0; i < actualNodes; i++) {
//			if (nodes[i].getStop()->getId() == from) {
//				nodes[i].getList()->addEdge(toBusStop, dist);
//			}
//		}
//	}
//
//	void undirectedConnect(string one, string two, int dist) {
//		connect(one, two, dist);
//		connect(two, one, dist);
//	}
//
//	int getNodes() {
//		return actualNodes;
//	}
//	GraphNode* getNode(int idx) {
//		if (idx >= actualNodes) return nullptr;
//		return &nodes[idx];
//	}
//
//	string shortestPath(string currentStop, string nextStop, int& length) {
//
//		length = -1;
//		int startIdx = findIdx(currentStop);
//		int endIdx = findIdx(nextStop);
//
//		if (startIdx == -1 || endIdx == -1) return "";
//		if (startIdx == endIdx) {
//			length = 0;
//			return currentStop;
//		}
//
//		int* distances = new int[actualNodes];
//		bool* visited = new bool[actualNodes];
//		int* previous = new int[actualNodes];
//
//		for (int i = 0; i < actualNodes; i++) {
//			previous[i] = -1;
//			visited[i] = false;
//			distances[i] = pow(10, 9);
//		}
//
//		distances[startIdx] = 0;
//		for (int i = 0; i < actualNodes - 1; i++) {
//
//			int idx = minDistance(distances, visited, actualNodes);
//			if (idx == -1 || distances[idx] == pow(10, 9)) break;
//
//			visited[idx] = true;
//			if (idx == endIdx) break;
//
//			EdgesList* list = nodes[idx].getList();
//			for (int j = 0; j < list->getEdges(); j++) {
//				EdgeData* edge = list->getEdge(j);
//				if (!edge) continue;
//
//				BusStop* neighbour = edge->getDestination();
//				int neighbourIdx = findIdx(neighbour->getId());
//
//				if (neighbourIdx != -1 && !visited[neighbourIdx]) {
//					int newDist = distances[idx] + edge->getWeight();
//					if (newDist < distances[neighbourIdx]) {
//						distances[neighbourIdx] = newDist;
//						previous[neighbourIdx] = idx;
//					}
//				}
//
//			}
//		}
//
//		if (distances[endIdx] == pow(10, 9)) {
//			delete[]distances;
//			delete[]visited;
//			delete[]previous;
//			return "";
//		}
//
//		string retPath = "";
//		int currentIdx = endIdx;
//		string* pathArray = new string[actualNodes];
//		int len = 0;
//		while (currentIdx != -1) {
//			pathArray[len++] = nodes[currentIdx].getStop()->getId();
//			currentIdx = previous[currentIdx];
//		}
//
//		for (int i = len - 1; i >= 0; i--) {
//			retPath += pathArray[i];
//			if (i > 0) retPath += " -> ";
//		}
//
//		length = distances[endIdx];
//		delete[]distances;
//		delete[]visited;
//		delete[]previous;
//		delete[]pathArray;
//		return retPath;
//	}
//
//	int minDistance(int* distances, bool* visited, int count) {
//		int minDist = pow(10, 9);
//		int minIdx = 0;
//
//		for (int i = 0; i < count; i++) {
//			if (!visited[i] && distances[i] < minDist) {
//				minDist = distances[i];
//				minIdx = i;
//			}
//		}
//		return minIdx;
//	}
//	int findIdx(string id) {
//		for (int i = 0; i < actualNodes; i++) {
//			if (nodes[i].getStop() && nodes[i].getStop()->getId() == id) return i;
//		}
//		return -1;
//	}
//
//	void display() {
//		cout << "Transport Graph" << endl;
//		for (int i = 0; i < actualNodes; i++) {
//			BusStop* stop = nodes[i].getStop();
//			cout << stop->getId() << " (" << stop->getName() << "): ";
//
//			EdgesList* list = nodes[i].getList();
//			for (int j = 0; j < list->getEdges(); j++) {
//				EdgeData* data = list->getEdge(j);
//				if (data && data->getDestination()) {
//					cout << data->getDestination()->getId() << "(" << data->getWeight() << "km)";
//				}
//			}
//			cout << endl;
//		}
//	}
//};

class PassengerLocation {
private:
	string nearestStop;
	double x_cord;
	double y_cord;

public:
	PassengerLocation(string stop, double x, double y) {
		nearestStop = stop;
		x_cord = x;
		y_cord = y;
	}

	string getNearestStop() {
		return nearestStop;
	}
	double getXCord() {
		return x_cord;
	}
	double getYCord() {
		return y_cord;
	}

	void setNearestStop(string stop) {
		nearestStop = stop;
	}
	void setXCord(double x) {
		x_cord = x;
	}
	void setYCord(double y) {
		y_cord = y;
	}
};
class Passenger {
private:
	string name;
	string cnic;
	string destination;
	int ticketNumber;

public:
	Passenger(string n = "", string c = "", string d = "", int t = 0) {
		name = n;
		cnic = c;
		destination = d;
		ticketNumber = t;
	}

	string getName() {
		return name;
	}
	string getCnic() {
		return cnic;
	}
	string getDestination() {
		return destination;
	}
	int getTicketNumber() {
		return ticketNumber;
	}

	void setName(string name) {
		this->name = name;
	}
	void setCnic(string cnic) {
		this->cnic = cnic;
	}
	void setDestination(string destination) {
		this->destination = destination;
	}
	void setTicketNumber(int ticketNumber) {
		this->ticketNumber = ticketNumber;
	}

	void display() {
		cout << "(Passenger, CNIC, Ticket Number, Destination) = (" << name << ", " << cnic << ", "
			<< ticketNumber << ", " << destination << ")";
	}
};
class PassengerQueue {
private:
	Passenger* arr;
	int front;
	int rear;
	int capacity;
	int occupied;

public:
	PassengerQueue(int size = 50) {
		front = 0;
		rear = -1;
		occupied = 0;
		capacity = size;
		arr = new Passenger[capacity];
	}
	~PassengerQueue() {
		if (arr) delete[]arr; arr = nullptr;
	}

	bool isFull() {
		if (occupied == capacity) return true;
		return false;
	}
	bool isEmpty() {
		if (occupied == 0) return true;
		return false;
	}

	void enqueue(string name, string cnic, string destination, int ticketNumber) {

		if (isFull()) {
			cout << "Cannot add more passengers" << endl;
			return;
		}

		//Passenger* newNode = new Passenger(name, cnic, destination, ticketNumber);

		rear += 1;
		rear %= capacity;
		arr[rear] = Passenger(name, cnic, destination, ticketNumber);;

		arr[rear].display();
		cout << " added to the queue" << endl;
		occupied++;
	}
	void dequeue() {
		if (isEmpty()) {
			cout << "Cannot remove passengers" << endl;
			return;
		}

		Passenger removed = arr[front];
		front += 1;
		front %= capacity;
		occupied--;

		removed.display();
		cout << " removed from the queue" << endl;
	}

	int getFront() {
		return front;
	}
	int getRear() {
		return rear;
	}
	int getCapacity() {
		return capacity;
	}
	int getOccupied() {
		return occupied;
	}

	void display() {
		if (isEmpty()) {
			cout << "Queue is empty" << endl;
			return;
		}

		int idx = front;
		for (int i = 0; i < occupied; i++) {
			cout << "Position " << i + 1 << ": ";
			arr[idx].display();
			cout << endl;
			idx += 1;
			idx %= capacity;
		}
	}
	void clear() {
		front = 0;
		rear = -1;
		occupied = 0;
		cout << "Cleared the queue" << endl;
	}
};

class TravelRecord {
private:
	string busNumber;
	string from;
	string to;
	string time;
	int distance;

public:
	TravelRecord(string bN = "", string f = "", string t = "", string time = "", int d = 0) {
		busNumber = bN;
		from = f;
		to = t;
		this->time = time;
		distance = d;
	}

	string getBusNumber() {
		return busNumber;
	}
	string getFrom() {
		return from;
	}
	string getTo() {
		return to;
	}
	string getTime() {
		return time;
	}
	int getDistance() {
		return distance;
	}

	void setBusNumber(string busNumber) {
		this->busNumber = busNumber;
	}
	void setFrom(string from) {
		this->from = from;
	}
	void setTo(string to) {
		this->to = to;
	}
	void setTime(string time) {
		this->time = time;
	}
	void setDistance(int distance) {
		this->distance = distance;
	}

	void display() {
		cout << "(Bus Number, From Stop, To Stop, Time, Distance) = (" << busNumber << ", " << from << ", " << to
			<< ", " << time << ", " << distance << " km)" << endl;
	}
};
class TravelHistory {
private:
	TravelRecord* arr;
	int top;
	int capacity;

public:
	TravelHistory(int size = 100) {
		capacity = size;
		top = -1;
		arr = new TravelRecord[capacity];
	}
	~TravelHistory() {
		if (arr) delete[]arr; arr = nullptr;
	}

	bool isEmpty() {
		if (top == -1) return true;
		return false;
	}
	bool isFull() {
		if (top == capacity - 1) return true;
		return false;
	}
	void clear() {
		top = -1;
		cout << "Travel History cleared" << endl;
	}

	void push(string bN = "", string f = "", string t = "", string time = "", int d = 0) {
		
		if (isFull()) {
			cout << "Travel History is already full" << endl;
			return;
		}

		//TravelRecord* newRecord = new TravelRecord(bN, f, t, time, d);
		arr[++top] = TravelRecord(bN, f, t, time, d);;
	}
	void push(TravelRecord history) {
		if (isFull()) {
			cout << "Travel History is already full" << endl;
			return;
		}
		arr[++top] = history;
	}
	TravelRecord pop() {

		if (isEmpty()) {
			cout << "Travel History is currently empty" << endl;
			return TravelRecord();
		}
		return arr[top--];
	}

	int getOccupied() {
		return top + 1;
	}
	int getCapacity() {
		return capacity;
	}

	void display() {
		if (isEmpty()) {
			cout << "Nothing to display as travel history is empty" << endl;
			return;
		}

		cout << "Travel History:" << endl;
		TravelHistory* revHistory = new TravelHistory(capacity);
		while (!isEmpty()) revHistory->push(pop());

		while (!revHistory->isEmpty()) {
			TravelRecord record = revHistory->pop();
			record.display();
			push(record);
		}
		delete revHistory;
		cout << endl;
	}
};

class BusHashNode {
private:
	string number;
	Bus* bus;
	BusHashNode* next;

public:
	BusHashNode(string num, Bus* b) {
		number = num;
		bus = b;
		next = nullptr;
	}

	string getNumber() {
		return number;
	}
	Bus* getBus() {
		return bus;
	}
	BusHashNode* getNext() {
		return next;
	}

	void setNumber(string num) {
		number = num;
	}
	void setBus(Bus* bus) {
		this->bus = bus;
	}
	void setNext(BusHashNode* node) {
		next = node;
	}
};
class BusHashTable {
private:
	BusHashNode** table;
	int maxNodes;
	int actualNodes;

	int hashFunction(string key) {
		if (key.empty()) return 0;
		unsigned long hash = 0;
		int p = 31;
		int p_pow = 1;

		for (int i = 0; i < key.length(); i++) {
			hash = (hash + (unsigned char)key[i] * p_pow) % maxNodes;
			p_pow = (p_pow * p) % maxNodes;
		}
		return int(hash);
	}

public:
	BusHashTable() {
		maxNodes = 1000;
		table = new BusHashNode*[maxNodes];
		actualNodes = 0;

		for (int i = 0; i < maxNodes; i++) {
			table[i] = nullptr;
		}
	}
	~BusHashTable() {
		for (int i = 0; i < maxNodes; i++) {
			BusHashNode* curr = table[i];
			while (curr) {
				BusHashNode* temp = curr;
				curr = curr->getNext();
				delete temp;
			}
		}
		delete[]table;
	}

	void insertBus(Bus* bus) {

		if (!bus) return;

		string num = bus->getNumber();
		if (num.empty()) return;
		if (searchBus(num)) return;

		int idx = hashFunction(num);
		BusHashNode* newNode = new BusHashNode(num, bus);

		newNode->setNext(table[idx]);
		table[idx] = newNode;
		actualNodes++;
	}
	Bus* searchBus(string number) {

		if (number.empty()) return nullptr;

		int idx = hashFunction(number);
		BusHashNode* curr = table[idx];
		while (curr) {
			if (curr->getBus()->getNumber() == number) return curr->getBus();
			curr = curr->getNext();
		}
		return nullptr;
	}

	int getNodesCount() {
		return actualNodes;
	}
	void display() {
		cout << "Hash Table Data:" << endl;
		cout << "Total Buses: " << actualNodes << endl;
		cout << "Total Space: " << maxNodes << endl;

		int maxChain = 0;
		int empty = 0;

		for (int i = 0; i < maxNodes; i++) {
			int chainLen = 0;
			BusHashNode* curr = table[i];
			while (curr) {
				chainLen++;
				curr = curr->getNext();
			}
			if (chainLen == 0) empty++;
			if (chainLen > maxChain) maxChain = chainLen;
		}

		cout << "Max Chain: " << maxChain << endl;
		cout << "Empty Slots: " << empty << endl;
	}
};

class BusLocationTracker {
private:
	//TransportGraph* graph;
	Graph* graph;
	Bus** buses;
	int maxBuses;
	int currentBus;

public:
	/*BusLocationTracker(TransportGraph* graph) {
		this->graph = graph;
		maxBuses = 1000;
		currentBus = 0;
		buses = new Bus*[maxBuses];
		for (int i = 0; i < maxBuses; i++) {
			buses[i] = nullptr;
		}
	}*/
	BusLocationTracker(Graph* graph) {
		this->graph = graph;
		maxBuses = 1000;
		currentBus = 0;
		buses = new Bus * [maxBuses];
		for (int i = 0; i < maxBuses; i++) {
			buses[i] = nullptr;
		}
	}
	~BusLocationTracker() {
		delete[]buses;
	}

	void addBus(Bus* bus) {
		if (!bus || currentBus >= maxBuses) return;
		buses[currentBus] = bus;
		currentBus++;
	}
	string findNearest(string stop) {

		if (stop.empty()) return "";
		if (!graph->nodeExists(stop)) return "";

		string nearest = "";
		double minDistance = pow(10, 18);

		for (int i = 0; i < currentBus; i++) {
			
			if (!buses[i] || buses[i]->getCurrentStop().empty()) continue;

			double lenght = -1;
			string* path = graph->dijkstra(buses[i]->getCurrentStop(), stop, lenght);
			if (path) delete[] path;

			if (lenght >= 0 && lenght < minDistance) {
				minDistance = lenght;
				nearest = buses[i]->getNumber();
			}
		}
		return nearest;
	}
};

class TransportSector {
private:
	string company;
	//TransportGraph* graph;
	Graph* graph;
	Bus** buses;
	Route** routes;
	int maxBuses;
	int currentBus;
	int maxRoutes;
	int currentRoute;
	BusHashTable* busTable;
	BusLocationTracker* busTracker;
	PassengerQueue** passengerQueue;
	TravelHistory* travelHistory;
	int nextTicketNumber;

	bool isReUsed(double x, double y) {

		if (!graph) return false;
		int count = 0;
		string* ids = graph->getAllNodeIDs(count);
		if (!ids) return false;

		for (int i = 0; i < count; i++) {

			GraphNode* node = graph->getNode(ids[i]);
			if (!node) continue;

			double dx = node->latitude - x;
			double dy = node->longitude - y;

			if (dx == 0 && dy == 0) {
				delete[]ids;
				return graph->isStopId(node->id);
			}
		}
		delete[]ids;
		return false;
	}

public:
	TransportSector(Graph* graph, string c = "Default Transport") {
		
		this->graph = graph;
		company = c; nextTicketNumber = 1000;

		maxBuses = 1000; currentBus = 0;
		buses = new Bus * [maxBuses];
		for (int i = 0; i < maxBuses; i++) buses[i] = nullptr;

		maxRoutes = 1000; currentRoute = 0;
		routes = new Route*[maxRoutes];
		for (int i = 0; i < maxRoutes; i++) routes[i] = nullptr;

		passengerQueue = new PassengerQueue * [maxBuses];
		for (int i = 0; i < maxBuses; i++) passengerQueue[i] = nullptr;

		busTracker = new BusLocationTracker(graph);
		busTable = new BusHashTable;
		travelHistory = new TravelHistory(500);
	}
	~TransportSector() {
		for (int i = 0; i < currentBus; i++) delete buses[i]; delete[]buses;
		for (int i = 0; i < currentRoute; i++) delete routes[i]; delete[]routes;
		for (int i = 0; i < maxBuses; i++) delete passengerQueue[i]; delete[]passengerQueue;
		delete busTable;
		delete busTracker;
		delete travelHistory;
	}

	void addBus(string number, string comp, Route* route, string stop = "") {
		if (number.empty() || currentBus >= maxBuses) return;

		Bus* newBus = new Bus(number, comp, stop);
		
		buses[currentBus] = newBus;
		buses[currentBus]->setCurrentRoute(route);
		busTable->insertBus(newBus);
		busTracker->addBus(newBus);
		currentBus++;

		cout << "Bus " << number << " added" << endl;
	}
	void addStop(string id, string name, double x, double y) {

		if (!graph || id.empty() || name.empty()) return;

		if (graph->nodeExists(id)) {
			cout << "Stop " << id << " already exists" << endl;
			return;
		}

		if (isReUsed(x, y)) {
			cout << "A stop already exists at (" << x << ", " << y << ")" << endl;
			return;
		}

		//BusStop* newStop = new BusStop(id, name, x, y);
		graph->addNode(id, name, x, y);
		cout << "Stop " << id << " (" << name << ") added" << endl;
	}

	void connectStops(string stop1, string stop2, double dist, bool undirected = true) {	
		
		if (!graph || dist < 0) return;
		if (!graph->nodeExists(stop1) || !graph->nodeExists(stop2)) {
			cout << "One of the stops do not exist" << endl;
			return;
		}

		if (undirected) {
			graph->addUndirectedEdge(stop1, stop2, dist);
			cout << "Connected " << stop1 << " <-> " << stop2 << " (bidirectional)" << endl;
		}
		else {
			graph->addEdge(stop1, stop2, dist);
			cout << "Connected " << stop1 << " -> " << stop2 << " (directional)" << endl;
		}
	}
	void updateBusLocation(string number, string stop) {
		Bus* bus = busTable->searchBus(number);
		if (!bus || !graph->nodeExists(stop)) return;
		bus->setCurrentStop(stop);
		cout << "Bus " << number << " location updated to " << stop << endl;
	}

	string getNearestBus(string stop) {
		return busTracker->findNearest(stop);
	}
	string getShortestPath(string one, string two) {

		if (!graph) return "";

		double lenth = -1;
		string* path = graph->dijkstra(one, two, lenth);

		if (!path || lenth < 0) {
			cout << "No path found between " << one << " and " << two << endl;
			if (path) delete[]path;
			return "";
		}

		cout << "Shortest Path from " << one << " to " << two << ": ";
		string pathStr = "";
		for (int i = 0; i < 100 && !path[i].empty(); i++) {
			cout << path[i];
			pathStr += path[i];
			if (!path[i + 1].empty()) {
				cout << " ->";
				pathStr += " ->";
			}
		}
		cout << endl << "Total Distance: " << lenth << " km" << endl;
		delete[]path;
		return pathStr;
	}

	Bus* getBusDetails(string number) {

		Bus* bus = busTable->searchBus(number);

		if (!bus) return nullptr;
		cout << "Bus Details:" << endl;
		cout << "(Bus Number, Bus Company, Current Stop) = (" << bus->getNumber() << ", " << bus->getCompany() << ", "
			<< (bus->getCurrentStop().empty() ? "Not assigned" : bus->getCurrentStop()) << endl;

		if (bus->getCurrentRoute()) {
			cout << "Route: ";
			bus->getCurrentRoute()->display();
		}
		return bus;
	}

	int getStopsCount() {
		return graph->getNodeCount();
	}
	GraphNode* getStopAt(int idx) {

		if (!graph) return nullptr;

		int count = 0;
		string* ids = graph->getAllNodeIDs(count);
		if (idx < 0 || idx >= count) {
			delete[]ids;
			return nullptr;
		}

		GraphNode* node = graph->getNode(ids[idx]);
		delete[]ids;
		return node;
	}

	void displayBuses() {

		cout << "All Buses: " << endl;
		if (currentBus == 0) {
			cout << "No buses registered yet" << endl;
			return;
		}

		for (int i = 0; i < currentBus; i++) {
			cout << "(Bus, Bus Number, Bus Company, Bus Stop) = (" << i << ", " << buses[i]->getNumber() << ", "
				<< buses[i]->getCompany() << ", " << buses[i]->getCurrentStop() << ")" << endl;
		}
	}
	void displayGraph() {
		if (graph) graph->display();
		else cout << "No graph exists" << endl;
	}
	void displayHashState() {
		busTable->display();
	}

	Route* createRoute(string* stops, int count) {
		if (count <= 0 || currentRoute >= maxRoutes) return nullptr;
		Route* newRoute = new Route;
		for (int i = 0; i < count; i++) newRoute->insert(stops[i]);
		routes[currentRoute++] = newRoute;
		return newRoute;
	}

	void initializeQueue(string stopId, int cap = 50) {

		int stopIdx = -1;
		for (int i = 0; i < currentBus; i++) {
			if (!passengerQueue[i]) {
				stopIdx = i;
				break;
			}
		}

		if (stopIdx != -1 && !passengerQueue[stopIdx]) {
			passengerQueue[stopIdx] = new PassengerQueue(cap);
			cout << "Passenger Queue created for stop " << stopId << " (Capacity: " << cap << ")" << endl;
		}

	}
	void addPassenger(string stopId, string name, string cnic, string destination) {

		if (!graph->nodeExists(stopId)) {
			cout << "Stop " << stopId << " does not exists" << endl;
			return;
		}

		if (!passengerQueue[0]) {
			passengerQueue[0] = new PassengerQueue(50);
		}

		passengerQueue[0]->enqueue(name, cnic, destination, nextTicketNumber++);
	}
	void boardPassengers(string stopId, int num = 1) {

		if (!graph->nodeExists(stopId)) {
			cout << "Stop " << stopId << " does not exists" << endl;
			return;
		}

		if (!passengerQueue[0]) {
			cout << "No passenger queue at this stop" << endl;
			return;
		}

		cout << "Boarding " << num << " Passengers" << endl;
		for (int i = 0; i < num; i++) {
			if (passengerQueue[0]->isEmpty()) {
				cout << "No more waiting passengers" << endl;
				break;
			}
			passengerQueue[0]->dequeue();
		}
	}
	void displayPassengersQueue(string stop) {
		if (!graph->nodeExists(stop)) {
			cout << "Stop " << stop << " does not exists" << endl;
			return;
		}

		if (!passengerQueue[0]) {
			cout << "No passenger queue at this stop" << endl;
			return;
		}

		passengerQueue[0]->display();
	}
	int getQueueSize(string stop) {
		if (!passengerQueue[0]) return 0;
		return passengerQueue[0]->getCapacity();
	}

	void recordTravel(string busNumber, string from, string to, string time, int dist) {
		//TravelRecord* newRecord = new TravelRecord(busNumber, from, to, time, dist);
		travelHistory->push(busNumber, from, to, time, dist);
		cout << "Travel recorded in history" << endl;
	}
	void displayTravelHistory() {
		travelHistory->display();
	}
	void removeLastTravel() {
		if (travelHistory->isEmpty()) {
			cout << "Travel History is empty" << endl;
			return;
		}

		TravelRecord lastTravel = travelHistory->pop();
		cout << "Last Travel: ";
		lastTravel.display();
	}
	void clearTravelHistory() {
		travelHistory->clear();
	}

	void journeySimulation(string number, string from, string to) {
		Bus* bus = busTable->searchBus(number);
		if (!bus) {
			cout << "Bus " << number << " doesn't exist" << endl;
			return;
		}

		if (!graph) {
			cout << "No graph available for simulation" << endl;
			return;
		}

		double dist = -1;
		string* path = graph->dijkstra(from, to, dist);// shortestPath(from, to, dist);

		if (!path || dist < 0) {
			cout << "Cannot move forward as no path found" << endl;
			if (path) delete[]path;
			return;
		}

		cout << "Journey Simulation" << endl;
		cout << "Bus " << number << " route: ";
		
		string pathStr = "";
		for (int i = 0; i < 100 && !path[i].empty(); i++) {
			cout << path[i];
			pathStr += path[i];
			if (!path[i + 1].empty()) {
				cout << " -> ";
				pathStr += " -> ";
			}
		}
		cout << endl << "Total Distance: " << dist << " km" << endl;
		recordTravel(number, from, to, "have to enter proper time here", dist);

		bus->setCurrentStop(to);
		cout << "Bus is now at " << to << " stop" << endl;
		delete[]path;
	}
};