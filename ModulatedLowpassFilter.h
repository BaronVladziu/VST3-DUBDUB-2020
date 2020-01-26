#pragma once

#include <assert.h>

class ModulatedLowpassFilter {
	float _outputSample;

public:
	ModulatedLowpassFilter();
	~ModulatedLowpassFilter();
	float processSample(float inputSample, float modulation);
	void reset();
};
