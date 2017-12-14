// A program to demonstrate the operation of a circular buffer.

// General description

// A circular buffer is a type of first-in first-out queue, normally fixed in length
// and is used as a temporary store of information that needs to be transmitted 
// asynchronously from one process to another.

// Implementation details

// The circular buffer holds messages entered by the user which are to be sent to the
// screen. The operation of the buffer is controlled by a menu from which the user can
// choose one of the following: enter a new message, send (consume) a message from the
// buffer or display the contents of the buffer.

// The buffer is implemented as a fixed length array. Once all the elements in the array
// have been filled, the first element will need to be used again. As an example of the
// operation of the circular buffer, assume that there are 10 elements in the array,
// 9 messages have been entered by the producer, 6 have been consumed and then a further 5
// produced. The next message to be consumed (tail of the buffer) would be the 7th element
// in the array and the next message produced (head of the buffer) would become the 5th 
// element in the array.

// If the number of messages in the buffer is equal to the length of the array and a new
// message is entered, this simply overwrites the last message at the tail of the buffer. 
// This is termed an overflow.

#include <iostream>
#include <time.h>
using namespace std;

// the format of the messages in the buffer
struct Message {
	unsigned char data;  // single byte of information to be sent
	time_t time;  // number of seconds since 1 January 1970
};

// the length of the fixed array - must be at least unity and no greater than half the
// maximum value allowed in an unsigned long (see the file limits.h)
#define BUFFER_LENGTH 10

// function prototypes
void Produce(Message *buffer, unsigned long *buffer_tail, unsigned long *buffer_length);
void Consume(Message *buffer, unsigned long &buffer_tail, unsigned long &buffer_length);
void Show(Message buffer[BUFFER_LENGTH], unsigned long buffer_tail, unsigned long buffer_length);

// Control the entering, sending and displaying of messages in the buffer.
// Arguments: None
// Returns: 0 on completion
int main()
{
	Message buffer[BUFFER_LENGTH];   // the message buffer
	unsigned long buffer_tail = 0;  // position of the tail in the message buffer
									// the next message will be consumed from here
	unsigned long buffer_length = 0;  // number of messages in the buffer
	char UserInput;

	// loop until the user wishes to exit
	while (1) {

		// show the menu of options
		cout << endl;
		cout << "Buffer Management Menu" << endl;
		cout << "----------------------" << endl;
		cout << "1. Produce a new message for the buffer" << endl;
		cout << "2. Consume a message from the buffer" << endl;
		cout << "3. View the contents of the buffer" << endl;
		cout << "4. Exit from the program" << endl << endl;

		// get the user's choice
		cout << "Enter your option: ";
		cin >> UserInput;
		cout << endl;

		// act on the user's input
		switch (UserInput) {
		case '1':
			Produce(buffer, &buffer_tail, &buffer_length); // cant put an ampersand
			break;

		case '2':
			Consume(buffer, buffer_tail, buffer_length);
			break;

		case '3':
			Show(buffer, buffer_tail, buffer_length);
			break;

		case '4':
			return 0;

		default:
			cout << "Invalid entry" << endl << endl;
			break;
		}
	}
}
// Produce a new message and add it to the head of the buffer.
// The data for the message is obtained from the user and a time stamp is obtained from the
// time() function in the C standard library. 
// Arguments:
//   (1) start of the buffer
//   (2) position of the tail of the buffer
//   (3) number of messages in the buffer
// Returns: void
void Produce(Message *buffer, unsigned long *buffer_tail, unsigned long *buffer_length)
{
	time_t current_time;
	unsigned long buffer_head;  // the head of the buffer in which to store the message
								// find the element of the buffer in which to store the message
	if (*buffer_length < BUFFER_LENGTH) // Checking whether the buffer is full
	{
		if ((*buffer_length + *buffer_tail) < BUFFER_LENGTH) // Calculating the head of the buffer, checking whether the buffer has looped back around
		{
			buffer_head = *buffer_length + *buffer_tail; 
		}
		else // This happens if the head or tail have looped around to the beginning again
		{
			buffer_head = *buffer_length + *buffer_tail - BUFFER_LENGTH;
		}
	}
	else // If the buffer is full, then the buffer tail is incremented to overwrite the oldest data
	{
		buffer_head = *buffer_length + *buffer_tail - BUFFER_LENGTH;
		*buffer_tail += 1;
	}
	// get the value of the data for the message from the user
	cout << "Please enter something: ";
	cin >> buffer[buffer_head].data;
	cout << endl;
	// get the value of the time for the message
	current_time = time(0);
	buffer[buffer_head].time = current_time;
	// if no buffer overflow has occurred, adjust the buffer length
	if (*buffer_length < BUFFER_LENGTH)
	{
		*buffer_length += 1;
	}
	else // if a buffer overflow has occurred, display an error statement
	{
		cout << "The Buffer has overflowed, the oldest data has been overwritten." << endl;
	}
}
// Consume the message at the tail of the buffer.
// The message at the tail of the buffer is first displayed and then removed.
// Arguments:
//   (1) start of the buffer
//   (2) position of the tail of the buffer
//   (3) number of messages in the buffer
// Returns: void
void Consume(struct Message *buffer, unsigned long &buffer_tail, unsigned long &buffer_length)
{
	// if the buffer is empty, display an error statement
	if (buffer_length == 0)
	{
		cout << "The buffer is empty.";
	}
	else			// if the buffer is not empty, display the message at the tail, remove the message by
	{				// advancing the tail of buffer offset in a circular manner and adjust the buffer length
		cout << buffer[buffer_tail].data;
		buffer[buffer_tail].data = NULL;
		if (buffer_tail < BUFFER_LENGTH)
		{
			buffer_tail++;
			buffer_length--;
		}
		else
		{
			buffer_tail = 0;
			buffer_length--;
		}
	}
}
// Display all of the messages in the buffer.
// Arguments:
//   (1) start of the buffer
//   (2) position of the tail of the buffer
//   (3) number of messages in the buffer
// Returns: void
void Show(Message buffer[BUFFER_LENGTH], unsigned long buffer_tail, unsigned long buffer_length)
{
	unsigned long count; // count through the messages being displayed  
	unsigned long buffer_head;  // the head element of the buffer
	// if the buffer is empty, display an error statement
	if (buffer_length == 0)
	{
		cout << "The buffer is empty." << endl;
	}
	else // if the buffer is not empty, display all the messages in the buffer
	{
		for (count = 0; count < BUFFER_LENGTH; count++) // Incrementing through the buffer to display all of the messages
		{
			cout << buffer[count].data;
		}
		cout << endl;
	}
}