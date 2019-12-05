#include <iostream>
#include "Binary.h"
#include "Protocol.h"



void printVec(vector<int> inp, string mess)
{
	cout << mess << ": [ ";
	for (int i = 0; i < inp.size(); i++) { cout << inp[i] << " "; }
	cout << "]" << endl;
}



void APIToPhysical(std::string input)
{

	std::replace(input.begin(), input.end(), ' ', '_');
	Protokol p1(input);
	int sf = 0;
	int ul;
	while (sf != 1) {
		p1.divider();
		Binary FullFrame(p1.numberingSender());
		//        std::cout << p1.getFS() << std::endl;
		//        std::cout << p1.getF16() << std::endl;
		//        std::cout << p1.numbering() << std::endl;
		//        std::cout << p1.getFramecounter() << std::endl;
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
		//USE THIS AS THEIR FUNCTION        return FullFrame2.GetData();

				// GIVE FULLFRAME 2 TO PHYSICAL LAYER, THIS IS THE FINAL BIT STRING !!

	}
};

void PhysicalToAPI(std::vector<int> input)
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
		}
		else if (input == p2.ACKReq)
		{
			// USE THEIR FUNCTION HERE return previousControlFrame;
		}
		else
		{
			p2.numberingReceiver(p2.getData());
			p2.flagdetermineReceiver();
			p2.databytesDetermine();

			std::string fullMessage;

			if (p2.getsfReceiver() == 1)
			{
				addToFullMessage(p2.returnMessage());
				//USE THEIR FUNCTION HERE return fullMessageString;
				resetFullMessage();
				//USE THEIR FUNCTION HERE return ACK;
				setPreviousControlFrame(p2.ACK);
			}
			else
			{
				addToFullMessage(p2.returnMessage());
				//USE THEIR FUNCTION HERE return ACK;
				setPreviousControlFrame(p2.ACK);
			}
		}

	}

	else {

		//USE THEIR FUNCTION HERE return NACK;
		setPreviousControlFrame(p2.NACK);


	}

}



int main()
{

	return 0;
}
