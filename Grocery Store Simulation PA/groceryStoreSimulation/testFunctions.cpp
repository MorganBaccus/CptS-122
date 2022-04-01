/*
Programmer: Morgan Baccus
Class: CptS 122; Lab Section 1
Programming Assignment: PA 5
Description: This program simulates 2 grocery store lines using queues.
*/

#include "testFunctions.h"

void Tests::runTests(void)
{
	testEnqueueEmpty();
	testEnqueueOneNode();
	testDequeueOneNode();
	testDequeueTwoNodes();
	runSim24Hours();
}

void Tests::testEnqueueEmpty(void)
{
	std::cout << "Testing Enqueue on Empty Queue:" << std::endl;

	Queue empty;
	Data *newData = new Data(1, 2, 3);
	empty.enqueue(*newData);

	if (empty.getHead()->getData()->getCustomerNumber() != newData->getCustomerNumber())
	{
		std::cout << "Enqueue Did Not Work! newData != newData" << std::endl;
	}
	else
	{
		std::cout << "Enqueue Worked! newData == newData" << std::endl;
	}
}

void Tests::testEnqueueOneNode(void)
{
	std::cout << "Testing Enqueue One Node:" << std::endl;

	Queue oneNode;
	Data *firstNode = new Data(1, 2, 3);
	oneNode.enqueue(*firstNode);
	Data *secondNode = new Data(2, 3, 4);
	oneNode.enqueue(*secondNode);

	if (oneNode.getTail()->getData()->getCustomerNumber() != secondNode->getCustomerNumber())
	{
		std::cout << "Enqueue Did Not Work! tail->data != secondNode" << std::endl;
	}
	else
	{
		std::cout << "Enqueue Worked! tail->data == secondNode" << std::endl;
	}
}

void Tests::testDequeueOneNode(void)
{
	std::cout << "Testing Dequeue One Node:" << std::endl;

	Queue q;
	Data *d = new Data(1, 2, 3);
	q.enqueue(*d);
	q.dequeue();

	if (q.getHead() != nullptr && q.getTail() != nullptr)
	{
		std::cout << "Dequeue Failed! Head or Tail (or both) != nullptr!" << std::endl;
	}
	else
	{
		std::cout << "Dequeue Worked! Head and Tail == nullptr!" << std::endl;
	}
}

void Tests::testDequeueTwoNodes(void)
{
	std::cout << "Testing Dequeue Two Nodes:" << std::endl;

	Queue q;
	Data *d1 = new Data(1, 2, 3);
	Data *d2 = new Data(2, 3, 4);
	q.enqueue(*d1);
	q.enqueue(*d2);
	q.dequeue();

	// Checks for d2 after dequeue (based on insertion order)
	if (q.getHead()->getData()->getCustomerNumber() != d2->getCustomerNumber())
	{
		std::cout << "Dequeue Failed! Data d2 not persistent in queue!" << std::endl;
	}
	else
	{
		std::cout << "Dequeue Worked! Data d2 persistent in queue!" << std::endl;
	}
}

void Tests::runSim24Hours(void)
{
	std::cout << "BEGINNING 24 HOUR SIMULATION:" << std::endl;
	system("pause");
	runSimulation(MIN_IN_HOUR * 24);
}