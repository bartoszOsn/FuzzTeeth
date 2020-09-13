#pragma once

#include <math.h>

class SaturatorWavetable
{
public:
	SaturatorWavetable();
	SaturatorWavetable(int sampleNumber);
	~SaturatorWavetable();

	void initialise(int sampleNumber);
	float* getSamples();
	int getSampleNumber();

	void setGain(float gain);
	void setClip(float clip);

private:
	int sampleNumber;
	float* samples;

	float gain;
	float clip;

	void reCalc();
};