#include "GraphsComponent.h"

GraphsComponent::GraphsComponent()
{
	shaperGroup = new juce::GroupComponent("Shaper", "Wave Shaper");
	waveGroup = new juce::GroupComponent("wave", "Example Wave");
	addAndMakeVisible(shaperGroup);
	addAndMakeVisible(waveGroup);
	startTimerHz(30);
}

GraphsComponent::~GraphsComponent()
{
	delete shaperGroup;
	delete waveGroup;
}

///<summary>Paints component.</summary>
///<param name="g">juce Graphics object.</param>
void GraphsComponent::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	g.setColour(getLookAndFeel().findColour(juce::GroupComponent::ColourIds::outlineColourId));
	auto bounds = getLocalBounds().toFloat();
	auto shaperBounds = getShaperArea(bounds);
	auto waveBounds = getWaveArea(bounds);
	g.drawRoundedRectangle(shaperBounds, 5.0f, 2.0f);
	g.drawRoundedRectangle(waveBounds, 5.0f, 2.0f);

	auto samples = getWaveshaper()->getSamples();
	auto sampleNumber = getWaveshaper()->getSampleNumber();
	drawWaveShaper(g, shaperBounds, samples, sampleNumber);
	drawExampleWave(g, waveBounds, 4.0f * 3.14159265358979323846f, sampleNumber);
}

///<summary>Called by juce when this component is resized.</summary>
void GraphsComponent::resized()
{
	shaperGroup->setBoundsRelative(0, 0, 0.5, 1);
	waveGroup->setBoundsRelative(0.5, 0, 0.5, 1);

}
void GraphsComponent::timerCallback()
{
	repaint();
}
///<summary>
/// Returns area for drawing waveshaper.
///</summary>
///<param name="bounds">
/// Local bounds of this component. Is is passed as argument to avoid calculating it two times.
///</param>
juce::Rectangle<float> GraphsComponent::getShaperArea(juce::Rectangle<float> bounds)
{
	bounds.setWidth(bounds.getWidth() / 2.0f);
	bounds.removeFromTop(10.0f);
	bounds.reduce(drawingMargin, drawingMargin);

	//if width if larger than height
	if (bounds.getAspectRatio() > 1)
	{
		bounds.reduce((bounds.getWidth() - bounds.getHeight()) / 2.0f, 0.0f);
	}
	else
	{
		bounds.reduce(0.0f, (bounds.getHeight() - bounds.getWidth()) / 2.0f);
	}
	return bounds;
}

///<summary>
/// Returns area for drawing example wave.
///</summary>
///<param name="bounds">
/// Local bounds of this component. Is is passed as argument to avoid calculating it two times.
///</param>
juce::Rectangle<float> GraphsComponent::getWaveArea(juce::Rectangle<float> bounds)
{
	return getShaperArea(bounds).translated(bounds.getWidth() / 2.0f, 0.0f);
}

///<summary>plots function from samples in range[0, 1] inclusive.</summary>
///<param name="g">Graphics object</param>
///<param name="area">Area in which function should be drawn.</param>
///<param name="samples">Array of samples to be drawn.</param>
///<param name="sampleNumber">Length of array.</param>
void GraphsComponent::drawWaveShaper(juce::Graphics& g, juce::Rectangle<float> area, float* samples, int sampleNumber)
{
	area.reduce(drawingMargin, drawingMargin);
	drawCheckerboard(g, area);
	drawVolumeLevel(g, area);
	g.setColour(getLookAndFeel().findColour(juce::GroupComponent::ColourIds::outlineColourId));
	for (int i = 1; i < sampleNumber; i++)
	{
		float sample1 = samples[i - 1];
		float sample2 = samples[i];

		float x1 = (i - 1.0f) / (sampleNumber - 1.0f) * area.getWidth() + area.getX();
		float x2 = (float)i / (sampleNumber - 1.0f) * area.getWidth() + area.getX();

		float y1 = (1 - sample1) * area.getHeight() + area.getY();
		float y2 = (1 - sample2) * area.getHeight() + area.getY();

		g.drawLine(x1, y1, x2, y2, 2.0f);
	}
}

void GraphsComponent::drawExampleWave(juce::Graphics& g, juce::Rectangle<float> area, float frequency, int sampleNumber)
{
	area.reduce(drawingMargin, drawingMargin);
	drawCheckerboard(g, area);
	for (int i = 1; i < sampleNumber; i++)
	{
		float x1 = (i - 1.0f) / (sampleNumber - 1.0f);
		float x2 = i / (sampleNumber - 1.0f);

		float y1 = sinf(x1 * frequency);
		float y2 = sinf(x2 * frequency);

		y1 = waveShaper->processSample(y1);
		y2 = waveShaper->processSample(y2);

		//Transform points to area
		x1 = x1 * area.getWidth() + area.getX();
		x2 = x2 * area.getWidth() + area.getX();

		y1 = (-y1 + 1.0f) / 2.0f * area.getHeight() + area.getY();
		y2 = (-y2 + 1.0f) / 2.0f * area.getHeight() + area.getY();

		g.drawLine(x1, y1, x2, y2, 2.0f);
	}
}

void GraphsComponent::drawVolumeLevel(juce::Graphics& g, juce::Rectangle<float> area)
{
	area = area.getProportion(juce::Rectangle<float>(0, 0, audioLevel, 1));
	auto gr = juce::ColourGradient::horizontal(juce::Colours::transparentWhite, juce::Colour::fromRGBA(255, 255, 255, 128), area);

	g.setGradientFill(gr);
	g.fillRect(area);
}

///<summary>Draws Checkerboard in given area</summary>
void GraphsComponent::drawCheckerboard(juce::Graphics& g, juce::Rectangle<float> area)
{
	g.fillCheckerBoard(area, area.getWidth() / 10.0f, area.getHeight() / 10.0f, juce::Colour::fromRGBA(255, 255, 255, 30), juce::Colour::fromRGBA(0, 0, 0, 30));
}
