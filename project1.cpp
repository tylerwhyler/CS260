// Author: Tyler Isaacson
// Date: February 2, 2023
// CS260 Data Structures
// Instructor: Li Liang
// project1.cpp: the "front end" for the whole program, it gives the user information and takes the user's inputs

// This file is the driver for a fully-functional music library built using a linear linked list ADT

#include "project1.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <limits>
#include <fstream>

using namespace std;

void read_file(const char* file_name, const int MAX_CHAR_LENGTH, SongList* aList);

int main() {
	const int MAX_CHAR_LENGTH = 32;
	const char* FILE_NAME = "songs_data.csv";

	bool user_input = true;
	int user_selection = 0;

	SongList* myLibrary = new SongList;
	
	read_file(FILE_NAME, MAX_CHAR_LENGTH, myLibrary);

	while (user_input) {
		cout << "\nMake a selection:" << endl;
		cout << "(1) Enter 1 to add a song" << endl;
		cout << "(2) Enter 2 to edit a song's likes" << endl;
		cout << "(3) Enter 3 to delete all songs under X likes" << endl;
		cout << "(4) Enter 4 to see all songs" << endl;
		cout << "(5) Enter 5 to see all songs by a specific artist" << endl;
		cout << "(6) Enter 6 to delete entire music library and exit" << endl;

		cin.clear();
		while(!(std::cin >> user_selection)){
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	cout << "Invalid input, please input a number" << endl;;
    	}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		char title[MAX_CHAR_LENGTH];
		char artist[MAX_CHAR_LENGTH];
		float length = 0.0;
		int likes = 0;
		bool flag = false;

		switch (user_selection) {

			case 1:
				cout << "Enter the song's title" << endl;
				cin.getline(title, MAX_CHAR_LENGTH);

				cout << "Enter the song's artist" << endl;
				cin.getline(artist, MAX_CHAR_LENGTH);

				cout << "Enter the song's length (ex: 2.40)" << endl;
				cin >> length;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "Enter the song's number of likes" << endl;
				cin >> likes;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				try {
					flag = myLibrary->add_song(title, artist, length, likes);
					throw flag;
				} catch (bool flag) {
					if (flag) {
						cout << "\nSong added to playlist" << endl;
					}
					else {
						cout << "\nUnable to add song to playlist" << endl;	
					}
				}

				break;

			case 2:
				cout << "Enter the title of the song to update" << endl;
				cin.getline(title, 32);

				cout << "Enter the new number of likes" << endl;
				cin >> likes;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');


				try {
					flag = myLibrary->edit_likes(title, likes);
					throw flag;
				} catch (bool flag) {
					if (flag) {
						cout << "\n\""  << title << "\"'s likes edited successfully" << endl;
					}
					else {
						cout << "\nUnable to edit \"" << title << "\"'s likes" << endl;	
					}
				}

				break;

			case 3:
				cout << "Enter the amount of likes you want songs deleted under" << endl;
				cin >> likes;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				try {
					
					flag = myLibrary->delete_all_under_like_threshold(likes);
					throw flag;
				} catch (bool flag) {
					if (flag) {
						cout << "\nAny songs under " << likes << " likes were deleted successfully" << endl;
					}
					else {
						cout << "\nNo songs in playlsist!" << endl;	
					}
				}
				break;

			case 4:
				myLibrary->display_all_songs();
				break;

			case 5:
				cout << "Enter the artist of the songs you want displayed" << endl;
				cin.getline(artist, 32);
				
				myLibrary->display_songs_by_artist(artist);
				break;
				
			case 6:
				user_input = false;

		}
		
	}

	delete myLibrary;

	return 0;
}

void read_file(const char * file_name, const int MAX_CHAR_LENGTH, SongList* aList) {

	fstream file;
	file.open(file_name, ios::in);
	
	if (!file) {
		cerr << "\nFailed to open " << file_name << endl;
		return;
	}
	
	char title[MAX_CHAR_LENGTH];
	char artist[MAX_CHAR_LENGTH];
	float length = 0.0;
	int likes = 0;

	while(file.peek() != EOF) {

		file.get(title, MAX_CHAR_LENGTH, ',');
		file.ignore(MAX_CHAR_LENGTH, ',');
		file.ignore(MAX_CHAR_LENGTH, ' ');

		file.get(artist, MAX_CHAR_LENGTH, ',');
		file.ignore(MAX_CHAR_LENGTH, ',');

		file >> length;
		file.ignore(numeric_limits<streamsize>::max(), ',');

		file >> likes;
		file.ignore(numeric_limits<streamsize>::max(), '\n');

		aList->add_song(title, artist, length, likes);

	}
    
	file.close();
	cout << "\nSongs loaded into playlist successfully" << endl;   
}
