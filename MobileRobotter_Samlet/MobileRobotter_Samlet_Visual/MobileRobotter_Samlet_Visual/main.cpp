#include <iostream>
#include <string>
#include "application.h"
#include <thread>


int main()
{
	std::thread dataLink;
	application app;
	std::string input;


	std::cout << "Press [S] to send, or [R] to receive" << std::endl;
	std::cin >> input;

	while (true) {

		if (input == "R") {
			app.setState(1);
			std::cout << "Waiting to receive..." << std::endl;

			while (!app.hasReceived) {}
			app.hasReceived = false;
			//app.receiver("hdgSHdd"); // Protocol use here!! 
			input = "S";
		}

		else if (input == "S") {
			app.setState(0);
			std::cout << "Waiting to send..." << std::endl;
			 app.sender();// Protocol get from here!!
			input = "R";
		}
		else 
		{
			std::cout << "Wrong input! Press [S] to send, or [R] to receive" << std::endl;
			std::cin >> input;
		}
	
	}
	return 0;
}

