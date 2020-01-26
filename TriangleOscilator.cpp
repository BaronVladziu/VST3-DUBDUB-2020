#include "TriangleOscilator.h"

TriangleOscilator::TriangleOscilator(int samplingRate)
	: _samplingRate(samplingRate)
{
	//Sanity check
	assert(samplingRate > 0);
}

TriangleOscilator::~TriangleOscilator() {}

float TriangleOscilator::getNextSample() {
	//Update phase
	_phase += _frequency / _samplingRate;
	if (_phase >= 1.0) {
		_phase -= 1.0;
	}

	//Sanity check
	assert(_phase >= 0);
	assert(_phase < 1.0);

	//Return sample
	if (_phase < 0.25) {
		return 4 * _phase;
	}
	else if (_phase < 0.75) {
		return 2 - 4 * _phase;
	}
	else {
		return -4 + 4 * _phase;
	}
}

void TriangleOscilator::reset() {
	_phase = 0.0;
}

void TriangleOscilator::setFrequency(double frequency) {
	//Sanity check
	assert(frequency > 0);

	//Update
	_frequency = frequency;
}
