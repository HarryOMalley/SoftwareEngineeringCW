#include <iostream>
#include <time.h>
#include "Menu.h"
using namespace std;

Menu::Menu()
{
	
}

Menu::~Menu()
{
}

void Menu::menu() 
{
	cout << endl;
	cout << "Buffer Management Menu" << endl;
	cout << "----------------------" << endl;
	cout << "1. Produce a new message for the buffer" << endl;
	cout << "2. Consume a message from the buffer" << endl;
	cout << "3. View the contents of the buffer" << endl;
	cout << "4. Save the contents of the buffer to file" << endl;
	cout << "5. Load a file into the buffer" << endl;
	cout << "6. Exit from the program" << endl << endl;

	// get the user's choice
	cout << "Enter your option: ";
	cin >> UserInput;
	cout << endl;
}

void Menu::choose()
{
	switch (UserInput) {
	case '1':
		Produce();
		break;

	case '2':
		Consume();
		break;

	case '3':
		Show();
		break;

	case '4':
		Save();
		break;

	case '5':
		Load();
		break;
	
	case '6':
		return 0;

	default:
		cout << "Invalid entry" << endl << endl;
		break;
	}
}