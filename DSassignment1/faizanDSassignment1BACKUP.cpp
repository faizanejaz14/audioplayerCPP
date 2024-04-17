#include <iostream>
#include <dirent.h>
#include <string>
#include <windows.h>
#include <mmsystem.h>
#include <algorithm>
#include <random>

using namespace std;


//template <class T>
class node {
	string AUDIOname;
	node* next;


public:
	node() {
		AUDIOname = "NULL";
		next = NULL;
	}
	void setAudio(string d) {
		AUDIOname = d;
	}
	void setNext(node* p) {
		next = p;
	}
	string getAudio() {
		//cout << data;
		return AUDIOname;
	}
	node* getNext() {
		return next;
	}
};


class PlayList {
	string PLname;
	node* head;

public:
	PlayList() {
		PLname = "NULL";
		head = NULL;
	}
	void setPLName(string a) {
		PLname = a;
	}
	string getPLName() {
		return PLname;
	}

	void IAS(string a) {
		node* b = new node;
		b->setAudio(a);
		b->setNext(head);
		head = b;
	}
	void InsertAudio(string a) {
		if (head == NULL)
			IAS(a);
		else {
			node* b = new node;
			node* temp = head;
			while (temp->getNext() != NULL) {
				//cout << temp->getData();
				temp = temp->getNext();
			}
			b->setAudio(a);
			temp->setNext(b);

		}
	}
	void DAS() {
		node* prev = NULL;
		node* temp = head;
		if (temp == NULL)
			cout << "\nPlayList is empty" << endl;
		else if (temp != NULL) {
			prev = temp;
			head = temp->getNext();
			delete prev;
			prev = NULL;
		}
	}
	void DeleteAudio(int pos) {
		if (pos == 1) {
			DAS();
		}
		else {
			int size = 0;
			int count = 1;
			node* prev = NULL;
			node* temp = head;
			if (temp == NULL)
				cout << "\nPlayList is empty" << endl;
			else if (temp != NULL) {
				while (temp != NULL) {
					temp = temp->getNext();
					size++;
				}
				if (pos > 0 && pos <= size) {
					temp = head;
					node* temp1 = head;
					while (count != pos && temp != NULL) {
						prev = temp;
						temp = temp->getNext();
						temp1 = temp->getNext();
						count++;
					}
					temp->setNext(temp1->getNext());
					temp->setAudio(temp1->getAudio());
					delete temp1;
				}
			}
		}
	}
	string* playingPlayList(int a) {
		string* songname = new string[a];
		if (head != NULL) {
			node* temp = head;
			int i = 0;
			while (temp != NULL) {
				songname[i] = temp->getAudio();
				i++;
				temp = temp->getNext();
			}
		}
		return songname;

	}
	string* copyinArray(int s) {
		string* arrData = new string[s];
		node* temp = head;
		int i = 0;
		do {
			temp = temp->getNext();
			arrData[i] = temp->getAudio();

		} while (temp->getNext() != NULL);
		return arrData;
	}
	int transverse() {
		int count = 0;
		node* temp = head;
		while (temp != NULL) {
			temp = temp->getNext();
			count++;
		};
		return count;
	}
	void printSongs() {
		node* temp = head;
		int count = 1;
		while (temp != NULL) {
			cout << count << " > " << temp->getAudio() << endl;
			temp = temp->getNext();
			count++;
		};
	}
	string* getAllSongs() {
		int size = this->transverse();
		string* songs = new string[size];
		node* temp = head;
		int count = 1;
		while (temp != NULL) {
			songs[count - 1] = temp->getAudio();
			temp = temp->getNext();
			count++;
		};
		return songs;
	}
	~PlayList()
	{
		node* current = head;
		node* next;
		while (current != NULL) {
			next = current->getNext();
			delete current;
			current = next;
		}
		head = NULL;
	}
};


class AudioPlayer {
	DIR* dir = 0;
	struct dirent* ent = 0;
	string directory;
	int size = 5;
	PlayList* P1 = new PlayList[size];
public:
	AudioPlayer() {
		for (int i = 0; i < size; i++) {
			P1[i].setPLName("NULL");
		}

	}

	void selectDirectory() {
		int count = 0;
		cout << "Enter directory path: ";
		cin >> directory;
		cout << "\nContents of selected directory :" << endl;
		// Open directory and print its contents
		if ((dir = opendir(directory.c_str())) != NULL) {
			while ((ent = readdir(dir)) != NULL) {
				count++;
				if (count > 2)
					cout << "  > " << ent->d_name << endl;
			}
			closedir(dir);
		}
		else {
			perror("Could not open directory");
			//return EXIT_FAILURE;
		}

		//return EXIT_SUCCESS;
	}

	void changeDirectory() {
		for (int i = 0; i < 5; i++) {
			if (P1[i].getPLName() != "NULL") {
				P1[i].setPLName("NULL");
				P1[i].~PlayList(); //destructor called
			}
		}
		cout << "\nEnter directory path: " << endl;
		cin >> directory;
		cout << " Directory Change = Successful !" << endl;
		cout << "\nContents of selected directory :" << endl;
		// Open directory and print its contents
		if ((dir = opendir(directory.c_str())) != NULL) {
			while ((ent = readdir(dir)) != NULL) {
				cout << "  > " << ent->d_name << endl;
			}
			closedir(dir);
		}
		else {
			perror("Could not open directory");
			//return EXIT_FAILURE;
		}

		//return EXIT_SUCCESS;
	}
	void createPlayList() {
		cout << "\nEnter name for your new PlayList :";
		string n;
		cin >> n;
		for (int i = 0; i < 5; i++) {
			if (P1[i].getPLName() == "NULL") {
				P1[i].setPLName(n);
				i = i + 10;
			}
		}
		cout << "\n PlayList Creation = Successful !" << endl;
	}
	void insertAudioFile() {
		int count1 = 0;
		int serial1 = 0;
		int serial2 = 0;
		int count = 0;

		if ((dir = opendir(directory.c_str())) != NULL) {
			while ((ent = readdir(dir)) != NULL) {
				if (ent->d_type == DT_REG || ent->d_type == DT_DIR) {
					count1++;
				}
			}
			string* songs = new string[count1];
			closedir(dir); // Close directory

			cout << "\nSelect PlayList by pressing serial of each PlayList:" << endl;
			for (int i = 0; i < 5; i++) {
				cout << i + 1 << " > " << P1[i].getPLName() << endl;
			}
			cout << "\n";
			cin >> serial1;


			if ((dir = opendir(directory.c_str())) != NULL) {
				cout << "\nSelect song (from the current selected directory) which you want to add in your PlayList by pressing serial number of song :" << endl;
				while ((ent = readdir(dir)) != NULL) {
					count++;
					if (count > 2)
					{

						songs[count - 2] = ent->d_name;
						cout << count - 2 << " > " << ent->d_name << endl;
					}

				}
				closedir(dir);
				cout << "\n";
				cin >> serial2;
				P1[serial1 - 1].InsertAudio(songs[serial2]);
				cout << "\n AudioFile Insertion = Successful !" << endl;

			}
		}
	}
	void deleteAudioFile() {
		int serial1 = 0;
		int serial2 = 0;
		int count = 0;
		cout << "\nSelect PlayList in which you want to delete an AudioFile by pressing serial number of the PlayList :" << endl;
		for (int i = 0; i < 5; i++) {
			cout << i + 1 << " > " << P1[i].getPLName() << endl;
		}
		cout << "\n";
		cin >> serial1;
		cout << "\nSelect song which you want to Delete by pressing its serial number :" << endl;
		P1[serial1 - 1].printSongs();
		cout << "\n";
		cin >> serial2;
		P1[serial1 - 1].DeleteAudio(serial2);
		cout << "\n AudioFile Deletion = Successful !" << endl;

	}
	void shuffle() {
		int serial = 0;
		cout << "\n Select PlayList which you want to shuffle by pressing serial number of the PlayList" << endl;
		for (int i = 0; i < 5; i++) {
			cout << i + 1 << " > " << P1[i].getPLName() << endl;
		}
		cout << "\n";
		cin >> serial;
		int length = P1[serial - 1].transverse();
		string* songs = new string[length];
		songs = P1[serial - 1].getAllSongs();
		cout << "\n Before Shuffling :" << endl;
		P1[serial - 1].printSongs();

		cout << "\n After Shuffling :" << endl;
		random_shuffle(&songs[0], &songs[length]);
		random_shuffle(&songs[0], &songs[length]);
		string name = P1[serial - 1].getPLName();
		P1[serial - 1].~PlayList();
		P1[serial - 1].setPLName(name);
		for (int j = 0; j < length; j++) {
			P1[serial - 1].InsertAudio(songs[j]);
		}
		P1[serial - 1].printSongs();
	}
	void playListPLAY() {

		int serial = 0;

		cout << "\nSelect PlayList by entering the serial number of PlayList which you want to play :" << endl;
		for (int i = 0; i < 5; i++) {
			cout << i + 1 << " > " << P1[i].getPLName() << endl;
		}
		cin >> serial;
		int size = P1[serial - 1].transverse();
		string* songs = new string[size];
		songs = P1[serial - 1].playingPlayList(size);
		for (int j = 0; j < size; j++) {
			cout << "\n Playing : " << songs[j];
			playSoundFile(songs[j]);
			cout << "\n Next Song :-";
		}

		cout << "\n < PlayList Ended >" << endl;
	}
	void playSoundFile(string name) {
		name = directory + "\\" + name;
		wstring songName(name.begin(), name.end());
		PlaySound(songName.c_str(), NULL, SND_SYNC);
	}
	void printPlaylists() {
		cout << "\nNames of PlayLists : " << endl;
		for (int i = 0; i < 5; i++) {
			cout << i + 1 << " >" << P1[i].getPLName() << endl;
		}
	}
	void displaySongs() {
		int serial = 0;
		cout << "\nSelect PlayList by entering the serial number of PlayList to display names of its songs :" << endl;
		for (int i = 0; i < 5; i++) {
			cout << i + 1 << " > " << P1[i].getPLName() << endl;
		}
		cout << "\n";
		cin >> serial;
		cout << "\nList of songs in this PlayList :" << endl;
		P1[serial - 1].printSongs();
	}
};


int main() {
	cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<   FAIZAN's AUDIO PLAYER    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n" << endl;

	AudioPlayer A1;
	A1.selectDirectory();
	int infinite = 0, choice = 2;
	while (true) {
		cout << "\n---> Press 1 for Changing/Selecting Directory.\n---> Press 2 for Creating New PlayList.\n---> Press 3 for Inserting an Audio File.\n";
		cout << "---> Press 4 for Deleting an Audio File.\n---> Press 5 for Shuffling the PlayList.\n---> Press 6 for Playing the PlayList." << endl;
		cout << "---> Press 7 to display names of created PlayLists.\n---> Press 8 to display names of Songs added in the specific PlayList." << endl;
		cin >> choice;

		if (choice == 1) {
			A1.changeDirectory();
		}
		else if (choice == 2) {
			A1.createPlayList();
		}
		else if (choice == 3) {
			A1.insertAudioFile();
		}
		else if (choice == 4) {
			A1.deleteAudioFile();
		}
		else if (choice == 5) {
			A1.shuffle();
		}
		else if (choice == 6) {
			A1.playListPLAY();
		}
		else if (choice == 7) {
			A1.printPlaylists();
		}
		else if (choice == 8) {
			A1.displaySongs();
		}
		else
			cout << "Wrong Input ! Enter a number in between 1 to 8" << endl;
		cin.ignore();
	}
}