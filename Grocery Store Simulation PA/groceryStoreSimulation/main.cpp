/*
Programmer: Morgan Baccus
Class: CptS 122; Lab Section 1
Programming Assignment: PA 5
Description: This program simulates 2 grocery store lines using queues.
*/

#include "simulation.h"
#include "Queue.h"
#include "testFunctions.h"

using std::cout;
using std::endl;

int main(void)
{
	// Sets random number generation seed based on time
	srand(time(NULL));

	Tests t;
	t.runTests();


	system("pause");
	return 0;
}

void runSimulation(int numMinutes)
{
	int totalTimeElapsed = 0;
	int customerCount = 1;
	int normalLaneArrival = rand() % 5 + 1;
	int expressLaneArrival = rand() % 8 + 3;

	Queue normalLane;
	Queue expressLane;

	int minsUntilNextNormal = normalLaneArrival;
	int minsUntilNextExpress = expressLaneArrival;

	int normalFrontTimer = 0;
	int expressFrontTimer = 0;

	// Simulation loop-- once per minute
	while (totalTimeElapsed < numMinutes)
	{
		if (normalFrontTimer < 0 && !normalLane.isEmpty())
		{
			normalFrontTimer = normalLane.getTail()->getData()->getServiceTime();
		}

		if (expressFrontTimer < 0 && !expressLane.isEmpty())
		{
			expressFrontTimer = expressLane.getTail()->getData()->getServiceTime();
		}

		if (minsUntilNextNormal == 0) // Add customer into normal line
		{
			int serviceTime = rand() % 5 + 1;
			int sumTimes = normalLane.calculateSumServiceTimes(normalLane.getHead());
			int totalTime = serviceTime + sumTimes;
			Data *customer = new Data(customerCount++, serviceTime, totalTime);
			cout << "Customer #" << customer->getCustomerNumber() << " has entered the Normal Lane at Time " << totalTimeElapsed << "m." << endl;
			normalLane.enqueue(*customer);
			minsUntilNextNormal = rand() % 5 + 1;
		}
		else
		{
			minsUntilNextNormal--;
		}

		if (minsUntilNextExpress == 0) // Add customer into express line
		{
			int serviceTime = rand() % 8 + 3;
			int sumTimes = expressLane.calculateSumServiceTimes(expressLane.getHead());
			int totalTime = serviceTime + sumTimes;
			Data *customer = new Data(customerCount++, serviceTime, totalTime);
			cout << "Customer #" << customer->getCustomerNumber() << " has entered the Express Lane at Time " << totalTimeElapsed << "m." << endl;
			expressLane.enqueue(*customer);
			minsUntilNextExpress = rand() % 8 + 3;
		}
		else
		{
			minsUntilNextExpress--;
		}

		if (normalFrontTimer == 0 && !normalLane.isEmpty())
		{
			cout << "Customer #" << normalLane.getHead()->getData()->getCustomerNumber() << " has finished checking out of the Normal Lane." << endl;
			int time = normalLane.getHead()->getData()->getTotalTime();
			cout << "They were in line for " << time << "m and exited at " << totalTimeElapsed << "m." << endl;
			normalLane.dequeue();
		}

		if (expressFrontTimer == 0 && !expressLane.isEmpty())
		{
			cout << "Customer #" << expressLane.getHead()->getData()->getCustomerNumber() << " has finished checking out of the Express Lane." << endl;
			int time = expressLane.getHead()->getData()->getTotalTime();
			cout << "They were in line for " << time << "m and exited at " << totalTimeElapsed << "m." << endl;
			expressLane.dequeue();
		}

		if (totalTimeElapsed % 10 == 0)
		{
			cout << "TIME ELAPSED: " << totalTimeElapsed << "m" << endl;
			cout << "NORMAL LANE:" << endl;
			normalLane.printQueue(normalLane.getHead());
			cout << "EXPRESS LANE:" << endl;
			expressLane.printQueue(expressLane.getHead());
		}

		totalTimeElapsed++;
		normalFrontTimer--;
		expressFrontTimer--;
	}
}