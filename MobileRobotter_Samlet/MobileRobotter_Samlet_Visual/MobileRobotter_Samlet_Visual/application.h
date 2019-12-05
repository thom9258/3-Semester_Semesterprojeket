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
	string receiver(string h);


	bool state = 0;
	bool hasReceived = false;
};