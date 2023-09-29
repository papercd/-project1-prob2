#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>

using namespace std; 

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
			//get correct input from user. error handling should be implemented. 
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
		// STUDENT ID should be exactly 10 digits, BIRTH YEAR needs to be exactly 4 digits - in the correct birth year format
		// TEL should be up to 12 digits.

		void insertInfo(string filename, fstream &inoutfile) {
			char name[15];
			char ID[10];
			char birthYear[4];
			char tel[12];
			string dep;

			inoutfile.open(filename,ios::app);

			if (inoutfile.is_open())
			{
				cout << "Name: ";
				cin >> name;

		
				cout << "Student ID (10 digits): ";
				cin >> ID;

				cout << "Birth Year (4 digits): ";
				cin >> birthYear;



				cout << "Department: ";
				cin >> dep;



				cout << "Tel: ";
				cin >> tel;



				inoutfile << name << " " << birthYear << " "<< ID <<  " " << tel << " " << dep << "\n";
				
				inoutfile.close();
			}
			else cout << "Unable to open file"; 
		}

};

class Searcher {
	public:
		void search() {
			int option;
			cout << "- Search -" << endl; 
			cout << "1. Search by name" << endl; 
			cout << "2. Search by student ID (10 numbers)" << endl;
			cout << "3. Search by admission year (4 numbers)" << endl;
			cout << "4. Search by department name" << endl;
			cout << "5. List all" << endl;
			cout << "> ";
			option = OptionInputChecker(1, 5);
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
	fstream inoutfile;
	
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
			insert.insertInfo(filename, inoutfile);
			break;
		case 2:
			search.search();
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