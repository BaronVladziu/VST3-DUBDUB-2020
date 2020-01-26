#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DubADSR.h"
#include "ModulatedLowpassFilter.h"
#include "SineOscilator.h"
#include "TriangleOscilator.h"

//==============================================================================
struct DubDubSound : public SynthesiserSound
{
	DubDubSound() {}
	bool appliesToNote(int) override { return true; }
	bool appliesToChannel(int) override { return true; }
};

//==============================================================================
struct DubDubVoice : public SynthesiserVoice
{
	DubDubVoice() {
		_adsr = new DubADSR(getSampleRate());
		_triangleOscilator = new TriangleOscilator(getSampleRate());
		_upTriangleOscilator = new TriangleOscilator(getSampleRate());
		_lfo = new SineOscilator(getSampleRate());
		_lfo->reset();
		_lfo->setFrequency(15);
	}
	~DubDubVoice() {
		delete _adsr;
		delete _triangleOscilator;
		delete _upTriangleOscilator;
		delete _lfo;
	}
	bool canPlaySound(SynthesiserSound* sound) override {
		return dynamic_cast<DubDubSound*> (sound) != nullptr;
	}
	void startNote(int midiNoteNumber, float velocity,
			SynthesiserSound*, int /*currentPitchWheelPosition*/) override {
		_level = velocity * 0.1;
		auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
		_triangleOscilator->setFrequency(cyclesPerSecond);
		_triangleOscilator->reset();
		_upTriangleOscilator->setFrequency(2 * cyclesPerSecond);
		_upTriangleOscilator->reset();
		_adsr->start();
	}
	void stopNote(float /*velocity*/, bool allowTailOff) override {
		_adsr->stop();
		clearCurrentNote();
	}
	void pitchWheelMoved(int) override {}
	void controllerMoved(int, int) override {}
	void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override {
		while (--numSamples >= 0)
		{
			auto amplitude = _level * _adsr->getNextSample();
			auto currentSample = amplitude * (
				_upTriangleOscilator->getNextSample()
				+ _triangleOscilator->getNextSample()
			);
			float filteredSample = _lowpassFilter.processSample(
				currentSample,
				_lfo->getNextSample()
			);
			for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
				outputBuffer.addSample(i, startSample, filteredSample);
			++startSample;
		}
	}
	void updateAttack(float attackMs) {
		_adsr->updateAttack(attackMs);
	}
	void updateDecay(float decayMs) {
		_adsr->updateDecay(decayMs);
	}
	void updateSustain(float sustain) {
		_adsr->updateSustain(sustain);
	}
	void updateRelease(float releaseMs) {
		_adsr->updateRelease(releaseMs);
	}
	void updateModulationFrequency(int modulationFrequencyBPM) {
		_lfo->setFrequency(float(modulationFrequencyBPM) / 60);
	}
private:
	double _level;
	TriangleOscilator * _triangleOscilator;
	TriangleOscilator * _upTriangleOscilator;
	DubADSR * _adsr;
	ModulatedLowpassFilter _lowpassFilter;
	SineOscilator * _lfo;
};
//==============================================================================

class SynthAudioSource : public AudioSource
{
public:
	SynthAudioSource(MidiKeyboardState& keyState)
		: keyboardState(keyState)
	{
		for (auto i = 0; i < 10; ++i)
			synth.addVoice(new DubDubVoice());
		synth.addSound(new DubDubSound());
	}
	void setUsingSineWaveSound()
	{
		synth.clearSounds();
	}
	void prepareToPlay(int /*samplesPerBlockExpected*/, double sampleRate) override
	{
		synth.setCurrentPlaybackSampleRate(sampleRate);
	}
	void releaseResources() override {}
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override
	{
		bufferToFill.clearActiveBufferRegion();
		MidiBuffer incomingMidi;
		midiCollector.removeNextBlockOfMessages(incomingMidi, bufferToFill.numSamples);
		keyboardState.processNextMidiBuffer(incomingMidi, bufferToFill.startSample,
			bufferToFill.numSamples, true);
		synth.renderNextBlock(*bufferToFill.buffer, incomingMidi,
			bufferToFill.startSample, bufferToFill.numSamples);
	}
	void updateAttack(float attackMs) {
		for (auto i = 0; i < synth.getNumVoices(); ++i) {
			((DubDubVoice *)(synth.getVoice(i)))->updateAttack(attackMs);
		}
	}
	void updateDecay(float decayMs) {
		for (auto i = 0; i < synth.getNumVoices(); ++i) {
			((DubDubVoice*)(synth.getVoice(i)))->updateDecay(decayMs);
		}
	}
	void updateSustain(float sustain) {
		for (auto i = 0; i < synth.getNumVoices(); ++i) {
			((DubDubVoice*)(synth.getVoice(i)))->updateSustain(sustain / 100);
		}
	}
	void updateRelease(float releaseMs) {
		for (auto i = 0; i < synth.getNumVoices(); ++i) {
			((DubDubVoice*)(synth.getVoice(i)))->updateRelease(releaseMs);
		}
	}
	void updateModulationFrequency(int modulationFrequencyBPM) {
		for (auto i = 0; i < synth.getNumVoices(); ++i) {
			((DubDubVoice*)(synth.getVoice(i)))->updateModulationFrequency(modulationFrequencyBPM);
		}
	}
	MidiMessageCollector* getMidiCollector()
	{
		return &midiCollector;
	}
	MidiMessageCollector midiCollector;
private:
	MidiKeyboardState& keyboardState;
	Synthesiser synth;
};
