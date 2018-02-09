#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include "Menu.h"
#include "Data.h"
using namespace std;
// Constructor which acts as the main menu, loops around until the user wishes to end, in which case the deconstructor is called for both the Data Class and the Menu Class
Menu::Menu()
{
	Data bufferData; // Creates an Object of the Data Class, which will create the buffer and functions associated
	int stop = 0;
	while (stop != 1) {		// Loop until the user wishes to exit
		// Show the Menu of options
		cout << endl;
		cout << "Buffer Management Menu" << endl;
		cout << "----------------------" << endl;
		cout << "1. Produce a new message for the buffer" << endl;
		cout << "2. Consume a message from the buffer" << endl;
		cout << "3. View the contents of the buffer" << endl;
		cout << "4. Save the contents of the buffer to the disk" << endl;
		cout << "5. Load messages from the disk to the buffer" << endl;
		cout << "6. Exit from the program" << endl << endl;

		// Get the user's choice
		cout << "Enter your option: ";
		cin >> UserInput;
		cout << endl;

		// Act on the user's input
		switch (UserInput) {
		case '1':
			bufferData.Produce(); // Produce function within the Data class
			break;

		case '2':
			bufferData.Consume(); // Consume function within the Data class
			break;

		case '3':
			cout << bufferData; // Overloaded << operator in the Data class to do this
			break;

		case '4':
			cout << "Please enter the filename (without the extension): " << endl; // Getting the name of the file to write to
			cin >> fileName;
			fileName << bufferData; // Using the overloaded operator to write to the file
			cout << "Saved to " << fileName + ".dat" << endl;
			break;

		case '5':
			cout << "Please enter the filename (without the extension): " << endl; // Getting the name of the file to read from
			cin >> fileName;
			fileName >> bufferData; // Using the overloaded operator to read from the file
			cout << "Read the Data from " + fileName + ".dat" << endl;
			break;

		case '6':
			stop = 1; 
			break;

		default:
			cout << "Invalid entry" << endl << endl;
			break;
		}
	}
}
// Deconstructor
// Says goodbye and waits for the user to press enter to prevent the console from closing immediately
Menu::~Menu()
{
	cout << endl << endl << "Goodbye." << endl << "Press enter to exit." << endl;
	cin.ignore();
	cin.get();
}