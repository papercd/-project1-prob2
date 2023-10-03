#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std; 

void printLine(string info);
int OptionInputChecker(int from, int to);

class Student{
	public: 

	/*
	char name[15];
	char ID[10];
	char birthYear[4];
	char tel[12];
	char dep[30];
	char *ptr[5] = {name,ID,birthYear,tel,dep};
	*/
	string name;
	string ID; 
	string birthYear; 
	string tel; 
	string dep; 

	//string *ptr[5] = {&name,&ID,&birthYear,&tel,&dep};

	Student(){

	}

	Student(char name[15],char ID[10],char birthYear[4],char tel[12], char dep[30]){
		name = name; 
		ID = ID; 
		birthYear= birthYear;
		tel = tel; 
		dep = dep; 
	}
};

class MainMenu {
	int input = 0; 
	public:

		void showMenu() {
			cout << "- Main menu -"<<endl;;
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
			//char name[16];
			//char ID[11];
			string ID; 
			char birthYear[5];
			char tel[13];
			char dep[31];
			
			fstream inoutfile;


			inoutfile.open(filename,ios::app);

			if (inoutfile.is_open())
			{
				cin.ignore();

				cout << "Name: ";
				getline(cin,name);
				//cin.getline(name,16);
				while (name.length() == 0 || name.length() > 15)
				{
					cout << "name is either too long (15 characters is max) or entered blank." << endl;
					cout << "Please input a name: ";
					getline(cin,name);
				}
				inoutfile << name << ",";
		
				cout << "Student ID (10 digits): ";
				getline(cin,ID);
				while (ID.length() < 10 || ID.length() > 10)
				{
					cout << "ID is either not exactly 10 digits or entered blank." << endl;
					cout << "Please input Student ID: ";
					getline(cin,ID);
				}
				//search file and see if there is 



				inoutfile << ID << ",";

				//check for same student ID
				// if student ID is unique, check whether it is exactly 10 digits.
				//Id should not be blank.
				
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
				cin.getline(tel,13);
				inoutfile << tel << "\n";
				//can be left blank.

				inoutfile.close();
			}
			else cout << "Unable to open file."; 
		}

};

class SearchSort {
	int sortOption = 1;
	public:

		int searchInput(){
			int option;
			cout << "- Search -" << endl; 
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
				switch (searchInput())
				{

				case 1:
					char name[16];
					cout << "Name keyword?: ";
					cin.ignore();
					cin.getline(name,16);

					printSearchResult(name,1,inoutfile);
					break;
				case 2:
					char ID[11];
					cout << "Enter Student ID: ";
					cin.ignore();
					cin.getline(ID,11);
					
					printSearchResult(ID,2,inoutfile);
					
					break;
				case 3:
					

					break;
				case 4:
					char dep[31];
					cout << "Enter department name: ";
					cin.ignore();
					cin.getline(dep,31);
					
					printSearchResult(dep,4,inoutfile);
					break;
				case 5:
					

					//this is where you have to implement the sort 
					//step1: read the file and count the number of lines in the file, and create an array of that size with new.
					//read the file from the beginning again, and fill in the array with the information. 
					int count = 0;
					while (!inoutfile.eof())
					{
						string temp; 
						getline(inoutfile,temp);
						count++;
					}

					Student* arr; 
					arr = new Student[count];

					inoutfile.clear();
					inoutfile.seekg(0,ios::beg);

					count = 0;
					while (!inoutfile.eof())
					{
						string *ptr[5] = {&arr[count].name,&arr[count].ID,&arr[count].birthYear,&arr[count].dep,&arr[count].tel};
						
						//char*ptr[5] = {arr[count].name,arr[count].ID,arr[count].birthYear,arr[count].dep,arr[count].tel};

						string line; 
						getline(inoutfile,line);
						
						for (int i = 0; i < 5; i++)
						{	
							stringstream ss(line);
							string temp;
							for (int j = 0; j < i+1; j++)
							{
								getline(ss,temp,',');
							}
							*ptr[i] = temp; 
						}
						count++;
					}
					
					//step2: based on the sortOption, you need to sort the array that you created by comparing the target elements. 
					// If you are sorting by Name, Admission year or department name, you take the first characters of the comparing elements and compare their ascii codes, and the one with the lower value comes 
					// first. and if you are sorting by student ID, the smaller number comes first. the same for admission year.
					switch (sortOption)
					{
					case 1:
						sort(arr,arr+count,compareStudentName);
						break;
					case 2: 
						break;
					case 3: 
						break; 
					case 4: 
						break;
					}

					for (int i = 0; i < count; i++)
					{
						string line; 
						line = arr[i].name + ',' +arr[i].ID + ',' + arr[i].birthYear + ','+arr[i].dep + ','+arr[i].tel + ',';
						printLine(line);
					}
					
					break;
				}
				cout << endl;
			}
			else cout << "Unable to open file.";
			inoutfile.close();
		}
		
		// why does this need to be static? : if you want to use sort() then the comparison function need to be either static functions or non-members. What does this mean?

		static bool compareStudentName(Student a, Student b){
			
			int length; 

			if(a.name.length()<b.name.length()) 
				length = a.name.length();
			else length = b.name.length();
			for (int i = 0; i < length; i++)
			{
				if (tolower(a.name[i]) < tolower(b.name[i])){
					return true;
				}
					
				else if(tolower(a.name[i] > tolower(b.name[i]))){
					return false; 
				}
					
			}
			if (a.name.length()<b.name.length()){
				return true;
			}
			else{
				return false;
			}  			
		}
		

		bool compareStudentID(Student a, Student b){

		}

		bool compareStudentDep(Student a, Student b){

		}

		void ChooseSortingOption(){
			cout << "- Sorting Option -" << endl;
			cout << "1. Sort by Name" << endl;
			cout << "2. Sort by Student ID" << endl;
			cout << "3. Sort by Admission year" << endl;
			cout << "4. Sort by Department name" << endl;
			cout << "> ";
			sortOption = OptionInputChecker(1, 4);
		}

		void printSearchResult(string keyword,int location,fstream &inoutfile){
			string line;
			string temp; 

			while(!inoutfile.eof()){
				getline(inoutfile,line);
				stringstream ss(line);
				for(int i= 0; i <location; i++)
					getline(ss,temp,',');
				if(keyword.compare(temp)==0)
					printLine(line);
			}
		}
		
};

void printLine(string info) {
	string temp;
	stringstream ss(info);
	
	int spaces[5] = { 25,23,12,43,22 };

	for (int i = 0; i < 5 ;i++)
	{
		getline(ss, temp, ',');
		cout << setw(spaces[i]-temp.length())<< left << temp;
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