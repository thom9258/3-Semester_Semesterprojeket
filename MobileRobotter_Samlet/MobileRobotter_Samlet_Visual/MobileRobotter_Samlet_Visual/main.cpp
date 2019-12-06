#include <iostream>
#include <string>
#include <thread>
#include <algorithm>
#include "application.h"
#include "Binary.h"
#include "Protocol.h"
#include "PhysicalLayer.h"

application app;

void APPToPhysical(std::string input)
{

	std::replace(input.begin(), input.end(), ' ', '_');
	Protokol p1(input);
	int sf = 0;
	int ul;
	while (sf != 1) {
		p1.divider();
		Binary FullFrame(p1.numberingSender());

				//std::cout << p1.getFS() << std::endl;
		        //std::cout << p1.getF16() << std::endl;
		        //std::cout << p1.numberingSender() << std::endl;
		        //std::cout << p1.getFramecounter() << std::endl;
		p1.flagDetermineSender();
		sf = p1.getSF();
		ul = p1.getUL();
		Binary flag({ 0,0,ul,sf });
		FullFrame = FullFrame.BinaryAppend(FullFrame, flag);
		for (int i = 0; i < p1.getF16().length(); i++)
		{
			Binary singleChar(p1.getF16()[i]);
			FullFrame = FullFrame.BinaryAppend(FullFrame, singleChar);
		}
		std::string stringFrame = FullFrame.returnString();

		

		Binary FullFrame2(p1.SenderCRC(stringFrame));
		setPrevious(FullFrame2.GetData());

		std::cout << FullFrame2 << std::endl;
		// giving
		PhysicalLayer::sendBitString(FullFrame2.GetData());

	}
};

void PhysicalToAPP(std::vector<int> input)
{
	Protokol p2(input);
	if (p2.errorCheck(p2))
	{
		if (input == p2.ACK)
		{
			//End function
		}
		else if (input == p2.NACK)
		{
			// USE THEIR FUNCTION HERE return previousmessage;
			PhysicalLayer::sendBitString(previousmessage);
		}
		else if (input == p2.ACKReq)
		{
			// USE THEIR FUNCTION HERE return previousControlFrame;
			PhysicalLayer::sendBitString(previousControlFrame);
		}
		else
		{
			p2.numberingReceiver(p2.getData());
			p2.flagdetermineReceiver();
			p2.databytesDetermine();


			if (p2.getsfReceiver() == 1)
			{
				addToFullMessage(p2.returnMessage());
				//USE THEIR FUNCTION HERE return fullMessageString;
				app.receiver(fullMessageString);
				resetFullMessage();
				//USE THEIR FUNCTION HERE return ACK;
				PhysicalLayer::sendBitString(p2.ACK);
				setPreviousControlFrame(p2.ACK);
				p2.incframecounter();
			}
			else
			{
				addToFullMessage(p2.returnMessage());
				//USE THEIR FUNCTION HERE return ACK;
				PhysicalLayer::sendBitString(p2.ACK);
				setPreviousControlFrame(p2.ACK);
				p2.incframecounter();
			}
		}
	}

	else 
	{
		//USE THEIR FUNCTION HERE return NACK;
		PhysicalLayer::sendBitString(p2.NACK);
		setPreviousControlFrame(p2.NACK);
	}
}





int main()
{
	std::thread dataLink;
	
	std::string input;


	std::cout << "Press [S] to send, or [R] to receive" << std::endl;
	std::cin >> input;

	while (true) {
		if (input == "R") {
			std::cout << "Waiting to receive..." << std::endl;
			PhysicalLayer phy;
			phy.listenStartBit();
			std::cout << "hej" << std::endl;
			PhysicalToAPP(phy.listenToSound());
			app.setState(1);

			app.hasReceived = false;
			//app.receiver("hdgSHdd"); // Protocol use here!! 
			input = "S";
		}
		else if (input == "S")
		{
			app.setState(0);
			std::cout << "Waiting to send..." << std::endl;
			//std::cout << app.sender() << std::endl;
			APPToPhysical(app.sender());// Protocol get from here!!
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