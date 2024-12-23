/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

 /* Constant controlling the default size of our queue. */
	const int kDefaultSize = 4;


HeapPriorityQueue::HeapPriorityQueue() {
	length = 0;
	allocatedLength = kDefaultSize;
	elems = new string[allocatedLength];// Allocate memory for elements.
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] elems;// Release memory allocated for elements.
}

int HeapPriorityQueue::size() {
	return length;
}

bool HeapPriorityQueue::isEmpty() {
	return length==0;
}

void HeapPriorityQueue::enqueue(string value) {
	if (allocatedLength == length) {
		grow();//Allocate more memory is array is full
	}
	if (isEmpty()) {//if array is empty
		elems[0] = value;
	}
	//bubbleUp
	else {//if there was elements already in array
		int index = length;
		elems[index] = value;//inser element at the end
		while (true) {//this loop sorts array correctly according heap logic 
			int parent = (index - 1) / 2;
			if (elems[parent] > elems[index]) {//swap
				swap(elems[parent], elems[index]);
				index = parent;
			}
			else {
				break;
			}
			if (index == 0) {
				break;
			}
		}
	}
	length++;
}

string HeapPriorityQueue::peek() {
	if (isEmpty()) {
		error("There is no element in queue");
	}
	return elems[0];
}

string HeapPriorityQueue::dequeueMin() {
	if (isEmpty()) {
		error("There is no element in queue");
	}
	string min = elems[0];//save result
	//replace root with last element
	elems[0] = elems[length - 1];
	length--;
	int parent = 0;
	//bubbleDown
	while (true) {//this loop sorts array correctly according heap logic 
		int child1 = 2 * parent + 1;
		int child2 = 2 * parent + 2;
		int minChild;
		if (child1 < length && child2 < length) {// if both children exist
			if (elems[child1] < elems[child2]) {
				minChild = child1;
			}
			else {
				minChild = child2;
			}
		}
		else if (child1 < length && child2 >= length) {// if only one child exists
			minChild = child1;
		}
		else {// if no child exists
			break;
		}
		if (elems[parent] > elems[minChild]) {//swap
			swap(elems[parent], elems[minChild]);
			parent = minChild;
		}
		else {
			break;
		}
	}
	return min;
}
//this method creates more memery space for new elements
void HeapPriorityQueue::grow() {
	allocatedLength *= 2;//for efficiency
	string* tmp = new string[allocatedLength];
	for (int i = 0; i < length; i++) {
		tmp[i] = elems[i];
	}
	delete[] elems;
	elems = tmp;
}

