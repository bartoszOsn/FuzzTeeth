#pragma once

#include <JuceHeader.h>
#include "../waveShaper.h"

///<summary>
/// A JUCE component which displays respectively: waveshapers function and example sinus function with applied waveshaper to it.
///</summary>
class GraphsComponent  : public juce::Component, juce::Timer
{
public:
    GraphsComponent();
    ~GraphsComponent() override;

	void paint(juce::Graphics& g) override;
    void resized() override;

	///<summary>Getter for waveshaper that is drawn</summary>
	WaveShaper* getWaveshaper() { return waveShaper; }
	///<summary>Setter for waveshaper that is drawn</summary>
	///<param  name="waveShaper">waveshaper</param>
	void setWaveShaper(WaveShaper* waveShaper) { this->waveShaper = waveShaper; }

	///<summary>Gives this component info about current level of audio, in range [0, 1].</summary>
	///<param name="level">Current level of audio.</param>
	void setLevel(float level) { this->audioLevel = std::max(level, 0.9f * audioLevel); }


	void timerCallback() override;

private:
	///<summary>A waveshaper that is drawn</summary>
	WaveShaper* waveShaper;

	///<summary>Component which drawn outline around waveshaper graph</summary>
	juce::GroupComponent* shaperGroup;

	///<summary>Component which drawn outline around example sinus graph</summary>
	juce::GroupComponent* waveGroup;

	///<summary>Level of audio, that will be rendered.</summary>
	float audioLevel;

	///<summary>Margin between inner and outer (group) outline of the graph</summary>
	const float drawingMargin = 10.0f;

	juce::Rectangle<float> getShaperArea(juce::Rectangle<float> bounds);
	juce::Rectangle<float> getWaveArea(juce::Rectangle<float> bounds);
	void drawWaveShaper(juce::Graphics& g, juce::Rectangle<float> area, float* samples, int sampleNumber);
	void drawExampleWave(juce::Graphics& g, juce::Rectangle<float> area, float frequency, int sampleNumber);

	void drawVolumeLevel(juce::Graphics& g, juce::Rectangle<float> area);
	void drawCheckerboard(juce::Graphics& g, juce::Rectangle<float> area);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphsComponent)
};
