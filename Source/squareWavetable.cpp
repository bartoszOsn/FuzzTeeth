#include "squareWavetable.h"

///<summary>Creates SqareWavetable.</summary>
SquareWavetable::SquareWavetable()
{
	this->sampleNumber = 0;
}

///<summary>Creates SqareWavetable, then initialises it.</summary>
///<param name="sampleNumber">see <see cref="SquareWavetable::initialise" /></param>
SquareWavetable::SquareWavetable(int sampleNumber)
{
	initialise(sampleNumber);
}

///<summary>destructor</summary>
SquareWavetable::~SquareWavetable()
{
	if (sampleNumber > 0)
	{
		delete[] samples;
	}
}

///<summary>initialises this object.</summary>
///<param name="sampleNumber">
///How many samples this wavetable should be made of?
///This method uses twise as many, but there are sampleNumber of usable samples.
//</param>
void SquareWavetable::initialise(int sampleNumber)
{
	samples = new float[sampleNumber * 2];
	this->sampleNumber = sampleNumber;
	this->startIndex = sampleNumber / 2;
	this->endIndex = this->startIndex + sampleNumber - 1;


	this->fillArray();
}

///<summary>returns pointer to samples array.</summary>
float* SquareWavetable::getSamples()
{
	return samples + startIndex;
}

///<summary>
///Returns how many samples were this object initialised with.
///see <see cref="SquareWavetable::initialise" />
///<summary>
int SquareWavetable::getSampleNumber()
{
	return sampleNumber;
}

///<summary>Returns value of this wavetable.</summary>
///<param name="x">value from range [0, 1] inclusive.</param>
float SquareWavetable::get(float x)
{
	float result = 0;
	double* y = new double;
	//makes sure that x is in range [0, 1]
	x = modf(x, y);

	x = getIndex(x);
	float ratio = (int)modf(x, y);
	int i = (int)*y;

	//linear interpolation between two adjacent samples
	result = ratio * samples[i] + (1 - ratio) * samples[i + 1];
	delete y;

	return result;
}

///<summary>Sets frequency for low pass</summmary>
///<param name="freq">number in range [0, 1> where 1 is no low pass, and 0 is minimum allowed range.</param>
void SquareWavetable::setLowPassFrequency(float freq)
{
	freq *= freq;
	freq *= freq;
	freq *= freq;
	double frequency = this->sampleNumber * freq;
	lowPassFilter.reset();
	this->lowPassFilter.setCoefficients(juce::IIRCoefficients::makeLowPass(this->sampleNumber * 2, frequency));
	reCalc();
}

///<summary>Recalculate array of samples</summary>
void SquareWavetable::reCalc()
{
	fillArray();
	lowPassFilter.processSamples(samples, sampleNumber * 2);
}

///<summary>fills array with square wave.</summary>
void SquareWavetable::fillArray()
{
	for (int i = 0; i < this->sampleNumber * 2; i++)
	{
		if (i < this->startIndex)
		{
			this->samples[i] = -1;
		}
		else if (i < this->sampleNumber)
		{
			this->samples[i] = 1;
		}
		else if (i <= this->endIndex)
		{
			this->samples[i] = -1;
		}
		else
		{
			this->samples[i] = 1;
		}
	}
}

///<summary>
/// maps value x from range [0, 1] inclusive to range [startIndex, endIndex] inclusive.
///</summary>
///<param name="x">value in range [0, 1] inclusive.</param>
///<returns>value in range [startIndex, endIndex] inclusive.</returns>
float SquareWavetable::getIndex(float x)
{
	return x * (sampleNumber - 1) + startIndex;
}
