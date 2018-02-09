#pragma warning(disable: 4996) // This is to prevent the deprecation warnings to do with ctime
#include <string>
using namespace std;
#define BUFFER_LENGTH 10
struct Message {
	unsigned char data;  // single byte of information to be sent
	time_t time;  // number of seconds since 1 January 1970
};
class Data
{
public:
	// Function prototypes
	Data();
	~Data();
	void Produce();
	void Consume();
	fstream openFileIn(std::string fileName);
	fstream openFileOut(std::string fileName);
	friend ostream& operator<<(ostream& os, const Data& dataClass);
	friend fstream& operator<<(std::string fileName, Data& dataClass);
	friend fstream& operator>>(std::string fileName, Data& dataClass);
private:
	// Variables that will be used in the program that need to be stored outside of the scope
	unsigned long buffer_tail;
	unsigned long buffer_length;
	Message buffer[BUFFER_LENGTH];
};
