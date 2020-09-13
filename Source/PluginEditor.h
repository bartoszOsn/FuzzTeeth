#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/GroupedControlsComponent.h"
#include "Components/GraphsComponent.h"

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

	///<summary>object for setting layout</summary>
	juce::FlexBox flexbox;

	/// <summary>This group has controls for setting teeth properties.</summary>
	GroupedControlsComponent* teethGroup;

	/// <summary>This group has controls for setting saturation properties.</summary>
	GroupedControlsComponent* saturationGroup;

	///<summary>This component handles graphs</summary>
	GraphsComponent* graphs;

	void setLayout(juce::Rectangle<int> bounds);
	void initControls();
	void initFlexbox();
	void initGroups();
	void initGraphs();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FuzzTeethAudioProcessorEditor)
};
