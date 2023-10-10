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


class checker{
	public: 
		
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
						inoutfile.close();
						return true;
					}
				}
				inoutfile.close();
				return false;
			}
			else
			{
				cout << "file could not be opened." << endl;
				inoutfile.close();
				return NULL;
			}
		}

		bool checkForChar(string name){
			for (int i = 0; i < name.length(); i++)
			{
				if(isalpha(name[i]))
				{
					return true;
				}
			}
			return false; 
		}

		bool checkForNumber(string name) {
			for (int i = 0; i < name.length(); i++)
			{
				if (isdigit(name[i]))
				{
					return true;
				}
			}
			return false; 
		}

		void eraseSpaces(string& info){
			size_t p = info.find_first_not_of(" \t");
			info.erase(0, p);

			p = info.find_last_not_of(" \t");
			if (string::npos != p)
			{
				info.erase(p+1);
			}
		}

		void inputInfo(string& info){
	
			getline(cin,info);
			eraseSpaces(info);
		}

		void formatName(string& name){
			while (checkForNumber(name) || name.length() == 0 || name.length() > 15)
			{
				cout << "name is either too long (15 characters is max) or entered blank or contains a number.\n\n"; 
				cout << "Please input a name: ";
				inputInfo(name);
			}
		}

		void formatID(string& ID){
			ID.erase(remove_if(ID.begin(), ID.end(), ::isspace), ID.end());
			while (checkForChar(ID)||ID.length() < 10 || ID.length() > 10 || ID[0] == '0')
			{
				cout << "ID is either not exactly 10 digits or entered blank or is not in the right format.\n\n";
				cout << "Please input Student ID: ";
					
				getline(cin,ID);
				ID.erase(remove_if(ID.begin(), ID.end(), ::isspace), ID.end());
			}
		}

		void formatBY(string& birthYear){
			birthYear.erase(remove_if(birthYear.begin(), birthYear.end(), ::isspace), birthYear.end());
			while (checkForChar(birthYear) || birthYear.length() != 4 || birthYear[0] == '0')
			{
				if (birthYear.length() == 0)
				{
					break;
				}
				cout << "Birth Year is either not exactly 4 digits or is not in the right format.\n\n";
				cout << "Please input Birth Year: ";
				getline(cin,birthYear);
				birthYear.erase(remove_if(birthYear.begin(), birthYear.end(), ::isspace), birthYear.end());

			}
		}

		void formatDep(string dep){
			while (checkForNumber(dep) || dep.length()>30)
			{
				cout << "the input contains a number, or is too long. (maximum is 30) \n\n";
				cout << "Please input correct Department Name: ";
				inputInfo(dep);
			}
		}

		void formatTel(string& tel){
			tel.erase(remove_if(tel.begin(), tel.end(), ::isspace), tel.end());
			while (checkForChar(tel) || tel.length() > 12)
			{
				cout << "Number is either longer than 12 digits or contains a character.\n\n";
				cout << "Please input tel : ";
				getline(cin,tel);
				tel.erase(remove_if(tel.begin(), tel.end(), ::isspace), tel.end());

			}
		}
};

class MainMenu {
	int input = 0; 
	checker check;
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
			input = check.OptionInputChecker(1, 4);
		}

		int returnInput() {
			return input; 
		}
};



class Inserter {

	checker check; 
	public:
		void insertInfo(string filename) {
			
			string name;
			string ID; 
			string birthYear;
			string tel;
			string dep;
			
			fstream inoutfile;
			inoutfile.open(filename,ios::app);

			if (inoutfile.is_open())
			{
				cin.ignore();
	
				cout << "Name: ";
				check.inputInfo(name);
				check.formatName(name);
				inoutfile << name << ",";
	


				cout << "Student ID (10 digits): ";			
				do
				{
					check.inputInfo(ID);
					check.formatID(ID);
					
					if(check.checkID(filename,ID))
					{	
						cout << "Student ID already exists.\n\n";
						cout << "Please input Student ID: ";
					}
				} while (check.checkID(filename,ID));
				inoutfile << ID << ",";
				
				
				cout << "Birth Year (4 digits): ";
				check.inputInfo(birthYear);
				check.formatBY(birthYear);
				inoutfile << birthYear << ",";
				

				cout << "Department: ";
				check.inputInfo(dep);
				check.formatDep(dep);
				inoutfile << dep << ",";
	
				cout << "Tel: ";
				check.inputInfo(tel);
				check.formatTel(tel);
				inoutfile << tel<<'\n';

				inoutfile.close();
			}
			else cout << "Unable to open file."; 
		}
};


class SearchSort {
	private: 
		
		//sortOption is by Name (1) in default.
		checker check; 
		int sortOption = 1;
		int printSpaces[5] = { 17,12,30,12,12 };

		int searchInput(){
			cout << "\n- Search -\n";
			cout << "1. Search by name\n"; 
			cout << "2. Search by student ID (10 numbers)\n";
			cout << "3. Search by admission year (4 numbers)\n";
			cout << "4. Search by department name\n";
			cout << "5. List all\n\n";
			cout << "> ";
			return check.OptionInputChecker(1, 5); 
		}

		void printHeader(){

			string header[5] = { "Name","Student ID","Dept", "Birth Year", "Tel" };

			for (int i = 0; i < 5; i++)
			{
				cout << setw(printSpaces[i]) << left << header[i];
			}
			cout << "\n===================================================================================\n";

		}

		static bool compareStudentName(Student a, Student b){
		
			int length;

			string noSpaceA =a.name;
			string noSpaceB = b.name;
			
			noSpaceA.erase(remove(noSpaceA.begin(),noSpaceA.end(),' '),noSpaceA.end());
			noSpaceB.erase(remove(noSpaceB.begin(), noSpaceB.end(), ' '), noSpaceB.end());

			if (noSpaceA.length() < noSpaceB.length())
				length = noSpaceA.length();
			else length = noSpaceB.length();
			for (int i = 0; i < length; i++)
			{
				if (tolower(noSpaceA[i]) != tolower(noSpaceB[i])) {
					return tolower(noSpaceA[i]) < tolower(noSpaceB[i]);
				}
			}
			return noSpaceA.length() <= noSpaceB.length();
		}

		static bool compareStudentID(Student a, Student b){
			return stoi(a.ID) < stoi(b.ID);
		}

		static bool compareStudentDep(Student a, Student b){
			
			int length;

			string noSpaceA =a.dep;
			string noSpaceB = b.dep;

			noSpaceA.erase(remove(noSpaceA.begin(),noSpaceA.end(),' '),noSpaceA.end());
			noSpaceB.erase(remove(noSpaceB.begin(), noSpaceB.end(), ' '), noSpaceB.end());

			if (noSpaceA.length() < noSpaceB.length())
				length = noSpaceA.length();
			else length = noSpaceB.length();
			for (int i = 0; i < length; i++)
			{
				if (tolower(noSpaceA[i]) != tolower(noSpaceB[i])) {
					return tolower(noSpaceA[i]) < tolower(noSpaceB[i]);
				}
			}
			return noSpaceA.length() <= noSpaceB.length(); 
		}

		
		void printMatch(string keyword,Student student,int location){

			string* printOrder[5] = { &student.name, &student.ID, &student.dep, &student.birthYear, &student.tel };


			int keyLength = keyword.length();
			int infoLength = (*printOrder[location]).length();

			
			if (keyLength <= infoLength)
			{
				bool found;
				
				for (int i = 0; i < infoLength - keyLength+1; i++)
				{
					found = true;
					for (int j = 0; j < keyLength; j++)
					{
						if (tolower(keyword[j]) != tolower((*printOrder[location])[i+j]))
						{
							found = false; 
							break; 
						}
					}
					if (found)
					{
						for (int k = 0; k < 5; k++)
						{
							cout << setw(printSpaces[k]) <<left << *printOrder[k];
						}
						cout <<endl; 
						break;
					}	
				}

			}

		}

		void printMatchAy(string keyword,Student student){
			string* printOrder[5] = { &student.name,&student.ID,&student.dep,&student.birthYear,&student.tel };
					
			bool equal = true; 
				
			for (int i = 0; i < 4; i++)
			{
				if (keyword[i] != student.ID[i])
				{
					equal = false; 
					break;
				}
				
			}
			if (equal)
			{
				for (int j = 0; j < 5; j++)
				{
					cout << setw(printSpaces[j]) << left << *printOrder[j];
				}
				cout << endl;
			}
		}

		void printSearchResult(string keyword, int location, Student* arr, int size) {
			
			switch (sortOption)
			{
			case 1:
				cout << "(Sorted by Name)\n";
				break;
			case 2:
				cout << "(Sorted by Student ID)\n";
				break;
			case 3:
				cout << "(Sorted by Admission Year)\n";
				break;
			case 4:
				cout << "(Sorted by Department name)\n";
				break;
			}

			cout <<endl;

			printHeader(); 
			
			if (location == 0 || location == 1 || location == 2)
			{	
				
				for (int i = 0; i < size; i++)
				{
					printMatch(keyword,arr[i],location);
				}
			}
			else {

				for (int i = 0; i < size; i++)
				{
					printMatchAy(keyword,arr[i]);
				}
			}
		}

	
	public:
		
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
				{
					string name;
					cout << "Name keyword?: ";
					cin.ignore();
					check.inputInfo(name);
					check.formatName(name);
					printSearchResult(name,0,arr,count);

					break;
				}
				case 2:{
					string ID;
					cout << "Enter Student ID: ";
					cin.ignore();
					check.inputInfo(ID);
					check.formatID(ID);
					printSearchResult(ID,1,arr,count);
					
					break;
				}
				case 3:{
					string admYear; 
					cout << "Enter Admission year: ";
					cin.ignore();
					check.inputInfo(admYear);
					check.formatBY(admYear);
					printSearchResult(admYear, 3, arr,count);

					break;
				}
				case 4:{
					string dep; 
					cout << "Enter department name: ";
					cin.ignore();
					check.inputInfo(dep);
					check.formatDep(dep);
					printSearchResult(dep,2,arr,count);
					break;
				}
				case 5:
					
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
					cout <<endl;
					
					printHeader();
					
					for (int i = 0; i < count; i++)
					{
						string* order[5] = { &arr[i].name, &arr[i].ID, &arr[i].dep, &arr[i].birthYear, &arr[i].tel };
						for (int j = 0; j < 5; j++)
						{
							cout << setw(printSpaces[j]) << left << *order[j];
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
		
	
		void ChooseSortingOption(){
			cout << endl << "- Sorting Option -" << endl;
			cout << "1. Sort by Name" << endl;
			cout << "2. Sort by Student ID" << endl;
			cout << "3. Sort by Admission year" << endl;
			cout << "4. Sort by Department name" << endl;
			cout << "> ";
			sortOption = check.OptionInputChecker(1, 4);
		}
};


int main(int argc, char*argv[]) {

	if (argc != 2)
	{
		cout << "detected wrong format of input arguements. Please input a .txt filename after executable file ." << endl;
		return 0;
	}


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