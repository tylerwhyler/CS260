// Tyler Isaacson
// CS260
// project1
// project1_impl.cpp: the thie file implements all the functions as described in the header file
// Contains all the backend logic for how each feature actually works 


#include "project1.h"
#include <iostream>
#include <iomanip>
#include <cstring>

Song::Song(char* title, char* artist, float length, int likes_num ) {
	this->title = title;
	this->artist_name = artist;
	this->length = length;
	this->number_of_likes = likes_num;
	this->next_node = nullptr;
}

char* Song::get_artist_name() {
	return artist_name;
}

char* Song::get_title() {
	return title;
}

float Song::get_length() {
	return length;
}

int Song::get_number_of_likes() {
	return number_of_likes;
}

Song* Song::get_next_node() {
	return next_node;
}

void Song::set_next_node(Song* node) {
	next_node = node;
}

void Song::set_number_of_likes(int likes) {
	number_of_likes = likes;
}

SongList::SongList() {
	this->head = nullptr;
	this->current = nullptr;
	this->song_list_length = 0;
}

SongList::~SongList() {
	//Begins recursive delete by passing the SongList's head node (only if there is at least 1 song in the list)
	if (this->song_list_length != 0) {
		delete_all_songs(this->head);
	}
}

void SongList::delete_all_songs(Song* aSong) {
	//Recursively deletes every song, and deletes each song's title and artist char array beforehand

	if (aSong->get_next_node() != nullptr) {
		delete_all_songs(aSong->get_next_node());
	}
	delete [] aSong->get_artist_name();
	delete [] aSong->get_title();
	delete aSong;
}

bool SongList::delete_all_under_like_threshold(int likes) {
	//Traverses the linked list checking if each node's likes value is below the like number
	//
	//Checks the head node after the rest of the list if checked, otherwise you would have to check
	//the head uniquely from the subsequent nodes every single iteration
	
	if (this->song_list_length == 0) return false;	

	this->current = this->head;

	while (this->current->get_next_node() != nullptr) {

		if (this->current->get_next_node()->get_number_of_likes() < likes) {
			Song* next_node_copy = this->current->get_next_node();
			
			if (this->current->get_next_node()->get_next_node() != nullptr) {
				this->current->set_next_node(this->current->get_next_node()->get_next_node());
			}
			else {
				this->current->set_next_node(nullptr);
			}

			delete [] next_node_copy->get_artist_name();
			delete [] next_node_copy->get_title();
			delete next_node_copy;
			this->song_list_length--;
		}
		else {
			this->current = this->current->get_next_node();
		}
	}

	if (this->head->get_number_of_likes() < likes) {
		Song* head_copy = this->head;

		if (this->song_list_length == 1) {
			this->head = nullptr;
			this->current = nullptr;
			this->song_list_length--;
		}
		else {
			this->head = this->head->get_next_node();
			this->song_list_length--;
		}
		delete [] head_copy->get_artist_name();
		delete [] head_copy->get_title();
		delete head_copy;
	}
	
	return true;
}

bool SongList::edit_likes(char* title, int likes) {
	
	//Find the song with the matching song title, save data to temp variables, and remove it from the linked list
	
	//Use temp variables to add new song with the add_song member function so that it adds it correct order of popularity with new likes value.

	if (this->song_list_length == 0) return false;	

	char* temp_title;
	char* temp_artist;
	float temp_length;

	this->current = this->head;

	while (this->current->get_next_node() != nullptr) {
		if (strcmp(this->current->get_next_node()->get_title(), title) == 0) {
			Song* next_node_copy = this->current->get_next_node();
	
			if (this->current->get_next_node()->get_next_node() != nullptr) {
				this->current->set_next_node(this->current->get_next_node()->get_next_node());
			}
			else {
				this->current->set_next_node(nullptr);
			}

			temp_title = next_node_copy->get_title();
			temp_artist = next_node_copy->get_artist_name();
			temp_length = next_node_copy->get_length();

			this->add_song(temp_title, temp_artist, temp_length, likes);
			delete [] next_node_copy->get_artist_name();
			delete [] next_node_copy->get_title();
			delete next_node_copy;
			this->song_list_length--;

			return true;
		}

		else {
			this->current = this->current->get_next_node();
		}
	}


	if (strcmp(this->head->get_title(), title) == 0) {
		if (this->song_list_length == 1) {
			this->head->set_number_of_likes(likes);
		}
		else {
			Song* head_copy = this->head;
			this->head = this->head->get_next_node();

			temp_title = head_copy->get_title();
			temp_artist = head_copy->get_artist_name();
			temp_length = head_copy->get_length();

			this->add_song(temp_title, temp_artist, temp_length, likes);
			delete [] head_copy->get_artist_name();
			delete [] head_copy->get_title();
			delete head_copy;
			this->song_list_length--;

			return true;
		}
	}
	return false;
	
}

bool SongList::add_song(char* temp_title, char* temp_artist, float length, int likes) {
	//Must make a copy of the title and artist variables otherwise they all point to the same memory location
	
	char* title = new char[32];
	char* artist = new char[32];
	strcpy(title, temp_title);
	strcpy(artist, temp_artist);

	this->current = this->head;
	
	//If the list is empty, the new song is created as the head of the songlist and the function returns out
	if (this->song_list_length == 0) {
		this->head = new Song(title, artist, length, likes);
		this->song_list_length++;
		return true;
	}
	
	//If the list wasn't empty, but the new song has more likes than the head node, the new song is made the head node
	if (likes > this->head->get_number_of_likes()) {
		Song* head_copy = this->head;
		this->head = new Song(title, artist, length, likes);
		this->head->set_next_node(head_copy);
		this->song_list_length++;
		return true;
	}

	//Traverse the linked list and insert the new song before the next node if the next node's likes is less than the new song's
	for (this->current = this->head; this->current->get_next_node() != nullptr; this->current = this->current->get_next_node()) {
		if (likes > current->get_next_node()->get_number_of_likes()) {
			Song* next_node_copy = current->get_next_node();
			current->set_next_node(new Song(title, artist, length, likes));
			current->get_next_node()->set_next_node(next_node_copy);
			this->song_list_length++;
			return true;
		}		
	}
	
	//If none of the songs have fewer likes, the new song is put at the end of the linked list
	//The songlist's current node is left on the final node thanks to the forloop above
	if (this->current->get_next_node() == nullptr) {
		current->set_next_node(new Song(title, artist, length, likes));
		this->song_list_length++;
		return true;
	}
	
	//Return a failure if the song isn't added
	return false;
}

void SongList::display_all_songs() {
	//Print each node, starting at the head node. Only if the list isn't empty

	std::cout << "\nEntire playlist" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << std::fixed << std::setprecision(2);

	if (this->song_list_length != 0) {
		int count = 1;
		for (this->current = this->head; this->current->get_next_node() != nullptr; this->current = this->current->get_next_node()) {
			std::cout << "Track #" << count << std::endl;
			std::cout << "Title: " << current->get_title() << std::endl;
			std::cout << "Artist: " << current->get_artist_name() << std::endl;
			std::cout << "Duration: " << current->get_length() << std::endl;
			std::cout << "Likes: " << current->get_number_of_likes() << "\n" << std::endl;
			count++;
		
			//Check if the next node is the last node in the list. If it is, print it before the forloop ends	
			if (this->current->get_next_node()->get_next_node() == nullptr) {
				std::cout << "Track #" << count << std::endl;
				std::cout << "Title: " << current->get_next_node()->get_title() << std::endl;
				std::cout << "Artist: " << current->get_next_node()->get_artist_name() << std::endl;
				std::cout << "Duration: " << current->get_next_node()->get_length() << std::endl;
				std::cout << "Likes: " << current->get_next_node()->get_number_of_likes() << "\n" << std::endl;
	
			}
		}
		
		//A songlist with only one node, a head node, is printed here
		if (this->song_list_length == 1) {
			this->current = this->head;
			std::cout << "Track #" << count << std::endl;
			std::cout << "Title: " << current->get_title() << std::endl;
			std::cout << "Artist: " << current->get_artist_name() << std::endl;
			std::cout << "Duration: " << current->get_length() << std::endl;
			std::cout << "Likes: " << current->get_number_of_likes() << "\n" << std::endl;
		}
	}

}

void SongList::display_songs_by_artist(const char* artist) {

	std::cout << "\nSongs by " << artist << " in order of popularity" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << std::fixed << std::setprecision(2);
		
	if (this->song_list_length != 0) {
		int count = 1;

		
		//Traverse the linked list if there is more than 1 node, and print each node	
		for (this->current = this->head; this->current->get_next_node() != nullptr; this->current = this->current->get_next_node()) {
			if (strcmp(this->current->get_artist_name(), artist) == 0) {
				std::cout << "Track #" << count << std::endl;
				std::cout << "Title: " << current->get_title() << std::endl;
				std::cout << "Artist: " << current->get_artist_name() << std::endl;
				std::cout << "Duration: " << current->get_length() << std::endl;
				std::cout << "Likes: " << current->get_number_of_likes() << "\n" << std::endl;	
			}
			count++;

			//Check if the next node is the final node, and print it out before the forloop exits (if the artist name matches)
			if (strcmp(this->current->get_next_node()->get_artist_name(), artist) == 0 && this->current->get_next_node()->get_next_node() == nullptr) {
				std::cout << "Track #" << count << std::endl;
				std::cout << "Title: " << current->get_next_node()->get_title() << std::endl;
				std::cout << "Artist: " << current->get_next_node()->get_artist_name() << std::endl;
				std::cout << "Duration: " << current->get_next_node()->get_length() << std::endl;
				std::cout << "Likes: " << current->get_next_node()->get_number_of_likes() << "\n" << std::endl;
			}
		}
		
		//If there is ONLY a head node in the songlist
		if (this->song_list_length == 1) {
			this->current = this->head;
			if (strcmp(this->current->get_artist_name(), artist) == 0) {
				std::cout << "Track #" << count << std::endl;
				std::cout << "Title: " << current->get_title() << std::endl;
				std::cout << "Artist: " << current->get_artist_name() << std::endl;
				std::cout << "Duration: " << current->get_length() << std::endl;
				std::cout << "Likes: " << current->get_number_of_likes() << "\n" << std::endl;
			}
		}
	}
}

