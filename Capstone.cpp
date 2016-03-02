//Capstone project
//from the menu, enter persons name
//vehicle information
//in addition next recommended service due
//by estimated vehicle mileage and/or date
//Created by Joshua Butzen beginning on 2/25/2016

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

//function prototypes
void displayMonth();
void enterName();
void searchMonth();
void searchName();

int main()
{
	//declare variable
	int menuOption = 0;

	//begin loop
	do {
		//display menu and get option
		cout << endl;
		cout << "1 Enter customer name and vehicle information" << endl;
		cout << "2 Display all services for year" << endl;
		cout << "3 Search recommended services by month" << endl;
		cout << "4 Search by Customer name" << endl;
		cout << "5 End Program" << endl;
		cout << "Enter menu option: ";
		cin >> menuOption;
		cin.ignore (100, '\n');
		cout << endl;

		//call appropriate function
		if (menuOption == 1)
			enterName();
		else
			if (menuOption == 2)
				displayMonth();
		else
            if (menuOption == 3)
                searchMonth();
        else
            if (menuOption == 4)
                searchName();
                    //end if
                //end if
			//end if
		//end if
	} while (menuOption != 5);

} //end main function

//*****function definitions*****
void enterName()
{
	//writes customer name and vehicle information to access file
	string name = "";
	string vehicle = "";
	string nextDate = "";
	int mileage = 0;
	int curMiles = 0;

	//create txt file and open file
	ofstream outFile;
	//user enters customers name
	cout << "Enter customer's first and last name (-1 to stop): ";
	getline(cin, name);
	//begin while
	while (name != "-1") {
		outFile.open("Services.txt", ios::app);
		//check if file is opened successfully
		if (outFile.is_open()) {
			//user enters vehicle information,
            //next recommended date, and
			//current mileage (function adds 3000 and equates
			//out to next recommended mileage
			cout << "Vehicle info (year make model): ";
			getline(cin, vehicle);
            cout << "Enter next recommended service date (dd/Month/yy): ";
			getline(cin, nextDate);
            cout << "Current vehicle mileage: ";
			cin >> curMiles;
			mileage = curMiles + 3000;
			cin.ignore(100, '\n');
			//write the record
			outFile << name << ", " << vehicle << ", " << nextDate << ", " << mileage << endl;
		} //end if
		else
		cout << "File did not open correctly." << endl;
		//user enters next name
		cout << endl << endl;
		cout << "Enter customer's first and last name (-1 to stop): ";
		getline(cin, name);
		//close the file
		outFile.close();
	} //end while
} //end of enterName function

//display all services
//ideally I'd like to have the dates automatically
//sorted and organized, but I'm still
//learning, and haven't come across that
void displayMonth()
{
    //declare string variables
    string name = "";
    string vehicle = "";
    string nextDate = "";
    string nextMileage = "";
    //create file
    ifstream inFile;
    //open Services.txt
    inFile.open("Services.txt", ios::in);
    //continue while pointer is not at end of file
    if (inFile.is_open()) {
        //read a record
        getline(inFile >> ws, name, ',');
        getline(inFile >> ws, vehicle, ',');
        getline(inFile >> ws, nextDate, ',');
        getline(inFile >> ws, nextMileage);
        //begin while statement
        while (!inFile.eof()) {
            //display the record
            cout << "Name:                      " << name << endl;
            cout << "Vehicle:                   " << vehicle << endl;
            cout << "Next service Date:         " << nextDate << endl;
            cout << "Next service mileage:      " << nextMileage << endl;
            cout << endl << endl;
            //read another file
            getline(inFile >> ws, name, ',');
            getline(inFile >> ws, vehicle, ',');
            getline(inFile >> ws, nextDate, ',');
            getline(inFile >> ws, nextMileage);
        } //end while
        //close file
        inFile.close();
    }
    else
        cout << "File could not be opened." << endl;
    //end if
} //end displayMonth function

//search by a specific month
void searchMonth()
{
    //declare string variables
    string sWord = "";
    string line = "";
    string nLine = "";

    //user enters month to search
    cout << "Enter month to search: ";
    cin >> sWord;
    cout << endl;
    cout << "***** Services recommended for " + sWord + " *****" << endl << endl;
    //create search object
    ifstream searchMon;
    //open Servicess.txt to search
    searchMon.open("Services.txt", ios::in);
    //while not at the end of file
    while(std::getline(searchMon, line)) {
        //if statement searches file for specific word
        //then displays the lines featuring that word
        if (line.find(sWord) != string::npos)
            //display line from text file
            cout << line << endl << endl;
        //end if
    } //end while
    //close file
    searchMon.close();
} //end searchMonth function

//search by a specific customer name
void searchName()
{
    //declare variables
    string sWord = "";
    string name = "";
    string vehicle = "";
    string nextDate = "";
    string estMiles = "";
    string nString = "";
    string nLine = "";

    //prompt user for name of item to search for
    cout << "Please enter the name of the customer: ";
    //assign input from keyboard to sWord variable
    getline(cin, sWord);
    //create searchinv ifstream object
    ifstream srchName;
    //open Services.txt as an input
    srchName.open("Services.txt", ios::in);
    //while not end of inventory.txt file
    while(!srchName.eof()) {
        //get line until comma delimiter and assign to name
        getline(srchName, name, ',');
        //get line until comma delimiter and assign to vehicle
        getline(srchName, vehicle, ',');
        //get line until comma delimiter and assign to nextDate
        getline(srchName, nextDate, ',');
        //get remainder of line and assign to estMiles
        getline(srchName, estMiles);
        //if search word is equal to name in this iteration
            if(sWord == name) {
                //assign string variables with values
                cout << endl;
                 nString = "Customer: " + name + " ----->" + vehicle + " ----->" + nextDate + " ----->" + estMiles;
                 nLine = "";
                //assign a number of - to the end of nLine based on the length of nString
                nLine.assign(nString.length(), '-');
                //display a line
                cout << nLine << endl;
                //display nString
                cout << nString << endl;
                //display a line
                cout << nLine << endl;
            } //end if
    } //end while
    //if nString is equal to an empty string after the while loop then there was no name that matched sWord
    if(nString == "") {
        //assign values to variables
        cout << endl;
        string err = "Customer " + sWord + " not listed";
        string eLine = "";
        //assign a number of - to eLine based on the length of err string
        eLine.assign(err.length(), '-');
        //display a line
        cout << eLine << endl;
        //display err string
        cout << err << endl;
        //display a line
        cout << eLine << endl;
    } //end if
    //go to new line
    cout << endl;
    //close file
    srchName.close();
} //end searchName function
