//class menu:
//variables:
//Userinput
//constructor:
//run() -- which would be a while loop calling menu`
//functions:
//menu()
//input()
//// WOUL KEEP ALL INFO ABOUT BUFFER WITHIN DATA
//	cout << endl;
//cout << "Buffer Management Menu" << endl;
//cout << "----------------------" << endl;
//cout << "1. Produce a new message for the buffer" << endl;
//cout << "2. Consume a message from the buffer" << endl;
//cout << "3. View the contents of the buffer" << endl;
//cout << "4. Exit from the program" << endl << endl;
//
//// get the user's choice
//cout << "Enter your option: ";
//cin >> UserInput;
//cout << endl;
//
//// act on the user's input
//switch (UserInput) {
//case '1':
//	Produce(buffer, buffer_tail, buffer_length);
//	break;
//
//case '2':
//	Consume(buffer, buffer_tail, buffer_length);
//	break;
//
//case '3':
//	Show(buffer, buffer_tail, buffer_length);
//	break;
//
//case '4':
//	return 0;
//
//default:
//	cout << "Invalid entry" << endl << endl;
//	break;
//}
//	}
//}
//
//
//
//class data:
//variables:
//buffer
//buffer_tail
//buffer_length
//buffer_head
//
//functions:
//produce();
//show();
//consume();
//
//class disk:
//	// going to overload the operater within the data class to achieve saving and loading
//variables:
//file location etc
//
//functions:
//save()
//load()