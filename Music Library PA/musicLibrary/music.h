/*******************************************************************************************
* Programmer: Morgan Baccus                                                                       *
* Class: CptS 122, Summer, 2019; Lab Section 1                                         *
* Programming Assignment: PA 3                                                     *
* Date: June 14, 2019                                                                               *
* Description: This program creates a doubly linked list that functions as a music library would.      *
*******************************************************************************************/

#ifndef MUSIC_H
#define MUSIC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct duration
{
	int minutes;
	int seconds;
}Duration;

typedef struct record
{
	char *artist;
	char *albumTitle;
	char *songTitle;
	char *genre;
	Duration length; // Struct with min and sec of song length
	int numPlayed;
	int rating; // 1-5
}Record;

typedef struct node
{
	Record data;
	struct node *pNext;
	struct node *pPrev;
} Node;

typedef struct list
{
	Node *pHead;
}List;


// Function Prototypes

// Search List
	// Traverse list and strcmp or int == int based on attribute
Node search(List recordList, char *artistName);

// Print main menu
void printMainMenu(void);

// 1 Load. Reads all records from .csv file into a dynamic doubly linked list by inserting at front
Node* makeNode(Record addSong);
Record *readInSong(FILE *recordfile);
int insertAtFront(List *pRecordList, Record addSong);
void loadList(FILE *recordFile, List *pRecordList); // Combines above functions, puts into linked list

// 2 Store. Saves the records into .csv file
void storeRecords(Node *list, FILE *recordfile);

// 3 Display. 1) Print all songs to the screen. 2) Print all songs by a specific artist to the screen
void displayAllRecords(List recordList);
void displayRecordsByArtist(List recordList, char *artistName);

// 4 Insert. Prompt user for song info and then insert at front
	// Scan in song info from user and stores into record struct
	// Call makeNode
	// Inser at front
void addSong(List recordList, FILE *recordFile); // that calls other functions

// 5 Delete. Prompt user for song title and delete song, if song is not in the list then the list is unchanged
	// Scan in song title
	// call Node search(List recordList);
void delete(List recordList, FILE *recordFile); // Combine above steps

// 6 Edit. Allows user to find a song by artist- if multiple songs by the same artist, ask which song. User can change all fields of song
	// Scan in artist
	// Search for song by artist with search()
	// scan in which field to edit and what to put in it
	// only change fields that make sense!!! not rate
void editRecordByArtist(List recordList, char *artistName);

// 7 Sort. Ask user if they want to sort artist A-Z, album A-Z, rating 1-5, number of times played big-small
	// scan in how to sort, if or switch statements to which case
	// make sub functions for each way to sort
	// store to .csv file the new order, call store()
void sort(Node *list, FILE *recordFile);

// 8 Rate. Allow a user to assign a number 1-5 to a song. 1 = low, 5 = high
	// scan in artist
	// search()
		// scan in which song to change
		// search()
	// scan in new rating
	// store() new rating
void editRatingByArtist(List recordList, char *artistName);

// 9 Play. Allow user to select song, display song info for short amount of time, clearing the screen, and continuing through the list until all songs have been played
	// Node traverseList(Node *list, List recordList);
	// print each record to screen
void playRecords(List recordList);

// 10 Shuffle. Create a random order for songs to be played, do not changes the order of links
	// traverseList() and count 
	//find number of songs
	// make parallel array really big
void playNthSong(List *recordList, int target);
void shuffle(List recordList, FILE *recordFile);


#endif // !MUSIC_H
