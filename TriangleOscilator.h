#pragma once

#include <assert.h>
#include <cmath>

class TriangleOscilator {
	int _samplingRate;
	double _frequency = 0.0;
	double _phase = 0.0;

public:
	TriangleOscilator(int samplingRate);
	~TriangleOscilator();
	float getNextSample();
	void reset();
	void setFrequency(double frequency);
};
