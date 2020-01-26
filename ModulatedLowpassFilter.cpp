#include "ModulatedLowpassFilter.h"

ModulatedLowpassFilter::ModulatedLowpassFilter()
{
	reset();
}

ModulatedLowpassFilter::~ModulatedLowpassFilter() {}

float ModulatedLowpassFilter::processSample(float inputSample, float modulation) {
	//Check inputs
	assert(inputSample >= -1.0);
	assert(inputSample <= 1.0);
	assert(modulation >= -1.0);
	assert(modulation <= 1.0);

	//Calculate output sample
	float decay = (modulation + 1) / 2;
	assert(decay >= 0.0);
	assert(decay <= 1.0);
	_outputSample = decay * inputSample + (1 - decay) * _outputSample;

	//Return
	return _outputSample;
}

void ModulatedLowpassFilter::reset() {
	_outputSample = 0;
}
