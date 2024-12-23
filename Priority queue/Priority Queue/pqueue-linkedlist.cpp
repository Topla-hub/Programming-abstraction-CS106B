/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	length = 0;
	head = NULL;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	//delete each node 
	while (head != NULL) {
		Node* next = head->next;
		delete head;
		head = next;
	}
	
}

int LinkedListPriorityQueue::size() {
	return length;
}

bool LinkedListPriorityQueue::isEmpty() {
	return length==0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	Node* toAdd = new Node;//new elemeny we want to add
	toAdd->next = NULL;
	toAdd->value = value;
	//easy cases
	if (head == NULL || value < head->value) {
		toAdd->next = head;
		head = toAdd;
	}
	else {//search correct place to add
		Node* first = head;//goes first trought linked list
		Node* follower =NULL;//follows the first one 
		while (first != NULL) {
			if (value > first->value) {
				//The follower should always be one step behind
				follower = first;
				first = first->next;
			}
			else {
				break;
			}
		}
		toAdd->next = first;
		if (follower != NULL) {
			follower->next = toAdd;
		}
		else { // If follower is NULL toAdd is the new head
			head = toAdd;
		}
	}
	//increase length
	length++;
}

string LinkedListPriorityQueue::peek() {
	if (isEmpty()) {
		error("There is no element in queue");
	}
	return head->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	 if (isEmpty()) {
        error("There is no element in queue");
    }
    string result = head->value;//save value to return
	//delete dequeued node
    Node* temp = head;
    head = head->next;//update new head
    delete temp;
	//decrease length
    length--;
    return result;
}

