#include <iostream>
#include <time.h>
#include "Menu.h"
#include "Data.h"
using namespace std;

Menu::Menu()
{
	Data bufferData;
	while (1) {		// loop until the user wishes to exit
		// show the menu of options
		cout << endl;
		cout << "Buffer Management Menu" << endl;
		cout << "----------------------" << endl;
		cout << "1. Produce a new message for the buffer" << endl;
		cout << "2. Consume a message from the buffer" << endl;
		cout << "3. View the contents of the buffer" << endl;
		cout << "4. Save the contents of the buffer to the disc" << endl;
		cout << "5. Load messages from the disc to the buffer" << endl;
		cout << "6. Exit from the program" << endl << endl;

		// get the user's choice
		cout << "Enter your option: ";
		cin >> UserInput;
		cout << endl;

		// act on the user's input
		switch (UserInput) {
		case '1':
			bufferData.Produce();
			break;

		case '2':
			bufferData.Consume();
			break;

		case '3':
			bufferData.Show();
			break;

		case '4':
			cout << "Please enter the filename (without the extension): " << endl;
			cin >> fileName;
			bufferData.Save(fileName);
			break;

		case '5':
			cout << "Please enter the filename (without the extension): " << endl;
			cin >> fileName;
			bufferData.Load(fileName);
			break;
		default:
			cout << "Invalid entry" << endl << endl;
			break;
		}
	}
}
Menu::~Menu()
{

}