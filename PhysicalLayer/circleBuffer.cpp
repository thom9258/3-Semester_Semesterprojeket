#include "circleBuffer.h"
#include <iostream>


circleBuffer::circleBuffer(unsigned size) : buffer(size) {
	readIndex = 0;
	writeIndex = size - 1;
}
circleBuffer::circleBuffer(){}

void circleBuffer::write(double input) {
	buffer[writeIndex++] = input;
	if (writeIndex == buffer.size())
		writeIndex = 0;
}

double circleBuffer::read() {
	double val = buffer[readIndex++];
	if (readIndex == buffer.size())
		readIndex = 0;
	return val;
}