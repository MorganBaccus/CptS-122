/*
Programmer: Morgan Baccus
Class: CptS 122; Lab Section 1
Programming Assignment: PA 5
Description: This program simulates 2 grocery store lines using queues.
*/

#pragma once

#include "simulation.h"
#include "QueueNode.h"
#include "Data.h"

class Queue
{
public:
	// Default Constructor
	Queue() : pHead(nullptr), pTail(nullptr) {}
	// Value Constructor
	Queue(QueueNode *_pHead, QueueNode *_pTail) : pHead(_pHead), pTail(_pTail) {}
	// Copy Constructor
	Queue(Queue &old) : pHead(old.pHead), pTail(old.pTail) {}

	// Recursively prints the queue by printing the customer number. Ends queue printing with newline
	void printQueue(QueueNode *next);

	// Checks if pHead in queue is nullptr (empty = true, not empty = false)
	bool isEmpty();

	// Adds node to end of queue
	bool enqueue(Data &newData);

	// Deletes pHead and reassigns it to the next node
	void dequeue();

	// Getters
	QueueNode *getHead(void);
	QueueNode *getTail(void);

	// Calculate time spent in a line based on customers in front of the head prior to insertion
	int calculateSumServiceTimes(QueueNode *next);

private:
	QueueNode *pHead;
	QueueNode *pTail;
};