#include "DubADSR.h"

DubADSR::DubADSR(int samplingRate)
	: _samplingRate(samplingRate)
{
	//Sanity check
	assert(samplingRate > 0);

	_attack = 0.02 * _samplingRate;
	_decay = 0.1 * _samplingRate;
	_sustain = 0.8;
	_release = 0.3 * _samplingRate;

	//Sanity check
	assert(_attack > 0);
	assert(_decay > 0);
	assert(_sustain >= 0);
	assert(_sustain <= 1);
	assert(_release > 0);
	
	//Initialize state
	reset();
}

DubADSR::~DubADSR() {}

float DubADSR::getNextSample() {
	//Sanity check
	if (_actualSample < 0) {
		_actualSample = INT_MAX;
	}
	assert(_actualSample >= 0);

	//Calculate output value
	float outputValue;
	if (_isOn) {
		if (_actualSample < _attack) {
			outputValue = float(_actualSample) / _attack;
		}
		else if (_actualSample < _attack + _decay) {
			outputValue = 1.0 - (float(_actualSample - _attack) / _decay) * (1.0 - _sustain);
		}
		else {
			outputValue = _sustain;
		}
	}
	else {
		if (_actualSample < _release) {
			outputValue = _sustain * (1.0 - float(_actualSample) / _release);
		}
		else {
			outputValue = 0;
		}
	}

	//Sanity check
	assert(outputValue >= 0);
	assert(outputValue <= 1);

	//Update state
	_actualSample++;

	//Return
	return outputValue;
}

void DubADSR::reset() {
	_actualSample = INT_MAX;
	assert(_actualSample >= 0);
	_isOn = false;
}

void DubADSR::start() {
	_actualSample = 0;
	_isOn = true;
}

void DubADSR::stop() {
	_actualSample = 0;
	_isOn = false;
}

void DubADSR::updateAttack(float attackMs) {
	//Check input
	assert(attackMs >= 0);

	_attack = attackMs / 1000 * _samplingRate;
}

void DubADSR::updateDecay(float decayMs) {
	//Check input
	assert(decayMs >= 0);

	_decay = decayMs / 1000 * _samplingRate;
}

void DubADSR::updateSustain(float sustain) {
	//Check input
	assert(sustain >= 0);
	assert(sustain <= 1);

	_sustain = sustain;
}

void DubADSR::updateRelease(float releaseMs) {
	//Check input
	assert(releaseMs >= 0);

	_release = releaseMs / 1000 * _samplingRate;
}
