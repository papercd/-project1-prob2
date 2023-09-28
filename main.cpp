#include <iostream>
using namespace std; 


class MainMenu {
	int input = 1; 
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
	public:
		void insertInfo() {

		}

};

class searcher {



};



int main(int argc, char*argv[]) {

	string filename = argv[1];
	MainMenu menu; 
	
	while (menu.returnInput())
	{
		menu.showMenu();
		menu.getInput();
		switch (menu.returnInput())
		{
		case 1:

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