#include <iostream>
#include <fstream>
#include <time.h>
#include "Menu.h"
#include "Data.h"
#include "string"

#define BUFFER_LENGTH 10
using namespace std;

Data::Data()
{
	buffer_tail = 0;
	buffer_length = 0;
}


Data::~Data()
{
}

void Data::Produce()
{
	time_t current_time;
	unsigned long buffer_head;

	// find the element of the buffer in which to store the message
	buffer_head = (buffer_tail + buffer_length) % BUFFER_LENGTH;

	// get the value of the data for the message from the user
	cout << "Add new data" << endl;
	cout << "------------" << endl;
	cout << "Enter data: ";
	cin >> buffer[buffer_head].data;
	cout << endl;

	// get the value of the time for the message
	buffer[buffer_head].time = time(&current_time);

	// if no buffer overflow has occurred, adjust the buffer length
	if (buffer_length < BUFFER_LENGTH) {
		buffer_length++;
	}

	// if a buffer overflow has occurred, display an error statement
	else {
		buffer_tail = (buffer_tail + 1) % BUFFER_LENGTH;
		cout << "Overflow error" << endl;
	}
}

void Data::Consume()
{
	// if the buffer is empty, display an error statement
	if (buffer_length == 0) {
		cout << "No messages in the buffer" << endl;
	}

	// if the buffer is not empty, display the message at the tail, remove the message by
	// advancing the tail of buffer offset in a circular manner and adjust the buffer length
	else {
		cout << endl;
		cout << "Offset Data        Time" << endl;
		cout << buffer_tail << "\t";
		cout << buffer[buffer_tail].data << "\t";
		cout << ctime(&buffer[buffer_tail].time);
		buffer_tail = (buffer_tail + 1) % BUFFER_LENGTH;
		buffer_length--;
	}
}

void Data::Show() const
{
	unsigned long count; // count through the messages being displayed
	unsigned long buffer_head;  // the position at which the next message would be pushed

								// if the buffer is empty, display an error statement
	if (buffer_length == 0) {
		cout << "No messages in the buffer" << endl;
	}

	// if the buffer is not empty, display all the messages in the buffer
	else {
		// display a title
		cout << endl;
		cout << "Offset Data        Time" << endl;

		// display messages if they are sequential in the array
		buffer_head = (buffer_tail + buffer_length) % BUFFER_LENGTH;
		if (buffer_tail < buffer_head) {
			for (count = buffer_tail; count < buffer_head; count++) {
				cout << count << "\t";
				cout << buffer[count].data << "\t";
				cout << ctime(&buffer[count].time);
			}
		}

		// display messages if part are at the end of the array and the remainder at the start
		else {
			for (count = buffer_tail; count < BUFFER_LENGTH; count++) {
				cout << count << "\t";
				cout << buffer[count].data << "\t";
				cout << ctime(&buffer[count].time);
			}
			for (count = 0; count < buffer_head; count++) {
				cout << count << "\t";
				cout << buffer[count].data << "\t";
				cout << ctime(&buffer[count].time);
			}
		}
	}
}

ostream & operator<<(ostream & os, const Data & dataClass)
{
	unsigned long count; // count through the messages being displayed
	unsigned long buffer_head;  // the position at which the next message would be pushed

								// if the buffer is empty, display an error statement
	if (dataClass.buffer_length == 0) {
		cout << "No messages in the buffer" << endl;
	}

	// if the buffer is not empty, display all the messages in the buffer
	else {
		// display a title
		cout << endl;
		cout << "Offset Data        Time" << endl;

		// display messages if they are sequential in the array
		buffer_head = (dataClass.buffer_tail + dataClass.buffer_length) % BUFFER_LENGTH;
		if (dataClass.buffer_tail < buffer_head) {
			for (count = dataClass.buffer_tail; count < buffer_head; count++) {
				cout << count << "\t";
				cout << dataClass.buffer[count].data << "\t";
				cout << ctime(&dataClass.buffer[count].time);
			}
		}

		// display messages if part are at the end of the array and the remainder at the start
		else {
			for (count = dataClass.buffer_tail; count < BUFFER_LENGTH; count++) {
				cout << count << "\t";
				cout << dataClass.buffer[count].data << "\t";
				cout << ctime(&dataClass.buffer[count].time);
			}
			for (count = 0; count < buffer_head; count++) {
				cout << count << "\t";
				cout << dataClass.buffer[count].data << "\t";
				cout << ctime(&dataClass.buffer[count].time);
			}
		}
	}
	return os;
}

fstream& operator<<(std::string fileName, Data & dataClass)
{
	fileName = fileName + ".dat";
	// Open the file again, this time for reading
	fstream filePointer;
	filePointer.open(fileName, ios::out);;
	if (!filePointer.good()) {
		cout << "FATAL ERROR";
		exit(1);
	}
	unsigned long count; // count through the messages being displayed
	unsigned long buffer_head;  // the position at which the next message would be pushed
	buffer_head = (dataClass.buffer_tail + dataClass.buffer_length) % BUFFER_LENGTH;
	if (dataClass.buffer_tail < buffer_head) {
		for (count = dataClass.buffer_tail; count < buffer_head; count++) {
			filePointer << count << ",";
			filePointer << dataClass.buffer[count].data << ",";
			filePointer << dataClass.buffer_length << ",";
			filePointer << dataClass.buffer_tail << ",";
			filePointer << dataClass.buffer[count].time << ",";
			filePointer << ctime(&dataClass.buffer[count].time);
		}
	}

	// display messages if part are at the end of the array and the remainder at the start
	else {
		for (count = dataClass.buffer_tail; count < BUFFER_LENGTH; count++) {
			filePointer << count << ",";
			filePointer << dataClass.buffer[count].data << ",";
			filePointer << dataClass.buffer_length << ",";
			filePointer << dataClass.buffer_tail << ",";
			filePointer << dataClass.buffer[count].time << ",";
			filePointer << ctime(&dataClass.buffer[count].time);

		}
		for (count = 0; count < buffer_head; count++) {
			filePointer << count << ",";
			filePointer << dataClass.buffer[count].data << ",";
			filePointer << dataClass.buffer_length << ",";
			filePointer << dataClass.buffer_tail << ",";
			filePointer << dataClass.buffer[count].time << ",";
			filePointer << ctime(&dataClass.buffer[count].time);
		}
	}
	filePointer.close();

	return filePointer;
}

fstream& operator>>(std::string fileName, Data & dataClass)
{
	fileName = fileName + ".dat";
	// Open the file again, this time for reading
	fstream filePointer;
	filePointer.open(fileName, ios::in);
	if (!filePointer.good()) {
		cout << "FATAL ERROR";
		exit(1);
	}
	std::string offset, data, time, unixTime, buffer_length, buffer_tail; // The variables used to read from the file
	int intOffset, intUnixTime; // The variables used 
	char charData;
	unsigned long count = 0; // count through the messages being displayed
	unsigned long buffer_head;	// the position at which the next message would be pushed
	unsigned long intbuffer_length;
	unsigned long intbuffer_tail;
	while (!filePointer.eof()) // Looping through all of the data in the file
	{
		std::getline(filePointer, offset, ','); // Getting the lines, splitting with a delimeter (which is the comma used in the saving process)
		std::getline(filePointer, data, ',');
		std::getline(filePointer, buffer_length, ',');
		std::getline(filePointer, buffer_tail, ',');
		std::getline(filePointer, unixTime, ',');
		std::getline(filePointer, time, '\n');
		if (!offset.length() == 0) // Checking to see if there is a blank line, often found at the end of the file
		{
			cout << "offset: " << offset << "\t";
			cout << "data: " << data << "\t";
			cout << "time:" << time << endl;
			charData = data[0]; // Converting the string to a char by taking the first (and only) character in the string
			intbuffer_length = atoi(buffer_length.c_str());
			intbuffer_tail = atoi(buffer_tail.c_str());
			intUnixTime = atoi(unixTime.c_str());
			dataClass.buffer[count].data = charData;
			dataClass.buffer[count].time = intUnixTime;	
			dataClass.buffer_length = intbuffer_length;
			dataClass.buffer_tail = intbuffer_tail;
		}			
		count++;
	}

	filePointer.close(); // finished reading: close the file 
	return filePointer;
}
