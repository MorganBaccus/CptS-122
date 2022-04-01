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

void readHeader(FILE * infile)
{
	char header[100] = { '\0' }; 

	fgets(header, 100, infile); // Read in target patient line
	fgets(header, 100, infile); // Read in header line
}

void findTargetPatient(FILE * infile, char * targetPatientID)
{
	char temp[20] = { '\0' };

	fgets(temp, 20, infile);

	strcpy(targetPatientID, strtok(temp, ",")); // Read patient ID without commas using comma delimiter
}

int readLine(const char * patient, FitbitData data[1500], FILE * infile, int iteration)
{
	// Strtok must be called 8 times for each line of data

	char line[100] = { '\0' };
	int badCommaIndex = findBadComma(line);
	int endComma = findEndComma(line);
	char id[100] = { '\0' };
	char minute[25] = { '\0' };

	fgets(line, 100, infile); // Read in line

	strcpy(id, strtok(line, ",")); // Save patient ID from file as ID in struct

	if (strcmp(patient, id) == 0) { // Compare target patient ID to patient ID read in from file, if they are the same proceed
		strcpy(minute, strtok(NULL, ",")); // Check if minute data is duplicate line
		if (iteration > 0)
		{
			if (strcmp(minute, data[iteration - 1].minute) == 0) {
				return 0;
			}
		}

		// Read in patient ID
		strcpy(data[iteration].patient, id);


		// Insert '\0' if missing minute data
		if (badCommaIndex == 1)
		{
			strcpy(data[iteration].minute, "\0");
		}

		else
		{
			strcpy(data[iteration].minute, minute);
		}


		// Insert -1.0 if missing calorie data
		if (badCommaIndex == 2)
		{
			data[iteration].calories = -1.0;
		}

		else
		{
			double calories = 0.0;
			sscanf(strtok(NULL, ","), "%lf", &calories);
			data[iteration].calories = calories;
		}


		// Insert -1.0 if missing distance data
		if (badCommaIndex == 3)
		{
			data[iteration].distance = -1.0;
		}

		else
		{
			double distance = 0.0;
			sscanf(strtok(NULL, ","), "%lf", &distance);
			data[iteration].distance = distance;
		}


		// Insert -1.0 if missing floor data
		if (badCommaIndex == 4) {
			data[iteration].floors = -1;
		}

		else
		{
			unsigned int floors = 0;
			floors = atoi(strtok(NULL, ","));
			data[iteration].floors = floors;
		}


		// Insert -1.0 if missing heart rate data
		if (badCommaIndex == 5) {
			data[iteration].heartRate = -1;
		}

		else
		{
			unsigned int heart = 0;
			heart = atoi(strtok(NULL, ","));
			data[iteration].heartRate = heart;
		}


		// Insert -1.0 if missing step data
		if (badCommaIndex == 6) {
			//bad comma = element # + 1
			data[iteration].steps = -1;
		}

		else
		{
			unsigned int steps = 0;
			steps = atoi(strtok(NULL, ","));
			data[iteration].steps = steps;
		}


		// Insert 0 if missing sleep data
		if (endComma || badCommaIndex == 7)
		{
			data[iteration].sleepLevel = 0;
		}

		else
		{
			Sleep sleepLevel = NONE;
			sleepLevel = atoi(strtok(NULL, ","));
			data[iteration].sleepLevel = sleepLevel;
		}
		return 1;
	}
	return 0;
}

void printLine(FitbitData data[1500], int iteration, int skipLine)
{
	printf("ITERATION %d, LINE %d\n", iteration, iteration + 3 + skipLine);
	printf("Patient ID: %s\n", data[iteration].patient);
	printf("Minute: %s\n", data[iteration].minute);
	printf("Calories: %lf\n", data[iteration].calories);
	printf("Distance: %lf\n", data[iteration].distance);
	printf("Floors: %u\n", data[iteration].floors);
	printf("Heartrate: %u\n", data[iteration].heartRate);
	printf("Steps: %u\n", data[iteration].steps);
	printf("Sleep Level: %d\n", data[iteration].sleepLevel);
}

int findBadComma(char * line)
{
	// If line contains a double comma, return 1. If not, return 0

	int count = 0;

	if (strstr(line, ",,") == NULL) // If no double comma, strstr will return null
	{
		return 0;
	}

	while (*line != '\0')
	{
		if (*line == ',' && *(line + 1) == ',')
		{
			return ++count;
		}
		else if (*line == ',' && *(line + 1) != ',')
		{
			count++;
		}
	
		line++;
	}

	return count;
}

int findEndComma(char * line)
{
	while (*line != '\0')
	{
		if (*line == ',' && *(line + 1) == '\0')
		{
			return 1;
		}

		line++;
	}

	return 0;
}

double calcCaloriesBurned(FitbitData data[1500], int iteration)
{
	double total = 0.0;
	int i = 0;

	while (i < iteration)
	{
		if (data[i].calories >= 0.0)
		{
			total += data[i].calories;
		}
		i++;
	}
	return total;
}

double calcDistanceWalked(FitbitData data[1500], int iteration)
{
	double total = 0.0;
	int i = 0;

	while (i < iteration)
	{
		if (data[i].distance >= 0.0)
		{
			total += data[i].distance;
		}
		i++;
	}

	return total;
}

int calcFloorsWalked(FitbitData data[1500], int iteration)
{
	int total = 0, i = 0;

	while (i < iteration)
	{
		if (data[i].floors != 4294967295) // Max unsigned int
		{
			total += data[i].floors;
		}
		i++;
	}

	return total;
}

int calcStepsTaken(FitbitData data[1500], int iteration)
{
	int total = 0, i = 0;

	while (i < iteration)
	{
		if (data[i].steps != 4294967295) // Max unsigned int
		{
			total += data[i].steps;
		}
		i++;
	}

	return total;
}

double calcAvgHeartRate(FitbitData data[1500], int iteration)
{
	double avg = 0.0;
	int num = 0, i = 0;

	while (i < iteration)
	{
		if (data[i].heartRate != 4294967295) // Max unsigned int
		{
			avg += data[i].heartRate;
			num++;
		}
		i++;
	}

	avg = avg / num;
	return avg;
}

int calcMaxStepsInMin(FitbitData data[1500], int iteration)
{
	int max = data[0].steps, i = 0;

	while (i < iteration)
	{
		if (data[i].steps >= max)
		{
			max = data[i].steps;
		}
		i++;
	}
	return max;
}

void calcLongestBadSleepPeriod(FitbitData data[1500], int iteration, char * startTime, char * endTime)
{
	int period = 1, j = 0;
	int sum[100] = { 0 };
	char start[50][15] = { { '\0' } };
	char end[50][15] = { { '\0' } };

	for (int i = 0; i < iteration; i++)
	{
		if (data[i].sleepLevel > 1)
		{
			if (period)
			{
				// Continuation of period
				sum[j] += data[i].sleepLevel;
			}

			else
			{
				// Start of new period
				period = 1;
				strcpy(start[j], data[i].minute);
				sum[j] += data[i].sleepLevel;
			}
		}

		else if (data[i - 1].sleepLevel > 1)
		{
			// End of period
			strcpy(end[j], data[i - 1].minute);
			period = 0;
			j++;
		}
	}


	// Find max of sums
	int max = sum[0];
	j = 0;

	while (sum[j] != 0)
	{
		if (sum[j] > max)
		{
			max = sum[j];
		}
		j++;
	}


	// Linear search for index of max
	j = 0;
	while (sum[j] != 0)
	{
		if (sum[j] == max)
		{
			break;
		}
		j++;
	}

	strcpy(startTime, start[j]);
	strcpy(endTime, end[j]);
}

void printResults(FILE * outfile, FitbitData data[1500], int iteration, double totalCalories, double totalMiles, unsigned int totalFloors, unsigned int totalSteps, double avgHeartRate, int maxSteps, char * startBadSleep, char * endBadSleep)
{
	// Print results to .csv file
	fprintf(outfile, "Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n");
	fprintf(outfile, "%lf,%lf,%u,%u,%lf,%d,%s:%s\n", totalCalories, totalMiles, totalFloors, totalSteps, avgHeartRate, maxSteps, startBadSleep, endBadSleep);
	for (int i = 0; i < iteration; i++) {
		fprintf(outfile, "%s,", data[i].patient);
		fprintf(outfile, "%s,", data[i].minute);
		fprintf(outfile, "%lf,", data[i].calories);
		fprintf(outfile, "%lf,", data[i].distance);
		fprintf(outfile, "%d,", data[i].floors);
		fprintf(outfile, "%d,", data[i].heartRate);
		fprintf(outfile, "%d,", data[i].steps);
		fprintf(outfile, "%d\n", data[i].sleepLevel);
	}

	// Print results to screen
	printf("Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n");
	printf("%lf,%lf,%u,%u,%lf,%d,%s:%s\n", totalCalories, totalMiles, totalFloors, totalSteps, avgHeartRate, maxSteps, startBadSleep, endBadSleep);
	for (int i = 0; i < iteration; i++) {
		printf("%s,", data[i].patient);
		printf("%s,", data[i].minute);
		printf("%lf,", data[i].calories);
		printf("%lf,", data[i].distance);
		printf("%d,", data[i].floors);
		printf( "%d,", data[i].heartRate);
		printf("%d,", data[i].steps);
		printf("%d\n", data[i].sleepLevel);
	}
}
