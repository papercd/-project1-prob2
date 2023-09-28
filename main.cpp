#include <iostream>
#include <limits>

using namespace std; 


class MainMenu {
	int input = 0; 
	public:

		void showMenu() {
			cout << "1. Insertion\n";
			cout << "2. Search\n";
			cout << "3. Sorting Option\n";
			cout << "4. Exit\n";
		}

		void getInput() {
			//get correct input from user. error handling should be implemented. 
			cout << "> ";
			cin >> input; 
			while ((!cin) || (input <=0 || input > 5))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "please input an integer from 1 to 4." << endl << "> ";
				cin >> input; 
			}
		}

		int returnInput() {
			return input; 
		}
};

class Inserter {
	char name[15];
	int ID;
	int birthYear;
	int tel;
	string dep; //size of department not defined 
	public:

		// NAME and STUDENT IT should not be blank. 
		// STUDENT ID should be exactly 10 digits, BIRTH YEAR needs to be exactly 4 digits - in the correct birth year format
		// TEL should be up to 12 digits.

		void insertInfo() {
			
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

			//write information onto the file 
		}

};

class Searcher {



};



int main(int argc, char*argv[]) {

	if (argc != 2)
	{
		cout << "detected wrong format of input arguements. Please input a filename after executable file : ";
		return 0;
	}

	string filename = argv[1];
	MainMenu menu;
	Inserter insert; 
	Searcher search; 
	
	while (menu.returnInput()!=4)
	{
		menu.showMenu();
		menu.getInput();
		switch (menu.returnInput())
		{
		case 1:
			insert.insertInfo();
			break;
		case 2:

			break; 
		case 3:

			break;
		case 4: 
			return 0;
		}

	}


	return 0;
}