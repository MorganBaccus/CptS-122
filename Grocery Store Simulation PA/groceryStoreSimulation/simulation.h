/*
Programmer: Morgan Baccus
Class: CptS 122; Lab Section 1
Programming Assignment: PA 5
Description: This program simulates 2 grocery store lines using queues.
*/

#pragma once

#include <iostream>
#include <string>
#include <time.h>

#define MIN_IN_HOUR 60 // Constant for number of minutes in an hour. Used for easy reading


// Runs simulation with various counters and two queues
void runSimulation(int numMinutes);