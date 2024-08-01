#include"Song.h"
#include<iostream>
#include<unordered_map>

using std::unordered_map;
int main() {
	try {
		//1
		Song s1("Lana del Rey", "High By The Beach", "(High-igh-igh-igh) High - igh - igh - igh Boy, look at you looking at me here", "songs_file.txt");
		s1.display();
		std::cout << std::endl;

		//2
		std::cout << "\tFROM FILE:\n" << std::endl;

		SongCollection repo("songs_file.txt");
		repo.songs_display();
		std::cout << std::endl;
		std::cout << std::endl;

		//3
		set<string> unique_artists = repo.unique_artist();
		for (auto elem : unique_artists)
			std::cout << elem << std::endl;
		std::cout << std::endl;

		//4
		//bucket for artist->all their songs
		unordered_map<string, string> artists_songs;

		vector<Song> songs = repo.get_songs();

		for (auto artist: unique_artists) {
			string all_titles = "";
			for (auto song: songs) {
				if (song.getArtist()==artist) {
					all_titles += "    "+song.getTitle();
			}
		    }
			artists_songs.insert(std::make_pair(artist, all_titles));
	    }
		
		for (auto artist_song : artists_songs)
			std::cout << artist_song.first << "-" << artist_song.second << std::endl;
		std::cout<<std::endl;

		//5
		//increasing-> artist name
		// GET THE NEXT 3 LINES OUT OF COMMENT IF YOU WANT TO SEE THIS SPECIFIC SORT
		//std::cout << "Songs sorted by artist name, increasing:" << std::endl;
		//repo.sort_artist_increasing();
		//repo.songs_display();

		//desc-> title
		// GET THE NEXT 3 LINES OUT OF COMMENT IF YOU WANT TO SEE THIS SPECIFIC SORT
		//std::cout << "Songs sorted by title, decreasing:" << std::endl;
		//repo.sort_title_descending();
		//repo.songs_display();

		//incr-> nr of words in lyrics
	     std::cout << "Songs sorted by number of words in lyrics, increasing:" << std::endl;
		 repo.sort_number_words_increasing();
		repo.songs_display();
	}
	catch (std::runtime_error& e1) {
		std::cout << e1.what() << std::endl;
	}
	return 0;
}