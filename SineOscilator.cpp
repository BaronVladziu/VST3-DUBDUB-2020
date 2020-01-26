#include "SineOscilator.h"

SineOscilator::SineOscilator(int samplingRate)
	: _samplingRate(samplingRate)
{
	//Sanity check
	assert(samplingRate > 0);
}

SineOscilator::~SineOscilator() {}

float SineOscilator::getNextSample() {
	//Update phase
	_phase += _frequency / _samplingRate;
	if (_phase >= 1.0) {
		_phase -= 1.0;
	}

	//Sanity check
	assert(_phase >= 0);
	assert(_phase < 1.0);

	//Return sample
	return std::sin(2 * PI * _phase);
}

void SineOscilator::reset() {
	_phase = 0.0;
}

void SineOscilator::setFrequency(double frequency) {
	//Sanity check
	assert(frequency > 0);

	//Update
	_frequency = frequency;
}
