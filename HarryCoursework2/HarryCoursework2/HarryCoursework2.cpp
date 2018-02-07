// HarryCoursework2.cpp : Defines the entry point for the console application.
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

int main()
{
	Menu menu;
}