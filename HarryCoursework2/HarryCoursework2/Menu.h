#pragma once
#include <string>
// Menu class which will run the main program, display the menu and call the data class member functions to access the buffer
class Menu 
{
public:
	// Function prototypes
	Menu(); // Constructor which will loop around the main function
	~Menu();
private:
	// Variables to hold the User input and filename
	char UserInput;
	std::string fileName;
};

