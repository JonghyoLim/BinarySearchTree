// bstAssignment5.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include "bst.h"


using namespace std;
bool quitFlag = false;
int DisplayMenu();


void ClearAddressBook();
void AddAddressBook();
void RemoveAddressBook();
void SearchByLetter();
void SearchBySurName();

void DoQuit();


TreeType<string> phoneBook;


int _tmain(int argc, _TCHAR* argv[])
{
	//cout << "INMAIN" << endl;
	system("color 70");
	cout << "\n\t Assignment 5\n";
	cout << "\t NAME: JONGHYO LIM\n";
	cout << "\t KNUM: K00222516\n\n\n";


	do
	{
		int option = DisplayMenu();
		switch (option)
		{

		case 1:
			ClearAddressBook();
			break;

		case 2:
			AddAddressBook();
			break;

		case 3:
			RemoveAddressBook();
			break;

		case 4:
			SearchByLetter();
			break;

		case 5:
			SearchBySurName();
			break;

		case 6:
			DoQuit();
			break;

		case 7:
			if (phoneBook.IsEmpty())
				cout << "\t Mobile phone book is completly Empty.." << endl;
			else
			{
				cout << "\t Moblie Phone book Lists:" << endl << endl;
				phoneBook.PrintTree();
			}
			break;

		default:
			cout << "\tInvaild Option \n";
		}

	} while (!quitFlag);


	return 0;
}

int DisplayMenu(void)
{
	int option;

	cout << "=====================================================================================\n\n";
	cout << "\t\t\tAssignment.5 Binary Search Book\n\n";
	cout << "=====================================================================================\n";
	cout << "\t1. Clear the Address Book\n";
	cout << "\t2. Add new entry to the Address Book \n";
	cout << "\t3. Remove an entry from the Address Book \n";
	cout << "\t4. Search by Letter (All Surname's beginning with this letter) \n";
	cout << "\t5. Search by Surname and display all the details about the entry \n";
	cout << "\t6. Exit from the application\n";
	cout << "\t7. Print Lists \n";
	cout << "=====================================================================================\n";

	cout << "\tPlease Enter Option-------->>  ";
	cin >> option;
	system("cls");
	cout << endl << endl;

	return option;

}


void ClearAddressBook()
{
	phoneBook.MakeEmpty();
	cout << " The Phone Book is completely removed!" << endl;

}

void AddAddressBook()
{
	string fName;
	string lName;
	string num;

	for (int i = 0; i < 5; i++)
	{

		cout << " Enter First name: ";
		cin >> fName;
		cout << " Enter Last name: ";
		cin >> lName;
		cout << " Enter Mobile Number: ";
		cin >> num;
		cout << endl;
	

		phoneBook.InsertItem(fName, lName, num);

	}

}

void RemoveAddressBook()
{
	string fName;
	string lName;
	string num;

	cout << " Enter First name: ";
	cin >> fName;
	cout << " Enter Last name: ";
	cin >> lName;
	cout << " Enter Mobile Number: ";
	cin >> num;
	cout << endl;

	phoneBook.DeleteItem(fName, lName, num);

	cout << " Removed from Phone book." << endl;

}

void SearchByLetter()
{
	string letter;
	bool found = true;

	
	cout << "Enter a letter: ";
	cin >> letter;


	phoneBook.RetrieveLetterItem(letter,found);

	if (!found)
		cout << " Sorry, there is not " << letter << " in address book.\n";
	else
		cout << " Yep, there is your searching details:" << letter << " in address book. \n";


}

void SearchBySurName()
{
	string lName;
	//string num;
	bool found = true;

	cout << "Enter Lastname: ";
	cin >> lName;
	//cout << "Enter Mobile Num: ";
	//cin >> num;


	phoneBook.RetrieveItem(lName, found);

	if (!found)
		cout << " Sorry, there is not " << lName << " in address book.\n";
	else
		cout << " Yep, there is your searching details:" << lName << " in address book. \n";
}


void DoQuit()
{
}
