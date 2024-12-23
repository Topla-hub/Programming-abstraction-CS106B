/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	//elems is initialized automatically.
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// No need to do anything here; no dynamic memory to free.
}

int VectorPriorityQueue::size() {
	return elems.size();
}

bool VectorPriorityQueue::isEmpty() {
	return size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
	elems += value;
}

string VectorPriorityQueue::peek() {
	if (isEmpty()) {
		error("There is no element in queue");
	}
	string lexicographicallyFirst = elems[0];
	for (string cur : elems) {//search min element
		if (cur < lexicographicallyFirst) {
			lexicographicallyFirst = cur;
		}
	}
	return lexicographicallyFirst;
}

string VectorPriorityQueue::dequeueMin() {
	if (isEmpty()) {
		error("There is no element in queue");
	}
	string lexicographicallyFirst = elems[0];
	int index = 0;
	for (int i = 1; i < elems.size(); i++) {//search index of min element
		if (elems[i] < lexicographicallyFirst) {
			lexicographicallyFirst = elems[i];
			index = i;
		}
	}
	elems.remove(index);
	return lexicographicallyFirst;
}

