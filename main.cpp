#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std; 



class Student{
	public: 

	string name;
	string ID; 
	string birthYear; 
	string tel; 
	string dep; 
	string* order[5] = { &name,&ID,&birthYear,&dep,&tel };

	Student(){

	}
};

void printLine(Student student);
int OptionInputChecker(int from, int to);

class MainMenu {
	int input = 0; 
	public:

		void showMenu() {
			cout << endl << "- Main menu -" << endl;;
			cout << "1. Insertion"<<endl;;
			cout << "2. Search"<<endl;;
			cout << "3. Sorting Option"<<endl;;
			cout << "4. Exit"<<endl<<endl;
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
			
			string name;
			string ID; 
			char birthYear[5];
			string tel;
			char dep[31];
			
			fstream inoutfile;


			inoutfile.open(filename,ios::app);

			if (inoutfile.is_open())
			{
				cin.ignore();

				cout << "Name: ";
				getline(cin,name);				
				while (checkName(name))
				{
					cout << "the input contains a number. " << endl;
					cout << "Please input a name: ";
					getline(cin, name);
				}
				while (name.length() == 0 || name.length() > 15)
				{
					cout << "name is either too long (15 characters is max) or entered blank." << endl;
					cout << "Please input a name: ";
					getline(cin,name);
				}
				inoutfile << name << ",";
		
				cout << "Student ID (10 digits): ";
				getline(cin,ID);
				while (ID.length() < 10 || ID.length() > 10 || ID[0] == '0')
				{
					cout << "ID is either not exactly 10 digits or entered blank or is not in the right format." << endl;
					cout << "Please input Student ID: ";
					getline(cin,ID);
				}
				//search file and see if there is 
				while (checkID(filename,ID))
				{
					cout << "Student ID already exists." << endl;
					cout << "Please input Student ID: ";
					getline(cin, ID);
				}

				inoutfile << ID << ",";

				
				
				cout << "Birth Year (4 digits): ";
				cin.getline(birthYear, 5);
				inoutfile << birthYear << ",";
				//if input is inserted, check whether it is exactly 4 digits.
				//can be left blank.

				
				cout << "Department: ";
				cin.getline(dep, 31);
				inoutfile << dep << ",";
				//can be left blank.

				
				cout << "Tel: ";
				getline(cin, tel);
				while (tel.length() > 12)
				{
					cout << "Number is longer than 12 digits." << endl;
					cout << "Please input Student ID: ";
					getline(cin, ID);
				}
				inoutfile << tel<<'\n';
				//can be left blank.

				inoutfile.close();
			}
			else cout << "Unable to open file."; 
		}

		bool checkID(string filename,string ID) {
			fstream inoutfile;
			inoutfile.open(filename, ios::in);
			if (inoutfile.is_open())
			{
				while (!inoutfile.eof())
				{
					string line;
					getline(inoutfile, line);
					stringstream ss(line);

					string temp;
					for (int i = 0; i < 2; i++)
					{
						getline(ss, temp, ',');
					}

					if (!temp.compare(ID))
					{
						return true;
					}
				}
				return false;
			}
			else
			{
				cout << "file could not be opened." << endl;
				return NULL;
			}
		}

		bool checkName(string name) {
			for (int i = 0; i < name.length(); i++)
			{
				if (isdigit(name[i]))
				{
					return true;
				}
			}
			return false; 
		}

};

class SearchSort {
	int sortOption = 1;
	public:

		int searchInput(){
			int option;
			cout << endl << "- Search -" << endl;
			cout << "1. Search by name" << endl; 
			cout << "2. Search by student ID (10 numbers)" << endl;
			cout << "3. Search by admission year (4 numbers)" << endl;
			cout << "4. Search by department name" << endl;
			cout << "5. List all" << endl<<endl;
			cout << "> ";
			option = OptionInputChecker(1, 5);
			return option; 
		}

		void search(string filename) {

			fstream inoutfile; 
			inoutfile.open(filename, ios::in );
			if (inoutfile.is_open())
			{
				int count = 0;


				while (!inoutfile.eof())
				{
					string temp;
					getline(inoutfile, temp);
					count++;
				}

				Student* arr;
				arr = new Student[count];

				inoutfile.clear();
				inoutfile.seekg(0, ios::beg);

				for (int i = 0; i < count; i++)
				{
					string line;
					getline(inoutfile, line);

					for (int j = 0; j < 5; j++)
					{
						stringstream ss(line);
						string temp;
						for (int k = 0; k < j + 1; k++)
						{
							getline(ss, temp, ',');
						}
						
						*(arr[i].order[j]) = temp;
						
					}
				}

			
				switch (sortOption)
				{
				case 1:
					sort(arr,arr+count-1, compareStudentName);
					break;
				case 2:
					sort(arr, arr + count-1, compareStudentID);
					break;
				case 3:
					sort(arr, arr + count-1, compareStudentID);
					break;
				case 4:
					sort(arr, arr + count-1, compareStudentDep);
					break;
				}
		

				switch (searchInput())
				{
					
				case 1:
					char name[16];
					cout << "Name keyword?: ";
					cin.ignore();
					cin.getline(name,16);
					printSearchResult(name,0,arr,count);

					break;
				case 2:
					char ID[11];
					cout << "Enter Student ID: ";
					cin.ignore();
					cin.getline(ID,11);
					printSearchResult(ID,1,arr,count);
					
					break;
				case 3:
					char admYear[5];
					cout << "Enter Admission year: ";
					cin.ignore();
					cin.getline(admYear, 5);
					printSearchResult(admYear, 3, arr,count);

					break;
				case 4:
					char dep[31];
					cout << "Enter department name: ";
					cin.ignore();
					cin.getline(dep,31);
					printSearchResult(dep,2,arr,count);
					break;
				case 5:
					int spaces[5] = { 17,12,30,12,12 };
					string header[5] = { "Name","Student ID","Dept", "Birth Year", "Tel" };
					cout << endl;
					switch (sortOption)
					{
					case 1:
						cout << "(Sorted by Name)" << endl;
						break;
					case 2: 
						cout << "(Sorted by Student ID)" << endl;
						break;
					case 3: 
						cout << "(Sorted by Admission Year)" << endl;
						break;
					case 4: 
						cout << "(Sorted by Department name)" << endl;
						break;
					}
					for (int i = 0; i < 5; i++)
					{
						cout << setw(spaces[i]) << left << header[i];
					}
					cout <<endl<< "==================================================================================="<<endl;

					for (int i = 0; i < count; i++)
					{
						//implement printLine 
						
						string* order[5] = { &arr[i].name, &arr[i].ID, &arr[i].dep, &arr[i].birthYear, &arr[i].tel };
						for (int j = 0; j < 5; j++)
						{
							cout << setw(spaces[j]) << left << *order[j];
						}
						cout << endl;
					}
					
					break;
				}
				cout << endl;
				delete[] arr;
			}
			else cout << "Unable to open file.";
			inoutfile.close();
		}
		

		// why does this need to be static? : if you want to use sort() then the comparison function need to be either static functions or non-members. What does this mean?


		//private
		static bool compareStudentName(Student a, Student b){
			int length;

			string newStringA =a.name;
			string newStringB = b.name;
			newStringA.erase(remove(newStringA.begin(),newStringA.end(),' '),newStringA.end());
			newStringB.erase(remove(newStringB.begin(), newStringB.end(), ' '), newStringB.end());

			if (newStringA.length() < newStringB.length())
				length = newStringA.length();
			else length = newStringB.length();
			for (int i = 0; i < length; i++)
			{
				if (tolower(newStringA[i]) != tolower(newStringB[i])) {
					return tolower(newStringA[i]) < tolower(newStringB[i]);
				}

			}
			return newStringA.length() <= newStringB.length();
		}
		
		//private
		static bool compareStudentID(Student a, Student b){

		
			return stoi(a.ID) < stoi(b.ID);
		}
		//private
		static bool compareStudentDep(Student a, Student b){
			
			
			int length;

			if (a.dep.length() < b.dep.length())
				length = a.dep.length();
			else length = b.dep.length();
			for (int i = 0; i < length; i++)
			{
				if (tolower(a.dep[i]) < tolower(b.dep[i])) {
					return true;
				}

				else if (tolower(a.dep[i] > tolower(b.dep[i]))) {
					return false;
				}

			}
			if (a.dep.length() < b.dep.length()) {
				return true;
			}
			else {
				return false;
			}
		}

		void ChooseSortingOption(){
			cout << endl << "- Sorting Option -" << endl;
			cout << "1. Sort by Name" << endl;
			cout << "2. Sort by Student ID" << endl;
			cout << "3. Sort by Admission year" << endl;
			cout << "4. Sort by Department name" << endl;
			cout << "> ";
			sortOption = OptionInputChecker(1, 4);
		}


		//private
		void printSearchResult(string keyword, int location, Student* arr, int size) {
			switch (location)
			{
			case 0:
				cout << "(Sorted by Name)" << endl;
				break;
			case 1:
				cout << "(Sorted by Student ID)" << endl;
				break;
			case 3:
				cout << "(Sorted by Admission Year)" << endl;
				break;
			case 2:
				cout << "(Sorted by Department name)" << endl;
				break;
			}
			int spaces[5] = { 17,12,30,12,12 };
			string header[5] = { "Name","Student ID","Dept", "Birth Year", "Tel" };
			cout << endl;
			for (int i = 0; i < 5; i++)
			{
				cout << setw(spaces[i]) << left << header[i];
			}
			cout <<endl<< "==================================================================================="<<endl;
			
			if (location == 0 || location == 1 || location == 2)
			{	
				
				for (int i = 0; i < size; i++)
				{
					string* order[5] = { &arr[i].name, &arr[i].ID, &arr[i].dep, &arr[i].birthYear, &arr[i].tel };
				
					if (!((*order[location]).compare(keyword)))
					{
						
						for (int j = 0; j < 5; j++)
						{
							cout << setw(spaces[j]) << left << *order[j];
						}
						cout << endl;
					}
				}
			}
			else {

				// if you need to search for admission year 
				for (int i = 0; i < size; i++)
				{
					string* order[5] = { &arr[i].name,&arr[i].ID,&arr[i].dep,&arr[i].birthYear,&arr[i].tel };
					
					bool equal = true; 
				
					for (int j = 0; j < 4; j++)
					{
						if (keyword[j] != arr[i].ID[j])
						{
							equal = false; 
							break;
						}
				
					}
					if (equal)
					{
						for (int k = 0; k < 5; k++)
						{
							cout << setw(spaces[k]) << left << *order[k];
						}
						cout << endl;
					}
				}
			}
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
	
	MainMenu menu;
	Inserter insert; 
	SearchSort searchAndSort; 

	
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
			searchAndSort.search(filename);
			break; 
		case 3:
			searchAndSort.ChooseSortingOption();
			break;
		case 4: 
			return 0;
		}

	}
	return 0;
}