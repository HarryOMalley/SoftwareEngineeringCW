#pragma once
#include <string>
class Menu
{
public:
	Menu(); // Constructor which will loop around the main function
	~Menu();
private:
	char UserInput;
	std::string fileName;
};

