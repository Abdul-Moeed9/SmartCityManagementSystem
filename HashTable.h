#pragma once
#include <string>
#include "LinkedList.h"
using namespace std;

struct HashEntry {
	string key;
	void* value;
	HashEntry(string k, void* v) {
		key = k;
		value = v;
	}
};
class HashTable {
private:
	LinkedList* table;
	int capacity;
	int count;

	//Polynomial hash function
	int hashFunction(const string& key) {
		unsigned long hash = 0;
		int p = 31;//Prime for better distribution
		int p_pow = 1;

		for (int i = 0; i < key.length(); i++) {
			hash = (hash + (key[i] - 'A' + 1) * p_pow) % capacity;
			p_pow = (p_pow * p) % capacity;
		}
		return hash;
	}
public:
	HashTable(int cap = 1000) {
		capacity = cap;
		count = 0;
		table = new LinkedList[capacity];
	}
	void insert(const string& key, void* value) {
		int index = hashFunction(key);

		// Check if key already exists
		Node* temp = table[index].getHead();
		while (temp != nullptr) {
			HashEntry* entry = (HashEntry*)temp->data;
			if (entry->key == key) {
				entry->value = value;  // Update existing
				return;
			}
			temp = temp->next;
		}

		// Insert new entry
		HashEntry* newEntry = new HashEntry(key, value);
		table[index].insert((void*)newEntry);
		count++;
	}
	void* search(const string& key) {
		int index = hashFunction(key);

		Node* temp = table[index].getHead();
		while (temp != nullptr) {
			HashEntry* entry = (HashEntry*)temp->data;
			if (entry->key == key) {
				return entry->value;
			}
			temp = temp->next;
		}

		return nullptr;  // Not found
	}

	// Delete by key
	bool remove(const string& key) {
		int index = hashFunction(key);

		Node* temp = table[index].getHead();
		Node* prev = nullptr;

		while (temp != nullptr) {
			HashEntry* entry = (HashEntry*)temp->data;
			if (entry->key == key) {
				if (prev == nullptr) {
					// Delete head
					table[index].deleteAt(0);
				}
				else {
					prev->next = temp->next;
					delete temp;
				}
				delete entry;
				count--;
				return true;
			}
			prev = temp;
			temp = temp->next;
		}

		return false;
	}
	int getCount() const {
		return count;
	}

	bool contains(const string& key) {
		return search(key) != nullptr;
	}

	string* getAllKeys(int& size)const {
		size = count;
		if (count == 0) return nullptr;

		string* keys = new string[count];
		int idx = 0;

		for (int i = 0; i < capacity; i++) {
			Node* temp = table[i].getHead();
			while (temp != nullptr) {
				HashEntry* entry = (HashEntry*)temp->data;
				keys[idx] = entry->key;
				idx++;
				temp = temp->next;
			}
		}

		return keys;
	}

	void display()const {
		for (int i = 0; i < capacity; i++) {
			if (!table[i].isEmpty()) {
				cout << "At Index " << i << ": ";
				Node* temp = table[i].getHead();
				while (temp != nullptr) {
					HashEntry* entry = (HashEntry*)temp->data;
					cout << "[" << entry->key << "] -> ";
					temp = temp->next;
				}
				cout << "NULL" << endl;
			}
		}
	}
	~HashTable() {
		for (int i = 0; i < capacity; i++) {
			Node* temp = table[i].getHead();
			while (temp != nullptr) {
				HashEntry* entry = (HashEntry*)temp->data;
				delete entry;
				temp = temp->next;
			}
		}
		delete[] table;
	}
};