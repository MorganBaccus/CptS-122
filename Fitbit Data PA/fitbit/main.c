/*******************************************************************************************
* Programmer: Morgan Baccus                                                                       *
* Class: CptS 122, Summer, 2019; Lab Section 1                                         *
* Programming Assignment: PA 1                                                     *
* Date: June 5, 2019                                                                               *
* Description: This program reads in data collected from a FitBit over 24 hours that is
	stored in a .csv file, cleans it, analyzes it, and prints out the analysis and cleaned
	data to a new .csv file.     *
*******************************************************************************************/

#include "fitbit.h"

int main(void)
{
	// Open "FitbitData.csv" to be read
	FILE *infile = NULL;
	infile = fopen("FitbitData.csv", "r");

	// Open "Results.csv" to be written in
	FILE *outfile = NULL;
	outfile = fopen("Results.csv", "w");

	FitbitData data[1500] = { "", "", 0.0, 0.0, 0, 0, 0, 0 };
	char targetPatient[100];
	int skipLine = 0, i =0;


	if (infile != NULL) // Check if infile was opened successfully
	{
		findTargetPatient(infile, targetPatient);
		readHeader(infile);

		for (i = 0; i < 1440; i++) // With no duplicates, there should be 0 to 1439 minutes
		{
			if (readLine(targetPatient, data, infile, i) == 0)
			{
				i--;
				skipLine++;
			}

			else
			{
				//Debug console line print message.
				//printPatientLine(data, i, skips);
			}
		}


		double caloriesBurned = calcCaloriesBurned(data, i);
		double distanceWalked = calcDistanceWalked(data, i);
		unsigned int floorsWalked = calcFloorsWalked(data, i);
		unsigned int stepsTaken = calcStepsTaken(data, i);
		double averageHeartRate = calcAvgHeartRate(data, i);
		int maxStepsInMinute = calcMaxStepsInMin(data, i);
		char startBadSleep[15] = { '\0' };
		char endBadSleep[15] = { '\0' };
		calcLongestBadSleepPeriod(data, i, startBadSleep, endBadSleep);


		if (outfile != NULL) // Outfile has been opened successfully
		{
			printResults(outfile, data, i, caloriesBurned, distanceWalked, floorsWalked, stepsTaken, averageHeartRate, maxStepsInMinute, startBadSleep, endBadSleep);
			printf("Output has been written to .csv file.\n");
		}

		else
		{
			printf("Error-- Unable to write output to .csv file.\n");
		}
	}

	else
	{
		printf("Error-- Unable to read file.\n");
	}


	// Close "FitbitData.csv"
	fclose(infile);

	// Close "Results.csv"
	fclose(outfile);
}