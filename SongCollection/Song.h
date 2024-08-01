#include<string>
#include<vector>
#include<set>
using std::set;
using std::vector;
using std::istream;
using std::string;
using std::ostream;

#pragma once
class Song
{
	vector<string> lyrics;
protected:
	string artist;
	string title;
	string path;
public:
	Song() = default;
	Song(const string& partist,const string& ptitle,const string& plyrics, const string& path);
	string getArtist() const;
	string getTitle() const;
	vector<string> getLyrics() const;
	void display();
	friend istream& operator>>(istream& is, Song& s);
	friend ostream& operator<<(ostream& os, const Song& s);
};

class SongCollection {
	vector<Song> songs;
	string path;
public:
	SongCollection() = default;
	SongCollection(const string& ppath);
	void songs_display();
	vector<Song> get_songs() const {
		return songs;
	};
	set<string> unique_artist();
	void sort_artist_increasing();
	void sort_title_descending();
	void sort_number_words_increasing();
};
