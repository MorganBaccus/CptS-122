/*
Programmer: Morgan Baccus
Class: CptS 122; Lab Section 1
Programming Assignment: PA 5
Description: This program simulates 2 grocery store lines using queues.
*/

#pragma once

#include "simulation.h"
#include "Data.h"

class QueueNode
{
public:
	// Default Constructor
	QueueNode() : pData(nullptr), pNext(nullptr) {}

	// Value Constructor
	QueueNode(Data *_pData, QueueNode *_pNext) : pData(_pData), pNext(_pNext) {}

	// Data-only Value Constructor
	QueueNode(Data *_pData);

	// Copy Constructor
	QueueNode(QueueNode &old) : pData(old.pData), pNext(old.pNext) {}

	// Getters
	QueueNode *getNext(void);
	Data *getData(void);

	// Setters
	void setNext(QueueNode* _pNext);
	void setData(Data *_pData);

private:
	Data *pData;
	QueueNode *pNext;
};