#include "waveShaper.h"

WaveShaper::WaveShaper() : squareWavetable()
{
}

WaveShaper::WaveShaper(int wavetableSampleNumber)
{
	initialise(wavetableSampleNumber);
}

WaveShaper::~WaveShaper()
{
	delete[] samples;
}

void WaveShaper::initialise(int wavetableSampleNumber)
{
	this->sampleNumber = wavetableSampleNumber;
	this->samples = new float[wavetableSampleNumber];
	this->teethSkew = 0.0f;
	squareWavetable.initialise(wavetableSampleNumber);
	saturatorWavetable.initialise(wavetableSampleNumber);

	reCalc();
}

float* WaveShaper::getSamples()
{
	return this->samples;
}

int WaveShaper::getSampleNumber()
{
	return this->sampleNumber;
}

float WaveShaper::processSample(float sample)
{
	if (sample < 0.0f)
	{
		return -processSample(-sample);
	}
	if (sample > 1.0f)
	{
		return processSample(1.0f);
	}

	float indexFloat = sample * (sampleNumber - 1);
	float* index = new float;
	float ratio = modf(indexFloat, index);

	int i = (int)*index;

	delete index;

	return samples[i] * ratio + samples[i + 1] * (1 - ratio);
}

void WaveShaper::setTeethSize(float size)
{
	this->teethSize = size;
	changed();
}

void WaveShaper::setTeethFrequency(float freq)
{
	this->teethFrequency = freq;
	changed();
}

void WaveShaper::setTeethLowPassFrequency(float freq)
{
	squareWavetable.setLowPassFrequency(freq);

	changed();
}

void WaveShaper::setTeethSkew(float skew)
{
	this->teethSkew = skew;

	changed();
}

void WaveShaper::setSaturationGain(float gain)
{
	saturatorWavetable.setGain(gain);
	changed();
}

void WaveShaper::setSaturationClip(float clip)
{
	saturatorWavetable.setClip(clip);
	changed();
}

///<summary>Sets event to be called when waveshaper function changes.</summary>
///<remarks>When you call this method, previously registered function is overriden</remarks>
///<param name="e">Function to be called when wavetable changes.</param>
void WaveShaper::setChangeEvent(std::function<void()> e)
{
	onChanged = e;
}

void WaveShaper::changed()
{
	reCalc();
	if (onChanged != nullptr)
	{
		onChanged();
	}
}

void WaveShaper::reCalc()
{
	float* saturatorSamples = saturatorWavetable.getSamples();
	for (int i = 0; i < sampleNumber; i++)
	{
		float x = (float)i / (sampleNumber - 1.0f);
		samples[i] = saturatorSamples[i];
		samples[i] += squareWavetable.get(x * teethFrequency) * teethSize * getSkew(x);
	}

	normaliseSamples();
}

///<summary>Normalises samples, so that the smallest one is equal to 0, and biggest is 1.
void WaveShaper::normaliseSamples()
{
	float min = samples[0], max = samples[sampleNumber - 1];
	for (int i = 0; i < sampleNumber; i++)
	{
		if (samples[i] < min)
		{
			min = samples[i];
		}
		else if (samples[i] > max)
		{
			max = samples[i];
		}
	}
	float scale = max - min;
 	for (int i = 0; i < sampleNumber; i++)
	{
		samples[i] -= min;
		samples[i] /= scale;
	}
}
///<summary>Returns value of skew function</summary>
///<remarks>skew function is: <c>(x - 1) * teethSkew + 1<c></remarks>
///<param name="x">value between 0 and 1</param>
float WaveShaper::getSkew(float x)
{
	return (x - 1.0f) * teethSkew + 1.0f;
}
