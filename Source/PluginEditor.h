#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/GraphsComponent.h"
#include "Components/Panel.h"

/// <summary>
/// Class of the window of the plugin.
/// </summary>
class FuzzTeethAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FuzzTeethAudioProcessorEditor (FuzzTeethAudioProcessor&);
    ~FuzzTeethAudioProcessorEditor() override;

    void resized() override;

	void setLevel(float level);

private:
	///<summary>Processor which distorts audio</summary>
    FuzzTeethAudioProcessor& audioProcessor;

	///<summary>This component handles graphs</summary>
	GraphsComponent* graphs;

	///<summary>provides components to modify audio parameters values.</summary>
	Panel* panel;

	void setLayout(juce::Rectangle<int> bounds);
	void initControls();
	void initGraphs();
	void initPanel();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FuzzTeethAudioProcessorEditor)
};
