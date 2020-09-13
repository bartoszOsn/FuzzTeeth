#include "SaturatorWavetable.h"

///<summary>parameterless constructor</summary>
SaturatorWavetable::SaturatorWavetable()
{
}

///<summary>Constructor which calls <see cref="SaturatorWavetable::initialise" /></summary>
SaturatorWavetable::SaturatorWavetable(int sampleNumber)
{
	initialise(sampleNumber);
}
///<summary>Destructor</summary>
SaturatorWavetable::~SaturatorWavetable()
{
	delete[] samples;
}

///<summary>Initialises wavetable</summary>
///<param name="sampleNumber">How many samples should this wavetable have?</param>
void SaturatorWavetable::initialise(int sampleNumber)
{
	this->sampleNumber = sampleNumber;
	this->samples = new float[sampleNumber];
	setGain(1.0f);
	setClip(1.0f);
}
///<summary>Return array of samples</summary>
float* SaturatorWavetable::getSamples()
{
	return samples;
}

///<summary>Returns number of samples</summary>
int SaturatorWavetable::getSampleNumber()
{
	return sampleNumber;
}

///<summary>sets gain of saturation and then recalculate samples</summary>
void SaturatorWavetable::setGain(float gain)
{
	this->gain = gain;
	reCalc();
}

///<summary>Sets level of hardclipping</summary>
void SaturatorWavetable::setClip(float clip)
{
	this->clip = clip;
	reCalc();
}

///<sumary>calculate samples based on gain and clip fields</summary>
void SaturatorWavetable::reCalc()
{
	for (int i = 0; i < sampleNumber; i++)
	{
		float x = (float)i / (sampleNumber - 1.0f);
		if (gain > 0.0f)
		{
			x = tanhf(x * gain) / tanhf(gain);
		}
		if (x > clip)
		{
			x = clip;
		}
		samples[i] = x;
	}
}
