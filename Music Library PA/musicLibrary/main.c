/*******************************************************************************************
* Programmer: Morgan Baccus                                                                       *
* Class: CptS 122, Summer, 2019; Lab Section 1                                         *
* Programming Assignment: PA 3                                                     *
* Date: June 14, 2019                                                                               *
* Description: This program creates a doubly linked list that functions as a music library would.      *
*******************************************************************************************/

#include "music.h"

int main(void)
{
	int menuSelection = 0;
	Node *pList = NULL;
	char *artistName = { NULL };
	char *songTitle = { NULL };
	List *list = { NULL };
	List songList = { NULL };

	FILE *recordFile = NULL;

		do
		{
			menuSelection = 0; // Reset menuSelection
			system("cls"); // Clear screen

			printMainMenu();
			scanf("%d", &menuSelection); // Read in value for menuSelection

			if (menuSelection == 1)
			{
				// Load
				
				recordFile = fopen("musicPlayList.csv", "r");

				loadList(recordFile, list);

				fclose(recordFile);
			}

			else if (menuSelection == 2)
			{
				// Store

				recordFile = fopen("musicPlayList.csv", "w");

				storeRecords(pList, recordFile);

				fclose(recordFile);
			}

			else if (menuSelection == 3)
			{
				// Display
				int choice = 0;
				char name[50] = { NULL };

				printf("Enter 1 to display all records, enter 2 to display records by a certain artist:\n");
				scanf("%d", &choice);

				if (choice == 1)
					displayAllRecords(songList);
				else if (choice == 2)
				{
					printf("Enter artist's name:\n");
					scanf("%s", &name);
					displayRecordsByArtist(songList, name);
				}
			}

			else if (menuSelection == 4)
			{
				// Insert
				recordFile = fopen("musicPlayList.csv", "w");

				addSong(songList, recordFile);

				fclose(recordFile);
			}

			else if (menuSelection == 5)
			{
				// Delete
				recordFile = fopen("musicPlayList.csv", "w");
				delete(songList, recordFile);
				fclose(recordFile);
			}

			else if (menuSelection == 6)
			{
				// Edit
				char name[50] = { NULL };

				printf("Enter artist that info you want to edit:\n");
				scanf("%s", &name);

				editRecordByArtist(songList, name);
			}

			else if (menuSelection == 7)
			{
				// Sort
				recordFile = fopen("musicPlayList.csv", "w");
				sort(pList, recordFile);
				fclose(recordFile);
			}

			else if (menuSelection == 8)
			{
				// Rate
				char name[50] = { NULL };

				printf("Enter artist of song that you want to rate:\n");
				scanf("%s", &name);

				editRatingByArtist(songList, name);
			}

			else if (menuSelection == 9)
			{
				// Play
				playRecords(songList);
			}

			else if (menuSelection == 10)
			{
				// Shuffle
				recordFile = fopen("musicPlayList.csv", "w");

				//shuffle(list, "recordFile");

				fclose(recordFile);
			}

			else if (menuSelection == 11)
			{
				// Exit
				printf("Goodbye!");

				recordFile = fopen("musicPlayList.csv", "w");
				storeRecords(pList, recordFile);
				fclose(recordFile);

				return 0;
			}

		} while (menuSelection != 11); // End of do-while loop

	system("pause");
	return 0;
}