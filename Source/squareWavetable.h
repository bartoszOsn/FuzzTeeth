#pragma once

#include <math.h>
#include "JuceHeader.h"

class SquareWavetable
{
public:
	SquareWavetable();
	SquareWavetable(int sampleNumber);
	~SquareWavetable();

	void initialise(int sampleNumber);
	float* getSamples();
	int getSampleNumber();
	float get(float x);

	void setLowPassFrequency(float freq);

private:
	///<summary>Array of raw samples</summary>
	///<remarks>It contains more samples than sampleNumber. To work on samples with sampleNumber number use <see cref="SquareWavetable::getSamples" /></remarks>
	float* samples;

	///<summary>Number of samples</summary>
	int sampleNumber;

	///<summary>Starting index where subarray of samples which is designed for working on it is</summary>
	int startIndex;
	///<summary>Ending index where subarray of samples which is designed for working on it is</summary>
	int endIndex;

	///<summary>Object for low pass filter</summary>
	juce::IIRFilter lowPassFilter;

	void reCalc();

	void fillArray();
	float getIndex(float x);
};