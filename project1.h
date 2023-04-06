// Tyler Isaacson
// CS260
// project1
// project1.h: the single header file for the entire program.
// Acts as an API for the driver program, it declares the various member functions and data and how to interact with the backend

#pragma once

class Song {
public:
	Song();
	Song(char* title, char* artist, float length, int likes_num);
	
	char* get_artist_name();
	char* get_title();
	float get_length();
	int get_number_of_likes();
	Song* get_next_node();

	void set_next_node(Song* node);
	void set_number_of_likes(int likes);
	
private:
	char* artist_name;
	char* title;
	float length;
	int number_of_likes;
	Song* next_node;
};

class SongList {
public:
	SongList();
	~SongList();

	bool add_song(char* temp_title, char* temp_artist, float length=0, int likes=0);
	bool edit_likes(char* title, int likes);	
	bool delete_all_under_like_threshold(int likes);

	void display_all_songs();
	void display_songs_by_artist(const char* artist);

private:
	void delete_all_songs(Song* aSong);
	
	Song* head;
	Song* current;
	int song_list_length;

};
