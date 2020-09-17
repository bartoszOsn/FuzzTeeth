#pragma once

#include <JuceHeader.h>
#include "ParameterFloatControl.h"

class Panel  : public juce::Component
{
public:
    Panel();
    ~Panel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

	void addSection(juce::String name);
	void addSlider(juce::RangedAudioParameter* parameter, int sectionIndex);
	void addButton(juce::RangedAudioParameter* parameter, int sectionIndex);

private:
	juce::Array<juce::GroupComponent*> sections;
	juce::Array<juce::Component*> components;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Panel)
};
