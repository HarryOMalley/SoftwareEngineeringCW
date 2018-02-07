// A program to demonstrate the operation of a circular buffer.
//
// General description
// A circular buffer is a type of first-in first-out queue, normally fixed in length
// and is used as a temporary store of information that needs to be transmitted 
// asynchronously from one process to another.
//
// Implementation details
// The circular buffer holds messages entered by the user which are to be sent to the
// screen. The operation of the buffer is controlled by a menu from which the user can
// choose one of the following: enter a new message, send (consume) a message from the
// buffer or display the contents of the buffer.
//
// The buffer is implemented as a fixed length array. Once all the elements in the array
// have been filled, the first element will need to be used again. As an example of the
// operation of the circular buffer, assume that there are 10 elements in the array,
// 9 messages have been entered by the producer, 6 have been consumed and then a further 5
// produced. The next message to be consumed (tail of the buffer) would be the 7th element
// in the array and the next message entered (head of the buffer) would become the 5th 
// element in the array.
//
// If the number of messages in the buffer is equal to the length of the array and a new
// message is entered, this simply overwrites the last message at the tail of the buffer. 
// This is termed an overflow.

#include <iostream>
#include <time.h>
#include "Data.h"
#include "Menu.h"
using namespace std;

// the format of the messages in the buffer
//struct Message {
//	unsigned char data;  // single byte of information to be sent
//	time_t time;  // number of seconds since 1 January 1970
//};

// the length of the fixed array to be used for the FIFO buffer - must be at least one
// and no greater than half the maximum value allowed in an unsigned long (see
// the file limits.h)
#define BUFFER_LENGTH 10

// function prototypes
//void Produce(Message*, unsigned long&, unsigned long&);
//void Consume(const Message*, unsigned long&, unsigned long&);
//void Show(const Message*, unsigned long, unsigned long);


// Control the entering, sending and displaying of messages in the buffer.
// Arguments: None
// Returns: 0 on completion
int main()
{
	Menu menu;
}
//	
//	Message buffer[BUFFER_LENGTH];   // the message buffer
//	unsigned long buffer_tail = 0;  // position of the tail in the message buffer -
//									// the next message will be consumed from here
//	unsigned long buffer_length = 0;  // number of messages in the buffer
//	char UserInput;
//
//	// loop until the user wishes to exit
//	while (1) {
//
//		// show the menu of options
//		cout << endl;
//		cout << "Buffer Management Menu" << endl;
//		cout << "----------------------" << endl;
//		cout << "1. Produce a new message for the buffer" << endl;
//		cout << "2. Consume a message from the buffer" << endl;
//		cout << "3. View the contents of the buffer" << endl;
//		cout << "4. Exit from the program" << endl << endl;
//
//		// get the user's choice
//		cout << "Enter your option: ";
//		cin >> UserInput;
//		cout << endl;
//
//		// act on the user's input
//		switch (UserInput) {
//		case '1':
//			Produce(buffer, buffer_tail, buffer_length);
//			break;
//
//		case '2':
//			Consume(buffer, buffer_tail, buffer_length);
//			break;
//
//		case '3':
//			Show(buffer, buffer_tail, buffer_length);
//			break;
//
//		case '4':
//			return 0;
//
//		default:
//			cout << "Invalid entry" << endl << endl;
//			break;
//		}
//	}
//}
//
//
//
//// Create a new message and add it to the head of the buffer.
//// The data for the message is obtained from the user and a time stamp is obtained from the
//// time() function in the C standard library. 
//// Arguments:
////   (1) start of the buffer
////   (2) position of the tail of the buffer
////   (3) number of messages in the buffer
//// Returns: void
//void Produce(Message* buffer, unsigned long& buffer_tail, unsigned long& buffer_len)
//{
//	time_t current_time;
//	unsigned long buffer_head;
//
//	// find the element of the buffer in which to store the message
//	buffer_head = (buffer_tail + buffer_len) % BUFFER_LENGTH;
//
//	// get the value of the data for the message from the user
//	cout << "Add new data" << endl;
//	cout << "------------" << endl;
//	cout << "Enter data: ";
//	cin >> buffer[buffer_head].data;
//	cout << endl;
//
//	// get the value of the time for the message
//	buffer[buffer_head].time = time(&current_time);
//
//	// if no buffer overflow has occurred, adjust the buffer length
//	if (buffer_len < BUFFER_LENGTH) {
//		buffer_len++;
//	}
//
//	// if a buffer overflow has occurred, display an error statement
//	else {
//		buffer_tail = (buffer_tail + 1) % BUFFER_LENGTH;
//		cout << "Overflow error" << endl;
//	}
//}
//
//
//// Pop the message at the head of the buffer and display it.
//// Arguments:
////   (1) start of the buffer
////   (2) position of the tail of the buffer
////   (3) number of messages in the buffer
//// Returns: void
//void Consume(const Message* buffer, unsigned long& buffer_tail, unsigned long& buffer_len)
//{
//	// if the buffer is empty, display an error statement
//	if (buffer_len == 0) {
//		cout << "No messages in the buffer" << endl;
//	}
//
//	// if the buffer is not empty, display the message at the tail, remove the message by
//	// advancing the tail of buffer offset in a circular manner and adjust the buffer length
//	else {
//		cout << endl;
//		cout << "Offset Data        Time" << endl;
//		cout << buffer_tail << "\t";
//		cout << buffer[buffer_tail].data << "\t";
//		cout << ctime(&buffer[buffer_tail].time);
//		buffer_tail = (buffer_tail + 1) % BUFFER_LENGTH;
//		buffer_len--;
//	}
//}
//
//
//
//// Display all of the messages in the buffer.
//// Arguments:
////   (1) start of the buffer
////   (2) position of the tail of the buffer
////   (3) number of messages in the buffer
//// Returns: void
//void Show(const Message* buffer, unsigned long buffer_tail, unsigned long buffer_len)
//{
//	unsigned long count; // count through the messages being displayed
//	unsigned long buffer_head;  // the position at which the next message would be pushed
//
//								// if the buffer is empty, display an error statement
//	if (buffer_len == 0) {
//		cout << "No messages in the buffer" << endl;
//	}
//
//	// if the buffer is not empty, display all the messages in the buffer
//	else {
//		// display a title
//		cout << endl;
//		cout << "Offset Data        Time" << endl;
//
//		// display messages if they are sequential in the array
//		buffer_head = (buffer_tail + buffer_len) % BUFFER_LENGTH;
//		if (buffer_tail < buffer_head) {
//			for (count = buffer_tail; count<buffer_head; count++) {
//				cout << count << "\t";
//				cout << buffer[count].data << "\t";
//				cout << ctime(&buffer[count].time);
//			}
//		}
//
//		// display messages if part are at the end of the array and the remainder at the start
//		else {
//			for (count = buffer_tail; count<BUFFER_LENGTH; count++) {
//				cout << count << "\t";
//				cout << buffer[count].data << "\t";
//				cout << ctime(&buffer[count].time);
//			}
//			for (count = 0; count<buffer_head; count++) {
//				cout << count << "\t";
//				cout << buffer[count].data << "\t";
//				cout << ctime(&buffer[count].time);
//			}
//		}
//	}
//}