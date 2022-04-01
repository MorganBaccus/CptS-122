/*
Programmer: Morgan Baccus
Class: CptS 122; Lab Section 1
Programming Assignment: PA 5
Description: This program simulates 2 grocery store lines using queues.
*/

#pragma once

#include "simulation.h"

class Data
{
public:
	// Default Constructor
	Data() : customerNumber(0), serviceTime(0), totalTime(0) {}
	// Value Constructor
	Data(int _customerNumber, int _serviceTime, int _totalTime) : customerNumber(_customerNumber), serviceTime(_serviceTime), totalTime(_totalTime) {}
	// Copy Constructor
	Data(Data &old) : customerNumber(old.customerNumber), serviceTime(old.serviceTime), totalTime(old.totalTime) {}

	// Getters
	int getCustomerNumber(void);
	int getServiceTime(void);
	int getTotalTime(void);

private:
	int customerNumber;
	int serviceTime;
	int totalTime;
};