#include <iostream>
#include <fstream>
#include <time.h>
#include "Data.h"
#include "string"
#define BUFFER_LENGTH 10
using namespace std;

Data::Data() // Constructor
{
	buffer_tail = 0; // Initialising the two variables to zero
	buffer_length = 0;
}

Data::~Data() // Deconstructor
{
	cout << "Deconstructing the Data Object..." << endl; // Message to say the Object is being deconstructed
}

// Create a new message and add it to the head of the buffer.
// The data for the message is obtained from the user and a time stamp is obtained from the
// time() function in the C standard library. 
// Arguments:
//   (1) start of the buffer
//   (2) position of the tail of the buffer
//   (3) number of messages in the buffer
// Returns: void
// This function hasn't changed since Task 1, instead being held within a class
void Data::Produce() 
{
	time_t current_time;
	unsigned long buffer_head;

	// Find the element of the buffer in which to store the message
	buffer_head = (buffer_tail + buffer_length) % BUFFER_LENGTH;

	// Get the value of the data for the message from the user
	cout << "Add new data" << endl;
	cout << "------------" << endl;
	cout << "Enter data: ";
	cin >> buffer[buffer_head].data;
	cout << endl;

	// Get the value of the time for the message
	buffer[buffer_head].time = time(&current_time);

	// If no buffer overflow has occurred, adjust the buffer length
	if (buffer_length < BUFFER_LENGTH) 
	{
		buffer_length++;
	}

	// If a buffer overflow has occurred, display an error statement
	else 
	{
		buffer_tail = (buffer_tail + 1) % BUFFER_LENGTH;
		cout << "Overflow error" << endl;
	}
}

// Pop the message at the head of the buffer and display it.
// Arguments:
//   (1) start of the buffer
//   (2) position of the tail of the buffer
//   (3) number of messages in the buffer
// Returns: void
// This function hasn't changed since Task 1, instead being held within a class
void Data::Consume() 
{
	// If the buffer is empty, display an error statement
	if (buffer_length == 0) 
	{
		cout << "No messages in the buffer" << endl;
	}
	// If the buffer is not empty, display the message at the tail, remove the message by
	// Advancing the tail of buffer offset in a circular manner and adjust the buffer length
	else 
	{
		cout << endl;
		cout << "Offset Data        Time" << endl;
		cout << buffer_tail << "\t";
		cout << buffer[buffer_tail].data << "\t";
		cout << ctime(&buffer[buffer_tail].time);
		buffer_tail = (buffer_tail + 1) % BUFFER_LENGTH;
		buffer_length--;
	}
}

// Function to open a file as an input
// Arguments:
//		(1) Name of the file to open as input
// Returns the filePointer if it opens correctly, otherwise it will exit the program
// Due to the data types of the functions, it is not possible to return back to the menu if the file does not open properly
// It would require changing the data types of the functions, it is easier to exit the program if the file does not open properly
// Because of this, it first outputs the error message, i.e that the file could not be opened to read, then waits for user input
// This is to prevent the console from closing immediately, which it does sometimes on some operating systems. This way it maximises compatibility so that the user knows what the problem is.
fstream Data::openFileIn(std::string fileName) 
{
	fileName = fileName + ".dat"; // Concatenating the filename with the .dat extension
	fstream filePointer;		  // Creating the file pointer to open the file for reading
	filePointer.open(fileName, ios::in);
	// Display error and return if file fails to open
	if (!filePointer.good()) 
	{ 
		cout << endl << "Error: Could not open file to read!" << endl;
		cout << "Press enter to exit."; // Allowing time for the user to read the error message
		cin.ignore();
		cin.get();
		exit(1);	// Cannot go back to the main function as you would need to return the pointer, better to exit.
	}
	return filePointer;
}

// Function to open a file as an output
// Arguments:
//		(1) Name of the file to open as output
// Returns the filePointer if it opens correctly, otherwise it will exit the program
// Due to the data types of the functions, it is not possible to return back to the menu if the file does not open properly
// It would require changing the data types of the functions, it is easier to exit the program if the file does not open properly
// Because of this, it first outputs the error message, i.e that the file could not be opened to write, then waits for user input
// This is to prevent the console from closing immediately, which it does sometimes on some operating systems. This way it maximises compatibility so that the user knows what the problem is.
fstream Data::openFileOut(std::string fileName) 
{
	fileName = fileName + ".dat"; // Concatenating the filename with the .dat extension
	fstream filePointer;		  // Creating the file pointer to open the file for writing
	filePointer.open(fileName, ios::out);
	// Display error and return if file fails to open
	if (!filePointer.good()) 
	{
		cout << endl << "Error: Could not open file to write!" << endl;
		cout << "Press enter to exit.";	// Allowing time for the user to read the error message
		cin.ignore();
		cin.get();
		exit(1);	// Cannot go back to the main function as you would need to return the pointer, better to exit.
	}
	return filePointer; // Returning it to the function, leave the checking for the main function as it can revert back to the menu.
}

// Overloaded << operator to be able to use cout directly with the bufferClass to output the data from buffer
// Arguments:
//		(1) ostream os
//		(2) Data Object
// Takes two arguments, the cout ostream function and the dataClass which it will extract the relevant information from
// Returns the os which will output the information that was written to it in this function
// The function itself is largely the same as the show function from task 1, instead being used with the overloaded << operator
ostream & operator<<(ostream & os, const Data & dataClass) 
{
	unsigned long count = 0; // Count through the messages being displayed
	unsigned long buffer_head;  // The position at which the next message would be pushed

	// If the buffer is empty, display an error statement
	if (dataClass.buffer_length == 0) 
	{
		os << "No messages in the buffer" << endl;
	}
	// If the buffer is not empty, display all the messages in the buffer
	else 
	{
		// Display a title
		os << endl;
		os << "Offset Data        Time" << endl;

		// Display messages if they are sequential in the array
		buffer_head = (dataClass.buffer_tail + dataClass.buffer_length) % BUFFER_LENGTH;
		if (dataClass.buffer_tail < buffer_head) 
		{
			for (count = dataClass.buffer_tail; count < buffer_head; count++) 
			{
				os << count << "\t";
				os << dataClass.buffer[count].data << "\t";
				os << ctime(&dataClass.buffer[count].time);
			}
		}
		// Display messages if part are at the end of the array and the remainder at the start
		else 
		{
			for (count = dataClass.buffer_tail; count < BUFFER_LENGTH; count++) 
			{
				os << count << "\t";
				os << dataClass.buffer[count].data << "\t";
				os << ctime(&dataClass.buffer[count].time);
			}
			for (count = 0; count < buffer_head; count++) 
			{
				os << count << "\t";
				os << dataClass.buffer[count].data << "\t";
				os << ctime(&dataClass.buffer[count].time);
			}
		}
	}
	return os;
}

// Overloaded << operator used to save the dataClass buffer to file
// Arguments:
//		(1) Name of the file to save to as a string
//		(2) Data Object
// Takes two arguments, the file name and the dataClass. The file name is then concatenated with the extension (.dat) and the file is opened with the openFileOut function
// Returns the filePointer
// The values of buffer_length and buffer_tail are outputted also. Considering that it does not take up that much extra storage it is worthwhile to make it simpler to import it again when loading
// If this was not done, instead you could calculate the position of the buffer_tail and the buffer_length with the offset and number of data entries.
fstream& operator<<(std::string fileName, Data & dataClass)
{
	// Checking to make sure that there are messages to save, otherwise it will cause an access violation
	if (dataClass.buffer_length == 0) 
	{
		cout << endl << "Error: No messages to save!" << endl;
		cout << "Press enter to exit.";	// Allowing time for the user to read the error message
		cin.ignore();
		cin.get();
		exit(1);	// Cannot go back to the main function as you would need to return the pointer, better to exit.
	}
	fstream filePointer = dataClass.openFileOut(fileName); // Creating the filePointer with the openFileOut function
	unsigned long count; // count through the messages being displayed
	unsigned long buffer_head;  // the position at which the next message would be pushed
	buffer_head = (dataClass.buffer_tail + dataClass.buffer_length) % BUFFER_LENGTH;
	// If the buffer hasnt wrapped around, then output normally
	if (dataClass.buffer_tail < buffer_head) 
	{
		for (count = dataClass.buffer_tail; count < buffer_head; count++) 
		{
			// Outputting to the file the various pieces of data
			filePointer << count << ","; // Outputting all of the data to the file
			filePointer << dataClass.buffer[count].data << ",";
			filePointer << dataClass.buffer_length << ","; // Outputting the values for buffer_length and buffer_tail also, to ensure that this could be restored later
			filePointer << dataClass.buffer_tail << ",";
			filePointer << dataClass.buffer[count].time << ",";
			filePointer << ctime(&dataClass.buffer[count].time);
		}
	}
	// If the buffer has wrapped around then output them from start to finish
	else 
	{
		for (count = dataClass.buffer_tail; count < BUFFER_LENGTH; count++) 
		{
			filePointer << count << ","; // Outputting all of the data to the file
			filePointer << dataClass.buffer[count].data << ",";
			filePointer << dataClass.buffer_length << ","; // Outputting the values for buffer_length and buffer_tail also, to ensure that this could be restored later
			filePointer << dataClass.buffer_tail << ",";
			filePointer << dataClass.buffer[count].time << ",";
			filePointer << ctime(&dataClass.buffer[count].time);
		}
		for (count = 0; count < buffer_head; count++) 
		{
			filePointer << count << ","; // Outputting all of the data to the file
			filePointer << dataClass.buffer[count].data << ",";
			filePointer << dataClass.buffer_length << ","; // Outputting the values for buffer_length and buffer_tail also, to ensure that this could be restored later
			filePointer << dataClass.buffer_tail << ",";
			filePointer << dataClass.buffer[count].time << ",";
			filePointer << ctime(&dataClass.buffer[count].time);
		}
	}
	filePointer.close(); // Close the filePointer when we have finished writing to it
	return filePointer;
}

// Overloaded >> operator to load from a file into the buffer
// Arguments:
//		(1) Name of the file to read from as a string
//		(2) Data Object
// Takes two operators, the file name and the dataClass, to which the data will be stored into the buffer.
// The file is opened by the openFileIn function using the file name which is concatenated with the extension (.dat)
// By using filePointer.eof(), the file can be read until the program gets to the end. 
// Each line is read by the std::getline function, with delimeters. The delimeters allow each part of the file to be seperated and read into variables
// Each entry is split up by a comma, which makes it still possible to read the file and easy to read it back in.
// The file usually has an empty line at the end, which can result in the program outputting an empty line also, so we check to make sure that the length of the line is not 0
// The data is loaded into a string, which then needs to be converted either integers, or a char for the data entry.
fstream& operator>>(std::string fileName, Data & dataClass)
{
	fstream filePointer = dataClass.openFileIn(fileName);
	// The variables used to read from the file
	std::string offset, data, time, unixTime, buffer_length, buffer_tail; 
	// Looping through all of the data in the file
	while (!filePointer.eof()) 
	{
		// Getting the lines, splitting with a delimeter (which is the comma used in the saving process)
		std::getline(filePointer, offset, ','); 
		std::getline(filePointer, data, ',');
		std::getline(filePointer, buffer_length, ',');
		std::getline(filePointer, buffer_tail, ',');
		std::getline(filePointer, unixTime, ',');
		std::getline(filePointer, time, '\n');
		// Checking to make sure the line isn't blank, often found at the end of the file 
		if (!offset.length() == 0) 
		{
			// Outputting what has been read from the file
			cout << "Offset: \t" << offset << "\t";
			cout << "Data: \t" << data << "\t";
			cout << "Time: \t" << time << endl;
			// Converting the string to a char by taking the first (and only) character in the string. The offset is also converted to an integer to be used as an index.
			dataClass.buffer[atoi(offset.c_str())].data = data[0]; 
			// Converting the string into an integer and loading into the buffer array, the offset is also converted to an integer to be used as an index.
			dataClass.buffer[atoi(offset.c_str())].time = atoi(unixTime.c_str()); 
			dataClass.buffer_length = atoi(buffer_length.c_str());
			dataClass.buffer_tail = atoi(buffer_tail.c_str());
		}
	}
	filePointer.close(); // Finished reading: close the file 
	return filePointer;
}
