#include "application.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

void application::setState(int k)
{
	state = k; // if n equals zero, then we are in reciever mode
}

int application::getState()
{
	return state;
}

string application::sender()
{
	if (state == 1) {
		// check state to see if the user is allowed to send data .
		// If state is 1 the function continue.
		string input, firstWord, restOfWords, entireSentence;
		cin >> input;
		firstWord = input;
		//takes the first word and saves it in q.
		getline(cin, input);
		//takes the rest of the words and saves them in w.
		restOfWords = input;
		// Putting all the words together and saves them in d.
		entireSentence = firstWord + restOfWords;
		return entireSentence;
		setState(0);
		cout << "State er nu 0 (modtager mode)" << endl;

	}

	else if (state == 0) {
		// check state to see if the user is allowed to send data.
		// If the state is 0 the user is not allowed to send.
		cout << "Du kan ikke sende" << endl;;
		setState(0);
		cout << "State er nu 0 (modtager mode)"<< endl;

	}

}

void application::receiver(string y)
{
	if (state == 0) {
		// check state to see if the user is allowed to send data.
		// If the state is 0 the user is  allowed to receive.
		cout << y << endl;
		cout << "Du er i modtager mode\n";
	
	}
	else if (state == 1) {
		// check state to see if the user is allowed to send data.
		// If the state is 1 the user is not allowed to receive.
		cout << "Du kan ikke modtage"<<endl;


	}
	setState(1);
	cout << "State er nu 1 (sender mode)"<<endl;
}
