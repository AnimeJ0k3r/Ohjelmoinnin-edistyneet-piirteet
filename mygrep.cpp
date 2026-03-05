#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void increment1();
void increment2(int type, string search_from, string search_for);

int main(int argc, char* argv[]) {

	switch (argc) {
		// inkrementti 1
		// /mygrep.exe
		case 1:
			increment1();
			break;

		// inkrementti 2
		// esim. /mygrep.exe following man_grep_plain_ASCII.txt
		case 3:
			increment2(1, argv[2], argv[1]);
			break;

		// inkrementti 3
		// esim. /mygrep.exe -olo following man_grep_plain_ASCII.txt
		// type 2 "-olo" == molemmat
		// type 3 "-ol" == rivinumerot
		// type 4 "-oo" == rivien määrä
		case 4:
			if (string(argv[1]) == "-olo") {
				increment2(2, argv[3], argv[2]);
			}
			else if (string(argv[1]) == "-ol") {
				increment2(3, argv[3], argv[2]);
			}
			else if (string(argv[1]) == "-oo") {
				increment2(4, argv[3], argv[2]);
			}
			break;
		// default = jos ei löydy tulosta.
		default:
			cout << "Too few or too many arguments." << endl;
			break;
	}

	return 0;
}

// Oikeasti pelkkä checker, en jaksa vaihtaa nimee...
bool checker2(string A, string B) {

	bool result = false;

	if (B.length() > A.length()) {
		return false;
	}

	for (int i = 0; i < A.length(); i++) {

		if (A[i] == B[0]) {
			for (int j = 0; j < B.length();) {
				if (i + j >= A.length() || A[i + j] != B[j]) {
					break;
				}
				else if (j == B.length() - 1) {
					return true;
				}
				j = j + 1;
			}
		}
	}

	return false;
}

void increment1() {
	string search_from, search_for;
	int position = -1;

	cout << "Give a string from which to search for: ";
	getline(cin, search_from);
	cout << endl;

	cout << "Give search string: ";
	getline(cin, search_for);
	cout << endl;

	if (search_for.length() > search_from.length()) {
		return;
	}

	for (int i = 0; i < search_from.length(); i++) {

		// etsii samat kirjaimet
		if (search_from[i] == search_for[0]) {
			// etsi samanlaisuudet
			for (int j = 0; j < search_for.length();) {
				if (i + j >= search_from.length() || search_from[i + j] != search_for[j]) {
					break;
				}
				else if (j == search_for.length() - 1) {
					position = i;
					cout << "'" << search_for << "' found in '" << search_from << "' in position " << position << endl;
				}
				j = j + 1;
			}
		}
	}
	if (position < 0) {
		cout << "'" << search_for << "' NOT found in '" << search_from << "'." << endl;
	}
}

// increment2 sisältää myös inkrementin 3
void increment2(int type, string search_from, string search_for) {

	string line;
	int line_num = 0;
	int num_of_lines = 0;

	// man_grep_plain_ASCII.txt
	ifstream ReadFile;
	ReadFile.open(search_from);

	if (ReadFile.fail()) {
		cout << "Error with either opening the file or file not found. :(" << endl;
	}

	else {
		while (getline(ReadFile, line)) {
			line_num = line_num + 1;
			bool result = checker2(line, search_for);

			if (result == true) {
				num_of_lines = num_of_lines + 1;

				if (type == 2 || type == 3) {
					cout << line_num << ":";
				}
				cout << line << endl;
			}
		}
		if (type == 2 || type == 4) {
			cout << "Occurrances of lines containing '" << search_for << "': " << num_of_lines << endl;
		}
	}

	ReadFile.close();
}

