#include "Song.h"
#include <sstream>
#include<iostream>
#include<fstream>
#include<stdexcept>
#include<algorithm>
using std::stringstream;
using std::getline;

string toLowercase(const string& str)
{
    string result;
    for (char c : str)
    {
        // Check if the character is uppercase
        if (c >= 'A' && c <= 'Z')
        {
            // Convert to lowercase by adding 32 to the ASCII value
            result += c + 32;
        }
        else
        {
            // If the character is not uppercase, just append it as is
            result += c;
        }
    }
    return result;
}

vector<string> tokenize(string str, const string& delimiters)
{
    vector<string> result;
    size_t start = 0, end = 0;
    //iterates through the input string str until no delimiter is found (find_first_of returns npos)
    while ((end = str.find_first_of(delimiters, start)) != string::npos)
    {
        //If the substring between start and end is not empty
        if (end != start)
        {
            result.push_back(toLowercase(str.substr(start, end - start)));
        }
        start = end + 1;
    }
    if (start < str.length())
        result.push_back(str.substr(start));
    return result;
}

Song::Song(const string& partist, const string& ptitle, const string& plyrics, const string& ppath)
{
    this->path = ppath;
    artist = partist;
    title = ptitle;
	this->lyrics = tokenize(plyrics, ",.!?;1234567890- ()'");
}

string Song::getArtist() const
{
    return artist;
}

string Song::getTitle() const
{
    return title;
}

vector<string> Song::getLyrics() const
{
    return lyrics;
}

void Song::display()
{
    std::cout << artist << std::endl;
    std::cout << title << std::endl;
    for (size_t i = 0; i < lyrics.size(); i++)
        std::cout << lyrics[i] << " ";
}

SongCollection::SongCollection(const string& ppath)
{
    this->path = ppath;
    songs.clear();
    std::ifstream inputfile{ path };
    if (!inputfile.is_open())
        throw std::runtime_error("Cannot open file!");
    Song s;
    while (inputfile >> s)
        songs.push_back(s);
    
}

istream& operator>>(istream& is, Song& s)
{
    /*
    std::ifstream inputfile{ s.path };
    std::cout << s.path;
    if (!inputfile.is_open())
        throw std::runtime_error("Cannot open file!");
*/
    string line;
    s.lyrics.clear();
    // Parse until the end of the file or until the next song entry

    // Parse until the end of the file
    while (getline(is, line)) {
        size_t pos;
        if ((pos = line.find("__Artist:")) != string::npos) {
            s.artist = line.substr(pos + 10); // Skip "__Artist: "
        }
        else if ((pos = line.find("__Song:")) != string::npos) {
            s.title = line.substr(pos + 8); // Skip "__Sing: "
        }
        else if ((pos = line.find("__Lyrics:")) != string::npos) {
            // Start reading the lyrics
            while (getline(is, line)) {
                if (line.empty() || line.find("__Artist:") != string::npos || line.find("__Song:") != string::npos) // Empty line or start of next song indicates end of lyrics
                    break;
                s.lyrics.push_back(line);
            }
            // Done with reading this song
            return is;
        }
    }
    
    // If we reach here, the end of the file is reached
    // This is to handle the case where the last song doesn't end with an empty line
    return is;
}

ostream& operator<<(ostream& os, const Song& s)
{
    // TODO: insert return statement here
    os << s.artist << std::endl << s.title << std::endl;
    for (size_t i = 0; i < s.lyrics.size(); i++)
        os << s.lyrics[i] << std::endl;

    return os;
}

    void SongCollection::songs_display()
    {
        for (size_t i = 0; i < songs.size(); i++)
            std::cout << songs[i] << std::endl;
    }

    set<string> SongCollection::unique_artist()
    {
        set<string> unique_artists;
        for (size_t i = 0; i < songs.size(); i++)
            unique_artists.insert(songs[i].getArtist());
        return unique_artists;
    }

    void SongCollection::sort_artist_increasing()
    {
        std::sort(songs.begin(), songs.end(),
            [](const Song& s1, const Song& s2) {
                return s1.getArtist() < s2.getArtist();
            });
    }

    void SongCollection::sort_title_descending()
    {
        std::sort(songs.begin(), songs.end(),
            [](const Song& s1, const Song& s2) {
                return s1.getTitle() > s2.getTitle();
            });
    }

    void SongCollection::sort_number_words_increasing()
    {
        std::sort(songs.begin(), songs.end(),
            [](const Song& s1, const Song& s2) {
                return s1.getLyrics().size() < s2.getLyrics().size();
            });
    }
