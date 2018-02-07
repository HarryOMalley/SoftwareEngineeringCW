#include <iostream>
#include <time.h>
#include "Menu.h"
using namespace std;
#include "Data.h"
Menu::Menu()
{
	Data bufferData;
	while (1)
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
			bufferData.Save();
			break;

		case '5':
			bufferData.Load();
			break;

		case '6':
			return;

		default:
			cout << "Invalid entry" << endl << endl;
			break;
		}
	}
}
Menu::~Menu()
{

}