// last changed: 09/12/19

#include <iostream>
#include <string>
#include <thread>
#include <algorithm>
#include "application.h"
#include "Binary.h"
#include "Protocol.h"
#include "PhysicalLayer.h"

// instantiate app
application app;


// dataLink layer, converting input from app into output given to physical
void APPToPhysical(std::string input)
{
	while (canSendFrame == false) {}

	// make sure there are no spaces in the transmitted message
	std::replace(input.begin(), input.end(), ' ', '_');

	// instantiate protocol object
	Protokol p1(input);
	int sf = 0;
	int ul;
	while (sf != 1) {

		// is a return function and might not be needed here?
		p1.divider();

		Binary FullFrame(p1.numberingSender());

		// debug
		//std::cout << p1.getFS() << std::endl;
		//std::cout << p1.getF16() << std::endl;
        //std::cout << p1.numberingSender() << std::endl
		//std::cout << p1.getFramecounter() << std::endl;

		// determine the flag nibble
		p1.flagDetermineSender();
		sf = p1.getSF();
		ul = p1.getUL();
		Binary flag({ 0,0,ul,sf });

		// append numbering onto data length
		FullFrame = FullFrame.BinaryAppend(FullFrame, flag);

		// convert the 16 first char's in the string into binary and append
		for (int i = 0; i < p1.getF16().length(); i++)
		{
			Binary singleChar(p1.getF16()[i]);
			FullFrame = FullFrame.BinaryAppend(FullFrame, singleChar);
		}

		//  create crc rest and append onto frame
		std::string stringFrame = FullFrame.returnString();
		Binary FullFrame2(p1.SenderCRC(stringFrame));

		// remember the sent frame in a buffer
		setPrevious(FullFrame2.GetData());

		// debug
		//std::cout << FullFrame2 << std::endl;

		// give the string to the physical layer
		PhysicalLayer::sendBitString(FullFrame2.GetData());
		updateFrameDelay(false);
	}
};

// dataLink layer, converting input from physical into output given to the app
void PhysicalToAPP(std::vector<int> input)
{
	// object instantiation
	Protokol p2(input);
	// check if the recieved frame is readable
	if (p2.errorCheck(p2))
	{
		if (input == p2.ACK)
		{
			updateFrameDelay(true);
			//End function
		}
		else if (input == p2.NACK)
		{
			// resend frame from buffer
			PhysicalLayer::sendBitString(previousmessage);
		}
		else if (input == p2.ACKReq)
		{
			// resend control frame from buffer
			PhysicalLayer::sendBitString(previousControlFrame);
		}
		else // if the incoming message is a recieved data frame
		{
			// determine the amount of data in the recieved frame
			p2.numberingReceiver(p2.getData());
			p2.flagdetermineReceiver();
			p2.databytesDetermine();

			// determine if the recieved message is the last
			if (p2.getsfReceiver() == 1)
			{
				addToFullMessage(p2.returnMessage());
				// delive the full message to app
				app.receiver(fullMessageString);
				resetFullMessage();
				//send ack
				PhysicalLayer::sendBitString(p2.ACK);
				setPreviousControlFrame(p2.ACK);
				p2.incframecounter();
			}
			else
			{
				// save the recieved data
				addToFullMessage(p2.returnMessage());
				// send ack
				PhysicalLayer::sendBitString(p2.ACK);
				setPreviousControlFrame(p2.ACK);
				p2.incframecounter();
			}
		}
	}
	else // if the recieved frame is unreadable
	{
		//send a NACK
		PhysicalLayer::sendBitString(p2.NACK);
		setPreviousControlFrame(p2.NACK);
	}

}

// application layer
int main()
{
	// do we use this?
	//std::thread dataLink;
	
	std::string input;

	std::cout << "Press [S] to send, or [R] to receive" << std::endl;
	std::cin >> input;
	if (input == "S") {
		app.setState(1);
	}
	else if(input=="R"){
		app.setState(0);
	}
	// always run this code
	while (true) {
		// check if the user wants to start as reciever or sender
		if (input == "R") {
			
			std::cout << "Waiting to receive..." << std::endl;
			// start listening
			PhysicalLayer phy;
			phy.listenStartBit();

			// debug
			//std::cout << "listening has started" << std::endl;
			 PhysicalToAPP(phy.listenToSound());
			
	
			input = "S";
		}
		else if (input == "S")
		{
			std::cout << "Waiting to send..." << std::endl;
			// deliver message to datalink layer
			std::string nytInput;
			std::cin >> nytInput;
			APPToPhysical(app.sender(nytInput));
			
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