#pragma once

#include <assert.h>
#include <climits>

class DubADSR {
	int _samplingRate;
	float _attack;
	float _decay;
	float _sustain;
	float _release;
	int _actualSample;
	bool _isOn;

public:
	DubADSR(int samplingRate);
	~DubADSR();
	float getNextSample();
	void reset();
	void start();
	void stop();
	void updateAttack(float attackMs);
	void updateDecay(float decayMs);
	void updateSustain(float sustain);
	void updateRelease(float releaseMs);
};
