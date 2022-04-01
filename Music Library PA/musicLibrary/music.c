/*******************************************************************************************
* Programmer: Morgan Baccus                                                                       *
* Class: CptS 122, Summer, 2019; Lab Section 1                                         *
* Programming Assignment: PA 3                                                     *
* Date: June 14, 2019                                                                               *
* Description: This program creates a doubly linked list that functions as a music library would.      *
*******************************************************************************************/

#include "music.h"

/*******************************************************************************************
* Function: search                                                               *
* Input Parameters: List recordList, char *artistName											   *
* Preconditions: N/A															   *
* Returns: Node                                                                *
* Description: This function searches through all nodes in the linked list and returns the one
		with the match attribute that was entered*
********************************************************************************************/
Node search(List recordList, char *artistName)
{
	Node *pMem = recordList.pHead;
	int count = 0;

	while (pMem != NULL) // There is a pNext
	{
		if (strcmp(pMem->data.artist, artistName) == 0) // If the name of artist entered is the same as one in the list
		{
			printf("Artist: %s\nAlbum Title: %s\nSong Title: %s\nGenre: %s\nSong Length: %d:%d\nNumber of times played: %d\nRating: %d\n",
				pMem->data.artist, pMem->data.albumTitle, pMem->data.songTitle, pMem->data.genre,
				pMem->data.length.minutes, pMem->data.length.seconds, pMem->data.numPlayed, pMem->data.rating);

			count += 1;
		}
		putchar('\n');
		pMem = pMem->pNext;
	}

	if (count == 0) // No songs in list by that artist
	{
		printf("No songs by %s were found.\n", artistName);
	}

	return *pMem;
}

/*******************************************************************************************
* Function: printMainMenu                                                               *
* Input Parameters: void										   *
* Preconditions: N/A															   *
* Returns: void                                                                *
* Description: This function prints all options of what the user can do to the screen     *
********************************************************************************************/
void printMainMenu(void)
{
	printf("Welcome to Morgan's Digital Music Manager!\nEnter the number next to the action you would like to do.\n\n");
	printf("Main Menu:\n");
	printf("1. Load\n");
	printf("2. Store\n");
	printf("3. Display\n");
	printf("4. Insert\n");
	printf("5. Delete\n");
	printf("6. Edit\n");
	printf("7. Sort\n");
	printf("8. Rate\n");
	printf("9. Play\n");
	printf("10. Shuffle\n");
	printf("11. Exit\n");
}

/*******************************************************************************************
* Function: makeNode                                                               *
* Input Parameters: Record addSong											   *
* Preconditions: N/A															   *
* Returns: A pointer to a Node*                                                                *
* Description: This function allocates spaces for a new node and initializes all struct
		values within the node *
********************************************************************************************/
Node* makeNode(Record addSong)
{
	Node *pMem = NULL;

	pMem = (Node*)malloc(sizeof(Node));
	if (pMem != NULL)
	{
		// Space was allocated
		strcpy(pMem->data.artist, addSong.artist);
		strcpy(pMem->data.albumTitle, addSong.albumTitle);
		strcpy(pMem->data.songTitle, addSong.songTitle);
		strcpy(pMem->data.genre, addSong.genre);
		pMem->data.length = addSong.length;
		pMem->data.numPlayed = addSong.numPlayed;
		pMem->data.rating = addSong.rating;
	}

	pMem->pNext = NULL;
	pMem->pPrev = NULL;

	return pMem;
}

/*******************************************************************************************
* Function: readInSongs                                                               *
* Input Parameters: FILE *recordfile											   *
* Preconditions: N/A															   *
* Returns: A node with song data saved in it                                               *
* Description: This function reads in data from a .csv file, parses it, and saves it to the
		correct part of the node *
********************************************************************************************/
Record *readInSong(FILE *recordfile)
{
	Record *song = { NULL };
	char songToken[50];

	// parse in song info
	// store info into record struct

	if (strcmp(songToken[0], '"') == 0)
	{
		strcat(songToken, "\"");
		strcpy(song->artist, strtok(songToken, "\""));
		char trash = '\0';
		strcpy(trash, strtok(songToken, ",")); // read in and ignore comma after "
	}
	else
	{
		strcpy(song->artist, strtok(songToken, ","));
	}

	strcpy(song->albumTitle, strtok(songToken, ","));
	strcpy(song->songTitle, strtok(songToken, ","));
	strcpy(song->genre, strtok(songToken, ","));

	// Time
	strcpy(song->length.minutes, strtok(songToken, ":"));
	strcpy(song->length.seconds, strtok(songToken, ","));

	strcpy(song->numPlayed, strtok(songToken, ","));
	strcpy(song->rating, strtok(songToken, ","));

	return song;
}

/*******************************************************************************************
* Function: insertAtFront                                                               *
* Input Parameters: List *pRecordList, Record addSong								   *
* Preconditions: N/A															   *
* Returns: An integer to indicate if the node was added succesfully or not               *
* Description: This function allocates spaces for a new node and adds it to the front of
		the list, returns 1 if successfull *
********************************************************************************************/
int insertAtFront(List *pRecordList, Record addSong)
{
	Node *pMem = makeNode(addSong);
	int success = 0;

	if (pMem != NULL)
	{
		// Space was allocated
		success = 1;

		pMem->pNext = pRecordList->pHead; // Set the pointer of new node equal to pHead
		pRecordList->pHead = pMem; // Update pHead to be first node (pMem)
	}

	return success;
}

/*******************************************************************************************
* Function: loadList                                                               *
* Input Parameters: FILE *recordFile, List *pRecordList								   *
* Preconditions: N/A															   *
* Returns: void               *
* Description: This function reads in data from the csv file, allocates spaces for a new node,
		and inserts the node at front *
********************************************************************************************/
void loadList(FILE *recordFile, List *pRecordList)
{
	Node *newNode = { NULL };
	Record song = { NULL };

	while (!EOF)
	{
		Record song = *readInSong(recordFile);
		newNode = makeNode(song);
		insertAtFront(pRecordList, song);
	}
}

/*******************************************************************************************
* Function: storeRecords                                                               *
* Input Parameters: Node *list, FILE *recordfile								   *
* Preconditions: N/A															   *
* Returns: An integer to indicate success. 1 = success              *
* Description:  Saves records to .csv file*
********************************************************************************************/
void storeRecords(Node *list, FILE *recordfile)
{
	while (!EOF)
	{
		fprintf(" %c,%c,%c,%c,%d:%d,%d,%d\n", list->data.artist, list->data.albumTitle, list->data.songTitle,
			list->data.genre, list->data.length.minutes, list->data.length.seconds,
			list->data.numPlayed, list->data.rating);
	}
}

/*******************************************************************************************
* Function: displayAllRecords                                             *
* Input Parameters: List recordList								   *
* Preconditions: N/A															   *
* Returns: N/A               *
* Description: This functions prints all info contained in each node, starting with the pHead*
********************************************************************************************/
void displayAllRecords(List recordList)
{
	Node *pMem = recordList.pHead;

	while (pMem != NULL) // There is a pNext
	{
		printf("Artist: %s\nAlbum Title: %s\nSong Title: %s\nGenre: %s\nSong Length: %d:%d\nNumber of times played: %d\nRating: %d\n",
			pMem->data.artist, pMem->data.albumTitle, pMem->data.songTitle, pMem->data.genre,
			pMem->data.length.minutes, pMem->data.length.seconds, pMem->data.numPlayed, pMem->data.rating);
		pMem = pMem->pNext;
	}
	putchar('\n');
}

/*******************************************************************************************
* Function: displayRecordsByArtist                                             *
* Input Parameters: List recordList, char *artistName								   *
* Preconditions: N/A															   *
* Returns: N/A               *
* Description: This function traverses through the list of songs and looks for all songs
		with a matching artist name to that entered and prints the details of that song   *
********************************************************************************************/
void displayRecordsByArtist(List recordList, char *artistName)
{
	Node *pMem = recordList.pHead;
	int count = 0;

	while (pMem != NULL) // There is a pNext
	{
		if (strcmp(pMem->data.artist, artistName) == 0) // If the name of artist entered is the same as one in the list
		{
			printf("Artist: %s\nAlbum Title: %s\nSong Title: %s\nGenre: %s\nSong Length: %d:%d\nNumber of times played: %d\nRating: %d\n",
				pMem->data.artist, pMem->data.albumTitle, pMem->data.songTitle, pMem->data.genre,
				pMem->data.length.minutes, pMem->data.length.seconds, pMem->data.numPlayed, pMem->data.rating);

			count += 1;
		}
		putchar('\n');
		pMem = pMem->pNext;
	}

	if (count == 0) // No songs in list by that artist
	{
		printf("No songs by %s were found.\n", artistName);
	}
}

/*******************************************************************************************
* Function: addSong                                             *
* Input Parameters: List recordList, FILE *recordFile								   *
* Preconditions: N/A															   *
* Returns: void               *
* Description: This function reads in information from the user and creates a new node storing
		that data. Inserts node at front of list*
********************************************************************************************/
void addSong(List recordList, FILE *recordFile)
{
	Record new = { NULL };

	int success = 0;

	printf("Enter artist name, album title, song title, genre, minutes, seconds, number of times played, and rating:\n");
	scanf("%s, %s, %s, %s, %d, %d, %d, %d", &new.artist, &new.albumTitle, &new.songTitle, &new.genre, &new.length.minutes, &new.length.seconds, &new.numPlayed, &new.rating);

	Node *pMem = NULL;
	pMem = makeNode(new);

	if (pMem != NULL)
		success = insertAtFront(pMem, new);

	if (success == 1)
		storeRecords(pMem, recordFile);
}

/*******************************************************************************************
* Function: delete                                             *
* Input Parameters: List recordList, FILE *recordFile								   *
* Preconditions: cannot be an empty list															   *
* Returns: void               *
* Description: This function scans through the list and looks for song with matching title
		to that entered and then removes node from list  *
********************************************************************************************/
void delete(List recordList, FILE *recordFile)
{
	char *target = { NULL };
	Node *pCur = recordList.pHead, *pTemp = NULL;

	printf("Enter song title to delete:\n");
	scanf("%s", target);

	while (pCur != NULL)
	{
		if (strcmp(target, pCur->data.songTitle) == 0)
		{
			pTemp = pCur;
			pCur->pPrev->pNext = pCur->pNext;
			pCur->pNext->pPrev = pCur->pPrev;

			free(pTemp);
		}

		pCur->pNext = pCur;
	}
}

/*******************************************************************************************
* Function: editRecordByArtist                                             *
* Input Parameters: List recordList, char *artistName								   *
* Preconditions: N/A															   *
* Returns: void               *
* Description: Scans in asrtist name, searches for songs by that artist, asks which song if
		multiple, asks which fields to edit, saves new data to csv file*
********************************************************************************************/
void editRecordByArtist(List recordList, char *artistName)
{
	Node *pMem = recordList.pHead;
	int count = 0, check = 0, choice = 0;
	char *temp = { NULL };

	while (pMem != NULL) // There is a pNext
	{
		if (strcmp(pMem->data.artist, artistName) == 0) // If the name of artist entered is the same as one in the list
		{
			printf("Song Title: %s \n", pMem->data.songTitle);

			printf("Enter 1 if you'd like to edit this song, 2 if you'd like to see the next song.");
			scanf("%d", &check);

			if (check == 1)
			{
				printf("What field would you like to change? 1.Artist 2.Album Name 3.Song Title 4.Genre 5.Minutes 6.Seconds");
				scanf("%d", &choice);
				if (choice == 1)
				{
					printf("Enter new artist name:");
					scanf("%s", &temp);
					pMem->data.artist = temp;
				}
				else if (choice == 2)
				{
					printf("Enter new album title:");
					scanf("%s", &temp);
					pMem->data.albumTitle = temp;
				}
				else if (choice == 3)
				{
					printf("Enter new song title:");
					scanf("%s", &temp);
					pMem->data.songTitle = temp;
				}
				else if (choice == 4)
				{
					printf("Enter new genre:");
					scanf("%s", &temp);
					pMem->data.genre = temp;
				}
				else if (choice == 5)
				{
					printf("Enter new minutes:");
					scanf("%d", &temp);
					pMem->data.length.minutes = temp;
				}
				else if (choice == 6)
				{
					printf("Enter new seconds:");
					scanf("%d", &temp);
					pMem->data.length.seconds = temp;
				}
				else
				{
					printf("You did not enter a valid option.");
				}
			}

			count += 1;
		}
		putchar('\n');
		pMem = pMem->pNext;
	}

	if (count == 0) // No songs in list by that artist
	{
		printf("No songs by %s were found.\n", artistName);
	}
}

/*******************************************************************************************
* Function: sort                                             *
* Input Parameters: Node *list, FILE *recordFile								   *
* Preconditions: N/A															   *
* Returns: void               *
* Description: Asks how to sort list, sorts using bubble sort*
********************************************************************************************/
void sort(Node *list, FILE *recordFile)
{
	// Using bubble sort
	int choice = 0;

	printf("Enter number that corresponds to sorting method to be selected:\n1. artist A-Z 2. album title A-Z 3. rating 1-5 4. number of times played big-small");
	scanf("%d", &choice);

	if (choice == 1)
	{
		// Sort artist A-Z
		Node *pCur = NULL, *before = NULL, *after = NULL;
		pCur = list;

		if (strcmp(pCur->data.artist, pCur->pNext->data.artist) > 0) // if artist 1 is b and artist 2 is a
		{
			before = pCur->pPrev;
			after = pCur->pNext;

			if (before != NULL)
			{
				before->pNext = after;
			}

			pCur->pNext = after->pNext;
			pCur->pPrev = after;
			after->pNext = pCur;
			after->pPrev = before;
		}
	}

	else if (choice == 2)
	{
		// Sort album title A-Z
		Node *pCur = NULL, *before = NULL, *after = NULL;
		pCur = list;

		if (strcmp(pCur->data.albumTitle, pCur->pNext->data.albumTitle) > 0)
		{
			before = pCur->pPrev;
			after = pCur->pNext;

			if (before != NULL)
			{
				before->pNext = after;
			}

			pCur->pNext = after->pNext;
			pCur->pPrev = after;
			after->pNext = pCur;
			after->pPrev = before;
		}
	}

	else if(choice == 3)
	{
		// Sort rating 1-5
		Node *pCur = NULL, *before = NULL, *after = NULL;
		pCur = list;

		if (pCur->data.rating > pCur->pNext->data.rating)
		{
			before = pCur->pPrev;
			after = pCur->pNext;

			if (before != NULL)
			{
				before->pNext = after;
			}

			pCur->pNext = after->pNext;
			pCur->pPrev = after;
			after->pNext = pCur;
			after->pPrev = before;
		}
	}

	else if (choice == 4)
	{
		// Sort num times play big-small
		Node *pCur = NULL, *before = NULL, *after = NULL;
		pCur = list;

		if (pCur->data.numPlayed > pCur->pNext->data.numPlayed)
		{
			before = pCur->pPrev;
			after = pCur->pNext;

			if (before != NULL)
			{
				before->pNext = after;
			}

			pCur->pNext = after->pNext;
			pCur->pPrev = after;
			after->pNext = pCur;
			after->pPrev = before;
		}
	}

	else
	{
		printf("Did not enter a valid choice.");
	}

	storeRecords(list, recordFile);
}

/*******************************************************************************************
* Function: editRatingByArtist                                             *
* Input Parameters: List recordList, char *artistName								   *
* Preconditions: N/A															   *
* Returns: void               *
* Description: Scans in artist name, asks which song if multiple, scans in and saves new rating *
********************************************************************************************/
void editRatingByArtist(List recordList, char *artistName)
{

	Node *pMem = recordList.pHead;
	int count = 0, check = 0;
	char *temp;

	while (pMem != NULL) // There is a pNext
	{
		if (strcmp(pMem->data.artist, artistName) == 0) // If the name of artist entered is the same as one in the list
		{
			printf("Song Title: %s \n", pMem->data.songTitle);

			printf("Enter 1 if you'd like to edit this song, 2 if you'd like to see the next song.");
			scanf("%d", &check);

			if (check == 1)
			{
				printf("Enter new rating:");
				scanf("%d", &temp);

				pMem->data.rating = temp;
			}

			count += 1;
		}
		putchar('\n');
		pMem = pMem->pNext;
	}

	if (count == 0) // No songs in list by that artist
	{
		printf("No songs by %s were found.\n", artistName);
	}
}

/*******************************************************************************************
* Function: playRecords                                             *
* Input Parameters: List recordList								   *
* Preconditions: N/A															   *
* Returns: void               *
* Description: traverses through linked list and prints song info to screen until user presses enter *
********************************************************************************************/
void playRecords(List recordList)
{
	Node *pMem = recordList.pHead;
	
	printf("Press enter to go to the next song.");

	while (pMem != NULL) // There is a pNext
	{
		printf("Artist: %s\nAlbum Title: %s\nSong Title: %s\nGenre: %s\nSong Length: %d:%d\nNumber of times played: %d\nRating: %d\n",
			pMem->data.artist, pMem->data.albumTitle, pMem->data.songTitle, pMem->data.genre,
			pMem->data.length.minutes, pMem->data.length.seconds, pMem->data.numPlayed, pMem->data.rating);

		system("pause");
		system("cls");
		pMem = pMem->pNext;
	}
	putchar('\n');
}

/*******************************************************************************************
* Function: playNthSong                                             *
* Input Parameters: List *recordList, int target								   *
* Preconditions: N/A															   *
* Returns: void               *
* Description: Looks for node in target position and prints to screen*
********************************************************************************************/
void playNthSong(List *recordList, int target)
{
	Node *songArr[100] = { NULL };
	Node *pArr = recordList->pHead;
	int count = 0;

	while (pArr != NULL)
	{
		songArr[count] = pArr;

		pArr->pNext = pArr;
		++count;
	}

	// print songArr(target) to screen??
}

/*******************************************************************************************
* Function: shuffle                                             *
* Input Parameters: List recordList, FILE *recordFile								   *
* Preconditions: N/A															   *
* Returns: void               *
* Description: Generates a random number and creates a parallel array that has indices that
		correspond with the random number. Checks if song has been played already in function call*
********************************************************************************************/
void shuffle(List recordList, FILE *recordFile)
{
	int parallelArr[100] = { -1 };
	int count = 0;
	Node *pCur = recordList.pHead;

	// Count how many songs there are in list
	int numSongs = 0;

	while (pCur != NULL)
	{
		++numSongs;
		pCur->pNext = pCur;
	}

	while (count < numSongs) // while the number of songs played is less than the number of songs in the list
	{
		int shuff = (rand() % numSongs) + 1;

		if (parallelArr[shuff] == -1) // -1 = not been played
		{
			parallelArr[shuff] = 1; // 1 = been played
			playNthSong(pCur, shuff); // play song
			++count; // increase count of songs played
		}
	}
}