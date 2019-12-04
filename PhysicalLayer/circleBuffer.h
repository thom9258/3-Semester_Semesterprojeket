#include "PhysicalLayer.h"  


class circleBuffer {
public:
	circleBuffer();
	circleBuffer(unsigned size);

	void write(double input);
	double read();

protected:
	std::vector<float> buffer;
	unsigned readIndex;
	unsigned writeIndex;
};
