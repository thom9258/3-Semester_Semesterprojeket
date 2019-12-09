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
		string j, q, w, d;
		cin >> j;
		q = j;
		getline(cin, j);
		w = j;
		d = q + w;
		return d;
	}

	else if (state == 0) {
		cout << "Du kan ikke sende";
	}
}

string application::receiver(string y)
{
	if (state == 0) {
		setState(1);
		cout << y << endl;
		return y;
	}
	else if (state == 1) {
		cout << "Du kan ikke modtage";


	}
}
