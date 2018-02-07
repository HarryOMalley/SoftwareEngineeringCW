#pragma warning(disable: 4996) // This is to prevent the deprecation warnings to do with ctime
#include <string>
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
	void Save(std::string fileName) const;
	void Load(std::string fileName);
private:
	unsigned long buffer_tail;
	unsigned long buffer_length;
	Message buffer[];
};
