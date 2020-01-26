#pragma once

#include <assert.h>
#include <cmath>

class SineOscilator {
	const double PI = 3.141592653589793238463;

	int _samplingRate;
	double _frequency = 0;
	double _phase = 0.0;

public:
	SineOscilator(int samplingRate);
	~SineOscilator();
	float getNextSample();
	void reset();
	void setFrequency(double frequency);
};
