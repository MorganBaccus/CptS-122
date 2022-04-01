/*
Programmer: Morgan Baccus
Class: CptS 122; Lab Section 1
Programming Assignment: PA 5
Description: This program simulates 2 grocery store lines using queues.
*/

#include "QueueNode.h"

QueueNode::QueueNode(Data *_pData)
{
	pData = _pData;
}

QueueNode *QueueNode::getNext(void)
{
	return pNext;
}

Data *QueueNode::getData(void)
{
	return pData;
}

void QueueNode::setNext(QueueNode* _pNext)
{
	pNext = _pNext;
}

void QueueNode::setData(Data *_pData)
{
	pData = _pData;
}
