/****************************************************************
*
* File: Assignment01 — Dictionary
* By: Sam Zaffanella
* Date: 7/1/2018
*
* Description: A dictionary program that reads a special text file
			   filled with multiple words with definitions
*
*
****************************************************************/
#include <string>
#include <fstream>
#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool inputSplitter(string input, string& word, string& type) {
	/*takes the getline input(later) and splits it into multiple
	 substrings. The 1st for the word and the 2nd for the part
	 of speech. If zero or more than two words are inputted then 
	 it returns false*/
	int splitPoint;
	if (input.empty()) {
		return false;
	}
	for (int i = 0; i < input.length(); i++) {
		if (input.at(i) == ' ' && word == "NULL") {
			word = input.substr(0, i);
			splitPoint = i + 1;
		}
		else if (input.at(i) == ' ' && word != "NULL") {
			return false;
		}
		else if (i == input.length() - 1 && word == "NULL") {
			word = input;
		}
		else if (i == input.length() - 1 && type == "NULL") {
			type = input.substr(splitPoint, i);
		}
	}
	return true;
}

string wordFinder(string x, string word, string nextWord) {
	/*This method takes the word inputted be the user and creates
	 a substring starting from the inputted word to the next word
	 in the dictionary. This is meant to make finding the specific
	 definitions easier. The substring is returned and is used in
	 typeFinder (later)*/ 
	unsigned int splitPoint = 1;
	string def;
	string substr;
	for (unsigned int i = 0; i < x.length(); i++) {
		if (x.substr(i, word.length()) == word && i < x.size() - 1) { // THIS IF STATEMENT IS WHAT YOU NEED TO CHANGE
			if (splitPoint == 1) {
				splitPoint = i;
			}
			if (nextWord == "NULL") {
				def = x.substr(splitPoint, x.length() - splitPoint);
				return def;
			}
		}
		//cout << x.substr(i, nextWord.length()) << endl;
		if (x.substr(i, nextWord.length()) == nextWord) {
			def = x.substr(splitPoint, i - splitPoint);
			return def;
		}
	}
	return "Null";
}

void displayDefinitions(string x, vector <string> typeList, string word) {
	/*This method is used instead of typeFinder(later) if the user does
	 not input a part of speech wants all definitions*/
	unsigned int splitPoint = 0;
	for (unsigned int i = 0; i < typeList.size(); i++) {
		for (unsigned int j = 0; j < x.length(); j++) {
			if (x.substr(j, (typeList.at(i)).length()) == typeList.at(i) && j < x.size() - 1) {
				/*this if statement checks if x at j position is the first letter of a word type.
				the second argument is used to prevent an std::out of range error*/
				splitPoint = j;
			}
			if (x.at(j) == '.' && x.substr(splitPoint, typeList.at(i).length()) == typeList.at(i)) {
				cout << "         " + word << " [" + typeList.at(i) + "] : " << x.substr(splitPoint + typeList.at(i).length() + 4, (j - splitPoint - typeList.at(i).length() - 3)) << endl;
				//prints out the entire definition for specified word type
				splitPoint = j + 1;
			}

		}
	}
}

void typeFinder(string x, string type, string word) {
	/*If a user inputs a valid word and part of speech, this method
	 will be used to correctly print out every definition for the
	 specified word and part of speech*/
	unsigned int splitPoint = 0;
	for (unsigned int j = 0; j < x.length(); j++) {
		if (x.substr(j, type.length()) == type  && j < x.size() - 1) {
			/*this if statement checks if x at j position is the first letter of a word type.
			  the second argument is used to prevent an std::out of range error*/
			splitPoint = j;
		}
		if (x.at(j) == '.' && x.substr(splitPoint, type.length()) == type) {
			cout << "         " + word << " [" + type + "] : " << x.substr(splitPoint + type.length() + 4, (j - splitPoint - type.length() - 3)) << endl;
			//prints out the entire definition for specified word type
			splitPoint = j + 1;
		}
	}
	if (splitPoint == 0) {
		cout << "         <Not found.>" << endl;
	}
}

int main() {
	/*The main method is used to obtain the user's input as well as
	 allow users to search multiple times in succession. I tried keep
	 the amount of content in the main to a limit but as you can see
	 that proved to be somewhat difficult, so a large chunk of my program
	 is contained within the main.*/
	ifstream file;
	string getcontent, input, data, word, type, nextWord;
	vector <string> dictionary = { "book", "bookable", "bookbinder", "bookcase", "csc210", "csc220", "csc340"};
	vector <string> typeList = { "noun", "verb", "adjective" };
	file.open("C:\\Users\\Sam\\Desktop\\Data.CS.SFSU.txt");
	cout << "! Opening data file... ./Data.CS.SFSU.txt" << endl;
	if (file.fail()) {
		cout << "Failed to open file: " << "Data.CS.SFSU.txt" << endl;
		exit(0);
	}
	else {
		cout << "! Loading data..." << endl;
		cout << "! Loading completed..." << endl;
		while (getline(file, getcontent)) {
			data.append(getcontent);
		}
		cout << "! Closing data file... ./Data.CS.SFSU.txt" << endl << endl;
		file.close();
	}

	cout << "-----DICTIONARY 340 C++-----" << endl << endl;
	while (input != "!Q") {
		word = "NULL";
		type = "NULL";
		cout << "Search: ";
		getline(cin, input);
		if (input == "!Q") {
			cout << endl << "-----THANK YOU-----" << endl;
			exit(0);
		}
		bool split = inputSplitter(input, word, type);
		if (split == true) {
			transform(word.begin(), word.end(), word.begin(), tolower);
			if (word == dictionary.back()) {
				nextWord = "NULL";
			}
			else {
				for (int i = 0; i < dictionary.size() - 1; i++) {
					if (dictionary.at(i) == word) {
						nextWord = dictionary.at(i + 1);
					}
				}
			}
			string results = wordFinder(data, word, nextWord);
			if (type == "NULL") {
				if (find(dictionary.begin(), dictionary.end(), word) != dictionary.end()) {
					cout << "        |" << endl;
					displayDefinitions(results, typeList, word);
					cout << "        |" << endl;
				}
				else {
					cout << "        |" << endl;
					cout << "         <Not found.>" << endl;
					cout << "        |" << endl;
				}
			}
			else if (find(typeList.begin(), typeList.end(), type) != typeList.end()) {
				if (find(dictionary.begin(), dictionary.end(), word) != dictionary.end()) {
					transform(type.begin(), type.end(), type.begin(), tolower);
					cout << "        |" << endl;
					typeFinder(results, type, word);
					cout << "        |" << endl;
				}
				else {
					cout << "        |" << endl;
					cout << "         <Not found.>" << endl;
					cout << "        |" << endl;
				}
			}
			else {
				cout << "        |" << endl;
				cout << "         <2nd argument must be part of speech.>" << endl;
				cout << "        |" << endl;
			}
		}
		else {
			cout << "        |" << endl;
			cout << "         <Please enter a search key (and a part of speech).>" << endl;
			cout << "        |" << endl;
		}
	}
	return 0;
}