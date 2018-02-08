#include <iostream>

#include "Data.h"
#include <time.h>
#include "Menu.h"
#include <fstream>

#define BUFFER_LENGTH 10
using namespace std;


Data::Data()
{
	//Message buffer[BUFFER_LENGTH];
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

void Data::Save(std::string fileName) const
{
	unsigned long count; // count through the messages being displayed
	unsigned long buffer_head;  // the position at which the next message would be pushed
	fstream FilePointer;
	fileName = fileName + ".dat";
	FilePointer.open(fileName, ios::out);
	buffer_head = (buffer_tail + buffer_length) % BUFFER_LENGTH;
	if (buffer_tail < buffer_head) {
		for (count = buffer_tail; count < buffer_head; count++) {
			FilePointer << count << ",";
			FilePointer << buffer[count].data << ",";
			FilePointer << ctime(&buffer[count].time) << ",";
		}
	}

	// display messages if part are at the end of the array and the remainder at the start
	else {
		for (count = buffer_tail; count < BUFFER_LENGTH; count++) {
			FilePointer << count << ",";
			FilePointer << buffer[count].data << ",";
			FilePointer << ctime(&buffer[count].time) << ",";
		}
		for (count = 0; count < buffer_head; count++) {
			FilePointer << count << ",";
			FilePointer << buffer[count].data << ",";
			FilePointer << ctime(&buffer[count].time) << ",";
		}
	}
	FilePointer.close();
}

void Data::Load(std::string fileName)
{
	fstream FilePointer;
	fileName = fileName + ".dat";
	// Open the file again, this time for reading
	FilePointer.open(fileName, ios::in);
	if (!FilePointer.good()) {
		cout << "FATAL ERROR";
		exit(1);
	}
std:string offset, data, time, bufferData;
	while (!FilePointer.eof())
	{
		std::getline(FilePointer, offset, ',');
		std::getline(FilePointer, data, ',');
		std::getline(FilePointer, time, ',');
		bufferData = offset + "\t" + data + "\t" + time + "\n";
		cout << "offset: " << offset << "\t";
		cout << "data: " << data << "\t";
		cout << "time:" << time << endl;
	}
	cout << "\nJust opened " << fileName << " for READING ";
	//for (int i = 0; i < 100; i++) {
	//	FilePointer >> NumberRead; // Read data
	//	cout << NumberRead << " " << endl;
	//}
	FilePointer.close(); // finished reading: close the file 

}
//std::fstream& operator>>(std::fstream& is, Data& d)
//{
//	std::string zipcode;
//	if (std::getline(is, zipcode, ',') &&
//		std::getline(is, d.city, ',') &&
//		std::getline(is, d.state))
//	{
//		d.zipCode = std::stoi(zipcode);
//	}
//
//	return is;
//}