/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	length = 0;
	head = NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	//delete each node 
	while (head != NULL) {
		Node* next = head->right;
		delete head;
		head = next;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return length;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return length==0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Node* toAdd = new Node;//new elemeny we want to add
	toAdd->value = value;
	toAdd->left = NULL;
	toAdd->right = NULL;
	if (head == NULL) {//if list is empty
		head = toAdd;
	}
	else {//if list isnot empty
		head->left = toAdd;
		toAdd->right = head;
		head=toAdd;
	}
	length++;
	
}

string DoublyLinkedListPriorityQueue::peek() {
	if (isEmpty()) {
		error("There is no element in queue");
	}
	string min = head->value;
	Node* curr = head->right;
	while (curr != nullptr) {//this loop search for the min string in list 
		if (curr->value < min) {
			min = curr->value;
		}
		curr = curr->right;
	}
	return min;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (isEmpty()) {
		error("There is no element in queue");
	}
	Node* curr = head->right;//for search loop
	Node* tag = head;//for found node that has min string 
	string min = head->value;
	while (curr!=NULL) {//this loop search for the min string in list
		if (curr->value<min) {
			min = curr->value;
			tag = curr;//tags the node
		}
		curr = curr->right;
	}
	//delete found node 
	if (tag->right != NULL&&tag->left!=NULL) {//if node is in the middle
		tag->right->left = tag->left;
		tag->left->right = tag->right;
	}
	if (tag->right == NULL&&tag->left!=NULL) {//if node is at the end
		tag->left->right = NULL;
	}if (tag->right != NULL && tag->left == NULL) {//if node is head  and list contains more than one node
		tag->right->left = NULL;
		head = tag->right;
	}if (tag->right == NULL && tag->left == NULL) {//if node contains only one node
		head = NULL;
	}
	delete tag;
	length--;
	return min;
}
