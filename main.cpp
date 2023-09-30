#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std; 

void printLine(string info);
int OptionInputChecker(int from, int to);

class MainMenu {
	int input = 0; 
	public:

		void showMenu() {
			cout << "- Main menu -\n";
			cout << "1. Insertion\n";
			cout << "2. Search\n";
			cout << "3. Sorting Option\n";
			cout << "4. Exit\n";
		}

		void getInput() {
			
			cout << "> ";
			input = OptionInputChecker(1, 4);
		}

		int returnInput() {
			return input; 
		}
};

class Inserter {
	public:

		// NAME and STUDENT IT should not be blank. 
		

		void insertInfo(string filename) {
			char name[15];
			char ID[10];
			char birthYear[4];
			char tel[12];
			char dep[30];
			
			fstream inoutfile;
			inoutfile.open(filename,ios::app);

			if (inoutfile.is_open())
			{
				//name should not be blank.
				cout << "Name: ";
				cin.ignore();
				cin.getline(name, 15);
				inoutfile << name << ",";

				cout << "Student ID (10 digits): ";
				cin >> ID;
				inoutfile << ID << ",";
				//check for same student ID
				// if student ID is unique, check whether it is exactly 10 digits.
				//Id should not be blank.

				cout << "Birth Year (4 digits): ";
				cin >> birthYear;
				inoutfile << birthYear << ",";
				//if input is inserted, check whether it is exactly 4 digits.
				//can be left blank.

				
				cout << "Department: ";
				cin.ignore();
				cin.getline(dep, 30);
				inoutfile << dep << ",";
				//can be left blank.

				cout << "Tel: ";
				cin >> tel;
				inoutfile << tel << "\n";
				//can be left blank.

				inoutfile.close();
			}
			else cout << "Unable to open file."; 
		}

};

class Searcher {
	public:
		void search(string filename) {
			int option;
			cout << "- Search -" << endl; 
			cout << "1. Search by name" << endl; 
			cout << "2. Search by student ID (10 numbers)" << endl;
			cout << "3. Search by admission year (4 numbers)" << endl;
			cout << "4. Search by department name" << endl;
			cout << "5. List all" << endl;
			cout << "> ";
			option = OptionInputChecker(1, 5);

			fstream inoutfile; 
			inoutfile.open(filename, ios::in );
			if (inoutfile.is_open())
			{
				string line;
				switch (option)
				{
				case 1:
					char name[15];
					
					cin.ignore();
					cout << "Name keyword?: ";
					cin.getline(name,15);

					while (!inoutfile.eof())
					{
						string temp;

						getline(inoutfile, line);
						stringstream ss(line);

						getline(ss, temp, ',');

						
						if (temp.compare(name) == 0 )
						{
							printLine(line);
						}
					}


					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				default:
					break;
				}
				cout << endl;
			}
			else cout << "Unable to open file.";
		}
};

class Sorter {
	int sortOption = 1;
	public:
		void ChooseSortingOption() {
			cout << "- Sorting Option -" << endl;
			cout << "1. Sort by Name" << endl;
			cout << "2. Sort by Name" << endl;
			cout << "3. Sort by Student ID" << endl;
			cout << "4. Sort by Department name" << endl;
			cout << "> ";
			sortOption = OptionInputChecker(1, 4);
		}
};

void printLine(string info) {
	string temp;
	stringstream ss(info);
	
	int spaces[5] = { 25,23,12,43,22 };

	for (int i = 0; i < 5 ;i++)
	{
		getline(ss, temp, ',');
		cout << setw(spaces[i]-temp.length())<<left << temp;
	}
	cout << endl;
}


int OptionInputChecker(int from, int to) {
	int input; 
	cin >> input; 
	while ((!cin) || (input < from || input > to))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "please input a number from " << from<< " to "<< to << endl << "> ";
		cin >> input;
	}
	return input; 
}


int main(int argc, char*argv[]) {

	if (argc != 2)
	{
		//error when input arguement is incorrect.
		cout << "detected wrong format of input arguements. Please input a .txt filename after executable file ." << endl;
		return 0;
	}
	//add another part that detects whether the string of input argument ends with .txt

	string filename = argv[1];
	
	MainMenu menu;
	Inserter insert; 
	Searcher search; 
	Sorter sort;
	
	while (menu.returnInput()!=4)
	{
		menu.showMenu();
		menu.getInput();
		switch (menu.returnInput())
		{
		case 1:
			insert.insertInfo(filename);
			break;
		case 2:
			search.search(filename);
			break; 
		case 3:
			sort.ChooseSortingOption();
			break;
		case 4: 
			return 0;
		}

	}


	return 0;
}