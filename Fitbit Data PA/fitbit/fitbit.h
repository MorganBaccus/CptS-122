/*******************************************************************************************
* Programmer: Morgan Baccus                                                                       *
* Class: CptS 122, Summer, 2019; Lab Section 1                                         *
* Programming Assignment: PA 1                                                     *
* Date: June 5, 2019                                                                               *
* Description: This program reads in data collected from a FitBit over 24 hours that is
	stored in a .csv file, cleans it, analyzes it, and prints out the analysis and cleaned
	data to a new .csv file.     *
*******************************************************************************************/

#ifndef FITBIT_H
#define FITBIT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Declare sleep enum
typedef enum sleep {
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

// Declare fitbit data struct
typedef struct fitbit {
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	int floors;
	unsigned int heartRate;
	int steps;
	Sleep sleepLevel;
} FitbitData;


// Function Prototypes

// Header does not contain data, so we want to read it in and discard it
void readHeader(FILE *infile);

// Used to return a copy of the target patient's ID (indirect value)
void findTargetPatient(FILE *infile, char *target);

int readLine(const char *patient, FitbitData data[1500], FILE *infile, int iteration);
 
void printLine(FitbitData data[1500], int iteration, int skipLine);
 
int findBadComma(char *line);
 
int findEndComma(char *line);
 
double calcCaloriesBurned(FitbitData data[1500], int iteration);
 
double calcDistanceWalked(FitbitData data[1500], int iteration);
 
int calcFloorsWalked(FitbitData data[1500], int iteration);
 
int calcStepsTaken(FitbitData data[1500], int iteration);
 
double calcAvgHeartRate(FitbitData data[1500], int iteration);
 
int calcMaxStepsInMin(FitbitData data[1500], int iteration);
 
void calcLongestBadSleepPeriod(FitbitData data[1500], int iteration, char *startTime, char *endTime);
 
void printResults(FILE *outfile, FitbitData data[1500], int iteration, double totalCalories, double totalMiles,
	unsigned int totalFloors, unsigned int totalSteps, double avgHeartRate, int maxSteps,
	char *startBadSleep, char *endBadSleep);

#endif
