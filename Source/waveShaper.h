#pragma once

#include "squareWavetable.h"
#include "SaturatorWavetable.h"

class WaveShaper
{
public:
	WaveShaper();
	WaveShaper(int wavetableSampleNumber);
	~WaveShaper();
	void initialise(int wavetableSampleNumber);
	float* getSamples();
	int getSampleNumber();

	float processSample(float sample);

	void setTeethSize(float size);
	void setTeethFrequency(float freq);
	void setTeethLowPassFrequency(float freq);
	void setTeethSkew(float skew);

	void setSaturationGain(float gain);
	void setSaturationClip(float clip);

	void setChangeEvent(std::function<void()> e);
private:
	int sampleNumber;
	float* samples;
	SquareWavetable squareWavetable;
	SaturatorWavetable saturatorWavetable;

	float teethSize;
	float teethFrequency;
	float teethSkew;

	std::function<void()> onChanged;

	void changed();
	void reCalc();
	void normaliseSamples();
	float getSkew(float x);
};