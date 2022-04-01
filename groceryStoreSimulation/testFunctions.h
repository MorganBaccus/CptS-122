/*
Programmer: Morgan Baccus
Class: CptS 122; Lab Section 1
Programming Assignment: PA 5
Description: This program simulates 2 grocery store lines using queues.
*/

#pragma once

#include "simulation.h"
#include "Queue.h"


class Tests
{
public:
	// Constructor
	Tests() {}
	// Destructor
	~Tests() {}

	// Test wrapper for test functions
	void runTests(void);

	// Tests enqueue() function on empty queue
	void testEnqueueEmpty(void);

	// Tests enqueue() function on a queue with one node
	void testEnqueueOneNode(void);

	// Tests dequeue() function on a queue with one node
	void testDequeueOneNode(void);

	// Tests dequeue() function on a queue with two nodes
	void testDequeueTwoNodes(void);

	// Uses runSimuation() function defined in PA5.h to run the simulation for 24 hours
	void runSim24Hours(void);
};