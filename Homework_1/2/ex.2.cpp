#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning(disable : 4996)

const char NAME_LENGTH = 64;
const int GENRES_COUNT = 5;
const int CONTENT_LENGTH = 256;
const int PLAYLIST_CAPACITY = 30;
const int MAX_GENRES_COUNT = 10;
const int TIME_ELEMENTS = 3;
const int BITS = 8;

//enum Genre {
//	rock,
//	pop,
//	hiphop,
//	elMusic,
//	jazz
//};

class Song { 
private:
	char name[NAME_LENGTH];
	unsigned duration[TIME_ELEMENTS]; //hours, minutes, seconds
	char genres[MAX_GENRES_COUNT];
	char content[CONTENT_LENGTH];

public:
	Song() = default;

	Song(const char* name, unsigned duration[], const char* genres, const char* content)
	{
		strcpy(this->name, name);

		for (int i = 0; i < TIME_ELEMENTS; i++)
		{
			this->duration[i] = duration[i];
		}

		strcpy(this->genres, genres);
		strcpy(this->content, content);
	}

	const char* getName() const
	{
		return this->name;
	}

	const char* getGenres() const
	{
		return this->genres;
	}

	//void setName(const char* name)
	//{
	//	strcpy(this->name, name);
	//}

	void setContent(const char* content)
	{
		strcpy(this->content, content);
	}

	void setDuration(unsigned duration[])
	{
		for (int i = 0; i < TIME_ELEMENTS; i++)
		{
			this->duration[i] = duration[i];
		}
	}

	void setGenres(const char* genres)
	{
		strcpy(this->genres, genres);
	}

	void printContent()
	{
		int length = strlen(content);
		for (size_t i = 0; i < length; i++)
		{
			char current = content[i];
			for (size_t j = 0; j < BITS; j++)
			{
				std::cout << (current & 1);
				current = current >> 1;
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}

	void printSong()
	{
		std::cout << "Name: " << name << "\nTime: ";

		for (int i = 0; i < TIME_ELEMENTS; i++)
		{
			if (duration[i] < 10)
			{
				std::cout << "0";
			}

			std::cout << duration[i];

			if (i < TIME_ELEMENTS - 1)
			{
				std::cout << ":";
			}
		}

		std::cout << "\nGenres: " << genres << std::endl;
	}

	bool containsGenre(char genre)
	{
		char* tempGenres = this->genres;
		//strcpy(tempGenres, this->genres);

		while (*tempGenres)
		{
			if (*tempGenres == genre)
			{
				return true;
			}
			tempGenres++;
		}
		return false;
	}

	int compareSongsDuration(const Song& other)
	{
		if (this->duration[0] == other.duration[0])
		{
			if (this->duration[1] == other.duration[1])
			{
				if (this->duration[2] == other.duration[2])
				{
					return 0;
				}
				return this->duration[2] > other.duration[2] ? 1 : -1;
			}
			return this->duration[1] > other.duration[1] ? 1 : -1;
		}
		return this->duration[0] > other.duration[0] ? 1 : -1;
	}

	void createAdditionalRhytm(size_t k)
	{
		if (k == 0)
		{
			return;
		}

		int length = strlen(content);
		int currentStep = 1;

		for (int i = length - 1; i >= 0; i--)
		{
			char temp = 1;
			for (int j = 0; j < BITS; j++)
			{
				if (currentStep == k)
				{
					content[i] = content[i] | temp;
					currentStep = 0;
				}
				temp = temp << 1;
				currentStep++;
			}
		}
	}

	void mixSongs(const Song& other)
	{
		int length1 = strlen(content);
		int length2 = strlen(other.content);

		int minLength = length1 < length2 ? length1 : length2;
		
		for (size_t i = 0; i < minLength; i++)
		{
			content[i] = content[i] ^ other.content[i];
		}
	}

};

void swapSongs(Song& song1, Song& song2)
{
	Song temp = song1;
	song1 = song2;
	song2 = temp;
}

class Playlist {
private:
	Song songs[PLAYLIST_CAPACITY];
	int count;
public:
	Playlist() : count(0)
	{

	}

	Playlist(const Song* songs, int count)
	{
		this->count = count;

		for (int i = 0; i < count; i++)
		{
			this->songs[i] = songs[i];
		}
	}

	void addSong(const char* name, unsigned duration[TIME_ELEMENTS],
		const char* genres, const char* filePath)
	{
		if (findSongByName(name) >= 0)
		{
			std::cout << "Already in playlist!" << std::endl;
			return;
		}

		std::ifstream ifs(filePath, std::ios::binary);

		if (!ifs.is_open())
		{
			std::cout << "File not found" << std::endl;
			return;
		}

		char line[CONTENT_LENGTH];
		ifs.getline(line, CONTENT_LENGTH);
		
		ifs.close();

		Song song {name, duration, genres, line};
		addSong(song);
	}
	
	void addSong(const Song& song)
	{
		if (findSongByName(song.getName()) >= 0)
		{
			std::cout << "Already in playlist!" << std::endl;
			return;
		}
		songs[count++] = song;
	}

	void printPlaylist()
	{
		for (int i = 0; i < count; i++)
		{
			songs[i].printSong();
			std::cout << std::endl;
		}
	}

	int findSongByName(const char* name)  //returns index, if not found the value is -1
	{
		for (int i = 0; i < count; i++)
		{
			if (!strcmp(name, songs[i].getName()))
			{
				return i;
			}
		}
		return -1;
	}

	Song* findSongsByGenre(char genre, int &currentCount)
	{
		Song result[PLAYLIST_CAPACITY];

		currentCount = 0;

		for (int i = 0; i < count; i++)
		{
			if (songs[i].containsGenre(genre))
			{
				result[currentCount++] = songs[i];
			}
		}
		return result;
	}

	void sortByDuration()
	{
		for (int i = 0; i < count - 1; i++)
		{
			for (int j = 0; j < count - i - 1; j++)
			{
				if (songs[j].compareSongsDuration(songs[j + 1]) > 0)
				{
					swapSongs(songs[j], songs[j + 1]);
				}
			}
		}
	}

	void sortByName()
	{
		for (int i = 0; i < count - 1; i++)
		{
			for (int j = 0; j < count - i - 1; j++)
			{
				if (strcmp(songs[j].getName(), songs[j + 1].getName()) > 0)
				{
					swapSongs(songs[j], songs[j + 1]);
				}
			}
		}
	}

	void saveSong(const char* filePath, const char* name)
	{
		int index = findSongByName(name);

		if (index == -1)
		{
			return;
		}

		std::ofstream ofs(filePath, std::ios::binary);

		if (!ofs.is_open())
		{
			std::cout << "File not found!";
			return;
		}

		ofs.write((const char*)&songs[index], sizeof(Song));

		ofs.close();
	}

	void readSong(const char* filePath)
	{
		Song song;

		std::ifstream ifs(filePath, std::ios::binary);

		if (!ifs.is_open())
		{
			std::cout << "File not found!";
			return;
		}

		ifs.read((char*)&song, sizeof(Song));

		addSong(song);

		ifs.close();
	}
};

int main()
{
	unsigned duration1[3] = { 0, 1, 55 };
	unsigned duration2[3] = { 0, 1, 5 };
	unsigned duration3[3] = { 0, 0, 5 };
	Song song1{ "hello", duration1, "rp", "@@@@" };
	Song song2{ "bad guy", duration2, "p", "Ua" };
	Song song3{ "despacito", duration3, "j", "aaa" };

	Playlist playlist = Playlist{};

	playlist.addSong("hello", duration1, "rp", "song1.txt");
	playlist.addSong("bad guy", duration2, "p", "song1.txt");
	playlist.addSong(song3);
	playlist.printPlaylist();

	std::cout << playlist.findSongByName("ala") << std::endl;
	std::cout << song1.containsGenre('r') << std::endl;
	
	int count = 0;
	Song* songs = playlist.findSongsByGenre('r', count);
	for (size_t i = 0; i < count; i++)
	{
		songs[i].printSong();
	}

	playlist.sortByDuration();
	playlist.printPlaylist();

	playlist.sortByName();
	playlist.printPlaylist();

	song2.printContent();
	song2.createAdditionalRhytm(3);
	song2.printContent();

	song1.printContent();	
	song2.printContent();
	song1.mixSongs(song2);
	song1.printContent();

	playlist.printPlaylist();
	playlist.saveSong("songSave.dat", "hello");
	playlist.readSong("songSave.dat");
	playlist.printPlaylist();
	//song2.printContent();
	//song3.printContent();
}