#pragma warning(disable: 4996)
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
	void Show();
	void Save();
	void Load();
private:
	unsigned long buffer_tail;
	unsigned long buffer_length;
	Message buffer[];
};
