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
	string j, q, w, d;
	cin >> j;
	q = j;
	getline(cin, j);
	w = j;
	d = q + w;
	if (state == 0) {
		setState(1);
		return d;
	}
}

string application::receiver(string y)
{
	hasReceived = true;

	if (state == 1) {
		setState(0);
		cout << y << endl;
		return y;
	}
	else if (state == 0) {
		setState(0);

		return "You can't receive!";
	}
}
