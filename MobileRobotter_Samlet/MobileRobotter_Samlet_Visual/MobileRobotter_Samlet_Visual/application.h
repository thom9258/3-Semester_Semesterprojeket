#include <string>

using namespace std;
class application
{
public:
	application(void) {};

	// decides if you can send or recieve (1 = send, 0 = recieve)
	void setState(int n);

	int getState();
	
	// inputs string from terminal
	string sender();

	// outputs string to terminal
	void receiver(string h);


	bool state;
	// State determine whether the sender and receiver function can receive or send. 
	// If state is 0 then the user can only receive data while if the state is 1 the user can only send data

};