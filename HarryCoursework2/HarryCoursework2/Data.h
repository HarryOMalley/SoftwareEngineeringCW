#pragma warning(disable: 4996) // This is to prevent the deprecation warnings to do with ctime
#include <string>
#define BUFFER_LENGTH 10
using namespace std;
struct Message {
	unsigned char data;  // single byte of information to be sent
	time_t time;  // number of seconds since 1 January 1970
};
class Data
{
public:
	Data();
	~Data();
	void Produce();
	void Consume();
	void Show() const;
	friend ostream& operator<<(ostream& os, const Data& dataClass);
	friend fstream& operator<<(std::string fileName, Data& dataClass);
	friend fstream& operator>>(std::string fileName, Data& dataClass);
private:
	unsigned long buffer_tail;
	unsigned long buffer_length;
	Message buffer[BUFFER_LENGTH];
};
